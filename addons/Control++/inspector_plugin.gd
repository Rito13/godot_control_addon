extends EditorInspectorPlugin

var ConstantIntEditor = preload("res://addons/Control++/constant_int_editor.gd")
var ConstantBoolEditor = preload("res://addons/Control++/constant_bool_editor.gd")
var ChangeNameEditor = preload("res://addons/Control++/change_name_editor.gd")

func _can_handle(object):
	if object is ExpandableButton:
		return true
	if object is AnimatedBar:
		return true
	if object is AnimatedTabContainer:
		return true
	return false


func _parse_property(object, type, name, hint_type, hint_string, usage_flags, wide):
	# We handle properties of type integer.
	if type == TYPE_INT and hint_string == "constant_int":
		add_property_editor(name, ConstantIntEditor.new())
		return true
	if (object is AnimatedBar or object is AnimatedTabContainer) and name == "clip_contents":
		add_property_editor(name, ConstantBoolEditor.new())
		return true
	if object is VAnimatedBar and name == "navigation_buttons_custom_left":
		var tmp = ChangeNameEditor.new()
		tmp.new_name = "Custom Top"
		tmp.new_raw_name = "_custom_top"
		add_property_editor(name, tmp)
		return false
	if object is VAnimatedBar and name == "navigation_buttons_custom_right":
		var tmp = ChangeNameEditor.new()
		tmp.new_name = "Custom Bottom"
		tmp.new_raw_name = "_custom_bottom"
		add_property_editor(name, tmp)
		return false
	else:
		return false
