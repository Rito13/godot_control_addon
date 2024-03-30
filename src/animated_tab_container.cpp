#include "animated_tab_container.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/rendering_server.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void AnimatedTabContainer::_bind_methods() {
	// Signals Conections Functions
	ClassDB::bind_method(D_METHOD("on_focus_changed","p_id"), &AnimatedTabContainer::on_focus_changed);
	ClassDB::bind_method(D_METHOD("on_focus_activated","p_id"), &AnimatedTabContainer::on_focus_activated);
	ClassDB::bind_method(D_METHOD("on_focus_deactivated","p_id"), &AnimatedTabContainer::on_focus_deactivated);
	ClassDB::bind_method(D_METHOD("clip_child","p_child"), &AnimatedTabContainer::clip_child);
}

AnimatedTabContainer::AnimatedTabContainer() {
	// Initialize any variables here.
	number_of_animated_bars = 0;
}

AnimatedTabContainer::~AnimatedTabContainer() {
	// Add your cleanup here.
}

void AnimatedTabContainer::clip_child(Control* child) {
	RID _rid = child->get_canvas_item();
	RenderingServer::get_singleton()->canvas_item_set_custom_rect(_rid,true,Rect2(-child->get_position(),child->get_size()));
	RenderingServer::get_singleton()->canvas_item_set_clip(_rid,true);
}

void AnimatedTabContainer::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_SORT_CHILDREN: {
			int n = get_child_count();
			number_of_animated_bars = 0;
			double _y = 0;
			for(int i = 0;i<n;i++) {
				AnimatedBar *child = Object::cast_to<AnimatedBar>(get_child(i));
				if(child == nullptr) continue;
				move_child(child,number_of_animated_bars);
				number_of_animated_bars++;
				double _x = child->get_left_size().x;
				_y += child->get_minimum_size().y;
				child->set_position(Vector2(_x,get_size().y-_y));
				Vector2 new_siz = Vector2(0,child->get_minimum_size().y);
				new_siz.x = get_size().x-child->get_lr_size().x;
				child->set_size(new_siz);
				Array a;
				a.append(number_of_animated_bars-1);
				if(child->is_connected("focus_changed",Callable(this, "on_focus_changed"))) continue;
				Error err1 = child->connect("focus_changed",Callable(this, "on_focus_changed").bindv(a));
				err1 = child->connect("focus_activated",Callable(this, "on_focus_activated").bindv(a));
				err1 = child->connect("focus_deactivated",Callable(this, "on_focus_deactivated"));
			}
			Vector2 _size = get_size();
			for(int i = number_of_animated_bars;i<n;i++) {
				Control *child = Object::cast_to<Control>(get_child(i));
				if(child == nullptr) continue;
				RID _rid = child->get_canvas_item();
				child->set_size(Vector2(_size.x,_size.y-_y));
				if(curent_tab==child) child->set_position(Vector2(0,0));
				else child->set_position(Vector2(0,_size.y-_y));
				RenderingServer::get_singleton()->canvas_item_set_custom_rect(_rid,true,Rect2(-child->get_position(),child->get_size()));
				RenderingServer::get_singleton()->canvas_item_set_clip(_rid,true);
				if(child->is_connected("draw",Callable(this, "clip_child"))) continue;
				Array a;
				a.append(child);
				Error err1 = child->connect("draw",Callable(this, "clip_child").bindv(a));
			}
		} break;
		/*
		case NOTIFICATION_DRAW: {
			int n = get_child_count();
			for(int i = number_of_animated_bars;i<n;i++) {
				Control *child = Object::cast_to<Control>(get_child(i));
				if(child == nullptr) continue;
				
			}
		} break;
		*/
		case NOTIFICATION_THEME_CHANGED: {
			update_minimum_size();
		} break;

		case NOTIFICATION_TRANSLATION_CHANGED:
		case NOTIFICATION_LAYOUT_DIRECTION_CHANGED: {
			queue_sort();
		} break;
	}
}

void AnimatedTabContainer::_process(double delta) {
	// Do Something
}

Vector2 AnimatedTabContainer::_get_minimum_size() const {
	Vector2 _min = Vector2(0,0);
	int n = get_child_count();
	if(number_of_animated_bars > n) return _min;
	for(int i = number_of_animated_bars;i<n;i++) {
		Control *child = Object::cast_to<Control>(get_child(i));
		if(child == nullptr) continue;
		Vector2 size = child->get_combined_minimum_size();
		if(size.x > _min.x) _min.x = size.x;
		if(size.y > _min.y) _min.y = size.y;
	}
	for(int i = 0;i<number_of_animated_bars;i++) {
		AnimatedBar *child = Object::cast_to<AnimatedBar>(get_child(i));
		if(child == nullptr) continue;
		Vector2 size = child->get_combined_minimum_size();
		size.x += child->get_lr_size().x;
		_min.y += size.y;
		if(size.x > _min.x) _min.x = size.x;
	}
	return _min;
}

void AnimatedTabContainer::on_focus_activated(int p_tab_id,int p_bar_id) {
	if(is_activated) curent_animated_bar->deactivate_focus();
	curent_tab = Object::cast_to<Control>(get_child(p_tab_id+number_of_animated_bars));
	curent_animated_bar = Object::cast_to<AnimatedBar>(get_child(p_bar_id));
}

void AnimatedTabContainer::on_focus_changed(int p_tab_id,int p_bar_id) {
	curent_tab = Object::cast_to<Control>(get_child(p_tab_id+number_of_animated_bars));
}

void AnimatedTabContainer::on_focus_deactivated() {
	is_activated = false;
	curent_tab = nullptr;
	curent_animated_bar = nullptr;
}

PackedStringArray AnimatedTabContainer::_get_configuration_warnings() const {
	PackedStringArray warnings;
	int n = get_child_count();
	if (n == 0) { 
		warnings.push_back(RTR("AnimatedTabContainer does not have child. Please add some children inheriting from the Control class to allow AnimatedTabContainer to work properly"));
		return warnings;
	}
	bool tmp = true;
	for(int i=0;i<n;i++) {
		AnimatedBar *child = Object::cast_to<AnimatedBar>(get_child(i));
		if (child != nullptr) {
			tmp = false;
			break;
		}
	}
	if(tmp) warnings.push_back(RTR("AnimatedTabContainer does not have child inheriting from the AnimatedBar class. Please add one or more to allow AnimatedTabContainer to work properly"));
	return warnings;
}
