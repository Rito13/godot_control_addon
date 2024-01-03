@tool
extends Documentation
class_name test1

#[color=#70bafa][b]Klasa:[/b][/color] [img]res://addons/control++/icons/DictionaryNode.svg[/img] test1 [br]
##[color=#60aaea]Dziedziczy:   [Documentation] < [img]res://Sprite2D.svg[/img] [Sprite2D] <   [Node2D] <   [CanvasItem] <   [Node] <   [Object][/color]
##
##t

var self_class = "test1"
##Define an amplitude
@export var amplitude = 30
# Called when the node enters the scene tree for the first time.
@export var print_scripts = false:
	set(value):
		if value:
			print(EditorPlugin.new().get_editor_interface().get_script_editor().get_open_scripts())

@export var print_signals = false:
	set(value):
		if value:
			for S in EditorPlugin.new().get_editor_interface().get_script_editor().get_signal_list():
				print(S["name"])

@export var print_children = false:
	set(value):
		if value:
			for C in EditorPlugin.new().get_editor_interface().get_script_editor().get_children():
				print(C)

@export var print_tree = false:
	set(value):
		if value:
			EditorPlugin.new().get_editor_interface().get_script_editor().print_tree()

@export var close = false:
	set(value):
		if value:
			var Class = "TabContainerReload"
			lol(Class)
			find_opened_doc(Class).find_child("@RichTextLabel*",false,false).connect("visibility_changed",lol)
 
func lol(Class):
	print(Class)
	Class = "TabContainerReload"
	var docs = list_opened_docs()
	var names = []
	for d in docs:
		if d.name != Class:
			names.append(d.name)
	var s = EditorPlugin.new().get_editor_interface().get_script_editor()
	s._close_docs_tab()
	names.append(self_class)
	for n in names:
		s._help_class_open(n)
	var label = find_opened_doc(self_class).find_child("@RichTextLabel*",false,false)
	for i in [0,1,2]:
		label.remove_paragraph(1)

@export var print_methods = false:
	set(value):
		if value:
			for C in list_opened_docs()[1].get_method_list():
				print(C["name"])

@export var print_methods_old = false:
	set(value):
		if value:
			for n in EditorPlugin.new().get_editor_interface().get_script_editor().get_method_list():
				print(n["name"])

##[color=orange]Orange Text[/color]
@export var open_dock_tab = false:
	set(value):
		if value:
			for i in range(_get_tabs_list_node().item_count):
				print(_get_tabs_list_node().get_item_text(i))
			var Class = "TabContainerReload"
			var doc = find_opened_doc(Class)
			if doc == null:
				EditorPlugin.new().get_editor_interface().get_script_editor()._help_class_open(Class)
			go_to_docs(Class)
			print(doc.get_children())

@export var print_text = false:
	set(value):
		if value:
			for P in find_opened_doc("TabContainerReload").get_property_list():
				print(P["name"])
				if P["name"] == "size":
					print("value: ",find_opened_doc("Button").get(P["name"]))
			find_opened_doc("TabContainerReload").set_text(find_opened_doc("Button").find_child("@RichTextLabel*",false,false).get_parsed_text())
			find_opened_doc("TabContainerReload").find_child("@RichTextLabel*",false,false).show()
			

var _tabcon = null
var _itmlst = {}

func _get_tabs_list_node(n = 2):
	if not _itmlst.has(str(n)):
		_itmlst[str(n)] = null
	if _itmlst[str(n)] == null:
		var script_edit = EditorPlugin.new().get_editor_interface().get_script_editor()
		var VBox = script_edit.find_child("@VBoxContainer@*",false,false)
		VBox = VBox.find_child("@HSplitContainer@*",false,false).find_child("@VSplitContainer@*",false,false)
		var Bs = VBox.find_children("@VBoxContainer@*","VBoxContainer",false,false)
		for B in Bs:
			if B.get_child_count() == n:
				_itmlst[str(n)] = B.find_child("@ItemList@*",false,false)
	return _itmlst[str(n)]

func _get_tab_container():
	if _tabcon == null:
		var script_edit = EditorPlugin.new().get_editor_interface().get_script_editor()
		var VBox = script_edit.find_child("@VBoxContainer@*",false,false)
		VBox = VBox.find_child("@HSplitContainer@*",false,false).find_child("@VBoxContainer@*",false,false)
		_tabcon = VBox.find_child("@TabContainer@*",false,false)
	return _tabcon

func list_opened_docs():
	var TabCon = _get_tab_container()
	var childs = TabCon.find_children("*","EditorHelp",false,false)
	return childs

func go_to_docs(ClassName:StringName):
	var TabCon = _get_tab_container()
	var i = 0
	for C in TabCon.get_children():
		if C.name == ClassName:
			TabCon.set_current_tab(i)
			var ItmList = _get_tabs_list_node()
			ItmList.select(i)
			ItmList.item_selected.emit(i)
			if ItmList.get_item_text(i) != ClassName:
				ItmList.set_item_text(i,ClassName)
			return
		i = 1 + i

func find_opened_doc(ClassName:StringName):
	var TabCon = _get_tab_container()
	var childs = TabCon.find_children(ClassName,"EditorHelp",false,false)
	if len(childs) <= 0:
		return null
	return childs[0]

func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
