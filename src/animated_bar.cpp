#include "animated_bar.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/translation_server.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>

using namespace godot;

void AnimatedBar::_bind_methods() {
	// Signals Conections Functions
	ClassDB::bind_method(D_METHOD("on_button_pressed","p_id","p_status"), &AnimatedBar::on_button_pressed);
	ClassDB::bind_method(D_METHOD("on_right_pressed"), &AnimatedBar::on_right_pressed);
	ClassDB::bind_method(D_METHOD("on_left_pressed"), &AnimatedBar::on_left_pressed);
	// Emited Signals
	ADD_SIGNAL(MethodInfo("focus_changed", PropertyInfo(Variant::INT, "focused_child_id")));
	ADD_SIGNAL(MethodInfo("focus_activated", PropertyInfo(Variant::INT, "focused_child_id")));
	ADD_SIGNAL(MethodInfo("focus_deactivated", PropertyInfo(Variant::INT, "focused_child_id")));
	// Speed Property
	ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &AnimatedBar::set_speed);
	ClassDB::bind_method(D_METHOD("get_speed"), &AnimatedBar::get_speed);
	ClassDB::add_property("AnimatedBar", PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");
	// Spacing Property
	ClassDB::bind_method(D_METHOD("set_spacing", "p_spacing"), &AnimatedBar::set_spacing);
	ClassDB::bind_method(D_METHOD("get_spacing"), &AnimatedBar::get_spacing);
	ClassDB::add_property("AnimatedBar", PropertyInfo(Variant::FLOAT, "spacing"), "set_spacing", "get_spacing");
	// Add tab for Navigation Buttons Properties
	ClassDB::add_property_group("AnimatedBar","Navigation Buttons Settings","navigation_buttons");
	// Navigation Buttons Spacing Property
	ClassDB::bind_method(D_METHOD("set_navigation_buttons_spacing", "p_spacing"), &AnimatedBar::set_spacing2);
	ClassDB::bind_method(D_METHOD("get_navigation_buttons_spacing"), &AnimatedBar::get_spacing2);
	ClassDB::add_property("AnimatedBar", PropertyInfo(Variant::FLOAT, "navigation_buttons_spacing"), "set_navigation_buttons_spacing", "get_navigation_buttons_spacing");
	// Navigation Buttons Visibility Property
	ClassDB::bind_method(D_METHOD("set_navigation_buttons_visibility", "is_enabled"), &AnimatedBar::set_lr_visibility);
	ClassDB::bind_method(D_METHOD("are_navigation_buttons_visible"), &AnimatedBar::get_lr_visibility);
	ClassDB::add_property("AnimatedBar", PropertyInfo(Variant::BOOL, "navigation_buttons_visibility"), "set_navigation_buttons_visibility", "are_navigation_buttons_visible");
	// Use Custom Navigation Buttons Property
	ClassDB::bind_method(D_METHOD("use_custom_navigation_buttons", "is_enabled"), &AnimatedBar::set_custom_lr);
	ClassDB::bind_method(D_METHOD("are_custom_navigation_buttons_used"), &AnimatedBar::get_custom_lr);
	ClassDB::add_property("AnimatedBar", PropertyInfo(Variant::BOOL, "navigation_buttons_use_custom"), "use_custom_navigation_buttons", "are_custom_navigation_buttons_used");
	// Custom Navigation Buttons Pointers
	ClassDB::bind_method(D_METHOD("set_custom_left_navigation_button", "p_button"), &AnimatedBar::set_custom_left);
	ClassDB::bind_method(D_METHOD("get_custom_left_navigation_button"), &AnimatedBar::get_custom_left);
	ClassDB::add_property("AnimatedBar", PropertyInfo(Variant::NODE_PATH, "navigation_buttons_custom_left"), "set_custom_left_navigation_button", "get_custom_left_navigation_button");
	ClassDB::bind_method(D_METHOD("set_custom_right_navigation_button", "p_button"), &AnimatedBar::set_custom_right);
	ClassDB::bind_method(D_METHOD("get_custom_right_navigation_button"), &AnimatedBar::get_custom_right);
	ClassDB::add_property("AnimatedBar", PropertyInfo(Variant::NODE_PATH, "navigation_buttons_custom_right",PROPERTY_HINT_INT_IS_POINTER), "set_custom_right_navigation_button", "get_custom_right_navigation_button");
}

