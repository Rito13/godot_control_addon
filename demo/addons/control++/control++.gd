@tool
extends EditorPlugin

var D:Documentation

func _enter_tree():
	D = Documentation.new()
	print_rich("[color=YELLOW_GREEN]● Control++:  Loading...\n	  «»-«»-«»")
	print_rich("[color=VIOLET]● Control++:  The documentation for GDExtension is not suported![/color]")
	print_rich("	  «»-«»-«»\n● Control++:  Loaded![color=SNOW]")

func _process(delta):
	if D.pass_time(delta,2):
		pass#print_rich("[color=yellow_green]● Control++:")
 # 		D._process(delta)
 # 		var editor_help = D.get_EditorHelps()
		#print(editor_help[0])
		#D.set_EditorHelp(editor_help[0])

func _exit_tree():
	pass
