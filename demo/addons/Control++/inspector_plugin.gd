extends EditorInspectorPlugin

var ConstantIntEditor = preload("res://addons/Control++/constant_int_editor.gd")
var ConstantBoolEditor = preload("res://addons/Control++/constant_bool_editor.gd")

func _can_handle(object):
	if object is ExpandableButton:
		return true
	if object is AnimatedBar:
		return true
	return false


func _parse_property(object, type, name, hint_type, hint_string, usage_flags, wide):
	# We handle properties of type integer.
	if type == TYPE_INT and hint_string == "constant_int":
		add_property_editor(name, ConstantIntEditor.new())
		return true
	if object is AnimatedBar and name == "clip_contents":
		add_property_editor(name, ConstantBoolEditor.new())
		return true
	else:
		return false
