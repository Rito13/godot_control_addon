#include "animated_bar.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/rendering_server.hpp>

using namespace godot;

void AnimatedBar::_bind_methods() {
	// Signals Conections Functions
	ClassDB::bind_method(D_METHOD("_on_button_pressed","p_id","p_status"), &AnimatedBar::_on_button_pressed);
	// Emited Signals
	ADD_SIGNAL(MethodInfo("focus_changed", PropertyInfo(Variant::INT, "focused_child_id")));
	ADD_SIGNAL(MethodInfo("focus_activated", PropertyInfo(Variant::INT, "focused_child_id")));
	ADD_SIGNAL(MethodInfo("focus_deactivated"));
	ADD_SIGNAL(MethodInfo("options_quantity_changed", PropertyInfo(Variant::INT, "new_quantity")));
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
	ClassDB::bind_method(D_METHOD("get_navigation_buttons_visibility"), &AnimatedBar::get_lr_visibility_v2);
	ClassDB::bind_method(D_METHOD("are_navigation_buttons_visible"), &AnimatedBar::get_lr_visibility);
	ClassDB::add_property("AnimatedBar", PropertyInfo(Variant::INT, "navigation_buttons_visibility",PROPERTY_HINT_ENUM, "OFF:0,ON:1,AUTO:3"), "set_navigation_buttons_visibility", "get_navigation_buttons_visibility");
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
	// Fill Remaining Space Property
	ClassDB::bind_method(D_METHOD("set_fill_remaining_space", "is_enabled"), &AnimatedBar::set_fill_remaining_space);
	ClassDB::bind_method(D_METHOD("is_remaining_space_filled"), &AnimatedBar::is_remaining_space_filled);
	ClassDB::add_property("AnimatedBar", PropertyInfo(Variant::BOOL, "fill_remaining_space"), "set_fill_remaining_space", "is_remaining_space_filled");
	/* // Deactivate Process when Iddle Property
	ClassDB::bind_method(D_METHOD("set_deactivate_process_when_iddle", "is_enabled"), &AnimatedBar::set_deactivate_process);
	ClassDB::bind_method(D_METHOD("get_deactivate_process_when_iddle"), &AnimatedBar::get_deactivate_process);
	ClassDB::add_property("AnimatedBar", PropertyInfo(Variant::BOOL, "deactivate_process_when_iddle"), "set_deactivate_process_when_iddle", "get_deactivate_process_when_iddle");
	*/ 
	// Other Functions
	ClassDB::bind_method(D_METHOD("get_options_quantity"), &AnimatedBar::get_options_quantity);
	ClassDB::bind_method(D_METHOD("deactivate_focus"), &AnimatedBar::deactivate_focus);
	ClassDB::bind_method(D_METHOD("get_orientation"), &AnimatedBar::get_orientation);
	//ClassDB::bind_method(D_METHOD("_ready"), &AnimatedBar::_ready);
	//ClassDB::bind_method(D_METHOD("_process","delta"), &AnimatedBar::_process);
	// Enum
	BIND_ENUM_CONSTANT(ORIENTATION_HORIZONTAL);
	BIND_ENUM_CONSTANT(ORIENTATION_VERTICAL);
	BIND_ENUM_CONSTANT(ORIENTATION_UNDEFINED);
}

void HAnimatedBar::_bind_methods() {
	// Signals Conections Functions
	ClassDB::bind_method(D_METHOD("_on_right_pressed"), &HAnimatedBar::_on_right_pressed);
	ClassDB::bind_method(D_METHOD("_on_left_pressed"), &HAnimatedBar::_on_left_pressed);
	ClassDB::bind_method(D_METHOD("_clip_child","p_child"), &HAnimatedBar::_clip_child);
	// Other Functions
	ClassDB::bind_method(D_METHOD("get_navigation_buttons_size"), &HAnimatedBar::get_lr_size);
	ClassDB::bind_method(D_METHOD("get_left_navigation_button_size"), &HAnimatedBar::get_left_size);
	ClassDB::bind_method(D_METHOD("get_right_navigation_button_size"), &HAnimatedBar::get_right_size);
}

