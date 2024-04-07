extends EditorProperty


var real_property: EditorProperty
var new_name: String
var new_raw_name: String

func _init():
	#set("label","Custom Top")
	#refresh_control_text()
	hide()

func _process(delta):
	var chidren = get_parent().get_children()
	for c in chidren:
		if c == self:
			continue
		if c is EditorProperty:
			if c.label == label:
				real_property = c
				_update_property()
	set_process(false)

func _update_property():
	if(real_property == null):
		return
	if "_" in real_property.get_label():
		real_property.set("label",new_raw_name)
		return
	real_property.set("label",new_name)
	