AnimatedBar::AnimatedBar() {
	// Initialize any variables here.
	spacing = 10.0;
	spacing2 = 5.0;
	set_clip_contents(true);
	left = memnew(Button);
	right = memnew(Button);
	Button *l = Object::cast_to<Button>(left);
	l->set_text("<-");
	Button *r = Object::cast_to<Button>(right);
	r->set_text("->");
	add_child(right);
	add_child(left);
	Error err1 = right->connect("pressed",Callable(this, "on_right_pressed"));
	err1 = left->connect("pressed",Callable(this, "on_left_pressed"));
	left->set_as_top_level(true);
	right->set_as_top_level(true);
}

AnimatedBar::~AnimatedBar() {
	// Add your cleanup here.
	left->queue_free();
	right->queue_free();
}

void AnimatedBar::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_SORT_CHILDREN: {
			int n = get_child_count();
			if(n<2) {
				UtilityFunctions::print_rich("[color=VIOLET]",String(L"●")," Control++:  "+String(get_name())+" have no children. Please add some.","[color=SNOW]");
			}
			Control *children[n];
			BaseButton *button_children[n];
			double x = -subtracted_value;
			double y = 0;
			double height = 0;
			move_child(left,0);
			move_child(right,n-1);
			Vector2 _pos = get_position();
			Vector2 ms = left->get_combined_minimum_size();
			left->set_position(Vector2(_pos.x-ms.x-spacing2,y+_pos.y));
			children[0] = left;
			children[n-1] = right;
			button_children[0] = left;
			button_children[n-1] = right;
			for(int i=1;i<n-1;i++) {
				children[i] = Object::cast_to<Control>(get_child(i));
				button_children[i] = Object::cast_to<BaseButton>(get_child(i));
				if(children[i] == nullptr) continue;
				children[i]->set_position(Vector2(x,y));
				ms = children[i]->get_combined_minimum_size();
				x += ms.x + spacing;
				if(height<ms.y) height = ms.y;
			}
			right->set_position(Vector2(get_size().x+_pos.x+spacing2,y+_pos.y));
			for(int i=0;i<n;i++) {
				if(children[i] == nullptr) continue;
				ms = children[i]->get_combined_minimum_size();
				children[i]->set_size(Vector2(ms.x,height));
				if(button_children[i] == nullptr) continue;
				if(i!=0 && i!=n-1 && !Engine::get_singleton()->is_editor_hint()) {
					button_children[i]->set_toggle_mode(true);
					button_children[i]->disconnect("pressed",Callable(this, "on_button_pressed"));
					Array a;
					a.append(i);
					a.append(button_children[i]);
					Error err1 = button_children[i]->connect("pressed",Callable(this, "on_button_pressed").bindv(a));
					//UtilityFunctions::print(err1);
				}
			}
		} break;

		case NOTIFICATION_THEME_CHANGED: {
			update_minimum_size();
		} break;

		case NOTIFICATION_TRANSLATION_CHANGED:
		case NOTIFICATION_LAYOUT_DIRECTION_CHANGED: {
			queue_sort();
		} break;
	}
}

void AnimatedBar::_process(double delta) {
	double _delta_speed = delta*60*speed;
	if(abs(subtracted_value-to_subtract_value)<_delta_speed) {
		subtracted_value = to_subtract_value;
		queue_sort();
		return;
	}
	if(subtracted_value<to_subtract_value) {
		subtracted_value += _delta_speed;
		queue_sort();
		return;
	}
	if(subtracted_value>to_subtract_value) {
		subtracted_value -= _delta_speed;
		queue_sort();
		return;
	}
}

Vector2 AnimatedBar::_get_minimum_size() const {
	Vector2 _min = Vector2(0,0);
	for(int i = 0;i<get_child_count();i++) {
		Control *child = Object::cast_to<Control>(get_child(i));
		if(child == nullptr) continue;
		Vector2 size = child->get_combined_minimum_size();
		if(size.x > _min.x) _min.x = size.x;
		if(size.y > _min.y) _min.y = size.y;
	}
	_min.x += spacing + 1;
	return _min;
}

void AnimatedBar::on_button_pressed(int id,BaseButton *button) {
	if(button->is_pressed()) {
		if(focus) emit_signal("focus_changed",id);
		else emit_signal("focus_activated",id);
		for(int i = 1;i<get_child_count()-1;i++) {
			BaseButton *child = Object::cast_to<BaseButton>(get_child(i));
			if (child == nullptr) continue;
			child->set_pressed_no_signal(false);
		}
		button->set_pressed_no_signal(true);
		focus = true;
	} else emit_signal("focus_deactivated",id);
	//UtilityFunctions::print(button->get_name(),"   ",id);
}

