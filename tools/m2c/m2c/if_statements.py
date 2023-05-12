from collections import defaultdict
from dataclasses import dataclass, field, replace
from typing import DefaultDict, Dict, List, Optional, Set, Tuple, Union

from .flow_graph import (
    BasicNode,
    ConditionalNode,
    FlowGraph,
    Node,
    ReturnNode,
    SwitchNode,
    TerminalNode,
)
from .options import Options, Target
from .translate import (
    BinaryOp,
    BlockInfo,
    CommaConditionExpr,
    Condition,
    Expression,
    Formatter,
    FunctionInfo,
    Literal,
    Statement as TrStatement,
    SwitchControl,
    early_unwrap_ints,
    format_expr,
    get_block_info,
    simplify_condition,
)
from .types import Type


@dataclass
class Context:
    flow_graph: FlowGraph
    fmt: Formatter
    options: Options
    is_void: bool = True
    switch_nodes: Dict[Node, int] = field(default_factory=dict)
    case_nodes: DefaultDict[Node, List[Tuple[int, str]]] = field(
        default_factory=lambda: defaultdict(list)
    )
    goto_nodes: Set[Node] = field(default_factory=set)
    emitted_nodes: Set[Node] = field(default_factory=set)
    has_warned: bool = False


@dataclass
class IfElseStatement:
    condition: Condition
    if_body: "Body"
    else_body: Optional["Body"] = None

    def should_write(self) -> bool:
        return True

    def format(self, fmt: Formatter) -> str:
        space = fmt.indent("")
        condition = simplify_condition(self.condition)
        cond_str = format_expr(condition, fmt)
        after_ifelse = f"\n{space}" if fmt.coding_style.newline_after_if else " "
        before_else = f"\n{space}" if fmt.coding_style.newline_before_else else " "
        with fmt.indented():
            if_str = "\n".join(
                [
                    f"{space}if ({cond_str}){after_ifelse}{{",
                    self.if_body.format(fmt),  # has its own indentation
                    f"{space}}}",
                ]
            )
        if self.else_body is not None and not self.else_body.is_empty():
            sub_if = self.else_body.get_lone_if_statement()
            if sub_if:
                sub_if_str = sub_if.format(fmt).lstrip()
                else_str = f"{before_else}else {sub_if_str}"
            else:
                with fmt.indented():
                    else_str = "\n".join(
                        [
                            f"{before_else}else{after_ifelse}{{",
                            self.else_body.format(fmt),
                            f"{space}}}",
                        ]
                    )
            if_str = if_str + else_str
        return if_str


def comments_for_switch(index: int) -> List[str]:
    if index == 0:
        return []
    return [f"switch {index}"]


@dataclass
class SwitchStatement:
    jump: SwitchControl
    body: "Body"
    # If there are multiple switch statements in a single function, each is given a
    # unique index starting at 1. This is used in comments to make control flow clear.
    index: int

    def should_write(self) -> bool:
        return True

    def format(self, fmt: Formatter) -> str:
        lines = []
        comments = []
        body_is_empty = self.body.is_empty()
        comments.extend(comments_for_switch(self.index))
        if self.jump.is_irregular:
            comments.append("irregular")
        elif not self.jump.jump_table:
            comments.append("unable to parse jump table")
        elif body_is_empty:
            comments.append(f"jump table: {self.jump.jump_table.symbol_name}")
        head = f"switch ({format_expr(self.jump.control_expr, fmt)})"
        if body_is_empty:
            lines.append(fmt.with_comments(f"{head};", comments))
        else:
            if fmt.coding_style.newline_after_if:
                lines.append(fmt.with_comments(f"{head}", comments))
                lines.append(fmt.indent("{"))
            else:
                lines.append(fmt.with_comments(f"{head} {{", comments))
            with fmt.indented(fmt.coding_style.switch_indent_level):
                lines.append(self.body.format(fmt))
            lines.append(fmt.indent("}"))
        return "\n".join(lines)


@dataclass
class SimpleStatement:
    contents: Optional[Union[str, TrStatement]]
    comments: List[str] = field(default_factory=list)
    is_jump: bool = False
    indent: int = 0

    def should_write(self) -> bool:
        return self.contents is not None or bool(self.comments)

    def format(self, fmt: Formatter) -> str:
        if self.contents is None:
            content = ""
        elif isinstance(self.contents, str):
            content = self.contents
        else:
            content = self.contents.format(fmt)

        return fmt.with_comments(content, self.comments, indent=self.indent)

    def clear(self) -> None:
        self.contents = None
        self.comments = []


@dataclass
class LabelStatement:
    context: Context
    node: Node

    def should_write(self) -> bool:
        return self.node in self.context.goto_nodes or bool(
            self.context.case_nodes.get(self.node)
        )

    def format(self, fmt: Formatter) -> str:
        lines = []
        if self.node in self.context.case_nodes:
            for (switch, case_label) in self.context.case_nodes[self.node]:
                comments = comments_for_switch(switch)
                lines.append(fmt.with_comments(f"{case_label}:", comments, indent=-1))
        if self.node in self.context.goto_nodes:
            lines.append(f"{label_for_node(self.context, self.node)}:")
        return "\n".join(lines)


@dataclass
class DoWhileLoop:
    body: "Body"
    condition: Condition

    def should_write(self) -> bool:
        return True

    def format(self, fmt: Formatter) -> str:
        space = fmt.indent("")
        after_do = f"\n{space}" if fmt.coding_style.newline_after_if else " "
        cond = format_expr(simplify_condition(self.condition), fmt)
        with fmt.indented():
            return "\n".join(
                [
                    f"{space}do{after_do}{{",
                    self.body.format(fmt),
                    f"{space}}} while ({cond});",
                ]
            )


Statement = Union[
    SimpleStatement,
    IfElseStatement,
    LabelStatement,
    SwitchStatement,
    DoWhileLoop,
]


