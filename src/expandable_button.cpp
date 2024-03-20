#include "expandable_button.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
//#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void ExpandableButton::_bind_methods() {
    // Expansion Size Property
    ClassDB::bind_method(D_METHOD("set_expansion_size", "p_size"), &ExpandableButton::set_expansion_size);
	ClassDB::bind_method(D_METHOD("get_expansion_size"), &ExpandableButton::get_expansion_size);
	ClassDB::add_property("ExpandableButton", PropertyInfo(Variant::INT, "expansion_size"), "set_expansion_size", "get_expansion_size");
	// Expansion Indentation Property
	ClassDB::bind_method(D_METHOD("set_expansion_indentation", "p_indentation"), &ExpandableButton::set_expansion_indentation);
	ClassDB::bind_method(D_METHOD("get_expansion_indentation"), &ExpandableButton::get_expansion_indentation);
	ClassDB::add_property("ExpandableButton", PropertyInfo(Variant::INT, "expansion_indentation"), "set_expansion_indentation", "get_expansion_indentation");
	// Expansion Speed Property
	ClassDB::bind_method(D_METHOD("set_expansion_speed", "p_speed"), &ExpandableButton::set_expansion_speed);
	ClassDB::bind_method(D_METHOD("get_expansion_speed"), &ExpandableButton::get_expansion_speed);
	ClassDB::add_property("ExpandableButton", PropertyInfo(Variant::FLOAT, "expansion_speed"), "set_expansion_speed", "get_expansion_speed");
	// Expand Methods
	ClassDB::bind_method(D_METHOD("expand"), &ExpandableButton::expand);
	ClassDB::bind_method(D_METHOD("reduce"), &ExpandableButton::reduce);
	// Expansion Informations Property
	ClassDB::bind_method(D_METHOD("set_expansion_info", "p_int"), &ExpandableButton::set_expansion_info);
	ClassDB::bind_method(D_METHOD("get_expansion_info"), &ExpandableButton::get_expansion_info);
	ClassDB::add_property("ExpandableButton", PropertyInfo(Variant::INT, "expansion_information", PROPERTY_HINT_ENUM, "Image,Text"), "set_expansion_info", "get_expansion_info");
	// Informations Margin Property
	ClassDB::bind_method(D_METHOD("set_info_margin", "p_margin"), &ExpandableButton::set_info_margin);
	ClassDB::bind_method(D_METHOD("get_info_margin"), &ExpandableButton::get_info_margin);
	ClassDB::add_property("ExpandableButton", PropertyInfo(Variant::INT, "information_margin"), "set_info_margin", "get_info_margin");
	//ClassDB::bind_method(D_METHOD("_get_minimum_size"), &ExpandableButton::_get_minimum_size);
	// Signals Methods
	//ClassDB::bind_method(D_METHOD("on_timer_out2"), &ExpandableButton::on_timer_out2);
    // ClassDB::bind_method(D_METHOD("_on_self_up"), &ExpandableButton::on_self_up);
    // ClassDB::bind_method(D_METHOD("_on_self_down"), &ExpandableButton::on_self_down);
    // ClassDB::bind_method(D_METHOD("_on_self_toggled", "p_state"), &ExpandableButton::on_self_toggled);
}

ExpandableButton::ExpandableButton() {
    set_theme_type_variation("_ExpandableButton_hidden");

	// Initialize internal childs
	// expansion_parent = memnew(Control);
	// expansion = memnew(RevisedButton);
	//idle_time_timer = memnew(Timer);
	// base = memnew(Button);

    // Create internal tree
	// add_child(expansion_parent, false, INTERNAL_MODE_FRONT);
	// expansion_parent->add_child(expansion, false, INTERNAL_MODE_FRONT);
	//expansion_parent->add_child(idle_time_timer, false, INTERNAL_MODE_FRONT);
	// add_child(base, false, INTERNAL_MODE_FRONT);

	// Setup childs
    // expansion->hide();
	// base->hide();
	//idle_time_timer->set_autostart(true);
	//idle_time_timer->set_one_shot(true);
	// expansion_parent->set_clip_contents(true);
    // expansion_parent->set_mouse_filter(Control::MouseFilter::MOUSE_FILTER_IGNORE);
	// expansion->set_mouse_filter(Control::MouseFilter::MOUSE_FILTER_IGNORE);
	// base->set_mouse_filter(Control::MouseFilter::MOUSE_FILTER_IGNORE);
	// expansion->set_toggle_mode(true);
	// base->set_toggle_mode(true);
	set_expansion_size(expansion_size);
	reduce();

	// Signalls
	// Error err = connect("button_down", Callable(this, "_on_self_down"));
	//err = idle_time_timer->connect("timeout", Callable(this, "on_timer_out2"));
	// err = connect("button_up", Callable(this, "_on_self_up"));
	// err = connect("toggled", Callable(this, "_on_self_toggled"));
	Error err = connect("mouse_entered", Callable(this, "expand"));
	err = connect("mouse_exited", Callable(this, "reduce"));
}