void AnimatedBar::on_left_pressed() {
	if(get_child(first_child_id) != first_child) {
		first_child_id = 1;
		first_child = Object::cast_to<Control>(get_child(1));
		queue_sort();
		return;
	}
	if(first_child_id <= 1 || first_child == nullptr) return;
	int size = get_size().x;
	size -= first_child->get_position().x;
	int i = first_child_id-1;
	int _size = size;
	while (i>0) {
		Control *child = Object::cast_to<Control>(get_child(i));
		if(child == nullptr) {
			i--;
			continue;
		}
		if((-1)*(child->get_position().x)<=_size) {
			size = (-1)*(child->get_position().x);
			first_child = child;
			first_child_id = i;
			i--;
			continue;
		} 
		if((-1)*(child->get_position().x+child->get_size().x)<=_size) size = _size;
		break;
	}
	to_subtract_value -= size;
	UtilityFunctions::print(first_child->get_name(),"   ",first_child_id,"   ",size);
	queue_sort();
}

void AnimatedBar::on_right_pressed() {
	if(get_child(first_child_id) != first_child) {
		first_child_id = 1;
		first_child = Object::cast_to<Control>(get_child(1));
		queue_sort();
		return;
	}
	int n = get_child_count();
	if(first_child_id >= n-2 || first_child == nullptr) return;
	int size = get_size().x;
	size -= first_child->get_position().x;
	int i = first_child_id+1;
	int _size = size;
	while (i<n-1) {
		Control *child = Object::cast_to<Control>(get_child(i));
		if(child == nullptr) {
			i++;
			continue;
		}
		if((child->get_position().x)<=_size) {
			size = (child->get_position().x);
			first_child = child;
			first_child_id = i;
			i++;
			continue;
		} break;
	}
	i = first_child_id;
	int _s_, _i_;
	while (i<n-1) {
		Control *child = Object::cast_to<Control>(get_child(i));
		if(child == nullptr) {
			i++;
			continue;
		}
		int x = (child->get_position().x+child->get_size().x);
		if((x)<=_size+size) {
			_s_ = x;
			_i_ = i;
			i++;
			continue;
		}
		to_subtract_value += size;
		UtilityFunctions::print(first_child->get_name(),"   ",first_child_id,"   ",size);
		queue_sort();
		return;
	}
	to_subtract_value += _s_;
	UtilityFunctions::print("   ",first_child_id,"   ",_s_);
	i = _i_;
	_size = get_size().x;
	while (i>0) {
		Control *child = Object::cast_to<Control>(get_child(i));
		if(child == nullptr) {
			i--;
			continue;
		}
		if((-1)*(child->get_position().x-_s_)<=_size) {
			size = (-1)*(child->get_position().x-_s_);
			first_child = child;
			first_child_id = i;
			i--;
			continue;
		} 
		size = _size;
		break;
	}
	to_subtract_value -= size;
	UtilityFunctions::print(first_child->get_name(),"   ",first_child_id,"   ",size,"   ",_size);
	queue_sort();
}

double AnimatedBar::get_spacing() {
	return spacing;
}

void AnimatedBar::set_spacing(double p_spacing) {
	spacing = p_spacing;
	queue_sort();
}

double AnimatedBar::get_spacing2() {
	return spacing2;
}

void AnimatedBar::set_spacing2(double p_spacing) {
	spacing2 = p_spacing;
	Vector2 _pos = get_position();
	Vector2 ms = left->get_combined_minimum_size();
	int y = 0;
	left->set_position(Vector2(_pos.x-ms.x-spacing2,y+_pos.y));
	right->set_position(Vector2(get_size().x+_pos.x+spacing2,y+_pos.y));
}

double AnimatedBar::get_speed() {
	return speed;
}

void AnimatedBar::set_speed(double p_speed) {
	speed = p_speed;
}

bool AnimatedBar::get_lr_visibility() {
	return lr_visibility;
}

void AnimatedBar::set_lr_visibility(bool is_enabled) {
	lr_visibility = is_enabled;
	left->set_visible(lr_visibility);
	right->set_visible(lr_visibility);
}

bool AnimatedBar::get_custom_lr() {
	return custom_lr;
}

