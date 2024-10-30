#!/usr/bin/env python
import os
import sys

env = SConscript("extern/godot-cpp/SConstruct")
#envDebug = Environment()
#envDebug.Append(CXXFLAGS = ['/DEBUG'])
#envDebug.Export("env")
#envDebug = SConscript("extern/godot-cpp/SConstruct")
#envDebug.Append(CXXFLAGS = ['/DEBUG'])

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["src/"])
#envDebug.Append(CPPPATH=["src/"])
sources = Glob("src/*.cpp")

#libgdexample.linux.template_debug.x86_64.so
#lib/linux-x86_64/libControl++.so

name = ""

if env["target"] == "template_debug":
    env.Append(CPPDEFINES=["DEBUG_ENABLED", "DEBUG_METHODS_ENABLED"])
    name = "-d"

if env["target"] in ["editor", "template_debug"]:
    try:
        doc_data = env.GodotCPPDocData("src/gen/doc_data.gen.cpp", source=Glob("doc_classes/*.xml"))
        sources.append(doc_data)
    except AttributeError:
        print("Not including class reference as we're targeting a pre-4.3 baseline.")

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "addons/Control++/lib/{}/libControl++{}.framework/libgdexample.{}".format(
            "MacOS", name, env["platform"], env["target"]
        ),
        source=sources,
    )
else:
    library = env.SharedLibrary(
        "addons/Control++/lib/{}-{}/libControl++{}{}".format(env["platform"].title(),env["arch"], name, env["SHLIBSUFFIX"]),
        source=sources,
    )
"""
env.Default(library)
env.Alias('release',library)

print("Compiling debug version")

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "addons/Control++/lib/{}/libControl++-d.framework/libgdexample.{}.{}".format(
            "MacOS", env["platform"], env["target"]
        ),
        source=sources,
        LINKFLAGS=['/DEBUG'],
    )
else:
    library = env.SharedLibrary(
        "addons/Control++/lib/{}-{}/libControl++-d{}".format(env["platform"].title(),env["arch"], env["SHLIBSUFFIX"]),
        source=sources,
        LINKFLAGS=['/DEBUG'],
    )
"""
Default(library)
#envDebug.Default(library)
#envDebug.Alias('debug',library)