@dataclass
class Body:
    print_node_comment: bool
    statements: List[Statement] = field(default_factory=list)

    def extend(self, other: "Body") -> None:
        """Add the contents of `other` into ourselves"""
        self.print_node_comment |= other.print_node_comment
        self.statements.extend(other.statements)

    def add_node(self, node: Node, comment_empty: bool) -> None:
        block_info = get_block_info(node)
        statements = block_info.statements_to_write()

        # Add node header comment
        if self.print_node_comment and (statements or comment_empty):
            self.add_comment(f"Node {node.name()}")
        # Add node contents
        for item in statements:
            self.statements.append(SimpleStatement(item))

    def add_statement(self, statement: Statement) -> None:
        self.statements.append(statement)

    def add_comment(self, contents: str) -> None:
        self.add_statement(SimpleStatement(None, comments=[contents]))

    def add_if_else(self, if_else: IfElseStatement) -> None:
        if if_else.else_body is None or if_else.if_body.ends_in_jump():
            # We now know that we have an IfElseStatement like `if (A) { B; goto C; } else { D; }`
            # where `D` may be empty. We can rewrite this into `if (A) { B; goto C; } D;`
            # which reduces indentation to make the output more readable.

            # Append the final outermost `if_else`, without an `else_body` and rewritten to try
            # to avoid CommaConditionExprs.
            self.statements.append(rewrite_if_ands(if_else.condition, if_else.if_body))

            # Move the original `else_body` out of the block (if set)
            if if_else.else_body is not None:
                self.extend(if_else.else_body)
        else:
            # Simple case; perform no further rewrites
            self.statements.append(if_else)

    def add_do_while_loop(self, do_while_loop: DoWhileLoop) -> None:
        self.statements.append(do_while_loop)

    def add_switch(self, switch: SwitchStatement) -> None:
        self.add_statement(switch)

    def is_empty(self) -> bool:
        return not any(statement.should_write() for statement in self.statements)

    def ends_in_jump(self) -> bool:
        """
        Returns True if the body ends in an unconditional jump (`goto` or `return`),
        which may allow for some syntax transformations.
        For example, this is True for bodies ending in a ReturnNode, because
        `return ...;` statements are marked with is_jump.
        This function is conservative: it only returns True if we're
        *sure* if the control flow won't continue past the Body boundary.
        """
        for statement in self.statements[::-1]:
            if not statement.should_write():
                continue
            return isinstance(statement, SimpleStatement) and statement.is_jump
        return False

    def get_lone_if_statement(self) -> Optional[IfElseStatement]:
        """If the body consists solely of one IfElseStatement, return it, else None."""
        ret: Optional[IfElseStatement] = None
        for statement in self.statements:
            if statement.should_write():
                if not isinstance(statement, IfElseStatement) or ret:
                    return None
                ret = statement
        return ret

    def elide_empty_returns(self) -> None:
        """Remove `return;` statements from the end of the body.
        If the final statement is an if-else block, recurse into it."""
        for statement in self.statements[::-1]:
            if (
                isinstance(statement, SimpleStatement)
                and statement.contents == "return;"
            ):
                statement.clear()
            if not statement.should_write():
                continue
            if isinstance(statement, IfElseStatement):
                statement.if_body.elide_empty_returns()
                if statement.else_body is not None:
                    statement.else_body.elide_empty_returns()
            # We could also do this to SwitchStatements, but the generally
            # preferred style is to keep the final return/break
            break

    def format(self, fmt: Formatter) -> str:
        return "\n".join(
            statement.format(fmt)
            for statement in self.statements
            if statement.should_write()
        )


def rewrite_if_ands(condition: Condition, if_body: "Body") -> IfElseStatement:
    """
    Iterate through the left-heavy `&&`-joined subconditions in `condition`, checking
    or CommaConditionExprs. When encountered, convert the original if statement into
    a series of nested if's.

    This can transform input like:      if (cond1 && cond2 && cond3) { if_body }
    into nested ifs like:               if (cond1) { if (cond2) { if (cond3) { if_body } } }
    ...when `cond2` and `cond3` are CommaConditionExprs, which avoids the need for the comma operator.

    Warning: This rewrite is only valid if there is no else block in the original if
    statement, or if `if_body` ends in a jump.
    """
    outer_cond: Condition = condition
    inner_conds: List[Condition] = []
    while (
        isinstance(outer_cond, BinaryOp)
        and isinstance(outer_cond.left, Condition)
        and outer_cond.op == "&&"
        and isinstance(outer_cond.right, Condition)
    ):
        # Move the iterator forward
        cond = outer_cond.right
        outer_cond = outer_cond.left

        if not isinstance(cond, CommaConditionExpr):
            inner_conds.append(cond)
        else:
            # Rewrite the CommaConditionExpr into a nested IfElseStatement.
            # Start by joining all of the iterated `inner_conds` together, following
            # the same left-heavy pattern used in try_make_if_condition.
            inner_cond = cond.condition
            while inner_conds:
                inner_cond = join_conditions(inner_cond, "&&", inner_conds.pop())

            # Split the `if` into two nested `if`s, to move the CommaConditionExpr and
            # all of the `inner_conds` into an inner if statement. After moving them,
            # we can drop them from the outer if statement (`condition`).
            new_body = Body(print_node_comment=if_body.print_node_comment)
            for stmt in cond.statements:
                new_body.add_statement(SimpleStatement(stmt))
            new_body.add_if_else(
                IfElseStatement(
                    condition=inner_cond,
                    if_body=if_body,
                    else_body=None,
                )
            )
            if_body = new_body
            condition = outer_cond

    return IfElseStatement(condition=condition, if_body=if_body, else_body=None)


def label_for_node(context: Context, node: Node) -> str:
    if node.loop:
        return f"loop_{node.block.index}"
    else:
        return f"block_{node.block.index}"


def emit_node(context: Context, node: Node, body: Body) -> bool:
    """
    Try to emit a node for the first time, together with a label for it.
    The label is only printed if something jumps to it, e.g. a loop.

    For return nodes, it's preferred to emit multiple copies, rather than
    goto'ing a single return statement.

    For other nodes that were already emitted, instead emit a goto.
    Since nodes represent positions in assembly, and we use phi's for preserved
    variable contents, this will end up semantically equivalent. This can happen
    sometimes when early returns/continues/|| are not detected correctly, and
    this hints at that situation better than if we just blindly duplicate the block
    """
    if node in context.emitted_nodes:
        # TODO: Treating ReturnNode as a special case and emitting it repeatedly
        # hides the fact that we failed to fold the control flow. Maybe remove?
        if not isinstance(node, ReturnNode):
            emit_goto(context, node, body)
            return False
        else:
            body.add_comment(
                f"Duplicate return node #{node.name()}. Try simplifying control flow for better match"
            )
    else:
        body.add_statement(LabelStatement(context, node))
        context.emitted_nodes.add(node)

    body.add_node(node, comment_empty=True)
    if isinstance(node, ReturnNode):
        emit_return(context, node, body)
    return True