void AnimatedBar::set_custom_lr(bool is_enabled) {
	custom_lr = is_enabled;
	queue_sort();
	UtilityFunctions::print(custom_left,"   ",custom_right,"   ",custom_left == nullptr,"   ",custom_right == nullptr);
	if(!custom_lr) {
		left->set_as_top_level(false);
		right->set_as_top_level(false);
		left->disconnect("pressed",Callable(this, "on_left_pressed"));
		right->disconnect("pressed",Callable(this, "on_right_pressed"));
		left = memnew(Button);
		right = memnew(Button);
		Button *l = Object::cast_to<Button>(left);
		l->set_text("<-");
		Button *r = Object::cast_to<Button>(right);
		r->set_text("->");
		add_child(right);
		add_child(left);
		Error err1 = right->connect("pressed",Callable(this, "on_right_pressed"));
		err1 = left->connect("pressed",Callable(this, "on_left_pressed"));
		left->set_as_top_level(true);
		right->set_as_top_level(true);
	} else {
		left->disconnect("pressed",Callable(this, "on_left_pressed"));
		right->disconnect("pressed",Callable(this, "on_right_pressed"));
		remove_child(left);
		remove_child(right);
		left -> queue_free();
		right -> queue_free();
		if(custom_left == nullptr) {
			left = memnew(Button);
			Button *l = Object::cast_to<Button>(left);
			l->set_text("<-");
			add_child(left);
		} else {
			Node *par = custom_left->get_parent();
			if(par != this) custom_left->reparent(this);
			left = custom_left;
		}
		if(custom_right == nullptr) {
			right = memnew(Button);
			Button *r = Object::cast_to<Button>(right);
			r->set_text("->");
			add_child(right);
		} else {
			Node *par = custom_right->get_parent();
			if(par != this) custom_right->reparent(this);
			right = custom_right;
		}
		Error err1 = right->connect("pressed",Callable(this, "on_right_pressed"));
		err1 = left->connect("pressed",Callable(this, "on_left_pressed"));
		left->set_as_top_level(true);
		right->set_as_top_level(true);
	}
}

NodePath AnimatedBar::get_custom_left() {
	if(custom_left == nullptr) return NodePath("");
	return custom_left->get_path();
}

NodePath AnimatedBar::get_custom_right() {
	if(custom_right == nullptr) return NodePath("");
	return custom_right->get_path();
}

void AnimatedBar::set_custom_left(NodePath p_path) {
	custom_left = Object::cast_to<BaseButton>(get_node_or_null(p_path));
	if(custom_left == nullptr) {
		UtilityFunctions::print_rich("[color=VIOLET]",String(L"●")," Control++:  Custom left node path have to refer to node inheriting from the BaseButton class.","[color=SNOW]");
		return;
	}
	Node *par = custom_left->get_parent();
	if(Engine::get_singleton()->is_editor_hint() && (par != this)) {
		UtilityFunctions::print_rich("[color=VIOLET]",String(L"●")," Control++:  Custom left node path have to refer to ",get_name(),"'s child.","[color=SNOW]");
		custom_left = nullptr;
		return;
	}
	if(custom_lr) {
		left->set_as_top_level(false);
		left->disconnect("pressed",Callable(this, "on_left_pressed"));
		if(par != this) custom_left->reparent(this);
		left = custom_left;
		Error err1 = left->connect("pressed",Callable(this, "on_left_pressed"));
		left->set_as_top_level(true);
		queue_sort();
	}
}

void AnimatedBar::set_custom_right(NodePath p_path) {
	custom_right = Object::cast_to<BaseButton>(get_node_or_null(p_path));
	if(custom_right == nullptr) {
		UtilityFunctions::print_rich("[color=VIOLET]",String(L"●")," Control++:  Custom right node path have to refer to node inheriting from the BaseButton class.","[color=SNOW]");
		return;
	}
	Node *par = custom_right->get_parent();
	if(Engine::get_singleton()->is_editor_hint() && (par != this)) {
		UtilityFunctions::print_rich("[color=VIOLET]",String(L"●")," Control++:  Custom right node path have to refer to ",get_name(),"'s child.","[color=SNOW]");
		custom_right = nullptr;
		return;
	}
	if(custom_lr) {
		right->set_as_top_level(false);
		right->disconnect("pressed",Callable(this, "on_right_pressed"));
		if(par != this) custom_right->reparent(this);
		right = custom_right;
		Error err1 = right->connect("pressed",Callable(this, "on_right_pressed"));
		right->set_as_top_level(true);
		queue_sort();
	}
}

PackedStringArray AnimatedBar::_get_configuration_warnings() const {
	PackedStringArray warnings;
	int n = get_child_count();
	if (n == 0) {
		warnings.push_back(RTR("AnimatedBar does not have child. Please add some children inheriting from the BaseButton class to allow AnimatedBar to work properly"));
		return warnings;
	}
	for(int i=0;i<n;i++) {
		BaseButton *child = Object::cast_to<BaseButton>(get_child(i));
		if (child == nullptr) {
			warnings.push_back(RTR(get_child(i)->get_name()+String(" does not inherit from the BaseButton class. Please remove it if it isn't necessary.")));
		}
	}
	return warnings;
}
