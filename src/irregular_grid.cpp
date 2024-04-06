#include "irregular_grid.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/rendering_server.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;
using namespace control_plus_plus;

void IrregularGridContainer::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_spacing", "p_spacing"), &IrregularGridContainer::set_spacing);
	ClassDB::bind_method(D_METHOD("get_spacing"), &IrregularGridContainer::get_spacing);
	ClassDB::add_property("IrregularGridContainer", PropertyInfo(Variant::FLOAT, "spacing"), "set_spacing", "get_spacing");
}

IrregularGrid::IrregularGrid() {
	// Initialize any variables here.
	spacing = 0.0;
}

IrregularGrid::~IrregularGrid() {
	// Add your cleanup here.
}

void IrregularGrid::Add(Control *child) {
	int j = GRID.size()-1;
	Vector2 ms = child->get_combined_minimum_size();
	if(j < 0) {
		irregular_grid_element a;
		a.x = ms.x;
		a.count = 1;
		a.aditional = 0;
		GRID.push_back(a);
		return;
	}
	if(GRID[j].x + ms.x + spacing < get_size().x) {
		GRID[j].x += ms.x + spacing;
		GRID[j].count++;
	} else {
		irregular_grid_element a;
		a.x = ms.x;
		a.count = 1;
		a.aditional = 0;
		GRID.push_back(a);
	}
}

void IrregularGrid::Add_ExpandableButton(ExpandableButton *child) {
	int j = GRID.size()-1;
	// Notice we use Vector2 as 2 difrend variables not nodes size
	// X - childs base width
	// Y - childs expansion width
	Vector2 ms = child->get_base_minimum_size();
	ms = ms.max(child->get_custom_minimum_size());
	ms.y = child->get_expansion_size() - child->get_expansion_indentation();
	if(ms.x + ms.y < child->get_combined_minimum_size().x) {
		Add(child);
		return;
	}
	if(j < 0) {
		irregular_grid_element a;
		a.x = ms.x + ms.y;
		a.count = 1;
		a.aditional = ms.y + 1;
		GRID.push_back(a);
		return;
	}
	float tmp = 0.0;
	if(GRID[j].aditional < ms.y + 1) {
		tmp = ms.y - GRID[j].aditional;
	}
	if(GRID[j].x + ms.x + tmp + spacing < get_size().x) {
		GRID[j].x += ms.x + spacing + tmp;
		GRID[j].aditional = ms.y + 1;
		GRID[j].count++;
	} else {
		irregular_grid_element a;
		a.x = ms.x + ms.y;
		a.count = 1;
		a.aditional = ms.y + 1;
		GRID.push_back(a);
	}
}

void IrregularGrid::Clear() {
	GRID.clear();
}

void IrregularGrid::sort() {
	Clear();
	int n = get_child_count();
	for(int i=0;i<n;i++) {
		Control *child = Object::cast_to<Control>(get_child(i));
		if(child == nullptr) continue;
		ExpandableButton *exp_button = Object::cast_to<ExpandableButton>(child);
		if(exp_button == nullptr) Add(child);
		else Add_ExpandableButton(exp_button);
	}
}

void IrregularGrid::rearrange(bool from_exp_button) {
	//if(from_exp_button) {
	//	rearrange_with_b();
	//	return;
	//}
	sort();
	int error_handler = get_child_count();
	int n = GRID.size();
	int i = 0;
	double _y = 0.0;
	for(int j=0;j<n;j++) {
		double used = 0.0;
		int ii = 0;
		double height = 0.0;
		for(int tmp=0;tmp<GRID[j].count;tmp++) {
			if(i+ii >= error_handler) continue;
			Control *child = Object::cast_to<Control>(get_child(i+ii));
			ii++;
			if(child == nullptr) continue;
			Vector2 ms = child->get_combined_minimum_size();
			used += ms.x + spacing;
			if(height < ms.y) height = ms.y;
		}
		used -= spacing;
		double free_for_one = (get_size().x-used)/GRID[j].count;
		used = 0.0;
		for(int tmp=0;tmp<GRID[j].count;tmp++) {
			if(i >= error_handler) continue;
			Control *child = Object::cast_to<Control>(get_child(i));
			i++;
			if(child == nullptr) continue;
			Vector2 ms = child->get_combined_minimum_size();
			ms.x += free_for_one;
			ms.y = height;
			child->set_size(ms);
			child->set_position(Vector2(used,_y));
			used += ms.x + spacing;
			ExpandableButton *exp_b = Object::cast_to<ExpandableButton>(child);
			if(exp_b != nullptr) exp_b->queue_redraw();
		}
		_y += height + spacing;
	}
}

void IrregularGrid::rearrange_with_b() {
	UtilityFunctions::print("rearrange_with_b");
	int error_handler = get_child_count();
	int n = GRID.size();
	int i = 0;
	double _y = 0.0;
	for(int j=0;j<n;j++) {
		double used = 0.0;
		int ii = 0;
		double height = 0.0;
		for(int tmp=0;tmp<GRID[j].count;tmp++) {
			if(i+ii >= error_handler) continue;
			Control *child = Object::cast_to<Control>(get_child(i+ii));
			ii++;
			if(child == nullptr) continue;
			Vector2 ms = child->get_combined_minimum_size();
			ExpandableButton *exp_b = Object::cast_to<ExpandableButton>(child);
			if(exp_b != nullptr) ms = ms.max(exp_b->_get_minimum_size());
			used += ms.x + spacing;
			if(height < ms.y) height = ms.y;
		}
		used -= spacing;
		double free_for_one = (get_size().x-used)/GRID[j].count;
		used = 0.0;
		for(int tmp=0;tmp<GRID[j].count;tmp++) {
			if(i >= error_handler) continue;
			Control *child = Object::cast_to<Control>(get_child(i));
			i++;
			if(child == nullptr) continue;
			Vector2 ms = child->get_combined_minimum_size();
			ExpandableButton *exp_b = Object::cast_to<ExpandableButton>(child);
			if(exp_b != nullptr) ms = ms.max(exp_b->_get_minimum_size());
			ms.x += free_for_one;
			ms.y = height;
			if(exp_b != nullptr) UtilityFunctions::print(exp_b->get_combined_minimum_size()," + ",exp_b->_get_minimum_size()," = ",ms);
			child->set_size(ms);
			child->set_position(Vector2(used,_y));
			//UtilityFunctions::print(ms," = ",child->get_size(),"      ",Vector2(used,_y)," = ",child->get_position());
			used += ms.x + spacing;
		}
		_y += height + spacing;
	}
}

void IrregularGridContainer::set_spacing(double p_spacing) {
	spacing = p_spacing;
	queue_sort();
}
	
double IrregularGridContainer::get_spacing() {
	return spacing;
}

void IrregularGridContainer::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_SORT_CHILDREN: {
			rearrange();
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

IrregularGridContainer::IrregularGridContainer() {}
IrregularGridContainer::~IrregularGridContainer() {}
