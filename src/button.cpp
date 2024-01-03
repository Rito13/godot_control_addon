#include "button.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/text_server.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>
//#include <iostream>

using namespace godot;

void RevisedButton::_bind_methods() {
    // Bind methods to godot editor
    ClassDB::bind_method(D_METHOD("get_text"), &RevisedButton::get_text);
	ClassDB::bind_method(D_METHOD("set_text", "p_text"), &RevisedButton::set_text);
	ClassDB::bind_method(D_METHOD("get_v_text_alignment"), &RevisedButton::get_v_text_alignment);
	ClassDB::bind_method(D_METHOD("set_v_text_alignment", "p_alignment"), &RevisedButton::set_v_text_alignment);
	ClassDB::bind_method(D_METHOD("get_text_autowrap"), &RevisedButton::get_text_autowrap);
	ClassDB::bind_method(D_METHOD("set_text_autowrap", "p_autowrap"), &RevisedButton::set_text_autowrap);
	ClassDB::bind_method(D_METHOD("on_timer_out"), &RevisedButton::on_timer_out);
	ClassDB::bind_method(D_METHOD("set_adaptable_speed", "p_autowrap"), &RevisedButton::set_adaptable_speed);
	ClassDB::bind_method(D_METHOD("get_adaptable_speed"), &RevisedButton::get_adaptable_speed);
	// An funny property
	ClassDB::add_property_group("RevisedButton","Advance Text Behavior","");
	ClassDB::add_property("RevisedButton", PropertyInfo(Variant::FLOAT, "auto_scrolling_speed"), "set_adaptable_speed", "get_adaptable_speed");
	ClassDB::add_property("RevisedButton", PropertyInfo(Variant::INT, "vertical_text_alignment", PROPERTY_HINT_ENUM, "Top,Center,Bottom"), "set_v_text_alignment", "get_v_text_alignment");
	ClassDB::add_property("RevisedButton", PropertyInfo(Variant::INT, "autowrap_mode", PROPERTY_HINT_ENUM, "Arbitrary:1,Word:2,Word (Smart):3"), "set_text_autowrap", "get_text_autowrap");
	ClassDB::add_property("RevisedButton", PropertyInfo(Variant::STRING, "text"), "set_text", "get_text");
	/*// Theme
	BIND_THEME_ITEM(Theme::DATA_TYPE_COLOR, Button, font_color);
	BIND_THEME_ITEM(Theme::DATA_TYPE_COLOR, Button, font_focus_color);
	BIND_THEME_ITEM(Theme::DATA_TYPE_COLOR, Button, font_pressed_color);
	BIND_THEME_ITEM(Theme::DATA_TYPE_COLOR, Button, font_hover_color);
	BIND_THEME_ITEM(Theme::DATA_TYPE_COLOR, Button, font_hover_pressed_color);
	BIND_THEME_ITEM(Theme::DATA_TYPE_COLOR, Button, font_disabled_color); */
}

RevisedButton::RevisedButton() {
	// Initialize variables
	time_passed = 0.0;
	amplitude = 30;

	// Initialize internal childs
	text_parent = memnew(Control);
	scroll = memnew(AutoScroll);
	text_container = memnew(RichTextLabel);
	idle_time_timer = memnew(Timer);

    // Create internal tree
	add_child(text_parent, false, INTERNAL_MODE_FRONT);
	text_parent->add_child(text_container, false, INTERNAL_MODE_FRONT);
	text_parent->add_child(idle_time_timer, false, INTERNAL_MODE_FRONT);
	Node *scroll_bar = text_container->get_child(0,true);
	scroll_bar->add_child(scroll, false, INTERNAL_MODE_FRONT);

	// Setup other nodes
	update_text_vertical_alignment();
	idle_time_timer->set_one_shot(true);
	text_parent->set_clip_contents(true);
    text_parent->set_mouse_filter(Control::MouseFilter::MOUSE_FILTER_IGNORE);
	Error err1 = idle_time_timer->connect("timeout", Callable(this, "on_timer_out"));
	idle_time_timer->start();

	// Setup RichTextLabel (text_container)
	text_container->set_autowrap_mode(TextServer::AutowrapMode::AUTOWRAP_WORD_SMART);
	text_container->set_use_bbcode(true);
	text_container->set_mouse_filter(Control::MouseFilter::MOUSE_FILTER_IGNORE);
	text_container->set_scroll_active(false);
	text_container->set_scroll_follow(false);

	UtilityFunctions::print(theme_cache.font_color,"  ",theme_cache.font_hover_color);
}

