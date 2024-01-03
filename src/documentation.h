#ifndef DOCUMENTATION_H
#define DOCUMENTATION_H

#include <godot_cpp/classes/editor_plugin.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/script_editor.hpp>
#include <godot_cpp/classes/editor_interface.hpp>
#include "editor/editor_help.h"
#include "editor/doc_tools.h"
#include <godot_cpp/variant/typed_array.hpp>

namespace godot {

class Documentation : public Object {
	GDCLASS(Documentation, Object)

private:
	double time_passed;
	EditorPlugin *editorplugin;
	EditorInterface *editorinterface;
	ScriptEditor *scripteditor;
	TypedArray<Node> editor_helps ;
    const String s1 = "*";
	const String s2 = "EditorHelp";
	static DocTools *doc_data;
	bool done = false;
	EditorHelp *editor_help;
	//get_editor_interface().get_script_editor()

protected:
	static void _bind_methods();

public:
	Documentation();
	~Documentation();

	void set_amplitude(const double p_delta);
	double get_amplitude() const;
	void _process(double delta);
	TypedArray<Node> get_EditorHelps();
	bool pass_time(double delta, int max_value = -1);
	void set_EditorHelp(Object *edit);
};

}

#endif