void VAnimatedBar::_bind_methods() {
	// Signals Conections Functions
	ClassDB::bind_method(D_METHOD("_on_right_pressed"), &VAnimatedBar::_on_right_pressed);
	ClassDB::bind_method(D_METHOD("_on_left_pressed"), &VAnimatedBar::_on_left_pressed);
	ClassDB::bind_method(D_METHOD("_clip_child","p_child"), &VAnimatedBar::_clip_child);
	// Other Functions
	ClassDB::bind_method(D_METHOD("get_navigation_buttons_size"), &VAnimatedBar::get_lr_size);
	ClassDB::bind_method(D_METHOD("get_left_navigation_button_size"), &VAnimatedBar::get_left_size);
	ClassDB::bind_method(D_METHOD("get_right_navigation_button_size"), &VAnimatedBar::get_right_size);
}

AnimatedBar::AnimatedBar() {
	// Initialize any variables here.
	spacing = 10.0;
	spacing2 = 5.0;
	//set_clip_contents(true);
	left = memnew(Button);
	right = memnew(Button);
	left->set_name("__DefaultLeft__");
	right->set_name("__DefaultRight__");
	add_child(right);
	add_child(left);
	Button *l = Object::cast_to<Button>(left);
	l->set_text(_labels.left);
	Button *r = Object::cast_to<Button>(right);
	r->set_text(_labels.right);
	right->connect("pressed",Callable(this, "_on_right_pressed"));
	left->connect("pressed",Callable(this, "_on_left_pressed"));
	left->set_as_top_level(true);
	//right->set_as_top_level(true);
}

AnimatedBar::~AnimatedBar() {
	// Add your cleanup here.
	//left->queue_free();
	//right->queue_free();
}

void AnimatedBar::ready() {
	after_ready = true;
	//UtilityFunctions::print_rich("after_ready = ",after_ready);
	set_custom_right(for_ready.right_path);
	set_custom_left(for_ready.left_path);
	set_custom_lr(for_ready.custom_lr);
	set_lr_visibility(for_ready.lr_visibility);
	int n = get_child_count();
	if(n<=2) return;
	first_child_id = 1;
	first_child = Object::cast_to<Control>(get_child(1));
}

void HAnimatedBar::_clip_child(Control* child) {
	RID _rid = child->get_canvas_item();
	Vector2 _pos = get_left_size();
	_pos.y = 0;
	_pos -= child->get_position();
	Vector2 _size = get_size();
	_size.x -= get_lr_size().x;
	RenderingServer::get_singleton()->canvas_item_set_custom_rect(_rid,true,Rect2(_pos,_size));
	RenderingServer::get_singleton()->canvas_item_set_clip(_rid,true);
}

void VAnimatedBar::_clip_child(Control* child) {
	RID _rid = child->get_canvas_item();
	Vector2 _pos = get_left_size();
	_pos.x = 0;
	_pos -= child->get_position();
	Vector2 _size = get_size();
	_size.y -= get_lr_size().y;
	RenderingServer::get_singleton()->canvas_item_set_custom_rect(_rid,true,Rect2(_pos,_size));
	RenderingServer::get_singleton()->canvas_item_set_clip(_rid,true);
}

