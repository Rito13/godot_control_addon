#include "expandable_button.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void ExpandableButton::_bind_methods() {
}

ExpandableButton::ExpandableButton() {
	RevisedButton::set_is_text_off(true);

	// Initialize internal childs
	expand_parent = memnew(Control);
	expand = memnew(RevisedButton);
	idle_time_timer = memnew(Timer);

    // Create internal tree
	add_child(expand_parent, false, INTERNAL_MODE_FRONT);
	expand_parent->add_child(expand, false, INTERNAL_MODE_FRONT);
	expand_parent->add_child(idle_time_timer, false, INTERNAL_MODE_FRONT);

	// Setup childs
	idle_time_timer->set_one_shot(true);
	expand_parent->set_clip_contents(true);
    expand_parent->set_mouse_filter(Control::MouseFilter::MOUSE_FILTER_IGNORE);
	Error err1 = idle_time_timer->connect("timeout", Callable(this, "on_timer_out"));
}

ExpandableButton::~ExpandableButton() {
	expand_parent->queue_free();
	expand->queue_free();
	idle_time_timer->queue_free();
}

void ExpandableButton::_process(double delta) {
    RevisedButton::_process(delta);
}

void ExpandableButton::set_is_text_off(bool p_status) {
    is_text_off = p_status;
}

bool ExpandableButton::get_is_text_off() {
    return is_text_off;
}

void ExpandableButton::set_expand_size(int p_size) {
    expand_size = p_size;
}

int ExpandableButton::get_expand_size() {
    return expand_size;
}