def emit_goto(context: Context, target: Node, body: Body) -> None:
    assert not isinstance(target, TerminalNode), "cannot goto a TerminalNode"
    label = label_for_node(context, target)
    context.goto_nodes.add(target)
    body.add_statement(SimpleStatement(f"goto {label};", is_jump=True))


def add_labels_for_switch(
    context: Context,
    node: Node,
    case_type: Type,
    cases: List[Tuple[int, Node]],
    default_node: Optional[Node],
) -> int:
    assert cases, "jtbl list must not be empty"
    switch_index = context.switch_nodes[node]

    # Force hex for case labels if the highest label is above 50, and there are no negative labels
    indexes = sorted([i for i, _ in cases])
    use_hex = context.fmt.coding_style.hex_case or (
        min(indexes) >= 0 and max(indexes) > 50
    )

    # Keep track of which labels we skipped because they weren't required
    skipped_labels: List[Tuple[Node, Tuple[int, str]]] = []
    emitted_label_count = 0

    # Mark which labels we need to emit
    for index, target in cases:
        enum_name = case_type.get_enum_name(index)
        if enum_name:
            case_label = f"case {enum_name}"
        elif use_hex:
            if index < 0:
                case_label = f"case -0x{-index:X}"
            else:
                case_label = f"case 0x{index:X}"
        else:
            case_label = f"case {index}"

        # Do not emit extra `case N:` labels for the `default:` block, skip the
        # switch block entirely, or are just jumps to these kinds of nodes.
        if is_empty_goto(target, default_node) or is_empty_goto(
            target, node.immediate_postdominator
        ):
            skipped_labels.append((target, (switch_index, case_label)))
        else:
            context.case_nodes[target].append((switch_index, case_label))
            emitted_label_count += 1

    if default_node is not None:
        # `None` is a sentinel value to mark the `default:` block
        context.case_nodes[default_node].append((switch_index, "default"))
        emitted_label_count += 1

    # If a switch statement only has a few labels, the compiler will prefer to emit
    # a series of branches instead of using a jump table. It's sometimes possible to
    # force a jump table by including extra labels, even if they're redundant.
    # The exact threshold depends on the compiler & exact structure.
    # These labels may look redundant or be outside of the `switch (...) { ... }` block.
    if emitted_label_count < 5:
        for target, label in skipped_labels:
            context.case_nodes[target].append(label)

    return switch_index


def switch_guard_expr(node: Node) -> Optional[Expression]:
    """
    Check if `node` is a ConditionalNode for checking the bounds of a SwitchNode's
    control expression. If it is, return the control expression, otherwise return None.
    ConditionalNodes matching this pattern can usually be combined with the successor
    SwitchNode in the output.
    """
    if not isinstance(node, ConditionalNode):
        return None
    cond = get_block_info(node).branch_condition
    assert cond is not None

    switch_node = node.fallthrough_edge
    if not isinstance(switch_node, SwitchNode):
        return None
    switch_block_info = get_block_info(switch_node)
    assert switch_block_info.switch_control is not None

    # The SwitchNode must have no statements, and the conditional
    # from the ConditionalNode must properly check the jump table bounds.
    if (
        switch_node.parents == [node]
        and not switch_block_info.statements_to_write()
        and switch_block_info.switch_control.matches_guard_condition(cond)
    ):
        return switch_block_info.switch_control.control_expr
    return None


def is_empty_goto(node: Node, end: Optional[Node]) -> bool:
    """Return True if `node` represents a jump to `end` without any other statements"""
    if end is None:
        return False
    seen_nodes = {node}
    while True:
        if node == end:
            return True
        block_info = get_block_info(node)
        if block_info.statements_to_write():
            return False
        if (
            isinstance(node, ReturnNode)
            and isinstance(end, TerminalNode)
            and block_info.return_value is None
        ):
            # An empty return counts as a jump to the TerminalNode
            return True
        elif isinstance(node, BasicNode):
            node = node.successor
            if node in seen_nodes:
                return False
            seen_nodes.add(node)
        else:
            return False
    return False


def gather_any_comma_conditions(block_info: BlockInfo) -> Condition:
    branch_condition = block_info.branch_condition
    assert branch_condition is not None
    comma_statements = block_info.statements_to_write()
    if comma_statements:
        assert not isinstance(branch_condition, CommaConditionExpr)
        return CommaConditionExpr(comma_statements, branch_condition)
    else:
        return branch_condition


@dataclass(frozen=True)
class Bounds:
    """
    Utility class for tracking possible switch control values across multiple
    conditional branches.
    """

    lower: int = -(2**31)  # `INT32_MAX`
    upper: int = (2**32) - 1  # `UINT32_MAX`
    holes: Set[int] = field(default_factory=set)

    def __post_init__(self) -> None:
        assert self.lower <= self.upper

    def without(self, hole: int) -> "Bounds":
        return replace(self, holes=self.holes | {hole})

    def at_most(self, val: int) -> "Bounds":
        if self.lower <= val <= self.upper:
            return replace(self, upper=val)
        elif val > self.upper:
            return self
        else:
            return Bounds.empty()

    def at_least(self, val: int) -> "Bounds":
        if self.lower <= val <= self.upper:
            return replace(self, lower=val)
        elif val < self.lower:
            return self
        else:
            return Bounds.empty()

    def values(self, *, max_count: int) -> Optional[List[int]]:
        values: List[int] = []
        for i in range(self.lower, self.upper + 1):
            if i not in self.holes:
                values.append(i)
                if len(values) > max_count:
                    return None
        return values

    @staticmethod
    def empty() -> "Bounds":
        return Bounds(lower=0, upper=0, holes={0})


