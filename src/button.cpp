#include "button.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/text_server.hpp>
#include <godot_cpp/classes/theme.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>
//#include <iostream>
#include <string>

using namespace godot;

void RevisedButton::_bind_methods() {
    // Bind methods to godot editor
    ClassDB::bind_method(D_METHOD("get_text"), &RevisedButton::get_text);
	ClassDB::bind_method(D_METHOD("set_text", "p_text"), &RevisedButton::set_text);
	ClassDB::bind_method(D_METHOD("get_button_icon"), &RevisedButton::get_icon);
	ClassDB::bind_method(D_METHOD("set_button_icon", "p_icon"), &RevisedButton::set_icon);
	ClassDB::bind_method(D_METHOD("get_text_alignment"), &RevisedButton::get_text_alignment);
	ClassDB::bind_method(D_METHOD("set_text_alignment", "p_alignment"), &RevisedButton::set_text_alignment);
	ClassDB::bind_method(D_METHOD("get_v_text_alignment"), &RevisedButton::get_v_text_alignment);
	ClassDB::bind_method(D_METHOD("set_v_text_alignment", "p_alignment"), &RevisedButton::set_v_text_alignment);
	ClassDB::bind_method(D_METHOD("get_text_autowrap"), &RevisedButton::get_text_autowrap);
	ClassDB::bind_method(D_METHOD("set_text_autowrap", "p_autowrap"), &RevisedButton::set_text_autowrap);
	ClassDB::bind_method(D_METHOD("get_icon_alignment"), &RevisedButton::get_icon_alignment);
	ClassDB::bind_method(D_METHOD("set_icon_alignment", "p_alignment"), &RevisedButton::set_icon_alignment);
	ClassDB::bind_method(D_METHOD("get_vertical_icon_alignment"), &RevisedButton::get_vertical_icon_alignment);
	ClassDB::bind_method(D_METHOD("set_vertical_icon_alignment", "p_alignment"), &RevisedButton::set_vertical_icon_alignment);
	ClassDB::bind_method(D_METHOD("on_timer_out"), &RevisedButton::on_timer_out);
	ClassDB::bind_method(D_METHOD("set_adaptable_speed", "p_autowrap"), &RevisedButton::set_adaptable_speed);
	ClassDB::bind_method(D_METHOD("get_adaptable_speed"), &RevisedButton::get_adaptable_speed);
	ClassDB::bind_method(D_METHOD("set_text_off", "p_status"), &RevisedButton::set_is_text_off);
	ClassDB::bind_method(D_METHOD("is_text_off"), &RevisedButton::get_is_text_off);
	ClassDB::bind_method(D_METHOD("get_theme", "p_bool"), &RevisedButton::get_theme);
	ClassDB::bind_method(D_METHOD("_texture_changed"), &RevisedButton::update_icon);
	ClassDB::bind_method(D_METHOD("set_flat", "p_status"), &RevisedButton::set_flat_status);
	ClassDB::bind_method(D_METHOD("is_flat"), &RevisedButton::get_flat_status);
	ClassDB::bind_method(D_METHOD("set_expand_icon", "p_status"), &RevisedButton::set_icon_shrink);
	ClassDB::bind_method(D_METHOD("is_expand_icon"), &RevisedButton::get_icon_shrink);
	ClassDB::bind_method(D_METHOD("set_alignment_order", "p_order"), &RevisedButton::set_force_vertical_alignment_before_horizontal);
	ClassDB::bind_method(D_METHOD("get_alignment_order"), &RevisedButton::get_force_vertical_alignment_before_horizontal);
	// An funny property
	ClassDB::add_property("RevisedButton", PropertyInfo(Variant::STRING, "text", PROPERTY_HINT_MULTILINE_TEXT), "set_text", "get_text");
	ClassDB::add_property("RevisedButton", PropertyInfo(Variant::OBJECT, "icon", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_button_icon", "get_button_icon");
	ClassDB::add_property("RevisedButton", PropertyInfo(Variant::BOOL, "flat"), "set_flat", "is_flat");
	ClassDB::add_property("RevisedButton", PropertyInfo(Variant::INT, "alignment_order", PROPERTY_HINT_ENUM, "Horizontal First:0,Vertical First:1"), "set_alignment_order", "get_alignment_order");
	ClassDB::add_property_group("RevisedButton","Text Behavior","");
	ClassDB::add_property("RevisedButton", PropertyInfo(Variant::BOOL, "is_text_off"), "set_text_off", "is_text_off");
	ClassDB::add_property("RevisedButton", PropertyInfo(Variant::FLOAT, "auto_scrolling_speed"), "set_adaptable_speed", "get_adaptable_speed");
	ClassDB::add_property("RevisedButton", PropertyInfo(Variant::INT, "horizontal_text_alignment", PROPERTY_HINT_ENUM, "Left,Center,Right"), "set_text_alignment", "get_text_alignment");
	ClassDB::add_property("RevisedButton", PropertyInfo(Variant::INT, "vertical_text_alignment", PROPERTY_HINT_ENUM, "Top,Center,Bottom"), "set_v_text_alignment", "get_v_text_alignment");
	ClassDB::add_property("RevisedButton", PropertyInfo(Variant::INT, "autowrap_mode", PROPERTY_HINT_ENUM, "Arbitrary:1,Word:2,Word (Smart):3"), "set_text_autowrap", "get_text_autowrap");
	ClassDB::add_property_group("RevisedButton","Icon Behavior","");
	ClassDB::add_property("RevisedButton", PropertyInfo(Variant::INT, "icon_alignment", PROPERTY_HINT_ENUM, "Left,Center,Right"), "set_icon_alignment", "get_icon_alignment");
	ClassDB::add_property("RevisedButton", PropertyInfo(Variant::INT, "vertical_icon_alignment", PROPERTY_HINT_ENUM, "Top,Center,Bottom"), "set_vertical_icon_alignment", "get_vertical_icon_alignment");
	ClassDB::add_property("RevisedButton", PropertyInfo(Variant::BOOL, "expand_icon"), "set_expand_icon", "is_expand_icon");
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
	amplitude = 31;
	get_theme(true);
	set_process_internal(true);

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
	idle_time_timer->connect("timeout", Callable(this, "on_timer_out"));
	//idle_time_timer->start();

	// Setup RichTextLabel (text_container)
	text_container->set_autowrap_mode(TextServer::AutowrapMode::AUTOWRAP_WORD_SMART);
	text_container->set_use_bbcode(true);
	text_container->set_mouse_filter(Control::MouseFilter::MOUSE_FILTER_IGNORE);
	text_container->set_scroll_active(false);
	text_container->set_scroll_follow(false);
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

bool RevisedButton::has_theme(uint8_t what,const StringName &name) const {
    switch (what) {
		case FHT_constant: {
			bool condition1 = has_theme_constant(name,"RevisedButton");
			bool condition2 = has_theme_constant(name,"Button");
			return condition1 || condition2;
		} break;
		case FHT_color: {
			bool condition1 = has_theme_color(name,"RevisedButton");
			bool condition2 = has_theme_color(name,"Button");
			return condition1 || condition2;
		} break;
		case FHT_stylebox: {
			bool condition1 = has_theme_stylebox(name,"RevisedButton");
			bool condition2 = has_theme_stylebox(name,"Button");
			return condition1 || condition2;
		} break;
		case FHT_font: {
			bool condition1 = has_theme_font(name,"RevisedButton");
			bool condition2 = has_theme_font(name,"Button");
			return condition1 || condition2;
		} break;
		case FHT_font_size: {
			bool condition1 = has_theme_font_size(name,"RevisedButton");
			bool condition2 = has_theme_font_size(name,"Button");
			return condition1 || condition2;
		} break;
		case FHT_icon: {
			bool condition1 = has_theme_icon(name,"RevisedButton");
			bool condition2 = has_theme_icon(name,"Button");
			return condition1 || condition2;
		} break;
	}
	return false;
}

void RevisedButton::find_theme(StringName type,bool check) {
	if(check) {
		if(has_theme_stylebox("normal",type))
			theme_cache.normal = get_theme_stylebox("normal",type);
		if(has_theme_stylebox("normal_mirrored",type))
			theme_cache.normal_mirrored = get_theme_stylebox("normal_mirrored",type);
		if(has_theme_stylebox("pressed",type))
			theme_cache.pressed = get_theme_stylebox("pressed",type);
		if(has_theme_stylebox("pressed_mirrored",type))
			theme_cache.pressed_mirrored = get_theme_stylebox("pressed_mirrored",type);
		if(has_theme_stylebox("hover",type))
			theme_cache.hover = get_theme_stylebox("hover",type);
		if(has_theme_stylebox("hover_mirrored",type))
			theme_cache.hover_mirrored = get_theme_stylebox("hover_mirrored",type);
		if(has_theme_stylebox("hover_pressed",type))
			theme_cache.hover_pressed = get_theme_stylebox("hover_pressed",type);
		if(has_theme_stylebox("hover_pressed_mirrored",type))
			theme_cache.hover_pressed_mirrored = get_theme_stylebox("hover_pressed_mirrored",type);
		if(has_theme_stylebox("disabled",type))
			theme_cache.disabled = get_theme_stylebox("disabled",type);
		if(has_theme_stylebox("disabled_mirrored",type))
			theme_cache.disabled_mirrored = get_theme_stylebox("disabled_mirrored",type);
		if(has_theme_stylebox("focus",type))
			theme_cache.focus = get_theme_stylebox("focus",type);

		if(has_theme_color("font_color",type))
			theme_cache.font_color = get_theme_color("font_color",type);
		if(has_theme_color("font_focus_color",type))
			theme_cache.font_focus_color = get_theme_color("font_focus_color",type);
		if(has_theme_color("font_pressed_color",type))
			theme_cache.font_pressed_color = get_theme_color("font_pressed_color",type);
		if(has_theme_color("font_hover_color",type))
			theme_cache.font_hover_color = get_theme_color("font_hover_color",type);
		if(has_theme_color("font_hover_pressed_color",type))
			theme_cache.font_hover_pressed_color = get_theme_color("font_hover_pressed_color",type);
		if(has_theme_color("font_disabled_color",type))
			theme_cache.font_disabled_color = get_theme_color("font_disabled_color",type);

		if(has_theme_font("font",type))
			theme_cache.font = get_theme_font("font",type);
		if(has_theme_font_size("font_size",type))
			theme_cache.font_size = get_theme_font_size("font_size",type);
		if(has_theme_constant("outline_size",type))
			theme_cache.outline_size = get_theme_constant("outline_size",type);
		if(has_theme_color("font_outline_color",type))
			theme_cache.font_outline_color = get_theme_color("font_outline_color",type);

		if(has_theme_color("icon_normal_color",type))
			theme_cache.icon_normal_color = get_theme_color("icon_normal_color",type);
		if(has_theme_color("icon_focus_color",type))
			theme_cache.icon_focus_color = get_theme_color("icon_focus_color",type);
		if(has_theme_color("icon_pressed_color",type))
			theme_cache.icon_pressed_color = get_theme_color("icon_pressed_color",type);
		if(has_theme_color("icon_hover_color",type))
			theme_cache.icon_hover_color = get_theme_color("icon_hover_color",type);
		if(has_theme_color("icon_hover_pressed_color",type))
			theme_cache.icon_hover_pressed_color = get_theme_color("icon_hover_pressed_color",type);
		if(has_theme_color("icon_disabled_color",type))
			theme_cache.icon_disabled_color = get_theme_color("icon_disabled_color",type);

		if(has_theme_constant("h_separation",type))
			theme_cache.h_separation = get_theme_constant("h_separation",type);
		if(has_theme_constant("icon_max_width",type))
			theme_cache.icon_max_width = get_theme_constant("icon_max_width",type);
	
	} else {
    	theme_cache.normal = get_theme_stylebox("normal",type);
    	theme_cache.normal_mirrored = get_theme_stylebox("normal_mirrored",type);
    	theme_cache.pressed = get_theme_stylebox("pressed",type);
    	theme_cache.pressed_mirrored = get_theme_stylebox("pressed_mirrored",type);
    	theme_cache.hover = get_theme_stylebox("hover",type);
    	theme_cache.hover_mirrored = get_theme_stylebox("hover_mirrored",type);
    	theme_cache.hover_pressed = get_theme_stylebox("hover_pressed",type);
    	theme_cache.hover_pressed_mirrored = get_theme_stylebox("hover_pressed_mirrored",type);
    	theme_cache.disabled = get_theme_stylebox("disabled",type);
    	theme_cache.disabled_mirrored = get_theme_stylebox("disabled_mirrored",type);
    	theme_cache.focus = get_theme_stylebox("focus",type);

    	theme_cache.font_color = get_theme_color("font_color",type);
    	theme_cache.font_focus_color = get_theme_color("font_focus_color",type);
    	theme_cache.font_pressed_color = get_theme_color("font_pressed_color",type);
    	theme_cache.font_hover_color = get_theme_color("font_hover_color",type);
    	theme_cache.font_hover_pressed_color = get_theme_color("font_hover_pressed_color",type);
    	theme_cache.font_disabled_color = get_theme_color("font_disabled_color",type);

    	theme_cache.font = get_theme_font("font",type);
    	theme_cache.font_size = get_theme_font_size("font_size",type);
    	theme_cache.outline_size = get_theme_constant("outline_size",type);
    	theme_cache.font_outline_color = get_theme_color("font_outline_color",type);

    	theme_cache.icon_normal_color = get_theme_color("icon_normal_color",type);
    	theme_cache.icon_focus_color = get_theme_color("icon_focus_color",type);
    	theme_cache.icon_pressed_color = get_theme_color("icon_pressed_color",type);
    	theme_cache.icon_hover_color = get_theme_color("icon_hover_color",type);
    	theme_cache.icon_hover_pressed_color = get_theme_color("icon_hover_pressed_color",type);
    	theme_cache.icon_disabled_color = get_theme_color("icon_disabled_color",type);

    	theme_cache.h_separation = get_theme_constant("h_separation",type);
    	theme_cache.icon_max_width = get_theme_constant("icon_max_width",type);
	}
}

void RevisedButton::get_theme(bool p_bool) {
    find_theme("Button");
	find_theme("RevisedButton",true);
}

void RevisedButton::update_text(bool recursive) {
    if(!recursive && v_text_alignment == VERTICAL_ALIGNMENT_CENTER) if(!update_text_vertical_alignment(true)) return;
    text_container->set_text(_color_bbcode+_h_bbcode+_v_bbcode+better_text);
    Range *range_object = Object::cast_to<Range>(scroll->get_parent());
    range_object->set_value(scroll->get_auto_min_value());
    //UtilityFunctions::print(range_object->get_step());
    //range_object->set_step(0);
    set_adaptable_speed(adaptable_speed);
	if(idle_time_timer->get_parent()==text_parent)
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

Vector2 RevisedButton::_get_minimum_size() const {
	Ref<Texture2D> p_icon;
	if (icon.is_null() && has_theme(FHT_icon,"icon")) {
		p_icon = get_theme_icon("icon","Button");
	} else {
		p_icon = icon;
	}

	Vector2 minsize = Vector2(0,0);

	if (!shrink_icon && p_icon.is_valid()) {
		Vector2 icon_size = _fit_icon_size(p_icon->get_size());
		if (vertical_icon_alignment == VERTICAL_ALIGNMENT_CENTER) {
			minsize.y = MAX(minsize.y, icon_size.y);
		} else {
			minsize.y += icon_size.y;
		}

		if (horizontal_icon_alignment != HORIZONTAL_ALIGNMENT_CENTER) {
			minsize.x += icon_size.x;
			minsize.x += MAX(0, theme_cache.h_separation);
		} else {
			minsize.x = MAX(minsize.x, icon_size.x);
		}
	}
	return theme_cache.normal->get_minimum_size() + minsize;
}

void RevisedButton::process(double delta) {
    // Update internal variables
	time_passed += delta;
	if(time_passed < 0.016) return;
	time_passed = 0;
	Vector2 siz = get_size();
	Vector2 pos = Vector2(0,0);
	Ref<Texture2D> texture = icon;
	if(is_CVA_calculated == 2) {
        is_CVA_calculated = 0;
        update_text_vertical_alignment();
	}
	//Check if texture exist
	if(texture.is_valid()) {
        Vector2 texture_size = old_icon_size+old_margin_size;
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
			//force_vertical_alignment_before_horizontal is true
			//VERTICAL_ALIGNMENT is TOP
			if(force_vertical_alignment_before_horizontal && v_aligment == VERTICAL_ALIGNMENT_TOP) {
				pos.y = texture_size.y;
            	siz.y -= texture_size.y;
			}
			//VERTICAL_ALIGNMENT is BOTTOM
			else if(force_vertical_alignment_before_horizontal && v_aligment == VERTICAL_ALIGNMENT_BOTTOM) {
				siz.y -= texture_size.y;
			}
            //TEXT_ALIGNMENT is LEFT
            else if(text_aligment == HORIZONTAL_ALIGNMENT_LEFT) {
                siz.x = (siz.x-texture_size.x)/2;
            }
            //TEXT_ALIGNMENT is RIGHT
            else if(text_aligment == HORIZONTAL_ALIGNMENT_RIGHT) {
                siz.x = (siz.x-texture_size.x)/2;
                pos.x = siz.x+texture_size.x;
            }
			//force_vertical_alignment_before_horizontal is false
			//VERTICAL_ALIGNMENT is TOP
			else if(v_aligment == VERTICAL_ALIGNMENT_TOP) {
				pos.y = texture_size.y;
            	siz.y -= texture_size.y;
			}
			//VERTICAL_ALIGNMENT is BOTTOM
			else if(v_aligment == VERTICAL_ALIGNMENT_BOTTOM) {
				siz.y -= texture_size.y;
			}
        }
	}

    if(is_text_off) return;

	// Update text alignment
	if(old_height!=siz.y) {
        old_height = siz.y;
        update_text_vertical_alignment();
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

void RevisedButton::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_LAYOUT_DIRECTION_CHANGED: {
			queue_redraw();
		} break;

		case NOTIFICATION_TRANSLATION_CHANGED: {
			//xl_text = atr(text);
			//_shape();

			update_minimum_size();
			queue_redraw();
		} break;

		case NOTIFICATION_THEME_CHANGED: {
			//_shape();
            get_theme(true);
			update_minimum_size();
			queue_redraw();
		} break;

		case NOTIFICATION_INTERNAL_PROCESS: {
			//UtilityFunctions::print(true);
			process(get_process_delta_time());
		} break;

		case NOTIFICATION_DRAW: {
            StringName type = StringName("Button");
			RID ci = get_canvas_item();
			Vector2 size = get_size();
			Color color;
			Color color_icon(1, 1, 1, 1);

			Ref<StyleBox> style = theme_cache.normal;
			bool rtl = is_layout_rtl();
			Color new_font_color = Color(1,1,1);

			switch (get_draw_mode()) {
				case DRAW_NORMAL: {
                    //const auto &what (Control::has_theme_stylebox);
					if (rtl && has_theme(FHT_stylebox,"normal_mirrored")) {
						style = theme_cache.normal_mirrored;
					} else {
						style = theme_cache.normal;
					}

					new_font_color = theme_cache.font_color;
					if (has_focus())
						new_font_color = theme_cache.font_focus_color;

					if (!flat) {
						style->draw(ci, Rect2(Vector2(0, 0), size));
					}

					// Focus colors only take precedence over normal state.
					if (has_focus()) {
						color = theme_cache.font_focus_color;
						if (has_theme(FHT_color,"icon_focus_color")) {
							color_icon = theme_cache.icon_focus_color;
						}
					} else {
						color = theme_cache.font_color;
						if (has_theme(FHT_color,"icon_normal_color")) {
							color_icon = theme_cache.icon_normal_color;
						}
					}
				} break;
				case DRAW_HOVER_PRESSED: {
					// Edge case for CheckButton and CheckBox.
					if (has_theme(FHT_stylebox,"hover_pressed")) {
						if (rtl && has_theme(FHT_stylebox,"hover_pressed_mirrored")) {
							style = theme_cache.hover_pressed_mirrored;
						} else {
							style = theme_cache.hover_pressed;
						}

						new_font_color = theme_cache.font_hover_pressed_color;

						if (!flat) {
							style->draw(ci, Rect2(Vector2(0, 0), size));
						}
						if (has_theme(FHT_color,"font_hover_pressed_color")) {
							color = theme_cache.font_hover_pressed_color;
						}
						if (has_theme(FHT_color,"icon_hover_pressed_color")) {
							color_icon = theme_cache.icon_hover_pressed_color;
						}

						break;
					}
					[[fallthrough]];
				}
				case DRAW_PRESSED: {
					if (rtl && has_theme(FHT_stylebox,"pressed_mirrored")) {
						style = theme_cache.pressed_mirrored;
					} else {
						style = theme_cache.pressed;
					}

					new_font_color = theme_cache.font_pressed_color;

					if (!flat) {
						style->draw(ci, Rect2(Vector2(0, 0), size));
					}
					if (has_theme(FHT_color,"font_pressed_color")) {
						color = theme_cache.font_pressed_color;
					} else {
						color = theme_cache.font_color;
					}
					if (has_theme(FHT_color,"icon_pressed_color")) {
						color_icon = theme_cache.icon_pressed_color;
					}

				} break;
				case DRAW_HOVER: {
					if (rtl && has_theme(FHT_stylebox,"hover_mirrored")) {
						style = theme_cache.hover_mirrored;
					} else {
						style = theme_cache.hover;
					}

					new_font_color = theme_cache.font_hover_color;

					if (!flat) {
						style->draw(ci, Rect2(Vector2(0, 0), size));
					}
					color = theme_cache.font_hover_color;
					if (has_theme(FHT_color,"icon_hover_color")) {
						color_icon = theme_cache.icon_hover_color;
					}

				} break;
				case DRAW_DISABLED: {
					if (rtl && has_theme(FHT_stylebox,"disabled_mirrored")) {
						style = theme_cache.disabled_mirrored;
					} else {
						style = theme_cache.disabled;
					}

					new_font_color = theme_cache.font_disabled_color;

					if (!flat) {
						style->draw(ci, Rect2(Vector2(0, 0), size));
					}
					color = theme_cache.font_disabled_color;
					if (has_theme(FHT_color,"icon_disabled_color")) {
						color_icon = theme_cache.icon_disabled_color;
					} else {
						color_icon.a = 0.4;
					}

				} break;
			}

			if (has_focus()) {
				Ref<StyleBox> style2 = theme_cache.focus;
				style2->draw(ci, Rect2(Vector2(), size));
			}

			if(new_font_color.to_html()!=used_font_color.to_html()) {
				used_font_color = new_font_color;
				String html = new_font_color.to_html();
				_color_bbcode = "[color=" + html + "]";
				update_text(true);
			}

			Ref<Texture2D> _icon;
			if (icon.is_null() && has_theme(FHT_icon,"icon")) {
				_icon = get_theme_icon("icon",type);
			} else {
				_icon = icon;
			}

			Rect2 icon_region;
			HorizontalAlignment icon_align_rtl_checked = horizontal_icon_alignment;
			HorizontalAlignment align_rtl_checked = h_text_alignment;
			// Swap icon and text alignment sides if right-to-left layout is set.
			if (rtl) {
				if (horizontal_icon_alignment == HORIZONTAL_ALIGNMENT_RIGHT) {
					icon_align_rtl_checked = HORIZONTAL_ALIGNMENT_LEFT;
				} else if (horizontal_icon_alignment == HORIZONTAL_ALIGNMENT_LEFT) {
					icon_align_rtl_checked = HORIZONTAL_ALIGNMENT_RIGHT;
				}
				if (h_text_alignment == HORIZONTAL_ALIGNMENT_RIGHT) {
					align_rtl_checked = HORIZONTAL_ALIGNMENT_LEFT;
				} else if (h_text_alignment == HORIZONTAL_ALIGNMENT_LEFT) {
					align_rtl_checked = HORIZONTAL_ALIGNMENT_RIGHT;
				}
			}
			if (!_icon.is_null()) {
				int valign = size.y - style->get_minimum_size().y;

				int voffset = 0;
				Vector2 icon_size = _icon->get_size();

				// Fix vertical size.
				/*if (vertical_icon_alignment != VERTICAL_ALIGNMENT_CENTER) {
					valign -= text_buf->get_size().y;
				}*/

				float icon_ofs_region = 0.0;
				Vector2 style_offset;
				if (icon_align_rtl_checked == HORIZONTAL_ALIGNMENT_LEFT) {
					style_offset.x = style->get_margin(SIDE_LEFT);
					if (_internal_margin[SIDE_LEFT] > 0) {
						icon_ofs_region = _internal_margin[SIDE_LEFT] + theme_cache.h_separation;
					}
				} else if (icon_align_rtl_checked == HORIZONTAL_ALIGNMENT_CENTER) {
					style_offset.x = 0.0;
				} else if (icon_align_rtl_checked == HORIZONTAL_ALIGNMENT_RIGHT) {
					style_offset.x = -style->get_margin(SIDE_RIGHT);
					if (_internal_margin[SIDE_RIGHT] > 0) {
						icon_ofs_region = -_internal_margin[SIDE_RIGHT] - theme_cache.h_separation;
					}
				}
				style_offset.y = style->get_margin(SIDE_TOP);

				if (shrink_icon) {
					Vector2 _size = get_size() - style->get_offset() * 2;
					int icon_text_separation = better_text.is_empty() ? 0 : theme_cache.h_separation;
					_size.x -= icon_text_separation + icon_ofs_region;
					/*if (!is_clipped && icon_align_rtl_checked != HORIZONTAL_ALIGNMENT_CENTER) {
						_size.x -= text_buf->get_size().x;
					}
					if (vertical_icon_alignment != VERTICAL_ALIGNMENT_CENTER) {
						_size.y -= text_buf->get_size().y;
					}*/
					float icon_width = _icon->get_width() * _size.y / _icon->get_height();
					float icon_height = _size.y;

					if (icon_width > _size.x) {
						icon_width = _size.x;
						icon_height = _icon->get_height() * icon_width / _icon->get_width();
					}

					icon_size = Vector2(icon_width, icon_height);
				}
				icon_size = _fit_icon_size(icon_size);

				if (vertical_icon_alignment == VERTICAL_ALIGNMENT_TOP) {
					voffset = -(valign - icon_size.y) / 2;
				}
				if (vertical_icon_alignment == VERTICAL_ALIGNMENT_BOTTOM) {
					voffset = (valign - icon_size.y) / 2;
				}

				if (icon_align_rtl_checked == HORIZONTAL_ALIGNMENT_LEFT) {
					icon_region = Rect2(style_offset + Vector2(icon_ofs_region, voffset + Math::floor((valign - icon_size.y) * 0.5)), icon_size);
				} else if (icon_align_rtl_checked == HORIZONTAL_ALIGNMENT_CENTER) {
					icon_region = Rect2(style_offset + Vector2(icon_ofs_region + Math::floor((size.x - icon_size.x) * 0.5), voffset + Math::floor((valign - icon_size.y) * 0.5)), icon_size);
				} else {
					icon_region = Rect2(style_offset + Vector2(icon_ofs_region + size.x - icon_size.x, voffset + Math::floor((valign - icon_size.y) * 0.5)), icon_size);
				}

				if (icon_region.size.x > 0) {
					old_icon_size = icon_region.size.round();
					Rect2 icon_region_rounded = Rect2(icon_region.position.round(), icon_region.size.round());
					draw_texture_rect(_icon, icon_region_rounded, false, color_icon);
				}
				if(style_offset.x<0) style_offset.x = style_offset.x*(-1);
				old_margin_size = style_offset;
			}

			Vector2 icon_ofs = !_icon.is_null() ? Vector2(icon_region.size.x + theme_cache.h_separation, 0) : Vector2();
			if (align_rtl_checked == HORIZONTAL_ALIGNMENT_CENTER && icon_align_rtl_checked == HORIZONTAL_ALIGNMENT_CENTER) {
				icon_ofs.x = 0.0;
			}

			int text_clip = size.x - style->get_minimum_size().x - icon_ofs.x;
			if (_internal_margin[SIDE_LEFT] > 0) {
				text_clip -= _internal_margin[SIDE_LEFT] + theme_cache.h_separation;
			}
			if (_internal_margin[SIDE_RIGHT] > 0) {
				text_clip -= _internal_margin[SIDE_RIGHT] + theme_cache.h_separation;
			}

			/*text_buf->set_width(is_clipped ? text_clip : -1);

			int text_width = MAX(1, is_clipped ? MIN(text_clip, text_buf->get_size().x) : text_buf->get_size().x);

			Vector2 text_ofs = (size - style->get_minimum_size() - icon_ofs - text_buf->get_size() - Vector2(_internal_margin[SIDE_RIGHT] - _internal_margin[SIDE_LEFT], 0)) / 2.0;

			if (vertical_icon_alignment == VERTICAL_ALIGNMENT_TOP) {
				text_ofs.y += icon_region.size.y / 2;
			}
			if (vertical_icon_alignment == VERTICAL_ALIGNMENT_BOTTOM) {
				text_ofs.y -= icon_region.size.y / 2;
			}

			text_buf->set_alignment(align_rtl_checked);
			text_buf->set_width(text_width);
			switch (align_rtl_checked) {
				case HORIZONTAL_ALIGNMENT_FILL:
				case HORIZONTAL_ALIGNMENT_LEFT: {
					if (icon_align_rtl_checked != HORIZONTAL_ALIGNMENT_LEFT) {
						icon_ofs.x = 0.0;
					}
					if (_internal_margin[SIDE_LEFT] > 0) {
						text_ofs.x = style->get_margin(SIDE_LEFT) + icon_ofs.x + _internal_margin[SIDE_LEFT] + theme_cache.h_separation;
					} else {
						text_ofs.x = style->get_margin(SIDE_LEFT) + icon_ofs.x;
					}
					text_ofs.y += style->get_offset().y;
				} break;
				case HORIZONTAL_ALIGNMENT_CENTER: {
					if (text_ofs.x < 0) {
						text_ofs.x = 0;
					}
					if (icon_align_rtl_checked == HORIZONTAL_ALIGNMENT_LEFT) {
						text_ofs += icon_ofs;
					}
					text_ofs += style->get_offset();
				} break;
				case HORIZONTAL_ALIGNMENT_RIGHT: {
					if (_internal_margin[SIDE_RIGHT] > 0) {
						text_ofs.x = size.x - style->get_margin(SIDE_RIGHT) - text_width - _internal_margin[SIDE_RIGHT] - theme_cache.h_separation;
					} else {
						text_ofs.x = size.x - style->get_margin(SIDE_RIGHT) - text_width;
					}
					text_ofs.y += style->get_offset().y;
					if (icon_align_rtl_checked == HORIZONTAL_ALIGNMENT_RIGHT) {
						text_ofs.x -= icon_ofs.x;
					}
				} break;
			}

			Color font_outline_color = theme_cache.font_outline_color;
			int outline_size = theme_cache.outline_size;
			if (outline_size > 0 && font_outline_color.a > 0) {
				text_buf->draw_outline(ci, text_ofs, outline_size, font_outline_color);
			}
			text_buf->draw(ci, text_ofs, color);*/
		} break;

		default: {
			BaseButton::_notification(p_what);
		} break;
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
	if(p_speed<=0) return;
	idle_time_timer->set_wait_time(p_speed);
	// Adapt scroll step
	Range *range_object = Object::cast_to<Range>(scroll->get_parent());
    range_object->set_step(0);
}

double RevisedButton::get_adaptable_speed() {
	return adaptable_speed;
}

void RevisedButton::set_text_alignment(HorizontalAlignment p_alignment) {
	if (h_text_alignment != p_alignment) {
		h_text_alignment = p_alignment;
		update_text_horizontal_alignment();
		queue_redraw();
	}
}

HorizontalAlignment RevisedButton::get_text_alignment() const {
	return h_text_alignment;
}

void RevisedButton::set_v_text_alignment(const VerticalAlignment p_alignment) {
    if (v_text_alignment != p_alignment) {
		v_text_alignment = p_alignment;
		update_text_vertical_alignment();
		queue_redraw();
	}
}

VerticalAlignment RevisedButton::get_v_text_alignment() const {
	return v_text_alignment;
}

void RevisedButton::set_icon_alignment(HorizontalAlignment p_alignment) {
    if (horizontal_icon_alignment != p_alignment) {
        horizontal_icon_alignment = p_alignment;
        update_minimum_size();
        queue_redraw();
    }
}

void RevisedButton::set_vertical_icon_alignment(VerticalAlignment p_alignment) {
    if (vertical_icon_alignment != p_alignment) {
        vertical_icon_alignment = p_alignment;
        update_minimum_size();
        queue_redraw();
    }
}

HorizontalAlignment RevisedButton::get_icon_alignment() const {
	return horizontal_icon_alignment;
}

VerticalAlignment RevisedButton::get_vertical_icon_alignment() const {
	return vertical_icon_alignment;
}

Vector2 RevisedButton::_fit_icon_size(const Vector2 &p_size) const {
	int max_width = theme_cache.icon_max_width;
	Vector2 icon_size = p_size;

	if (max_width > 0 && icon_size.x > max_width) {
		icon_size.y = icon_size.y * max_width / icon_size.x;
		icon_size.x = max_width;
	}

	return icon_size;
}

void RevisedButton::set_text_autowrap(const TextServer::AutowrapMode p_autowrap) {
    // Handle wrong arguments
    if(p_autowrap == TextServer::AutowrapMode::AUTOWRAP_OFF) {
        UtilityFunctions::print_rich("[color=VIOLET]",String(L"●")," Control++:  AUTOWRAP_OFF is not suported","[color=SNOW]");
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

void RevisedButton::set_icon(const Ref<Texture2D> p_icon) {
	if (icon == p_icon) {
		return;
	}
	if (icon.is_valid()) {
		icon->disconnect("changed", Callable(this, "_texture_changed"));
	}
	icon = p_icon;
	if (icon.is_valid()) {
		icon->connect("changed", Callable(this, "_texture_changed"));
	}
	queue_redraw();
	update_minimum_size();
}

Ref<Texture2D> RevisedButton::get_icon() const {
	return icon;
}

void RevisedButton::update_icon() {
	queue_redraw();
	update_minimum_size();
}

void RevisedButton::set_is_text_off(bool p_status) {
    is_text_off = p_status;
    if(p_status) text_parent->hide();
    else {
        text_parent->show();
        update_text();
    }
}

bool RevisedButton::get_is_text_off() {
    return is_text_off;
}

void RevisedButton::set_flat_status(bool p_status) {
	if (flat != p_status) {
    	flat = p_status;
    	queue_redraw();
	}
}

bool RevisedButton::get_flat_status() {
    return flat;
}

void RevisedButton::set_icon_shrink(bool p_status) {
	if (shrink_icon != p_status) {
    	shrink_icon = p_status;
    	queue_redraw();
		update_minimum_size();
	}
}

bool RevisedButton::get_icon_shrink() {
    return shrink_icon;
}

void RevisedButton::set_force_vertical_alignment_before_horizontal(const int p_order) {
	if(p_order == 0) force_vertical_alignment_before_horizontal = false;
	else if(p_order == 1) force_vertical_alignment_before_horizontal = true;
	else {
		std::string standardString = std::to_string(p_order);
		String godotString = String(standardString.c_str());
		String _msg = "Order of value "+godotString+" is not suported \n	Suported oredrs: \n	0 - HORIZONTAL_FIRST \n	1 - VERTICAL_FIRST";
		UtilityFunctions::print_rich("[color=VIOLET]",String(L"●")," Control++:  ",_msg,"[color=SNOW]");
        ERR_FAIL_MSG(_msg);
	}
}

int RevisedButton::get_force_vertical_alignment_before_horizontal() const {
	if(force_vertical_alignment_before_horizontal) return 1;
	else return 0;
}