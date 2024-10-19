#include "animated_tab_container.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/rendering_server.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void AnimatedTabContainer::_bind_methods() {
	// Signals Conections Functions
	ClassDB::bind_method(D_METHOD("on_focus_changed","p_id","p_bar_id"), &AnimatedTabContainer::on_focus_changed);
	ClassDB::bind_method(D_METHOD("on_focus_activated","p_id","p_bar_id"), &AnimatedTabContainer::on_focus_activated);
	ClassDB::bind_method(D_METHOD("on_focus_deactivated"), &AnimatedTabContainer::on_focus_deactivated);
	ClassDB::bind_method(D_METHOD("clip_child","p_child"), &AnimatedTabContainer::clip_child);
	// Speed Property
	ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &AnimatedTabContainer::set_speed);
	ClassDB::bind_method(D_METHOD("get_speed"), &AnimatedTabContainer::get_speed);
	ClassDB::add_property("AnimatedTabContainer", PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");
}

AnimatedTabContainer::AnimatedTabContainer() {
	// Initialize any variables here.
	number_of_animated_bars = 0;
	//set_clip_contents(true);
}

AnimatedTabContainer::~AnimatedTabContainer() {
	// Add your cleanup here.
}

void AnimatedTabContainer::clip_child(Control* child) {
	RID _rid = child->get_canvas_item();
	RenderingServer::get_singleton()->canvas_item_set_custom_rect(_rid,true,Rect2(-child->get_position(),child->get_size()));
	RenderingServer::get_singleton()->canvas_item_set_clip(_rid,true);
}

double AnimatedTabContainer::get_speed() {
	return speed;
}

void AnimatedTabContainer::set_speed(double p_speed) {
	speed = p_speed;
}

void AnimatedTabContainer::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_SORT_CHILDREN: {
			int n = get_child_count();
			number_of_animated_bars = 0;
			_y = 0;
			_x = 0;
			AnimatedBar::ORIENTATION _orient;
			for(int i = n-1;i>=0;i--) {
				AnimatedBar *child = Object::cast_to<AnimatedBar>(get_child(i));
				if(child == nullptr) continue;
				number_of_animated_bars++;
				move_child(child,n-number_of_animated_bars);
				_orient = child->get_orientation();
				switch (_orient) {
					case AnimatedBar::ORIENTATION_HORIZONTAL: {
						_y += child->get_minimum_size().y;
						child->set_position(Vector2(0,get_size().y-_y));
						child->set_size(Vector2(get_size().x,child->get_minimum_size().y));
					} break;
					case AnimatedBar::ORIENTATION_VERTICAL: {
						_x += child->get_minimum_size().x;
						child->set_position(Vector2(get_size().x-_x,0));
						child->set_size(Vector2(child->get_minimum_size().x,get_size().y));
					} break;
					default: {}
				}
				Array a;
				a.append(n-number_of_animated_bars);
				if(child->is_connected("focus_changed",Callable(this, "on_focus_changed"))) {
					child->disconnect("focus_changed",Callable(this, "on_focus_changed"));
					child->disconnect("focus_activated",Callable(this, "on_focus_activated"));
					child->disconnect("focus_deactivated",Callable(this, "on_focus_deactivated"));
				}
				Error err[3];
				err[0] = child->connect("focus_changed",Callable(this, "on_focus_changed").bindv(a));
				err[1] = child->connect("focus_activated",Callable(this, "on_focus_activated").bindv(a));
				err[2] = child->connect("focus_deactivated",Callable(this, "on_focus_deactivated"));
				for(int e=0;e<3;e++) 
					if(err[e] != OK) UtilityFunctions::print_rich("[color=VIOLET]",String(L"●")," Control++:  Error ",err[e]," while connecting ",child,"[color=SNOW]");
			}
			Vector2 _size = get_size();
			for(int i = 0;i<n-number_of_animated_bars;i++) {
				Control *child = Object::cast_to<Control>(get_child(i));
				if(child == nullptr) continue;
				RID _rid = child->get_canvas_item();
				child->set_size(Vector2(_size.x-_x,_size.y-_y));
				if(curent_tab==child) {
					child->set_position(Vector2(0,_size.y-_y-focus_status));
					//UtilityFunctions::print(child,"   is on focus   focus_status = ",focus_status);
				}
				else child->set_position(Vector2(0,_size.y-_y));
				RenderingServer::get_singleton()->canvas_item_set_custom_rect(_rid,true,Rect2(-child->get_position(),child->get_size()));
				RenderingServer::get_singleton()->canvas_item_set_clip(_rid,true);
				if(child->is_connected("draw",Callable(this, "clip_child"))) continue;
				Array a;
				a.append(child);
				Error err1 = child->connect("draw",Callable(this, "clip_child").bindv(a));
				if(err1 != OK) UtilityFunctions::print_rich("[color=VIOLET]",String(L"●")," Control++:  Error ",err1," while connecting ",child,"[color=SNOW]");
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

		case NOTIFICATION_INTERNAL_PROCESS: {
			process(get_process_delta_time());
		} break;
	}
}