def try_make_if_condition(
    chained_cond_nodes: List[ConditionalNode], end: Node
) -> Optional[Tuple[Condition, Node, Optional[Node]]]:
    """
    Try to express the nodes in `chained_cond_nodes` as a single `Condition` `cond`
    to make an if-else statement. `end` is the immediate postdominator of the first
    node in `chained_cond_nodes`, and is the node following the if-else statement.

    Returns a tuple of `(cond, if_node, else_node)` representing:
    ```
        if (cond) {
            goto if_node;
        } else {
            goto else_node;
        }
    ```
    If `else_node` is `None`, then the else block is empty and can be omitted.

    This function returns `None` if the topology of `chained_cond_nodes` cannot
    be represented by a single `Condition`.
    """
    start_node = chained_cond_nodes[0]
    if_node = chained_cond_nodes[-1].fallthrough_edge
    else_node: Optional[Node] = chained_cond_nodes[-1].conditional_edge
    assert else_node is not None

    # Check that all edges point "forward" to other nodes in the if statement
    # and translate this DAG of nodes into a dict we can easily modify
    allowed_nodes = set(chained_cond_nodes) | {if_node, else_node}
    node_cond_edges: Dict[ConditionalNode, Tuple[Condition, Node, Node]] = {}
    for node in chained_cond_nodes:
        if (
            node.conditional_edge not in allowed_nodes
            or node.fallthrough_edge not in allowed_nodes
        ):
            # Not a valid set of chained_cond_nodes
            return None
        allowed_nodes.remove(node)

        block_info = get_block_info(node)
        if node is start_node:
            # The first condition in an if-statement will have unrelated
            # statements in its to_write list, which our caller will already
            # have emitted. Avoid emitting them twice.
            cond = block_info.branch_condition
            assert isinstance(cond, Condition)
        else:
            # Otherwise, these statements will be added to the condition
            cond = gather_any_comma_conditions(block_info)

        node_cond_edges[node] = (cond, node.conditional_edge, node.fallthrough_edge)

    # Iteratively (try to) reduce the nodes into a single condition
    #
    # This is done through a process similar to "Rule T2" used in interval analysis
    # of control flow graphs, see ref. slides 17-21 of:
    # http://misailo.web.engr.illinois.edu/courses/526-sp17/lec1.pdf
    #
    # We have already ensured that all edges point forward (no loops), and there
    # are no incoming edges to internal nodes from outside the chain.
    #
    # Pick the first pair of nodes which form one of the 4 possible reducible
    # subgraphs, and then "collapse" them together by combining their conditions
    # and adjusting their edges. This process is repeated until no more changes
    # are possible, and is a success if there is exactly 1 condition left.
    while True:
        # Calculate the parents for each node in our subgraph
        node_parents: Dict[ConditionalNode, List[ConditionalNode]] = {
            node: [] for node in node_cond_edges
        }
        for node in node_cond_edges:
            for child in node_cond_edges[node][1:]:
                if child not in (if_node, else_node):
                    assert isinstance(child, ConditionalNode)
                    node_parents[child].append(node)

        # Find the first pair of nodes which form a reducible pair: one will always
        # be the *only* parent of the other.
        # Note: we do not include `if_node` or `else_node` in this search
        for child, parents in node_parents.items():
            if len(parents) != 1:
                continue
            parent = parents[0]
            child_cond, child_if, child_else = node_cond_edges[child]
            parent_cond, parent_if, parent_else = node_cond_edges[parent]

            # The 4 reducible subgraphs, see ref. slides 21-22 of:
            # https://www2.cs.arizona.edu/~collberg/Teaching/553/2011/Resources/ximing-slides.pdf
            # In summary:
            #   - The child must have exactly one incoming edge, from the parent
            #   - The parent's other edge must be in common with one of the child's edges
            #   - Replace the condition with a combined condition from the two nodes
            #   - Replace the parent's edges with the child's edges
            if parent_if is child_if and parent_else is child:
                parent_else = child_else
                cond = join_conditions(parent_cond, "||", child_cond)
            elif parent_if is child_else and parent_else is child:
                parent_else = child_if
                cond = join_conditions(parent_cond, "||", child_cond.negated())
            elif parent_if is child and parent_else is child_if:
                parent_if = child_else
                cond = join_conditions(parent_cond, "&&", child_cond.negated())
            elif parent_if is child and parent_else is child_else:
                parent_if = child_if
                cond = join_conditions(parent_cond, "&&", child_cond)
            else:
                continue

            # Modify the graph by replacing `parent`'s condition/edges, and deleting `child`
            node_cond_edges[parent] = (cond, parent_if, parent_else)
            node_cond_edges.pop(child)
            break
        else:
            # No pair was found, we're done!
            break

    # Were we able to collapse all conditions from chained_cond_nodes into one?
    if len(node_cond_edges) != 1 or start_node not in node_cond_edges:
        return None
    cond, left_node, right_node = node_cond_edges[start_node]

    # Negate the condition if the if/else nodes are backwards
    if (left_node, right_node) == (else_node, if_node):
        cond = cond.negated()
    else:
        assert (left_node, right_node) == (if_node, else_node)

    # Check if the if/else needs an else block
    if else_node is end:
        else_node = None
    elif if_node is end:
        # This is rare, but re-write if/else statements with an empty if body
        # from `if (cond) {} else { else_node; }` into `if (!cond) { else_node; }`
        cond = cond.negated()
        if_node = else_node
        else_node = None

    return (cond, if_node, else_node)