void HAnimatedBar::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_SORT_CHILDREN: {
			int n = get_child_count();
			if(n-2 != number_of_children) {
				number_of_children = n-2;
				emit_signal("options_quantity_changed",number_of_children);
			}
			if(n<2) {
				UtilityFunctions::print_rich("[color=VIOLET]",String(L"●")," Control++:  "+String(get_name())+" have no children. Please add some.","[color=SNOW]");
			}
			Control** children = new Control*[n];
			BaseButton** button_children = new BaseButton*[n];
			double x = -subtracted_value+get_left_size().x;
			double y = 0;
			double height = 0;
			move_child(left,0);
			move_child(right,n-1);
			Vector2 ms = left->get_combined_minimum_size();
			Vector2 _pos = get_global_position();
			left->set_position(Vector2(0,y)+_pos);
			height = ms.y;
			children[0] = left;
			children[n-1] = right;
			button_children[0] = left;
			button_children[n-1] = right;
			double expand_value = get_size().x;
			//if(!lr_auto_visibility && lr_visibility); //expand_value -= left and right xs 
			bool need_expand = true;
			for(int i=1;i<n-1;i++) {
				children[i] = Object::cast_to<Control>(get_child(i));
				button_children[i] = Object::cast_to<BaseButton>(get_child(i));
				if(children[i] == nullptr) continue;
				children[i]->set_position(Vector2(x,y));
				ms = children[i]->get_combined_minimum_size();
				x += ms.x + spacing;
				if(x-spacing>expand_value-subtracted_value) need_expand = false;
				if(height<ms.y) height = ms.y;
				_clip_child(children[i]);
				if(children[i]->is_connected("draw",Callable(this, "_clip_child"))) continue;
				Array a;
				a.append(children[i]);
				children[i]->connect("draw",Callable(this, "_clip_child").bindv(a));
			}
			ms = right->get_combined_minimum_size();
			right->set_position(Vector2(get_size().x-ms.x,y));
			if(height<ms.y) height = ms.y;
			for(int i=0;i<n;i++) {
				if(children[i] == nullptr) continue;
				ms = children[i]->get_combined_minimum_size();
				children[i]->set_size(Vector2(ms.x,height));
				if(button_children[i] == nullptr) continue;
				if(i!=0 && i!=n-1 && !Engine::get_singleton()->is_editor_hint()) {
					button_children[i]->set_toggle_mode(true);
					if(button_children[i]->is_connected("pressed",Callable(this, "_on_button_pressed")))
						button_children[i]->disconnect("pressed",Callable(this, "_on_button_pressed"));
					Array a;
					a.append(i);
					a.append(button_children[i]);
					button_children[i]->connect("pressed",Callable(this, "_on_button_pressed").bindv(a));
					//UtilityFunctions::print(err1);
				}
			}
			if(lr_auto_visibility) {
				bool tmp = lr_visibility;
				if(need_expand) lr_visibility = false;
				else lr_visibility = true;
				if(tmp != lr_visibility) emit_signal("minimum_size_changed");;
				//UtilityFunctions::print("lr_visibility = ",lr_visibility,"   need_expand = ",need_expand);
				left->set_visible(lr_visibility);
				right->set_visible(lr_visibility);
			}
			if(need_expand && do_expand) {
				double space_left = expand_value - (x-spacing);
				double space_for_each = space_left/(n-2);
				for(int i=1;i<n-1;i++) {
					if(children[i] == nullptr) continue;
					//size
					Vector2 tmp = children[i]->get_size();
					tmp.x += space_for_each;
					children[i]->set_size(tmp);
					//position
					tmp = children[i]->get_position();
					tmp.x += space_for_each*(i-1);
					children[i]->set_position(tmp);
				}
			}
			delete[] children;
			delete[] button_children;
		} break;

		case NOTIFICATION_THEME_CHANGED: {
			update_minimum_size();
		} break;

		case NOTIFICATION_TRANSLATION_CHANGED:
		case NOTIFICATION_LAYOUT_DIRECTION_CHANGED: {
			queue_sort();
		} break;

		default: {
			AnimatedBar::_notification(p_what);
		} break;
	}
}

