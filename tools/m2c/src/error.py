from dataclasses import dataclass
from typing import NoReturn


@dataclass
class DecompFailure(Exception):
    message: str

    def __str__(self) -> str:
        return self.message


def static_assert_unreachable(x: NoReturn) -> NoReturn:
    raise Exception(f"Unreachable: {repr(x)}")