def try_build_irregular_switch(
    context: Context, start: Node, end: Node
) -> Optional[SwitchStatement]:
    """
    Look for irregular switch-like structures from nested ConditionalNodes & SwitchNodes.
    If one is found, return the corresponding SwitchStatement; otherwise, return None.

    Both IDO & GCC can convert switch statements into a tree of comparisons & jump tables.
    We try to identify the largest contiguous tree of ConditionalNodes & SwitchNodes that
    all compare the same variable (`var_expr`). SwitchNodes and `(x == N)` ConditionalNodes
    represent jumps to specific case labels, whereas comparisons like `(x < N)` are
    primarily used to manage the overall tree depth.
    """
    # The start node must either be an if
    if not isinstance(start, ConditionalNode):
        return None

    assert end in start.postdominators
    start_block_info = get_block_info(start)
    control_expr = switch_guard_expr(start)
    var_expr: Optional[Expression] = None

    # Try to extract the switch's control expression
    if control_expr is not None:
        # `if (x >= len(jump_table))`: var_expr is `x`
        var_expr = control_expr
    elif start_block_info.branch_condition is not None:
        start_cond = simplify_condition(start_block_info.branch_condition)
        if (
            start_cond is not None
            and isinstance(start_cond, BinaryOp)
            and isinstance(start_cond.right, Literal)
        ):
            # `if (x == N)`: var_expr is `x`
            # The `start_cond.op` is checked in the first iter of the while loop below
            var_expr = start_cond.left
    if var_expr is None:
        return None

    # Unwrap EvalOnceExpr's and Cast's; ops like `<=` always include an `(s32)` cast
    uw_var_expr = early_unwrap_ints(var_expr)
    # Nodes we need to visit & their bounds, initially just the `start` node over a full int32
    node_queue: List[Tuple[Node, Bounds]] = [(start, Bounds())]
    # Nodes we have already visited, to avoid infinite loops
    visited_nodes: Set[Node] = set()
    # Nodes that have no statements, and should be marked as emitted if we emit a SwitchStatement.
    # A ConditionalNode like `if (x == N)` isn't directly emitted; it's replaced by a `case N:` label
    # This also includes empty BasicNodes & ReturnNodes that jump directly to the end
    nodes_to_mark_emitted: Set[Node] = set()
    # Map of label -> node. Similar to SwitchNode.cases, but the labels may not be contiguous
    cases: Dict[int, Node] = {}
    # The `default:`-labeled node, if found
    default_node: Optional[Node] = None
    # Number of "irregular" comparison nodes used (SwitchNodes & ConditionalNodes that aren't guards)
    irregular_comparison_count = 0

    while node_queue:
        node, bounds = node_queue.pop()
        if node in visited_nodes or node == end or node == default_node:
            continue
        visited_nodes.add(node)
        block_info = get_block_info(node)

        if node != start and block_info.statements_to_write():
            # Unless the node is the start node, it cannot have any statements to write
            pass

        elif is_empty_goto(node, end):
            # Empty returns/gotos are special cases: the compiler may have folded
            # this node together with one outside the original interval. So, this node
            # may fail the `start not in node.dominators` check below.
            # Otherwise, treat these like empty BasicNodes.
            nodes_to_mark_emitted.add(node)
            if isinstance(node, BasicNode):
                node_queue.append((node.successor, bounds))
            continue

        elif start not in node.dominators or end not in node.postdominators:
            # The node must be within the [start, end] interval
            pass

        elif isinstance(node, BasicNode):
            # This node has no statements, so it is just a goto
            nodes_to_mark_emitted.add(node)
            node_queue.append((node.successor, bounds))
            continue

        elif isinstance(node, ConditionalNode):
            # If this is a "switch guard" `if` statement, continue iterating on both branches
            control_expr = switch_guard_expr(node)
            if (
                control_expr is not None
                and early_unwrap_ints(control_expr) == uw_var_expr
            ):
                # We can get away without adjusting the bounds here, even though the switch guard
                # puts a hole in our bounds. If the switch guard covers the range `[n, m]` inclusive,
                # the fallthrough edge is a jump table for these values, and the jump table doesn't
                # need the bounds. On the conditional side, we would only need to accurately track the
                # bounds to find an `n-1` or `m+1` case; however, we can assume these don't exist,
                # because they could have been part of the jump table (instead of a separate conditional).
                node_queue.append((node.fallthrough_edge, bounds))
                node_queue.append((node.conditional_edge, bounds))
                nodes_to_mark_emitted.add(node)
                continue

            # Check if the branch_condition is a comparison between var_expr and a Literal
            assert block_info.branch_condition is not None
            cond = simplify_condition(block_info.branch_condition)
            if (
                isinstance(cond, BinaryOp)
                and isinstance(cond.right, Literal)
                and early_unwrap_ints(cond.left) == uw_var_expr
            ):
                # IDO typically uses `x == N` and `x < N` patterns in these if trees, but it
                # will use `x != N` when it needs to jump backwards to an already-emitted block.
                # GCC will more freely use either `x == N` or `x != N`.
                # Examples from PM: func_8026E558, pr_load_npc_extra_anims
                val = cond.right.value
                if cond.op == "==":
                    if val in cases:
                        return None
                    cases[val] = node.conditional_edge
                    node_queue.append((node.fallthrough_edge, bounds.without(val)))
                elif cond.op == "!=" and (
                    node.block.index > node.conditional_edge.block.index
                    or context.options.target.compiler != Target.CompilerEnum.IDO
                ):
                    if val in cases:
                        return None
                    cases[val] = node.fallthrough_edge
                    node_queue.append((node.conditional_edge, bounds.without(val)))
                elif cond.op == "<":
                    node_queue.append((node.fallthrough_edge, bounds.at_least(val)))
                    node_queue.append((node.conditional_edge, bounds.at_most(val - 1)))
                elif cond.op == ">=":
                    node_queue.append((node.fallthrough_edge, bounds.at_most(val - 1)))
                    node_queue.append((node.conditional_edge, bounds.at_least(val)))
                elif cond.op == "<=":
                    node_queue.append((node.fallthrough_edge, bounds.at_least(val + 1)))
                    node_queue.append((node.conditional_edge, bounds.at_most(val)))
                elif cond.op == ">":
                    node_queue.append((node.fallthrough_edge, bounds.at_most(val)))
                    node_queue.append((node.conditional_edge, bounds.at_least(val + 1)))
                else:
                    return None
                irregular_comparison_count += 1
                nodes_to_mark_emitted.add(node)
                continue

        elif isinstance(node, SwitchNode):
            # The switch must use the same control expression
            if block_info.switch_control is None:
                return None
            if early_unwrap_ints(block_info.switch_control.control_expr) != uw_var_expr:
                return None
            # Add the cases from the inner switch to our dict of cases
            for i, case in enumerate(
                node.cases, start=block_info.switch_control.offset
            ):
                if i in cases:
                    return None
                cases[i] = case
            nodes_to_mark_emitted.add(node)
            irregular_comparison_count += 1
            continue

        values = bounds.values(max_count=1)
        if values and context.options.target.compiler != Target.CompilerEnum.IDO:
            # The bounds only have a few possible values, so add this node to the set of cases
            # IDO won't make implicit cases like this, however.
            for value in values:
                if value in cases:
                    return None
                cases[value] = node
            nodes_to_mark_emitted.add(node)
            continue

        # If we've gotten here, then the node is not a valid jump target for the switch,
        # unless it could be the `default:`-labeled node.
        if default_node is not None:
            return None
        if isinstance(node, ReturnNode) or (
            start in node.dominators and end in node.postdominators
        ):
            default_node = node

    # Need at least two irregular comparisons (to skip the regular ConditionalNode guard + SwitchNode pairs)
    # Need to combine at least 3 nodes into 2 distinct cases, otherwise it could be a plain if/else with ||
    if (
        irregular_comparison_count < 2
        or len(nodes_to_mark_emitted) < 3
        or len(set(cases.values())) < 2
    ):
        return None

    # If this new irregular switch uses all of the other switch nodes in the function,
    # then we no longer need to add labelling comments with the switch_index
    for n in nodes_to_mark_emitted:
        context.switch_nodes.pop(n, None)
    if context.switch_nodes:
        switch_index = max(context.switch_nodes.values()) + 1
    else:
        switch_index = 0
    context.switch_nodes[start] = switch_index

    add_labels_for_switch(
        context,
        start,
        var_expr.type,
        cases=list(cases.items()),
        default_node=default_node,
    )

    case_nodes = list(cases.values())
    if default_node is not None:
        case_nodes.append(default_node)
    switch = build_switch_statement(
        context,
        SwitchControl.irregular_from_expr(var_expr),
        case_nodes,
        switch_index,
        end,
    )
    context.emitted_nodes |= nodes_to_mark_emitted
    return switch


