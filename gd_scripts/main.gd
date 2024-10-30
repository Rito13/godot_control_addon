@tool
extends Node

@export var p1 = false 
@export var p2 = false 
@export var p3 = false 
@export var p4 = false 
@export var p5 = false 
@export var p6 = false 
var p52 = false 
# Called when the node enters the scene tree for the first time.
func _ready():
	#p4 = true
	pass

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	$Label.text = String.num($"MarginContainer/ExpandableButton 4".get_combined_minimum_size().x,4)
	if p1:
		p1 = false
		print_rich("[color=#f34455ff] lol")
	if p3:
		p3 = false
		$"RevisedButton".print_tree()
		var s = $"RevisedButton/@Control@17950/@RichTextLabel@17951/@VScrollBar@17949"
		print(s.value," ",s.max_value," ",s.min_value," ",s.page," ",s.step)
	if p4:
		p4 = false
		$RevisedButton2.set_alignment_order(3)
		$RevisedButton2.set_text_autowrap(TextServer.AUTOWRAP_OFF)
	if p2:
		p2 = false
		$HScrollBar/AutoScroll.scroll_to(56.6)
		#print($AnimatedSprite2D._get_configuration_warnings())
	if p5:
		p5 = false
		$RevisedButton/Button.set_pressed_no_signal(p52)
		p52 = !p52
	if p6:
		p6 = false
		print(get_node_or_null(NodePath("./AnimatedBar/RevisedButton")),"   ",$AnimatedBar/RevisedButton)


func _on_revised_button_2_pressed():
	$PopupMenu.show()


func _on_expandable_button_2_item_rect_changed():
	print($GridContainer/ExpandableButton2.get_minimum_size())


func _on_expandable_button_button_down():
	$GridContainer.queue_sort()
	$GridContainer.queue_redraw()
	print($GridContainer/ExpandableButton.get_minimum_size())


func _on_expandable_button_minimum_size_changed():
	print($GridContainer/ExpandableButton.get_minimum_size())