ExpandableButton::~ExpandableButton() {
	// expansion_parent->queue_free();
	// expansion->queue_free();
	//idle_time_timer->queue_free();
	// base->queue_free();
}

void ExpandableButton::on_timer_out2() {
    //UtilityFunctions::print("Time out");
    //idle_time_timer->start();
}

void ExpandableButton::on_self_up() {
    if(is_toggle_mode()) return;
    // expansion->set_pressed_no_signal(false);
	// base->set_pressed_no_signal(false);
	//UtilityFunctions::print("on_self_up");
}

void ExpandableButton::on_self_down() {
    if(is_toggle_mode()) return;
    // expansion->set_pressed_no_signal(true);
	// base->set_pressed_no_signal(true);
	//UtilityFunctions::print("on_self_down");
}

void ExpandableButton::on_self_toggled(bool p_state) {
    // expansion->set_pressed_no_signal(p_state);
	// base->set_pressed_no_signal(p_state);
	//UtilityFunctions::print("toggled ",p_state);
}

void ExpandableButton::update_base_size() {
    Vector2 b_siz = get_size();
    //Vector2 ep_siz = expansion_parent->get_size();
    b_siz.y = old_size.y;
    b_siz.x = old_size.x;
    set_size(b_siz);  // Warning
}

void ExpandableButton::expand() {
    //expansion_parent->show();
    is_expanded = true;
}

void ExpandableButton::reduce() {
    //expansion_parent->hide();
    is_expanded = false;
}

void ExpandableButton::_notification(int p_what) {
    switch (p_what) {
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

					color = theme_cache.font_disabled_color;
					if (has_theme(FHT_color,"icon_disabled_color")) {
						color_icon = theme_cache.icon_disabled_color;
					} else {
						color_icon.a = 0.4;
					}

				} break;
			}

			Vector2 expansion_vector,expansion_point,base_vector;

			if (!flat) {
				double tmp = expansion_size_full;
				if(Engine::get_singleton()->is_editor_hint()) {
					if(tmp > size.x + added_size)
						tmp = size.x + added_size;
					expansion_vector = Vector2(tmp,size.y);
					expansion_point = Vector2(size.x-tmp+added_size, 0);
					base_vector = Vector2(size.x,size.y);
				} else {
					if(tmp > size.x)
						tmp = size.x;
					expansion_vector = Vector2(tmp,size.y);
					expansion_point = Vector2(size.x-tmp, 0);
					base_vector = Vector2(size.x-added_size,size.y);
				}
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
				Vector2 ex_size;
				if(expansion_info) {
					ex_size = Vector2(base_vector);
				} else {
					ex_size = Vector2(expansion_vector);
					ex_size.x = ex_size.x - expansion_indentation - info_margin;
				}
				int valign = ex_size.y - style->get_minimum_size().y;

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
					Vector2 _size = ex_size - style->get_offset() * 2;
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
					icon_region = Rect2(style_offset + Vector2(icon_ofs_region + Math::floor((ex_size.x - icon_size.x) * 0.5), voffset + Math::floor((valign - icon_size.y) * 0.5)), icon_size);
				} else {
					icon_region = Rect2(style_offset + Vector2(icon_ofs_region + ex_size.x - icon_size.x, voffset + Math::floor((valign - icon_size.y) * 0.5)), icon_size);
				}

				if(style_offset.x<0) style_offset.x = style_offset.x*(-1);
				old_margin_size = style_offset;
			}

			Vector2 text_size,text_parent_size,text_pos,text_parent_pos;

			if (!flat)	style->draw(ci, Rect2(expansion_point, expansion_vector));
			if (icon_region.size.x > 0 && !expansion_info) {
				icon_region.position.x += expansion_indentation + info_margin;
				old_icon_size = icon_region.size.round();
				Rect2 icon_region_rounded = Rect2(icon_region.position.round()+expansion_point, icon_region.size.round());
				draw_texture_rect(_icon, icon_region_rounded, false, color_icon);
			}
			if (!flat)	style->draw(ci, Rect2(Vector2(0, 0), base_vector));
			if (icon_region.size.x > 0 && expansion_info) {
				old_icon_size = icon_region.size.round();
				Rect2 icon_region_rounded = Rect2(icon_region.position.round(), icon_region.size.round());
				draw_texture_rect(_icon, icon_region_rounded, false, color_icon);
			}

			if(expansion_info) {
				text_pos = style->get_minimum_size();
				text_size = expansion_vector;
				text_size.x = text_size.x - expansion_indentation - info_margin;
				text_size -= text_pos*2;
				text_parent_size = Vector2(added_size-info_margin,size.y);
				text_parent_size -= text_pos*2;
				text_parent_pos.x = base_vector.x+text_pos.x+info_margin;
				text_pos = Vector2(text_parent_size.x-text_size.x,0);
				text_parent_pos.y = 0;
			} else {
				text_parent_pos = Vector2(style->get_minimum_size());
				text_pos = Vector2(0,0);
				text_size = Vector2(base_vector);
				text_size -= text_pos*2;
				text_parent_size = text_size;
			}

			text_container->set_size(text_size);
			text_parent->set_size(text_parent_size);
			text_parent->set_position(text_parent_pos);
			text_container->set_position(text_pos);

			if (has_focus()) {
				Ref<StyleBox> style2 = theme_cache.focus;
				style2->draw(ci, Rect2(Vector2(), size));
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
		} break;
        default: {
            RevisedButton::_notification(p_what);
        } break;
	}
}

