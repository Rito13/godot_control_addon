@tool
extends EditorPlugin

var D:Documentation
var Edited_Node:ExpandableButton

func _enter_tree():
	D = Documentation.new()
	print_rich("[color=YELLOW_GREEN]● Control++:  Loading...\n	  «»-«»-«»")
	print_rich("[color=VIOLET]● Control++:  The documentation for GDExtension is not suported![/color]")
	print_rich("	  «»-«»-«»\n● Control++:  Loaded![color=SNOW]")
	Edited_Node = ExpandableButton.new()

func _process(delta):
	if D.pass_time(delta,2):
		pass#print_rich("[color=yellow_green]● Control++:")
 # 		D._process(delta)
 # 		var editor_help = D.get_EditorHelps()
		#print(editor_help[0])
		#D.set_EditorHelp(editor_help[0])

func _handles(object: Object):
	if object is ExpandableButton:
		return true

func _edit(object: Object):
	print(object)
	if !object:
		print(Edited_Node," reduced because of ",object)
		Edited_Node.reduce()
		return
	if object is ExpandableButton:
		if object != Edited_Node:
			print(Edited_Node," reduced")
			Edited_Node.reduce()
		Edited_Node = object
		print(Edited_Node," expanded")
		Edited_Node.expand()


func _exit_tree():
	pass
