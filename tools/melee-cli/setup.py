#!/usr/bin/env python3
from setuptools import find_packages, setup

setup(
    name="melee-cli",
    version="0.0.1",
    description="An entry point for melee decomp command line tooling",
    packages=find_packages(),
    python_requires=">=3.10",
    scripts=["main.py"],
    entry_points={"console_scripts": ["melee = main:main"]},
    license="AGPLv3",
    classifiers=[
        "Intended Audience :: Developers",
        "Topic :: Software Development :: Build Tools",
        "License :: OSI Approved :: GNU Affero General Public License v3 or later (AGPLv3+)",
        "Programming Language :: Python :: 3.10",
    ],
)