void ExpandableButton::_process(double delta) {
	Vector2 text_size = text_container->get_size();
	Vector2 text_pos = text_container->get_position();
	Vector2 text_parent_size = text_parent->get_size();
	Vector2 text_parent_pos = text_parent->get_position();

    RevisedButton::_process(delta);
	
	text_container->set_size(text_size);
	text_parent->set_size(text_parent_size);
	text_parent->set_position(text_parent_pos);
	text_container->set_position(text_pos);

	set_adaptable_speed(adaptable_speed);

	double height = get_size().y;
    double width = get_size().x;

	if(old_size.y!=height) {
        old_size.y = height;
    }

	if(Engine::get_singleton()->is_editor_hint()) {
        if(old_size.x!=width)
            old_size.x = width;

		double delta_speed = delta*speed*abs(expansion_size)/10;

		if(is_expanded && added_size != expansion_size){
			if(added_size + delta_speed < expansion_size)
				added_size += delta_speed;
			else if(added_size - delta_speed > expansion_size)
				added_size -= delta_speed;
			else added_size = expansion_size;
        }
        if(!is_expanded && added_size > 0){
			added_size -= delta_speed;
        }
		queue_redraw();

	} else {
        if(old_size.x!=width)//-siz.x)
            old_size.x = width;//-siz.x;

		double delta_speed = delta*speed*expansion_size/10;

        if(is_expanded && added_size < expansion_size){
			added_size += delta_speed;
			width += delta_speed;
        }
        if(!is_expanded && added_size > 0){
			added_size -= delta_speed;
			width -= delta_speed;
        }
        set_size(Vector2(width,height));
        emit_signal("size_flags_changed");
        emit_signal("minimum_size_changed");
	}

    /* double height = get_size().y;
    double width = get_size().x;
    Vector2 siz = expansion_parent->get_size();
    Vector2 pos = expansion_parent->get_position();
    Vector2 pos_ex = expansion->get_position();

    if(old_size.y!=height) {
        old_size.y = height;
        siz.y = height;
    }

    if(Engine::get_singleton()->is_editor_hint()) {
        if(old_size.x!=width)
            old_size.x = width;

        expansion->set_size(Vector2(expansion_size+expansion_indentation,siz.y));
        pos_ex.x = pos_ex.x+expansion_indentation;
        double delta_speed = delta*speed*expansion_size/10;

        if(siz.x>expansion_size){
            siz.x -= delta_speed;
            width -= delta_speed;
        }
        if(is_expanded){
            if(siz.x+delta_speed<=expansion_size) siz.x += delta_speed;
            if(pos_ex.x+delta_speed<=0) pos_ex.x+=delta_speed;
            else pos_ex.x = 0;
        }
        if(!is_expanded){
            if(siz.x>0) siz.x -= delta_speed;
            if(pos_ex.x>-expansion_size) pos_ex.x-=delta_speed;
        }
        width = siz.x+old_size.x;
        pos.x = width-siz.x;
        pos_ex.x = pos_ex.x-expansion_indentation;

    } else {
        if(old_size.x!=width-siz.x)
            old_size.x = width-siz.x;

        expansion->set_size(Vector2(expansion_size+expansion_indentation,siz.y));
        pos_ex.x = pos_ex.x+expansion_indentation;
        double delta_speed = delta*speed*expansion_size/10;

        if(siz.x>expansion_size){
            siz.x -= delta_speed;
            width -= delta_speed;
        }
        if(is_expanded){
            if(siz.x+delta_speed<=expansion_size) siz.x += delta_speed;
            if(pos_ex.x+delta_speed<=0) pos_ex.x+=delta_speed;
            else pos_ex.x = 0;
        }
        if(!is_expanded){
            if(siz.x>0) siz.x -= delta_speed;
            if(pos_ex.x>-expansion_size) pos_ex.x-=delta_speed;
        }
        width = siz.x+old_size.x;
        pos.x = width-siz.x;
        pos_ex.x = pos_ex.x-expansion_indentation;

        set_size(Vector2(width,height));
        emit_signal("size_flags_changed");
        emit_signal("minimum_size_changed");
    }

    expansion_parent->set_size(siz);
    expansion_parent->set_position(pos);
    expansion->set_position(pos_ex);
    base->set_size(old_size);//update_base_size();

	base_x = old_size.x;
	double tmp = expansion->get_size().x;
	if(tmp<=siz.x) 	
		expansion_x = tmp;
	else expansion_x = siz.x;

    Ref<Texture2D> texture = get_icon();
    Ref<Texture2D> texture2 = base->get_button_icon();
    if(texture!=texture2) {
        base->set_button_icon(texture);
    } */
}

