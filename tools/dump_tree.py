#!/usr/bin/python3
import argparse
from pathlib import Path
from typing import cast

from bs4 import BeautifulSoup, Tag


def generate_nested_html_list(directory_path):
    root = Path(directory_path)

    # Create a new BeautifulSoup object
    soup = BeautifulSoup("<ul></ul>", "html.parser")
    ul = cast(Tag, soup.ul)

    # Iterate over the directory structure using a stack
    stack = [(root, ul)]

    while stack:
        current_dir, current_ul = stack.pop()

        # Iterate over the subdirectories and files in the current directory
        for item in sorted(current_dir.iterdir()):
            if item.is_dir():
                # Create a new <li> element for the subdirectory
                li = soup.new_tag("li")
                li.string = item.name

                # Create a new <ul> element for the subdirectory's contents
                sub_ul = soup.new_tag("ul")

                # Append the <li> and <ul> elements to the current <ul>
                current_ul.append(li)
                current_ul.append(sub_ul)

                # Push the subdirectory and its <ul> element to the stack
                stack.append((item, sub_ul))

            else:
                # Create a new <li> element for the file
                li = soup.new_tag("li")
                a = soup.new_tag("a")
                a.attrs["href"] = str(item.relative_to(root))
                a.attrs["target"] = "_blank"
                a.string = item.name

                # Append the <li> element to the current <ul>
                li.append(a)
                current_ul.append(li)

    return soup.prettify()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Generate nested HTML list from directory structure"
    )
    parser.add_argument("directory", type=Path, help="Path to the directory")
    parser.add_argument("output_file", type=Path, help="Path to the output HTML file")
    args = parser.parse_args()

    html_list = generate_nested_html_list(args.directory)
    args.output_file.write_text(html_list, encoding="utf-8")
