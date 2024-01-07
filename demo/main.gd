@tool
extends Node

@export var p1 = false 
@export var p2 = false 
@export var p3 = false 
@export var p4 = false 
@export var p5 = false 
var p52 = false 
# Called when the node enters the scene tree for the first time.
func _ready():
	pass


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	if p1:
		p1 = false
		var icon = $MenuButton.get_button_icon()
		$GridContainer/ExpandableButton.add_theme_icon_override("icon",icon)
	if p3:
		p3 = false
		$"RevisedButton".print_tree()
		var s = $"RevisedButton/@Control@17950/@RichTextLabel@17951/@VScrollBar@17949"
		print(s.value," ",s.max_value," ",s.min_value," ",s.page," ",s.step)
	if p4:
		p4 = false
		$RevisedButton/ExpandableButton.print_tree()
	if p2:
		p2 = false
		$HScrollBar/AutoScroll.scroll_to(56.6)
		#print($AnimatedSprite2D._get_configuration_warnings())
	if p5:
		p5 = false
		$RevisedButton/Button.set_pressed_no_signal(p52)
		p52 = !p52


func _on_revised_button_2_pressed():
	$PopupMenu.show()


func _on_expandable_button_2_item_rect_changed():
	print($GridContainer/ExpandableButton2.get_minimum_size())
