#!/usr/bin/env python3

import argparse
import subprocess
import os

def check_return_code(return_code:int,what:str,force_yes:bool):
    if return_code == 0:
        return
    if force_yes:
        print("Got return code = " + str(return_code) + " while " + what + ". Continuing.")
    s = input("Got return code = "+str(return_code)+" while "+what+" do you want to continue? [Y/n]: ")
    s = s.lower()
    if s != 'y':
        exit(return_code)

def inform_about_instaling_package(package_name:str):
    print(f"\nInstalling {package_name}\n")

APTS = [
    "x11-apps",
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

def set_up(verbose:bool = False,force_yes = False):
    distrobox_name = "debian-10-test"
    this_file_location = os.path.join(os.path.dirname(os.path.abspath(__file__)))
    os.chdir(this_file_location)
    y_param = ""
    if force_yes:
        y_param = "-y"

    return_code = subprocess.call(f"distrobox create -i debian:10 --name {distrobox_name}", shell=True)
    check_return_code(return_code, "creating distrobox", force_yes)
    inform_about_instaling_package("apt-file")
    return_code = subprocess.call(f"distrobox enter {distrobox_name} -- sudo apt install apt-file {y_param}", shell=True)
    check_return_code(return_code, "installing apt-file", force_yes)
    return_code = subprocess.call(f"distrobox enter {distrobox_name} -- sudo apt-file update", shell=True)
    check_return_code(return_code, "upgrading using apt-file", force_yes)
    for package in APTS:
        inform_about_instaling_package(package)
        return_code = subprocess.call(f"distrobox enter {distrobox_name} -- sudo apt install {package} {y_param}", shell=True)
        check_return_code(return_code, f"installing {package}", force_yes)
    print("\nUpgrading packages\n")
    return_code = subprocess.call(f"distrobox enter {distrobox_name} -- sudo sudo apt full-upgrade {y_param}", shell=True)
    check_return_code(return_code, "upgradeing using apt full-upgrade", force_yes)
    return_code = subprocess.call(f"distrobox enter {distrobox_name} -- python3 -m venv ../../venv-{distrobox_name}", shell=True)
    check_return_code(return_code, "creating python3 virtual enviroment", force_yes)
    inform_about_instaling_package("SCons")
    return_code = subprocess.call(f"distrobox enter {distrobox_name} -- ../../venv-{distrobox_name}/bin/pip install SCons==4.2.0", shell=True)
    check_return_code(return_code, "installing SCons in python3 virtual enviroment", force_yes)

def set_up_main(args):
    print("Starting Setup")
    set_up(args.verbose, args.yes)
    return

def compile_main(args):
    print("Starting Compilation")
    return

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--verbose",
        action="store_true",
        help="If passed, enables verbose printing.",
    )
    subparsers = parser.add_subparsers(help='subcommand help')

    # create the parser for the "setup" command
    parser_setup = subparsers.add_parser('setup', help='If passed, program will install dependencies and generate virtual enviroments.')
    parser_setup.add_argument("--yes", "-y", action="store_true", help="If passed, program will not ask user it to continue.")
    parser_setup.set_defaults(func=set_up_main)

    # create the parser for the "compile" command
    parser_compile = subparsers.add_parser('compile', help='Not useful yet.')
    parser_compile.add_argument("--lang", "-l", default="en", help="Language to use for section headings.")
    parser_compile.add_argument(
        "--color",
        action="store_true",
        help="If passed, force colored output even if stdout is not a TTY (useful for continuous integration).",
    )
    parser_compile.add_argument("--output", "-o", default="../", help="The directory to save output .zip files.")
    parser_compile.set_defaults(func=compile_main)
    
    args = parser.parse_args()
    try:
        args.func(args)
    except:
        print("Invalid usage, try to run this program wiht `--help` parameter for more information.")
    return

if __name__ == '__main__':
    main()
