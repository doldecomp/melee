from setuptools import setup, find_packages

setup(
    name="melee-cli",
    version="0.0.1",
    description="An entry point for melee decomp command line tooling",
    packages=find_packages(),
    python_requires='>=3.10',
    scripts=['main.py'],
    entry_points={ 'console_scripts': [ 'melee = main:main' ] },
)