void VAnimatedBar::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_SORT_CHILDREN: {
			int n = get_child_count();
			if(n-2 != number_of_children) {
				number_of_children = n-2;
				emit_signal("options_quantity_changed",number_of_children);
			}
			if(n<2) {
				UtilityFunctions::print_rich("[color=VIOLET]",String(L"●")," Control++:  "+String(get_name())+" have no children. Please add some.","[color=SNOW]");
			}
			Control** children = new Control*[n];
			BaseButton** button_children = new BaseButton*[n];
			double y = -subtracted_value+get_left_size().y;
			double x = 0;
			double width = 0;
			move_child(left,0);
			move_child(right,n-1);
			Vector2 ms = left->get_combined_minimum_size();
			Vector2 _pos = get_global_position();
			left->set_position(Vector2(x,0)+_pos);
			width = ms.x;
			children[0] = left;
			children[n-1] = right;
			button_children[0] = left;
			button_children[n-1] = right;
			double expand_value = get_size().y;
			//if(!lr_auto_visibility && lr_visibility); //expand_value -= left and right xs 
			bool need_expand = true;
			for(int i=1;i<n-1;i++) {
				children[i] = Object::cast_to<Control>(get_child(i));
				button_children[i] = Object::cast_to<BaseButton>(get_child(i));
				if(children[i] == nullptr) continue;
				children[i]->set_position(Vector2(x,y));
				ms = children[i]->get_combined_minimum_size();
				y += ms.y + spacing;
				if(y-spacing>expand_value-subtracted_value) need_expand = false;
				if(width<ms.x) width = ms.x;
				_clip_child(children[i]);
				if(children[i]->is_connected("draw",Callable(this, "_clip_child"))) continue;
				Array a;
				a.append(children[i]);
				children[i]->connect("draw",Callable(this, "_clip_child").bindv(a));
			}
			ms = right->get_combined_minimum_size();
			right->set_position(Vector2(x,get_size().y-ms.y));
			if(width<ms.x) width = ms.x;
			for(int i=0;i<n;i++) {
				if(children[i] == nullptr) continue;
				ms = children[i]->get_combined_minimum_size();
				children[i]->set_size(Vector2(width,ms.y));
				if(button_children[i] == nullptr) continue;
				if(i!=0 && i!=n-1 && !Engine::get_singleton()->is_editor_hint()) {
					button_children[i]->set_toggle_mode(true);
					if(button_children[i]->is_connected("pressed",Callable(this, "_on_button_pressed")))
						button_children[i]->disconnect("pressed",Callable(this, "_on_button_pressed"));
					Array a;
					a.append(i);
					a.append(button_children[i]);
					button_children[i]->connect("pressed",Callable(this, "_on_button_pressed").bindv(a));
					//UtilityFunctions::print(err1);
				}
			}
			if(lr_auto_visibility) {
				bool tmp = lr_visibility;
				if(need_expand) lr_visibility = false;
				else lr_visibility = true;
				if(tmp != lr_visibility) emit_signal("minimum_size_changed");;
				//UtilityFunctions::print("lr_visibility = ",lr_visibility,"   need_expand = ",need_expand);
				left->set_visible(lr_visibility);
				right->set_visible(lr_visibility);
			}
			if(need_expand && do_expand) {
				double space_left = expand_value - (y-spacing);
				double space_for_each = space_left/(n-2);
				for(int i=1;i<n-1;i++) {
					if(children[i] == nullptr) continue;
					//size
					Vector2 tmp = children[i]->get_size();
					tmp.y += space_for_each;
					children[i]->set_size(tmp);
					//position
					tmp = children[i]->get_position();
					tmp.y += space_for_each*(i-1);
					children[i]->set_position(tmp);
				}
			}
			delete[] children;
			delete[] button_children;
		} break;

		case NOTIFICATION_THEME_CHANGED: {
			update_minimum_size();
		} break;

		case NOTIFICATION_TRANSLATION_CHANGED:
		case NOTIFICATION_LAYOUT_DIRECTION_CHANGED: {
			queue_sort();
		} break;

		default: {
			AnimatedBar::_notification(p_what);
		} break;
	}
}

void AnimatedBar::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_INTERNAL_PROCESS: {
			process(get_process_delta_time());
		} break;

		case NOTIFICATION_READY: {
			ready();
		} break;

		default: {
			Container::_notification(p_what);
		} break;
	}
}

void AnimatedBar::set_to_subtract_value(int p_value) {
	to_subtract_value = p_value;
	set_process_internal(true);
	is_process = true;
}

