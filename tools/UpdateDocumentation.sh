#! /usr/bin/bash
distrobox enter debian-10 -- ../venv-debian10/bin/scons target=template_debug
distrobox enter debian-10 -- ../.files/Godot_v4.3-stable_linux.x86_64 --doctool ./ --gdextension-docs --verbose
distrobox enter debian-10 -- ../venv-debian10/bin/scons target=template_debug