def build_conditional_subgraph(
    context: Context, start: ConditionalNode, end: Node
) -> IfElseStatement:
    """
    Output the subgraph between `start` and `end`, including the branch condition
    in the ConditionalNode `start`.

    This function detects "plain" if conditions, as well as conditions containing
    nested && and || terms.

    As generated by IDO and GCC, conditions with && and || terms are emitted in a
    very particular way. There will be a "chain" ConditionalNodes, where each node
    falls through to the next node in the chain.
    Each conditional edge from the nodes in this chain will go to one of:
        - The head of the if block body (`if_node`)
        - The head of the else block body (`else_node`)
        - A *later* conditional node in the chain (no loops)

    We know IDO likes to emit the assembly for basic blocks in the same order that
    they appear in the C source. So, we generally call the fallthrough of the final
    ConditionNode the `if_node` (unless it is empty). By construction, it will be
    an earlier node than the `else_node`.
    """
    # Find the longest fallthrough chain of ConditionalNodes.
    # This is the starting point for finding the complex &&/|| Condition
    # The conditional edges will be checked in later step
    curr_node: Node = start
    chained_cond_nodes: List[ConditionalNode] = []
    while True:
        assert isinstance(curr_node, ConditionalNode)
        chained_cond_nodes.append(curr_node)
        curr_node = curr_node.fallthrough_edge
        if not (
            # If &&/|| detection is disabled, then limit the condition to one node
            context.options.andor_detection
            # Only include ConditionalNodes
            and isinstance(curr_node, ConditionalNode)
            # Only include nodes that are postdominated by `end`
            and end in curr_node.postdominators
            # Exclude the `end` node
            and end is not curr_node
            # Exclude any loop nodes (except `start`)
            and not curr_node.loop
            # Exclude nodes with incoming edges that are not part of the condition
            and all(p in chained_cond_nodes for p in curr_node.parents)
            # Exclude guards for SwitchNodes (they may be elided)
            and not switch_guard_expr(curr_node)
        ):
            break

    # We want to take the largest chain of ConditionalNodes that can be converted to
    # a single condition with &&'s and ||'s. We start with the largest chain computed
    # above, and then trim it until it meets this criteria. The resulting chain will
    # always have at least one node.
    while True:
        assert chained_cond_nodes
        cond_result = try_make_if_condition(chained_cond_nodes, end)
        if cond_result:
            break
        # Shorten the chain by removing the last node, then try again.
        chained_cond_nodes.pop()
    cond, if_node, else_node = cond_result

    # Mark nodes that may have comma expressions in `cond` as emitted
    context.emitted_nodes.update(chained_cond_nodes[1:])

    # Build the if & else bodies
    else_body: Optional[Body] = None
    if else_node:
        else_body = build_flowgraph_between(context, else_node, end)
    if_body = build_flowgraph_between(context, if_node, end)

    return IfElseStatement(cond, if_body, else_body)


def join_conditions(left: Condition, op: str, right: Condition) -> Condition:
    assert op in ["&&", "||"]
    return BinaryOp(left, op, right, type=Type.bool())


def emit_return(context: Context, node: ReturnNode, body: Body) -> None:
    ret_info = get_block_info(node)

    ret = ret_info.return_value
    if ret is not None:
        ret_str = format_expr(ret, context.fmt)
        body.add_statement(SimpleStatement(f"return {ret_str};", is_jump=True))
        context.is_void = False
    else:
        body.add_statement(SimpleStatement("return;", is_jump=True))


def build_switch_statement(
    context: Context,
    jump: SwitchControl,
    case_nodes: List[Node],
    switch_index: int,
    end: Node,
) -> SwitchStatement:
    """
    This is a helper function for building both regular & irregular switch bodies.
    It returns a SwitchStatement with the body populated with the given set of nodes.
    The nodes must already be labeled with `add_labels_for_switch` before calling this.
    """
    switch_body = Body(print_node_comment=context.options.debug)

    # If there are any case labels to jump to the `end` node immediately after the
    # switch block, emit them as `case ...: break;` at the start of the switch block
    # instead. This avoids having "dangling" `case ...:` labels outside of the block.
    remaining_labels = []
    for index, case_label in context.case_nodes[end]:
        if index == switch_index:
            comments = comments_for_switch(switch_index)
            switch_body.add_statement(
                SimpleStatement(f"{case_label}:", comments=comments, indent=-1)
            )
        else:
            remaining_labels.append((index, case_label))
    if len(remaining_labels) != len(context.case_nodes[end]):
        switch_body.add_statement(SimpleStatement("break;", is_jump=True))
        context.case_nodes[end] = remaining_labels

    # Order case blocks by their position in the asm, not by their order in the jump table
    # (but use the order in the jump table to break ties)
    sorted_cases = sorted(
        set(case_nodes), key=lambda node: (node.block.index, case_nodes.index(node))
    )
    next_sorted_cases: List[Optional[Node]] = []
    next_sorted_cases.extend(sorted_cases[1:])
    next_sorted_cases.append(None)
    for case, next_case in zip(sorted_cases, next_sorted_cases):
        if case in context.emitted_nodes or case is end:
            pass
        elif (
            next_case is not None
            and next_case not in context.emitted_nodes
            and next_case is not end
            and next_case in case.postdominators
        ):
            switch_body.extend(build_flowgraph_between(context, case, next_case))
            if not switch_body.ends_in_jump():
                switch_body.add_comment("fallthrough")
        else:
            switch_body.extend(build_flowgraph_between(context, case, end))
            if not switch_body.ends_in_jump():
                switch_body.add_statement(SimpleStatement("break;", is_jump=True))
    return SwitchStatement(jump, switch_body, switch_index)


def build_switch_between(
    context: Context,
    switch: SwitchNode,
    default: Optional[Node],
    end: Node,
) -> SwitchStatement:
    """
    Output the subgraph between `switch` and `end`, but not including `end`.
    The returned SwitchStatement starts with the jump to the switch's value.
    This is only used for single jump table switches; not irregular switches.
    """
    switch_cases = switch.cases[:]
    if default is end:
        default = None
    elif default is not None:
        switch_cases.append(default)

    jump = get_block_info(switch).switch_control
    assert jump is not None

    switch_index = add_labels_for_switch(
        context,
        switch,
        jump.control_expr.type,
        cases=list(enumerate(switch.cases, start=jump.offset)),
        default_node=default,
    )

    return build_switch_statement(context, jump, switch_cases, switch_index, end)