void AnimatedTabContainer::process(double delta) {
	if((focus_status == get_size().y-_y || focus_status == 0) && curent_tab == next_tab) {
		set_process_internal(false);
		return;
	}
	if(focus_status > get_size().y-_y) {
		focus_status = get_size().y-_y;
		queue_sort();
		//UtilityFunctions::print("focus_status > get_size().y-_y");
		return;
	}
	if(focus_status < 0) {
		focus_status = 0;
		queue_sort();
		//UtilityFunctions::print("focus_status < 0");
		return;
	}
	double delta_speed = delta*60*speed;
	if(next_tab == nullptr && focus_status != 0) {
		focus_status -= delta_speed;
		curent_tab->set_position(Vector2(0,curent_tab->get_position().y+delta_speed));
		clip_child(curent_tab);
		//UtilityFunctions::print("next_tab == nullptr && focus_status != 0");
		return;
	}
	if(curent_tab != next_tab) {
		curent_tab = next_tab;
		queue_sort();
	}
	if(curent_tab == nullptr) return;
	focus_status += delta_speed;
	curent_tab->set_position(Vector2(0,curent_tab->get_position().y-delta_speed));
	clip_child(curent_tab);
	//UtilityFunctions::print("curent_tab == next_tab");
}

Vector2 AnimatedTabContainer::_get_minimum_size() const {
	Vector2 _min = Vector2(0,0);
	int n = get_child_count();
	if(number_of_animated_bars > n) return _min;
	for(int i = 0;i<n-number_of_animated_bars;i++) {
		Control *child = Object::cast_to<Control>(get_child(i));
		if(child == nullptr) continue;
		Vector2 size = child->get_combined_minimum_size();
		if(size.x > _min.x) _min.x = size.x;
		if(size.y > _min.y) _min.y = size.y;
	}
	for(int i = n-number_of_animated_bars;i<n;i++) {
		AnimatedBar *child = Object::cast_to<AnimatedBar>(get_child(i));
		if(child == nullptr) continue;
		Vector2 size = child->get_combined_minimum_size();
		AnimatedBar::ORIENTATION _orient = child->get_orientation();
		switch (_orient) {
			case AnimatedBar::ORIENTATION_HORIZONTAL: {
				size.x += child->get_lr_size().x;
				_min.y += size.y;
				if(size.x > _min.x) _min.x = size.x;
			} break;
			case AnimatedBar::ORIENTATION_VERTICAL: {
				size.y += child->get_lr_size().y;
				_min.x += size.x;
				if(size.y > _min.y) _min.y = size.y;
			} break;
			default: {}
		}
	}
	return _min;
}

void AnimatedTabContainer::on_focus_activated(int p_tab_id,int p_bar_id) {
	int n = get_child_count();
	p_tab_id--;
	//UtilityFunctions::print("p_tab_id = ",p_tab_id,"   p_bar_id = ",p_bar_id,"   child_count = ",n,"   number_of_animated_bars = ",number_of_animated_bars);
	if(is_activated) curent_animated_bar->deactivate_focus();
	for(int i=p_bar_id+1;i<n;i++) {
		AnimatedBar *tmp = Object::cast_to<AnimatedBar>(get_child(i));
		p_tab_id += tmp->get_options_quantity();
		//UtilityFunctions::print(tmp,"   ",i," - 1 = ",p_bar_id);
	}
	if(p_tab_id >= n - number_of_animated_bars) {
		curent_animated_bar = Object::cast_to<AnimatedBar>(get_child(p_bar_id));
		curent_animated_bar->deactivate_focus();
		on_focus_deactivated();
		return;
	}
	//UtilityFunctions::print("p_bar_id = ",p_bar_id);
	next_tab = Object::cast_to<Control>(get_child(p_tab_id));
	set_process_internal(true);
	curent_animated_bar = Object::cast_to<AnimatedBar>(get_child(p_bar_id));
	//UtilityFunctions::print(next_tab,"   ",p_tab_id);
	queue_sort();
	is_activated = true;
}

void AnimatedTabContainer::on_focus_changed(int p_tab_id,int p_bar_id) {
	int n = get_child_count();
	p_tab_id--;
	for(int i=p_bar_id+1;i<n;i++) {
		AnimatedBar *tmp = Object::cast_to<AnimatedBar>(get_child(i));
		p_tab_id += tmp->get_options_quantity();
		//UtilityFunctions::print(tmp,"   ",i," - 1 = ",p_bar_id);
	}
	if(p_tab_id >= n - number_of_animated_bars) {
		curent_animated_bar = Object::cast_to<AnimatedBar>(get_child(p_bar_id));
		curent_animated_bar->deactivate_focus();
		on_focus_deactivated();
		return;
	}
	next_tab = Object::cast_to<Control>(get_child(p_tab_id));
	set_process_internal(true);
	//UtilityFunctions::print(next_tab,"   ",p_tab_id);
	queue_sort();
}

void AnimatedTabContainer::on_focus_deactivated() {
	//UtilityFunctions::print(next_tab,"   ",curent_animated_bar);
	is_activated = false;
	next_tab = nullptr;
	set_process_internal(true);
	curent_animated_bar = nullptr;
	//UtilityFunctions::print(next_tab,"   ",curent_animated_bar);
	queue_sort();
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
