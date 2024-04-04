#!/usr/bin/env python
import os
import sys

env = SConscript("extern/godot-cpp/SConstruct")

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["src/"])
sources = Glob("src/*.cpp")

#libgdexample.linux.template_debug.x86_64.so
#lib/linux-x86_64/libControl++.so

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "demo/addons/Control++/lib/{}/libControl++framework/libgdexample.{}.{}".format(
            "MacOS", env["platform"], env["target"]
        ),
        source=sources,
    )
else:
    library = env.SharedLibrary(
        "demo/addons/Control++/lib/{}-{}/libControl++{}".format(env["platform"].title(),env["arch"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)