def detect_loop(context: Context, start: Node, end: Node) -> Optional[DoWhileLoop]:
    assert start.loop

    # Find the the condition for the do-while, if it exists
    condition: Optional[Condition] = None
    for node in start.loop.backedges:
        if (
            node in start.postdominators
            and isinstance(node, ConditionalNode)
            and node.fallthrough_edge == end
        ):
            block_info = get_block_info(node)
            assert block_info.branch_condition is not None
            condition = block_info.branch_condition
            new_end = node
            break
    if not condition:
        return None

    loop_body = build_flowgraph_between(
        context,
        start,
        new_end,
        skip_loop_detection=True,
    )
    emit_node(context, new_end, loop_body)

    return DoWhileLoop(loop_body, condition)


def build_flowgraph_between(
    context: Context, start: Node, end: Node, skip_loop_detection: bool = False
) -> Body:
    """
    Output a section of a flow graph that has already been translated to our
    symbolic AST. All nodes between start and end, including start but NOT end,
    will be printed out using if-else statements and block info.

    `skip_loop_detection` is used to prevent infinite recursion, since (in the
    case of loops) this function can be recursively called by itself (via
    `detect_loop`) with the same `start` argument.
    """
    curr_start: Node = start
    body = Body(print_node_comment=context.options.debug)

    # We will split this graph into subgraphs, where the entrance and exit nodes
    # of that subgraph are at the same indentation level. "curr_start" will
    # iterate through these nodes by taking the immediate postdominators,
    # which are commonly referred to as articulation nodes.
    while curr_start != end:
        assert not isinstance(curr_start, TerminalNode)

        if (
            not skip_loop_detection
            and curr_start.loop
            and curr_start not in context.emitted_nodes
        ):
            # Find the immediate postdominator to the whole loop,
            # i.e. the first node outside the loop body
            imm_pdom: Node = curr_start
            while imm_pdom in curr_start.loop.nodes:
                assert imm_pdom.immediate_postdominator is not None
                imm_pdom = imm_pdom.immediate_postdominator

            # Construct the do-while loop
            do_while_loop = detect_loop(context, curr_start, imm_pdom)
            if do_while_loop:
                body.add_do_while_loop(do_while_loop)

                # Move on.
                curr_start = imm_pdom
                continue

        # If the current node has already been emitted and is equivalent to
        # goto'ing the end node, we don't need to emit anything else. This
        # avoids jumping to an empty node (or another jump) at the end of a
        # block, like `{ block_N: break; ... goto block_N; }`
        if curr_start in context.emitted_nodes and is_empty_goto(curr_start, end):
            break

        # Write the current node, or a goto, to the body
        if not emit_node(context, curr_start, body):
            # If the node was already witten, emit_node will use a goto
            # and return False. After the jump, there control flow will
            # continue from there (hopefully hitting `end`!)
            break

        if curr_start.emit_goto:
            # If we have decided to emit a goto here, then we should just fall
            # through to the next node by index, after writing a goto.
            emit_goto(context, curr_start, body)

            # Advance to the next node in block order. This may skip over
            # unreachable blocks -- hopefully none too important.
            index = context.flow_graph.nodes.index(curr_start)
            fallthrough = context.flow_graph.nodes[index + 1]
            if isinstance(curr_start, ConditionalNode):
                assert fallthrough == curr_start.fallthrough_edge
            curr_start = fallthrough
            continue

        # The interval to process is [curr_start, curr_start.immediate_postdominator)
        curr_end = curr_start.immediate_postdominator
        assert curr_end is not None

        # For nodes with branches, curr_end is not a direct successor of curr_start

        irregular_switch: Optional[SwitchStatement] = None
        if context.options.switch_detection:
            irregular_switch = try_build_irregular_switch(context, curr_start, curr_end)

        if irregular_switch is not None:
            body.add_switch(irregular_switch)
        elif switch_guard_expr(curr_start) is not None:
            # curr_start is a ConditionalNode that falls through to a SwitchNode,
            # where the condition checks that the switch's control expression is
            # within the jump table bounds.
            # We can combine the if+switch into just a single switch block.
            assert isinstance(
                curr_start, ConditionalNode
            ), "checked by switch_guard_expr"
            switch_node = curr_start.fallthrough_edge
            assert isinstance(switch_node, SwitchNode), "checked by switch_guard_expr"
            default_node = curr_start.conditional_edge
            # switch_guard_expr checked that switch_node has no statements to write,
            # so it is OK to mark it as emitted
            context.emitted_nodes.add(switch_node)
            if curr_end is switch_node:
                curr_end = switch_node.immediate_postdominator
                assert curr_end in curr_start.postdominators
            body.add_switch(
                build_switch_between(context, switch_node, default_node, curr_end)
            )
        elif isinstance(curr_start, SwitchNode):
            body.add_switch(build_switch_between(context, curr_start, None, curr_end))
        elif isinstance(curr_start, ConditionalNode):
            body.add_if_else(build_conditional_subgraph(context, curr_start, curr_end))
        elif (
            isinstance(curr_start, BasicNode) and curr_start.fake_successor == curr_end
        ):
            curr_end = curr_start.successor
        else:
            # No branch, but double check that we didn't skip any nodes.
            # If the check fails, then the immediate_postdominator computation was wrong
            assert curr_start.children() == [curr_end], (
                f"While emitting flowgraph between {start.name()}:{end.name()}, "
                f"skipped nodes while stepping from {curr_start.name()} to {curr_end.name()}."
            )

        # Move on.
        curr_start = curr_end
    return body