Vector2 ExpandableButton::_get_minimum_size() const {
    Ref<Texture2D> texture = get_icon();
	//Check if texture exist
	if(!texture.is_valid())
        texture = memnew(Ref<Texture2D>);
    Vector2 _min = Vector2(0,0);//get_minimum_size_for_text_and_icon("", texture);
	if(!Engine::get_singleton()->is_editor_hint())
    	_min.x += added_size;
	return _min;
}

void ExpandableButton::set_expansion_size(int p_size) {
    expansion_size_full = p_size;
    expansion_size = p_size - expansion_indentation;
}

int ExpandableButton::get_expansion_size() {
    return expansion_size_full;
}

void ExpandableButton::set_expansion_info(int p_int) {
    if(p_int<=0) expansion_info = false;
    else expansion_info = true;
}

int ExpandableButton::get_expansion_info() {
    if(expansion_info) return 1;
	else return 0;
}

void ExpandableButton::set_info_margin(int p_margin) {
    info_margin = p_margin;
}

int ExpandableButton::get_info_margin() {
    return info_margin;
}

void ExpandableButton::set_expansion_indentation(int p_indentation) {
    expansion_indentation = p_indentation;
    expansion_size = expansion_size_full - expansion_indentation;
    // Vector2 pos = expansion_parent->get_position();
    // pos.x = old_size.x-expansion_indentation;
    // expansion_parent->set_position(pos);
}

int ExpandableButton::get_expansion_indentation() {
    return expansion_indentation;
}

void ExpandableButton::set_expansion_speed(double p_speed) {
    speed = p_speed;
}

double ExpandableButton::get_expansion_speed() {
    return speed;
}

/* void ExpandableButton::set_theme_childs_type_variation(const StringName &p_theme_type) {
	if (theme_type_variation == p_theme_type) return;
	theme_type_variation = p_theme_type;
	base->set_theme_type_variation(p_theme_type);
	expansion->set_theme_type_variation(p_theme_type);
	if (is_inside_tree()) {
		notification(NOTIFICATION_THEME_CHANGED);
	}
} */

StringName ExpandableButton::get_theme_childs_type_variation() const {
	return theme_type_variation;
}