RevisedButton::~RevisedButton() {
	// Cleanup
	/*std::cout << get_child_count() << std::endl ;
	if(get_child_count()!=0) {
        Node *scroll_bar = text_container->get_child(0,true);
        scroll_bar->remove_child(scroll);                   // Don't work but should.
        //text_parent->remove_child(scroll);                // Work but shouldn't. I don't know why.
        text_parent->remove_child(text_container);
        text_parent->remove_child(idle_time_timer);
    }*/
    text_container->queue_free();
	scroll->queue_free();
	idle_time_timer->queue_free();
	remove_child(text_parent);
	text_parent->queue_free();
}

void RevisedButton::on_timer_out() {
    if(timer_time_2) {
        scrolling = false;
        timer_time_2 = false;
        return;
    }
    timer_time_2 = true;
    Range *range_object = Object::cast_to<Range>(scroll->get_parent());
    range_object->set_value(scroll->get_auto_min_value());
    idle_time_timer->start();
}

void RevisedButton::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_THEME_CHANGED: {
			UtilityFunctions::print(theme_cache.font_color,"  ",theme_cache.font_hover_color);
		} break;
    }
}

void RevisedButton::update_text(bool recursive) {
    if(!recursive && v_text_alignment == VERTICAL_ALIGNMENT_CENTER) if(!update_text_vertical_alignment(true)) return;
    text_container->set_text(_h_bbcode+_v_bbcode+better_text);
    Range *range_object = Object::cast_to<Range>(scroll->get_parent());
    range_object->set_value(scroll->get_auto_min_value());
    //UtilityFunctions::print(range_object->get_step());
    //range_object->set_step(0);
    set_adaptable_speed(adaptable_speed);
    idle_time_timer->start();
    scrolling = true;
    timer_time_2 = true;
}

void RevisedButton::update_text_horizontal_alignment() {
    if(h_text_alignment == HORIZONTAL_ALIGNMENT_LEFT) _h_bbcode = "[left]";
    else if(h_text_alignment == HORIZONTAL_ALIGNMENT_CENTER) _h_bbcode = "[center]";
    else _h_bbcode = "[right]";
    update_text();
}

double RevisedButton::calculate_center_vertical_alignment(double y) {
    if(is_CVA_calculated >= 1) {
        scroll->set_auto_min_value(0);
        text_container->set_text(_h_bbcode+better_text);
        is_CVA_calculated = 2;
        return -1;
    }
    Range *range_object = Object::cast_to<Range>(scroll->get_parent());
    double r_max = range_object->get_max();
    double margin = (y-r_max)/2;
    if(margin<2) margin = 2;
    is_CVA_calculated = 1;
    return margin;
}

bool RevisedButton::update_text_vertical_alignment(bool recursive) {
    double margin = 0;
    if(v_text_alignment == VERTICAL_ALIGNMENT_TOP) margin = 2;
    else if(v_text_alignment == VERTICAL_ALIGNMENT_CENTER) margin = calculate_center_vertical_alignment(double(get_size().y));
    else margin = double(get_size().y);
    if(margin == -1) return false;
    _v_bbcode = String("[table=1][cell][font_size=") + std::to_string(int(margin/1.375)).c_str() + "] [/font_size][/cell][cell]";
    scroll->set_auto_min_value(margin-2);
    if(!recursive) update_text(true);
    return true;
}