def build_naive(context: Context, nodes: List[Node]) -> Body:
    """Naive procedure for generating output with only gotos for control flow.

    Used for --gotos-only, when the regular if_statements code fails."""

    body = Body(print_node_comment=context.options.debug)

    def emit_goto_or_early_return(node: Node, body: Body) -> None:
        if isinstance(node, ReturnNode) and not node.is_real():
            emit_node(context, node, body)
        else:
            emit_goto(context, node, body)

    def emit_successor(node: Node, cur_index: int) -> None:
        if (
            cur_index + 1 < len(nodes)
            and nodes[cur_index + 1] == node
            and not (isinstance(node, ReturnNode) and not node.is_real())
        ):
            # Fallthrough is fine
            return
        emit_goto_or_early_return(node, body)

    for i, node in enumerate(nodes):
        if isinstance(node, ReturnNode):
            # Do not emit duplicated (non-real) return nodes; they don't have
            # a well-defined position, so we emit them next to where they are
            # jumped to instead.
            if node.is_real():
                emit_node(context, node, body)
        elif isinstance(node, BasicNode):
            emit_node(context, node, body)
            emit_successor(node.successor, i)
        elif isinstance(node, SwitchNode):
            jump = get_block_info(node).switch_control
            assert jump is not None
            index = add_labels_for_switch(
                context,
                node,
                jump.control_expr.type,
                cases=list(enumerate(node.cases, start=jump.offset)),
                default_node=None,
            )
            emit_node(context, node, body)
            body.add_switch(
                SwitchStatement(
                    jump=jump,
                    body=Body(print_node_comment=False),
                    index=index,
                )
            )
        elif isinstance(node, ConditionalNode):
            emit_node(context, node, body)
            if_body = Body(print_node_comment=True)
            emit_goto_or_early_return(node.conditional_edge, if_body)
            block_info = get_block_info(node)
            assert block_info.branch_condition is not None
            body.add_if_else(
                IfElseStatement(
                    block_info.branch_condition,
                    if_body=if_body,
                    else_body=None,
                )
            )
            emit_successor(node.fallthrough_edge, i)
        else:
            assert isinstance(node, TerminalNode)

    return body


def build_body(context: Context, options: Options) -> Body:
    start_node: Node = context.flow_graph.entry_node()
    terminal_node: Node = context.flow_graph.terminal_node()
    is_reducible = context.flow_graph.is_reducible()

    if options.debug:
        print("Here's the whole function!\n")

    # Label switch nodes
    switch_nodes = [n for n in context.flow_graph.nodes if isinstance(n, SwitchNode)]
    if len(switch_nodes) == 1:
        # There is only one switch in this function (no need to label)
        context.switch_nodes[switch_nodes[0]] = 0
    else:
        for i, switch_node in enumerate(switch_nodes):
            context.switch_nodes[switch_node] = i + 1

    body: Body
    if options.ifs and is_reducible:
        body = build_flowgraph_between(context, start_node, terminal_node)
        body.elide_empty_returns()
    else:
        body = Body(print_node_comment=context.options.debug)
        if options.ifs and not is_reducible:
            body.add_comment(
                "Flowgraph is not reducible, falling back to gotos-only mode."
            )
        body.extend(build_naive(context, context.flow_graph.nodes))

    # Check no nodes were skipped: build_flowgraph_between should hit every node in
    # well-formed (reducible) graphs; and build_naive explicitly emits every node
    for node in context.flow_graph.nodes:
        if node in context.emitted_nodes or isinstance(node, TerminalNode):
            continue
        if isinstance(node, ReturnNode) and not node.is_real():
            continue
        body.add_comment(
            f"bug: did not emit code for node #{node.name()}; contents below:"
        )
        emit_node(context, node, body)

    return body


def get_function_text(function_info: FunctionInfo, options: Options) -> str:
    fmt = options.formatter()
    context = Context(flow_graph=function_info.flow_graph, options=options, fmt=fmt)
    body: Body = build_body(context, options)

    function_lines: List[str] = []

    if function_info.symbol.demangled_str is not None:
        function_lines.append(
            fmt.with_comments("", [function_info.symbol.demangled_str])
        )

    fn_name = function_info.stack_info.function.name
    arg_strs = []
    for i, arg in enumerate(function_info.stack_info.arguments):
        if i == 0 and function_info.stack_info.replace_first_arg is not None:
            original_name, original_type = function_info.stack_info.replace_first_arg
            arg_strs.append(original_type.to_decl(original_name, fmt))
        else:
            arg_strs.append(arg.type.to_decl(arg.format(fmt), fmt))
    if function_info.stack_info.is_variadic:
        arg_strs.append("...")
    arg_str = ", ".join(arg_strs) or "void"

    fn_header = f"{fn_name}({arg_str})"

    if context.is_void:
        fn_header = f"void {fn_header}"
    else:
        fn_header = function_info.return_type.to_decl(fn_header, fmt)
    whitespace = "\n" if fmt.coding_style.newline_after_function else " "
    function_lines.append(f"{fn_header}{whitespace}{{")

    any_decl = False

    with fmt.indented():
        # Format the body first, because this can result in additional type inferencce
        formatted_body = body.format(fmt)

        local_vars = function_info.stack_info.local_vars
        # GCC's stack is ordered low-to-high (e.g. `int sp10; int sp14;`)
        # IDO's and MWCC's stack is ordered high-to-low (e.g. `int sp14; int sp10;`)
        if options.target.compiler != Target.CompilerEnum.GCC:
            local_vars = local_vars[::-1]
        for local_var in local_vars:
            type_decl = local_var.toplevel_decl(fmt)
            if type_decl is not None:
                comments = []
                if local_var.value in function_info.stack_info.weak_stack_var_locations:
                    comments = ["compiler-managed"]
                function_lines.append(
                    SimpleStatement(f"{type_decl};", comments=comments).format(fmt)
                )
                any_decl = True

        temp_decls = []
        for var in function_info.stack_info.temp_vars:
            if var.is_emitted:
                type_decl = var.type.to_decl(var.format(fmt), fmt)
                temp_decls.append(f"{type_decl};")
                any_decl = True
        for decl in sorted(temp_decls):
            function_lines.append(SimpleStatement(decl).format(fmt))

        for phi_var in function_info.stack_info.naive_phi_vars:
            type_decl = phi_var.type.to_decl(phi_var.get_var_name(), fmt)
            function_lines.append(SimpleStatement(f"{type_decl};").format(fmt))
            any_decl = True

        # Create a variable to cast the original first argument to the assumed type
        if function_info.stack_info.replace_first_arg is not None:
            assert len(function_info.stack_info.arguments) >= 1
            replaced_arg = function_info.stack_info.arguments[0]
            original_name, original_type = function_info.stack_info.replace_first_arg

            lhs = replaced_arg.type.to_decl(replaced_arg.format(fmt), fmt)
            rhs = f"({replaced_arg.type.format(fmt)}) {original_name}"
            function_lines.append(SimpleStatement(f"{lhs} = {rhs};").format(fmt))

        if any_decl:
            function_lines.append("")

        function_lines.append(formatted_body)
        function_lines.append("}")
    full_function_text: str = "\n".join(function_lines)
    return full_function_text
