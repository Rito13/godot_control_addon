#include "better_scroll.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/translation_server.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <cmath>

using namespace godot;

String RTR(const String &p_text, const String &p_context = String()) {
	if (TranslationServer::get_singleton()) {
		String rtr = TranslationServer::get_singleton()->translate(p_text, p_context);
		if (rtr.is_empty() || rtr == p_text) {
			return TranslationServer::get_singleton()->translate(p_text, p_context);
		} else {
			return rtr;
		}
	}

	return p_text;
}

void AutoScroll::_bind_methods() {
    // Add methods avaible in gdscript here.
    ClassDB::bind_method(D_METHOD("scroll_to","value"), &AutoScroll::scroll_to);
    ClassDB::bind_method(D_METHOD("is_scrolling"), &AutoScroll::is_scrolling);
    // Speed property
    ClassDB::bind_method(D_METHOD("set_speed","speed"), &AutoScroll::set_speed);
	ClassDB::bind_method(D_METHOD("get_speed"), &AutoScroll::get_speed);
    ClassDB::add_property("AutoScroll", PropertyInfo(Variant::INT, "speed"), "set_speed", "get_speed");
    // Auto Min Value property
    ClassDB::bind_method(D_METHOD("set_auto_min_value","value"), &AutoScroll::set_auto_min_value);
	ClassDB::bind_method(D_METHOD("get_auto_min_value"), &AutoScroll::get_auto_min_value);
    ClassDB::add_property("AutoScroll", PropertyInfo(Variant::FLOAT, "auto_min_value"), "set_auto_min_value", "get_auto_min_value");
}

AutoScroll::AutoScroll() {
	// Initialize any variables here.
}

AutoScroll::~AutoScroll() {
	// Add your cleanup here.
}

bool AutoScroll::is_scrolling() {
    return scrolling;
}

void AutoScroll::a_slide(Range *range_object, double step) {
    double value = range_object->get_value();
    if(value < custom_min) {
        value = range_object->get_max();
        if(step>0) step=0;
    }
    else if(value > range_object->get_max()) {
        value = custom_min;
        if(step<0) step=0;
    }
    if(step < range_object->get_step()) {
        minus_step = step - range_object->get_step();
        step = range_object->get_step();
    }
    if(end_value<range_object->get_value()) range_object->set_value(value - step);
    else range_object->set_value(value + step);
    //UtilityFunctions::print(value,"   ",step,"   ",scrolling,"   ",end_value);
}

void AutoScroll::set_speed(double p_speed) {
    if(p_speed > 0) speed = p_speed;
    else speed = 1;
}

double AutoScroll::get_speed() {
    if(speed <= 0) return 1;
    return speed;
}

void AutoScroll::set_auto_min_value(double p_value) {
    if(p_value == -INFINITY) {
        use_custom_min = false;
        return;
    }
    use_custom_min = true;
    Range *range_object = Object::cast_to<Range>(get_parent());
    if (range_object == nullptr) {
        custom_min = p_value;
        custom_min_to_reset = true;
        return;
    }
    double r_min = range_object->get_min();
    double r_max = range_object->get_max();
    if(p_value<r_min) p_value = r_min;
    else if(p_value>r_max) p_value = r_max;
    custom_min = p_value;
}

double AutoScroll::get_auto_min_value() {
    if(use_custom_min) return custom_min;
    else return - INFINITY;
}

void AutoScroll::scroll_to(double p_value) {
    Range *range_object = Object::cast_to<Range>(get_parent());
    if (range_object == nullptr) return;
    if (custom_min_to_reset) set_auto_min_value(custom_min);
    if(!use_custom_min) custom_min = range_object->get_min();
    double step = range_object->get_step();
    //UtilityFunctions::print(p_value,"  ",range_object->get_max());
    if(p_value < custom_min) p_value = custom_min;
    else if(p_value > range_object->get_max()) p_value = range_object->get_max();
    if(step!=0) {
        p_value = p_value-std::fmod(p_value,step);
    }
    end_value = p_value;
    scrolling = true;
    set_process_internal(true);
}

void AutoScroll::_notification(int p_what) {
	switch (p_what) {
        case NOTIFICATION_INTERNAL_PROCESS: {
			process(get_process_delta_time());
		} break;

		default: {
			Control::_notification(p_what);
		} break;
	}
}

void AutoScroll::process(double delta) {
    if(!scrolling) {
        set_process_internal(false);
        return;
    }
    Range *range_object = Object::cast_to<Range>(get_parent());
    if (range_object == nullptr) return;
    if (custom_min_to_reset) set_auto_min_value(custom_min);
    if(!use_custom_min) custom_min = range_object->get_min();
    minus_step += speed*delta;
    if(minus_step<=0) return;
    //UtilityFunctions::print(end_value);
    if(minus_step>speed*delta) {
        minus_step = speed*delta;
    }
    a_slide(range_object,minus_step);
    if((end_value-range_object->get_page())==range_object->get_value()) scrolling = false;
    if(abs((end_value-range_object->get_page())-range_object->get_value())<speed*delta) scrolling = false;
    if(end_value > range_object->get_max()) end_value = range_object->get_max();
    //UtilityFunctions::print(end_value,"  ",range_object->get_value(),"  ",speed,"   ",delta,"  ",range_object->get_max());
}

PackedStringArray AutoScroll::_get_configuration_warnings() const {
	PackedStringArray warnings;

	Range *range_object = Object::cast_to<Range>(get_parent());
	if (range_object == nullptr) {
		warnings.push_back(RTR("AutoScroll only serves to provide auto scrolling to a Range derived node. Please only use it as a child of HScrollBar, VScrollBar, HSlider, VSlider, ProgressBar, etc. to allow them to auto scroll."));
	}

	return warnings;
}
