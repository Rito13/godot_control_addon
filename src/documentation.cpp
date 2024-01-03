#include "documentation.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void Documentation::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_process", "delta"), &Documentation::_process);
    ClassDB::bind_method(D_METHOD("pass_time", "delta", "max_value"), &Documentation::pass_time,DEFVAL(-1));
    ClassDB::bind_method(D_METHOD("get_EditorHelps"), &Documentation::get_EditorHelps);
    ClassDB::bind_method(D_METHOD("get_amplitude"), &Documentation::get_amplitude);
	ClassDB::bind_method(D_METHOD("set_amplitude", "p_amplitude"), &Documentation::set_amplitude);
    ClassDB::add_property("Documentation", PropertyInfo(Variant::FLOAT, "The_documentation_for_GDExtension_is_not_suported_yet"), "set_amplitude", "get_amplitude");
}

Documentation::Documentation() {
	// Initialize any variables here.
	time_passed = 0.0;
	editorplugin = memnew(EditorPlugin);
	scripteditor = editorplugin->get_editor_interface()->get_script_editor();
}

Documentation::~Documentation() {
	// Add your cleanup here.
}

void Documentation::set_amplitude(const double p_delta) {
	time_passed = p_delta;
}

double Documentation::get_amplitude() const {
	return time_passed;
}

bool Documentation::pass_time(double delta, int max_value) {
	time_passed += delta;
	if(time_passed>max_value&&max_value>=0) {
        time_passed = 0;
        return true;
    }
    return false;
}

/*
void Documentation::set_EditorHelp(Object *p_edit) {
    const NodePath p = NodePath(".");
    editor_help = p_edit->cast_to<EditorHelp>(p_edit);//replace_by(editor_help);
    UtilityFunctions::print(editor_help);
}
*/

TypedArray<Node> Documentation::get_EditorHelps() {
    return editor_helps;
}

void Documentation::_process(double delta = 10) {
	time_passed += delta;
    if(done)return;
    editor_helps = scripteditor->find_children(s1,s2,true,false);
    UtilityFunctions::print(editor_helps);
    if(editor_helps.size() > 0) {
       UtilityFunctions::print(editor_helps.size());
       Variant parent = editor_helps.back();
       UtilityFunctions::print(parent);
       done = true;
    }
	//set_position(new_position);
}
