#!/usr/bin/env python3

import argparse
import subprocess
import os

def check_return_code(return_code:int,what:str):
    if return_code == 0:
        return
    s = input("Got return code = "+str(return_code)+" while "+what+" do you want to contiune? [Y/n]: ")
    s = s.lower()
    if s != 'y':
        exit(return_code)

APTS = [
    "libxkbcommon0",
    "libxinerama1",
    "libxrandr2",
    "libxi6",
    "libdbus-1-3",
    "libasound2",
    "bash-completion",
    "build-essential",
    "cmake",
    "python3",
    "python3-venv",
    "g++-mingw-w64-x86-64"
]

def set_up(verbose:bool = False):
    distrobox_name = "debian-10-test"
    return_code = subprocess.call(f"distrobox create -i debian:10 --name {distrobox_name}", shell=True)
    check_return_code(return_code, "creating distrobox")
    return_code = subprocess.call(f"distrobox enter {distrobox_name} -- python3", shell=True)
    check_return_code(return_code, "running python")

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--lang", "-l", default="en", help="Language to use for section headings.")
    parser.add_argument(
        "--color",
        action="store_true",
        help="If passed, force colored output even if stdout is not a TTY (useful for continuous integration).",
    )
    group = parser.add_mutually_exclusive_group()
    group.add_argument("--output", "-o", default="../", help="The directory to save output .zip files.")
    group.add_argument(
        "--set-up", "-su",
        action="store_true",
        help="If passed, program will install dependencies and generate virtual enviroments.",
    )
    parser.add_argument(
        "--verbose",
        action="store_true",
        help="If passed, enables verbose printing.",
    )
    args = parser.parse_args()

    if args.set_up:
        print("Starting Setup")
        set_up(args.verbose)
        return

    print("Starting Compilation")
    return

if __name__ == '__main__':
    main()