void AnimatedBar::process(double delta) {
	//UtilityFunctions::print("_process");
	double _delta_speed = delta*60*speed;
	if(abs(subtracted_value-to_subtract_value)<_delta_speed) {
		subtracted_value = to_subtract_value;
		queue_sort();
		set_process_internal(!deactivate_process);
		is_process = false;
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

Vector2 HAnimatedBar::_get_minimum_size() const {
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

Vector2 VAnimatedBar::_get_minimum_size() const {
	Vector2 _min = Vector2(0,0);
	for(int i = 0;i<get_child_count();i++) {
		Control *child = Object::cast_to<Control>(get_child(i));
		if(child == nullptr) continue;
		Vector2 size = child->get_combined_minimum_size();
		if(size.x > _min.x) _min.x = size.x;
		if(size.y > _min.y) _min.y = size.y;
	}
	_min.y += spacing + 1;
	return _min;
}

void AnimatedBar::deactivate_focus() {
	focus = false;
	for(int i = 1;i<get_child_count()-1;i++) {
			BaseButton *child = Object::cast_to<BaseButton>(get_child(i));
			if (child == nullptr) continue;
			child->set_pressed_no_signal(false);
	}
}

void AnimatedBar::_on_button_pressed(int id,BaseButton *button) {
	if(button->is_pressed()) {
		if(focus) call_deferred("emit_signal","focus_changed",id);
		else call_deferred("emit_signal","focus_activated",id);
		for(int i = 1;i<get_child_count()-1;i++) {
			BaseButton *child = Object::cast_to<BaseButton>(get_child(i));
			if (child == nullptr) continue;
			child->set_pressed_no_signal(false);
		}
		button->set_pressed_no_signal(true);
		focus = true;
		return;
	} 
	emit_signal("focus_deactivated");
	focus = false;
	//UtilityFunctions::print(button->get_name(),"   ",id);
}

void HAnimatedBar::_on_left_pressed() {
	if(is_process) return; 
	if(get_child(first_child_id) != first_child) {
		first_child_id = 1;
		first_child = Object::cast_to<Control>(get_child(1));
		queue_sort();
		if(get_child_count() > 2) call_deferred("_on_left_pressed");
		return;
	}
	if(first_child_id <= 1 || first_child == nullptr) return;
	int size = get_size().x;
	size -= first_child->get_position().x;
	int i = first_child_id-1;
	int _size = size;
	double _lx = get_left_size().x;
	while (i>0) {
		Control *child = Object::cast_to<Control>(get_child(i));
		if(child == nullptr) {
			i--;
			continue;
		}
		double _x = child->get_position().x-_lx;
		if((-1)*(_x)<=_size) {
			size = (-1)*(_x);
			first_child = child;
			first_child_id = i;
			i--;
			continue;
		} 
		if((-1)*(_x+child->get_size().x)<=_size) size = _size;
		break;
	}
	set_to_subtract_value(to_subtract_value-size);
	//UtilityFunctions::print(first_child->get_name(),"   ",first_child_id,"   ",size);
	queue_sort();
}

void HAnimatedBar::_on_right_pressed() {
	if(is_process) return;
	if(get_child(first_child_id) != first_child) {
		first_child_id = 1;
		first_child = Object::cast_to<Control>(get_child(1));
		queue_sort();
		if(get_child_count() > 2) call_deferred("_on_right_pressed");
		return;
	}
	int n = get_child_count();
	if(first_child_id >= n-2 || first_child == nullptr) return;
	int size = get_size().x-get_right_size().x;
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
		set_to_subtract_value(to_subtract_value+size);
		//UtilityFunctions::print(first_child->get_name(),"   ",first_child_id,"   ",size);
		queue_sort();
		return;
	}
	to_subtract_value += _s_;
	//UtilityFunctions::print("   ",first_child_id,"   ",_s_);
	i = _i_;
	_size = get_size().x-get_right_size().x;
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
	set_to_subtract_value(to_subtract_value-size);
	//UtilityFunctions::print(first_child->get_name(),"   ",first_child_id,"   ",size,"   ",_size);
	queue_sort();
}

void VAnimatedBar::_on_left_pressed() {
	if(is_process) return;
	if(get_child(first_child_id) != first_child) {
		first_child_id = 1;
		first_child = Object::cast_to<Control>(get_child(1));
		queue_sort();
		if(get_child_count() > 2) call_deferred("_on_left_pressed");
		return;
	}
	if(first_child_id <= 1 || first_child == nullptr) return;
	int size = get_size().y;
	size -= first_child->get_position().y;
	int i = first_child_id-1;
	int _size = size;
	double _ly = get_left_size().y;
	while (i>0) {
		Control *child = Object::cast_to<Control>(get_child(i));
		if(child == nullptr) {
			i--;
			continue;
		}
		double _y = child->get_position().y-_ly;
		if((-1)*(_y)<=_size) {
			size = (-1)*(_y);
			first_child = child;
			first_child_id = i;
			i--;
			continue;
		} 
		if((-1)*(_y+child->get_size().y)<=_size) size = _size;
		break;
	}
	set_to_subtract_value(to_subtract_value-size);
	//UtilityFunctions::print(first_child->get_name(),"   ",first_child_id,"   ",size);
	queue_sort();
}

void VAnimatedBar::_on_right_pressed() {
	if(is_process) return;
	if(get_child(first_child_id) != first_child) {
		first_child_id = 1;
		first_child = Object::cast_to<Control>(get_child(1));
		queue_sort();
		if(get_child_count() > 2) call_deferred("_on_right_pressed");
		return;
	}
	int n = get_child_count();
	if(first_child_id >= n-2 || first_child == nullptr) return;
	int size = get_size().y-get_right_size().y;
	size -= first_child->get_position().y;
	int i = first_child_id+1;
	int _size = size;
	while (i<n-1) {
		Control *child = Object::cast_to<Control>(get_child(i));
		if(child == nullptr) {
			i++;
			continue;
		}
		if((child->get_position().y)<=_size) {
			size = (child->get_position().y);
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
		int y = (child->get_position().y+child->get_size().y);
		if((y)<=_size+size) {
			_s_ = y;
			_i_ = i;
			i++;
			continue;
		}
		set_to_subtract_value(to_subtract_value+size);
		//UtilityFunctions::print(first_child->get_name(),"   ",first_child_id,"   ",size);
		queue_sort();
		return;
	}
	to_subtract_value += _s_;
	//UtilityFunctions::print("   ",first_child_id,"   ",_s_);
	i = _i_;
	_size = get_size().y-get_right_size().y;
	while (i>0) {
		Control *child = Object::cast_to<Control>(get_child(i));
		if(child == nullptr) {
			i--;
			continue;
		}
		if((-1)*(child->get_position().y-_s_)<=_size) {
			size = (-1)*(child->get_position().y-_s_);
			first_child = child;
			first_child_id = i;
			i--;
			continue;
		} 
		size = _size;
		break;
	}
	set_to_subtract_value(to_subtract_value-size);
	//UtilityFunctions::print(first_child->get_name(),"   ",first_child_id,"   ",size,"   ",_size);
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
	//Vector2 ms = right->get_combined_minimum_size();
	queue_sort();
}

double AnimatedBar::get_speed() {
	return speed;
}

void AnimatedBar::set_speed(double p_speed) {
	speed = p_speed;
}

bool AnimatedBar::get_lr_visibility() {
	if(!after_ready) return bool(for_ready.lr_visibility);
	return lr_visibility;
}

int AnimatedBar::get_lr_visibility_v2() {
	if(!after_ready) return for_ready.lr_visibility;
	if(lr_auto_visibility == true) return 3;
	return int(lr_visibility);
}

void AnimatedBar::set_lr_visibility(int p_state) {
	if(!after_ready) {
		for_ready.lr_visibility = p_state;
		return;
	}
	if(p_state == 0) {
		lr_visibility = false;
		lr_auto_visibility = false;
	} else if(p_state == 1) {
		lr_visibility = true;
		lr_auto_visibility = false;
	} else {
		lr_auto_visibility = true;
		queue_sort();
		//UtilityFunctions::print("lr_auto_visibility = ",lr_auto_visibility);
		return;
	}
	emit_signal("minimum_size_changed");
	left->set_visible(lr_visibility);
	right->set_visible(lr_visibility);
}

bool AnimatedBar::get_custom_lr() {
	if(!after_ready) return for_ready.custom_lr;
	return custom_lr;
}

void AnimatedBar::set_custom_lr(bool is_enabled) {
	if(!after_ready) {
		for_ready.custom_lr = is_enabled;
		return;
	}
	if(custom_lr == is_enabled) return;
	custom_lr = is_enabled;
	queue_sort();
	//UtilityFunctions::print(custom_left,"   ",custom_right,"   ",custom_left == nullptr,"   ",custom_right == nullptr);
	if(!custom_lr) {
		left->set_as_top_level(false);
		//right->set_as_top_level(false);
		if(left->is_connected("pressed",Callable(this, "_on_left_pressed")))
			left->disconnect("pressed",Callable(this, "_on_left_pressed"));
		if(right->is_connected("pressed",Callable(this, "_on_right_pressed")))
			right->disconnect("pressed",Callable(this, "_on_right_pressed"));
		if(left->get_name() == StringName("__DefaultLeft__")) {
			remove_child(left);
			left->queue_free();
		}
		if(right->get_name() == StringName("__DefaultRight__")) {
			remove_child(right);
			right->queue_free();
		}
		left = memnew(Button);
		right = memnew(Button);
		left->set_name("__DefaultLeft__");
		right->set_name("__DefaultRight__");
		Button *l = Object::cast_to<Button>(left);
		l->set_text(_labels.left);
		Button *r = Object::cast_to<Button>(right);
		r->set_text(_labels.right);
		add_child(right);
		add_child(left);
		right->connect("pressed",Callable(this, "_on_right_pressed"));
		left->connect("pressed",Callable(this, "_on_left_pressed"));
		left->set_as_top_level(true);
		//right->set_as_top_level(true);
	} else {
		if(left->is_connected("pressed",Callable(this, "_on_left_pressed")))
			left->disconnect("pressed",Callable(this, "_on_left_pressed"));
		if(right->is_connected("pressed",Callable(this, "_on_right_pressed")))
			right->disconnect("pressed",Callable(this, "_on_right_pressed"));
		remove_child(left);
		remove_child(right);
		left -> queue_free();
		right -> queue_free();
		if(custom_left == nullptr) {
			left = memnew(Button);
			left->set_name("__DefaultLeft__");
			Button *l = Object::cast_to<Button>(left);
			l->set_text(_labels.left);
			add_child(left);
		} else {
			Node *par = custom_left->get_parent();
			if(par != this) custom_left->reparent(this);
			else {
				if(custom_left->is_connected("pressed",Callable(this, "_clip_child")))
					custom_left->disconnect("pressed",Callable(this, "_clip_child"));
				if(custom_left->is_connected("pressed",Callable(this, "_on_button_pressed")))
					custom_left->disconnect("pressed",Callable(this, "_on_button_pressed"));
			}
			left = custom_left;
		}
		if(custom_right == nullptr) {
			right = memnew(Button);
			right->set_name("__DefaultRight__");
			Button *r = Object::cast_to<Button>(right);
			r->set_text(_labels.right);
			add_child(right);
		} else {
			Node *par = custom_right->get_parent();
			if(par != this) custom_right->reparent(this);
			else {
				if(custom_right->is_connected("pressed",Callable(this, "_clip_child")))
					custom_right->disconnect("pressed",Callable(this, "_clip_child"));
				if(custom_right->is_connected("pressed",Callable(this, "_on_button_pressed")))
					custom_right->disconnect("pressed",Callable(this, "_on_button_pressed"));
			}
			right = custom_right;
		}
		right->connect("pressed",Callable(this, "_on_right_pressed"));
		left->connect("pressed",Callable(this, "_on_left_pressed"));
		left->set_as_top_level(true);
		//right->set_as_top_level(true);
	}
}

int AnimatedBar::get_options_quantity() const {
	return number_of_children;
}

AnimatedBar::ORIENTATION AnimatedBar::get_orientation() const {
	return ORIENTATION_UNDEFINED;
}

AnimatedBar::ORIENTATION HAnimatedBar::get_orientation() const {
	return ORIENTATION_HORIZONTAL;
}

AnimatedBar::ORIENTATION VAnimatedBar::get_orientation() const {
	return ORIENTATION_VERTICAL;
}

Vector2 HAnimatedBar::get_lr_size() const {
	if(!lr_visibility) return Vector2(0,0);
	Vector2 _siz = Vector2(spacing2*2,0);
	_siz += left->get_size();
	_siz.x += right->get_size().x;
	return _siz;
}

Vector2 HAnimatedBar::get_left_size() const {
	if(!lr_visibility) return Vector2(0,0);
	Vector2 _siz = Vector2(spacing2,0);
	_siz += left->get_size();
	return _siz;
}

Vector2 HAnimatedBar::get_right_size() const {
	if(!lr_visibility) return Vector2(0,0);
	Vector2 _siz = Vector2(spacing2,0);
	_siz += right->get_size();
	return _siz;
}

Vector2 VAnimatedBar::get_lr_size() const {
	if(!lr_visibility) return Vector2(0,0);
	Vector2 _siz = Vector2(0,spacing2*2);
	_siz += left->get_size();
	_siz.y += right->get_size().y;
	return _siz;
}

Vector2 VAnimatedBar::get_left_size() const {
	if(!lr_visibility) return Vector2(0,0);
	Vector2 _siz = Vector2(0,spacing2);
	_siz += left->get_size();
	return _siz;
}

Vector2 VAnimatedBar::get_right_size() const {
	if(!lr_visibility) return Vector2(0,0);
	Vector2 _siz = Vector2(0,spacing2);
	_siz += right->get_size();
	return _siz;
}

Vector2 AnimatedBar::get_lr_size() const {
	if(!lr_visibility) return Vector2(0,0);
	Vector2 _siz = left->get_size();
	_siz += right->get_size();
	return _siz;
}

Vector2 AnimatedBar::get_left_size() const {
	if(!lr_visibility) return Vector2(0,0);
	return left->get_size();
}

Vector2 AnimatedBar::get_right_size() const {
	if(!lr_visibility) return Vector2(0,0);
	return right->get_size();
}

NodePath AnimatedBar::get_custom_left() {
	if(!after_ready) return for_ready.left_path;
	if(custom_left == nullptr) return NodePath("");
	String path = "./";
	path += custom_left->get_name();
	return NodePath(path);
}

NodePath AnimatedBar::get_custom_right() {
	if(!after_ready) return for_ready.right_path;
	if(custom_right == nullptr) return NodePath("");
	String path = "./";
	path += custom_right->get_name();
	return NodePath(path);
}

void AnimatedBar::set_custom_left(NodePath p_path) {
	if(!after_ready) {
		for_ready.left_path = p_path;
		return;
	}
	BaseButton *_custom_left = Object::cast_to<BaseButton>(get_node_or_null(p_path));
	//UtilityFunctions::print(this,"   ",get_node_or_null(NodePath(".")));
	if(_custom_left == nullptr) {
		UtilityFunctions::print_rich("[color=VIOLET]",String(L"●")," Control++:  Custom left node path have to refer to node inheriting from the BaseButton class.","[color=SNOW]");
		return;
	}
	Node *par = _custom_left->get_parent();
	if(par != this) {
		if(Engine::get_singleton()->is_editor_hint()) {
			UtilityFunctions::print_rich("[color=VIOLET]",String(L"●")," Control++:  Custom left node path have to refer to ",get_name(),"'s child.","[color=SNOW]");
			_custom_left = nullptr;
			return;
		}
		_custom_left->reparent(this);
	}
	custom_left = _custom_left;
	if(custom_lr) {
		left->set_as_top_level(false);
		if(left->is_connected("pressed",Callable(this, "_on_left_pressed")))
			left->disconnect("pressed",Callable(this, "_on_left_pressed"));
		if(left->get_name() == StringName("__DefaultLeft__")) {
			remove_child(left);
			left->queue_free();
		}
		left = custom_left;
		left->connect("pressed",Callable(this, "_on_left_pressed"));
		left->set_as_top_level(true);
		queue_sort();
	}
}

void AnimatedBar::set_custom_right(NodePath p_path) {
	if(!after_ready) {
		for_ready.right_path = p_path;
		return;
	}
	BaseButton *_custom_right = Object::cast_to<BaseButton>(get_node_or_null(p_path));
	//UtilityFunctions::print(custom_right,"   ",custom_right == nullptr,"   ",p_path);
	if(_custom_right == nullptr) {
		UtilityFunctions::print_rich("[color=VIOLET]",String(L"●")," Control++:  Custom right node path have to refer to node inheriting from the BaseButton class.","[color=SNOW]");
		return;
	}
	Node *par = _custom_right->get_parent();
	if(par != this) {
		if(Engine::get_singleton()->is_editor_hint()) {
			UtilityFunctions::print_rich("[color=VIOLET]",String(L"●")," Control++:  Custom right node path have to refer to ",get_name(),"'s child.","[color=SNOW]");
			_custom_right = nullptr;
			return;
		}
		_custom_right->reparent(this);
	}
	custom_right = _custom_right;
	if(custom_lr) {
		//right->set_as_top_level(false);
		if(right->is_connected("pressed",Callable(this, "_on_right_pressed")))
			right->disconnect("pressed",Callable(this, "_on_right_pressed"));
		if(right->get_name() == StringName("__DefaultRight__")) {
			remove_child(right);
			right->queue_free();
		}
		right = custom_right;
		right->connect("pressed",Callable(this, "_on_right_pressed"));
		//right->set_as_top_level(true);
		queue_sort();
	}
}

bool AnimatedBar::is_remaining_space_filled() {
	return do_expand;
}

void AnimatedBar::set_fill_remaining_space(bool is_enabled) {
	if(do_expand == is_enabled) return;
	do_expand = is_enabled;
	queue_sort();
}

bool AnimatedBar::get_deactivate_process() {
	return deactivate_process;
}

void AnimatedBar::set_deactivate_process(bool is_enabled) {
	deactivate_process = is_enabled;
}

PackedStringArray AnimatedBar::_get_configuration_warnings() const {
	PackedStringArray warnings;
	int n = get_child_count();
	if (n <= 2) {
		warnings.push_back(RTR("AnimatedBar does not have child. Please add some children inheriting from the BaseButton class to allow AnimatedBar to work properly"));
		return warnings;
	}
	for(int i=1;i<n-1;i++) {
		BaseButton *child = Object::cast_to<BaseButton>(get_child(i));
		if (child == nullptr) {
			warnings.push_back(RTR(get_child(i)->get_name()+String(" does not inherit from the BaseButton class. Please remove it if it isn't necessary.")));
		}
	}
	return warnings;
}

HAnimatedBar::HAnimatedBar() {
	Button *l = Object::cast_to<Button>(left);
	l->set_text(L"←");
	Button *r = Object::cast_to<Button>(right);
	r->set_text(L"→");
	_labels.left = L"←";
	_labels.right = L"→";
}

VAnimatedBar::VAnimatedBar() {
	Button *l = Object::cast_to<Button>(left);
	l->set_text("↑");
	Button *r = Object::cast_to<Button>(right);
	r->set_text("↓");
	_labels.left = "↑";
	_labels.right = "↓";
}

HAnimatedBar::~HAnimatedBar(){}
VAnimatedBar::~VAnimatedBar(){}