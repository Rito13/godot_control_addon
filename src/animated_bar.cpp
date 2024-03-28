#include "animated_bar.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/translation_server.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>

using namespace godot;

void AnimatedBar::_bind_methods() {
	ClassDB::bind_method(D_METHOD("on_button_pressed","p_id","p_status"), &AnimatedBar::on_button_pressed);
	ClassDB::bind_method(D_METHOD("on_right_pressed"), &AnimatedBar::on_right_pressed);
	ClassDB::bind_method(D_METHOD("on_left_pressed"), &AnimatedBar::on_left_pressed);
	ADD_SIGNAL(MethodInfo("focus_changed", PropertyInfo(Variant::INT, "focused_child_id")));
	ADD_SIGNAL(MethodInfo("focus_activated", PropertyInfo(Variant::INT, "focused_child_id")));
	ADD_SIGNAL(MethodInfo("focus_deactivated", PropertyInfo(Variant::INT, "focused_child_id")));
}

AnimatedBar::AnimatedBar() {
	// Initialize any variables here.
	spacing = 5.0;
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
			move_child(right,n-1);
			left->set_position(Vector2(0,y));
			Vector2 ms = left->get_combined_minimum_size();
			x += ms.x + spacing;
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
			ms = right->get_combined_minimum_size();
			right->set_position(Vector2(get_size().x-ms.x,y));
			for(int i=0;i<n;i++) {
				if(children[i] == nullptr) continue;
				ms = children[i]->get_combined_minimum_size();
				children[i]->set_size(Vector2(ms.x,height));
				if(button_children[i] == nullptr) continue;
				if(i!=0 && i!=n-1 && !Engine::get_singleton()->is_editor_hint()) {
					button_children[i]->set_toggle_mode(true);
					button_children[i]->disconnect("toggled",Callable(this, "on_button_pressed"));
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
	// Do Something
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
	size -= right->get_size().x;
	int i = first_child_id-1;
	while (i>0) {
		Control *child = Object::cast_to<Control>(get_child(i));
		if(child == nullptr) {
			i--;
			continue;
		}
		if((-1)*(child->get_position().x-left->get_size().x)<=size) {
			size = (-1)*(child->get_position().x-left->get_size().x);
			first_child = child;
			first_child_id = i;
		} else break;
		i--;
	}
	subtracted_value += size;
	UtilityFunctions::print(first_child->get_name(),"   ",first_child_id);
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
	if(first_child_id >= n-1 || first_child == nullptr) return;
	int size = get_size().x;
	size -= first_child->get_position().x;
	size -= right->get_size().x;
	int i = first_child_id+1;
	while (i<n) {
		Control *child = Object::cast_to<Control>(get_child(i));
		if(child == nullptr) {
			i++;
			continue;
		}
		if((child->get_position().x-left->get_size().x)<=size) {
			size = (child->get_position().x-left->get_size().x);
			first_child = child;
			first_child_id = i;
		} else break;
		i++;
	}
	subtracted_value -= size;
	UtilityFunctions::print(first_child->get_name(),"   ",first_child_id);
	queue_sort();
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
