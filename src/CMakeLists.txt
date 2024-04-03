# SPDX-License-Identifier: Unlicense

target_sources( ${PROJECT_NAME}
    PRIVATE
        register_types.cpp
        register_types.h
)

target_include_directories( ${PROJECT_NAME}
    PRIVATE
    	"."
        "editor"
        "core"
)
