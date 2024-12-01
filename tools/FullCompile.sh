#! /usr/bin/bash
distrobox enter debian-10 -- ../venv-debian10/bin/scons platform=windows target=template_release
distrobox enter debian-10 -- ../venv-debian10/bin/scons platform=windows target=template_debug
distrobox enter debian-10 -- ../venv-debian10/bin/scons target=template_release
distrobox enter debian-10 -- ../venv-debian10/bin/scons target=template_debug