void RevisedButton::_process(double delta) {
    // Update internal variables
	time_passed += delta;
	if(time_passed < 0.016) return;
	time_passed = 0;
	Vector2 siz = get_size();
	Vector2 pos = Vector2(0,0);
	Ref<Texture2D> texture = get_button_icon();
	if(is_CVA_calculated == 2) {
        is_CVA_calculated = 0;
        update_text_vertical_alignment();
	}
	//Check if texture exist
	if(texture.is_valid()) {
        Vector2 texture_size = texture->get_size();
        HorizontalAlignment h_aligment = get_icon_alignment();
        VerticalAlignment v_aligment = get_vertical_icon_alignment();

        //HORIZONTAL_ALIGNMENT is LEFT
        if(h_aligment == HORIZONTAL_ALIGNMENT_LEFT) {
            pos.x = texture_size.x;
            siz.x -= texture_size.x;
        }
        //HORIZONTAL_ALIGNMENT is RIGHT
        else if(h_aligment == HORIZONTAL_ALIGNMENT_RIGHT) {
            siz.x -= texture_size.x;
        }
        //HORIZONTAL_ALIGNMENT is CENTER
        else {
            HorizontalAlignment text_aligment = get_text_alignment();
            //TEXT_ALIGNMENT is LEFT
            if(text_aligment == HORIZONTAL_ALIGNMENT_LEFT) {
                siz.x = (siz.x-texture_size.x)/2;
            }
            //TEXT_ALIGNMENT is RIGHT
            else if(text_aligment == HORIZONTAL_ALIGNMENT_RIGHT) {
                siz.x = (siz.x-texture_size.x)/2;
                pos.x = siz.x+texture_size.x;
            }
        }
	}

	// Update text alignment
	if(old_height!=siz.y) {
        old_height = siz.y;
        update_text_vertical_alignment();
    }
	if(h_text_alignment!=get_text_alignment()) {
        h_text_alignment = get_text_alignment();
        update_text_horizontal_alignment();
	}

	// Update child sizes
	text_container->set_size(siz);
	text_parent->set_size(siz);
	text_parent->set_position(pos);

	if(Engine::get_singleton()->is_editor_hint()) return;           // Do not scroll while in editor

	// Scroll text
	if(!scrolling) {
        set_adaptable_speed(adaptable_speed);
        scroll->scroll_to(INFINITY);
        scrolling = true;
    }

    // Wrap text
    if(!scroll->is_scrolling()&&idle_time_timer->get_time_left()==0) {
        idle_time_timer->start();
    }
}

void RevisedButton::set_amplitude(const double p_amplitude) {
	amplitude = p_amplitude;
}

double RevisedButton::get_amplitude() const {
	return amplitude;
}

void RevisedButton::set_adaptable_speed(double p_speed) {
    adaptable_speed = p_speed;
    // Calculate adaptation of scrolling speed
    Vector2 t_size = text_container->get_size();
    p_speed = p_speed/100*(45000/(t_size.x*3));
	scroll->set_speed(int(p_speed));
	// Calculate adaptation of waiting speed
	p_speed = 22/p_speed;
	idle_time_timer->set_wait_time(p_speed);
	// Adapt scroll step
	Range *range_object = Object::cast_to<Range>(scroll->get_parent());
    range_object->set_step(0);
}

double RevisedButton::get_adaptable_speed() {
	return adaptable_speed;
}

void RevisedButton::set_v_text_alignment(const VerticalAlignment p_alignment) {
	v_text_alignment = p_alignment;
	update_text_vertical_alignment();
}

VerticalAlignment RevisedButton::get_v_text_alignment() const {
	return v_text_alignment;
}

void RevisedButton::set_text_autowrap(const TextServer::AutowrapMode p_autowrap) {
    // Handle wrong arguments
    if(p_autowrap == TextServer::AutowrapMode::AUTOWRAP_OFF) {
        UtilityFunctions::print("AUTOWRAP_OFF is not suported");
        ERR_FAIL_MSG("AUTOWRAP_OFF is not suported");
    }
	text_container->set_autowrap_mode(p_autowrap);
}

TextServer::AutowrapMode RevisedButton::get_text_autowrap() const {
	return text_container->get_autowrap_mode();
}

void RevisedButton::set_text(const String p_text) {
	better_text = p_text;
	update_text();
}

String RevisedButton::get_text() const {
	return better_text;
}
