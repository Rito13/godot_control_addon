#include "register_types.h"

#include "gdexample.h"
#include "button.h"
#include "documentation.h"
#include "better_scroll.h"
#include "expandable_button.h"
#include "animated_bar.h"
#include "animated_tab_container.h"
#include "irregular_grid.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

void initialize_control_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	GDREGISTER_CLASS(GDExample)
	GDREGISTER_CLASS(RevisedButton)
	GDREGISTER_CLASS(Documentation)
	GDREGISTER_CLASS(AutoScroll)
	GDREGISTER_CLASS(ExpandableButton)
	GDREGISTER_VIRTUAL_CLASS(AnimatedBar)
	GDREGISTER_CLASS(HAnimatedBar)
	GDREGISTER_CLASS(VAnimatedBar)
	GDREGISTER_CLASS(AnimatedTabContainer)
	GDREGISTER_CLASS(IrregularGridContainer)
}

void uninitialize_control_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT control_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

	init_obj.register_initializer(initialize_control_module);
	init_obj.register_terminator(uninitialize_control_module);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}
