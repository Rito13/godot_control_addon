#ifndef REVISED_BUTTON_H
#define REVISED_BUTTON_H

#include "better_scroll.h"
#include <godot_cpp/classes/v_scroll_bar.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/classes/rich_text_label.hpp>
#include <cstdint>
// For Theme
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/classes/style_box.hpp>
#include <godot_cpp/classes/font.hpp>

namespace godot {

typedef bool (*theme_has) (const StringName&, const StringName&);

class RevisedButton : public BaseButton {
	GDCLASS(RevisedButton, BaseButton)

private:
	double time_passed;
	double amplitude;
	double old_height = 0;
	//Internal children
	AutoScroll *scroll;
	Timer *idle_time_timer;
	Control *text_parent;
	RichTextLabel *text_container;
	double adaptable_speed = 20;
	//Aligment functions and variables
	String _h_bbcode = "[center]";
	String _v_bbcode = "";
	double calculate_center_vertical_alignment(double y);
	void update_text_horizontal_alignment();
	bool update_text_vertical_alignment(bool recursive = false);
	//State variables
	bool scrolling = true;
	bool timer_time_2 = false;
	uint8_t is_CVA_calculated = 0;
	bool is_text_off = false;
	bool force_vertical_alignment_before_horizontal = false;

protected:
	static void _bind_methods();
	String better_text = "Text";

	Vector2 _fit_icon_size(const Vector2 &p_size) const;
	//bool has_theme_something(bool (&what)(const StringName&, const StringName&)const,const StringName &name);
	bool has_theme(uint8_t what,const StringName &name) const;

	//Vars which expandable button uses
	Color used_font_color = Color(1,1,1);
	String _color_bbcode = "";
	float _internal_margin[4] = {};
	//Aligment functions and variables
	HorizontalAlignment horizontal_icon_alignment = HORIZONTAL_ALIGNMENT_CENTER;
	HorizontalAlignment h_text_alignment = HORIZONTAL_ALIGNMENT_CENTER;
	VerticalAlignment v_text_alignment = VERTICAL_ALIGNMENT_TOP;
	VerticalAlignment vertical_icon_alignment = VERTICAL_ALIGNMENT_TOP;
	//State variables
	bool flat = false;
	bool shrink_icon = false;
	Vector2 old_icon_size = Vector2(0,0);
	Vector2 old_margin_size = Vector2(0,0);
	Ref<Texture2D> icon;

	// Theme properties
	struct ThemeCache {
		Ref<StyleBox> normal;
		Ref<StyleBox> normal_mirrored;
		Ref<StyleBox> pressed;
		Ref<StyleBox> pressed_mirrored;
		Ref<StyleBox> hover;
		Ref<StyleBox> hover_mirrored;
		Ref<StyleBox> hover_pressed;
		Ref<StyleBox> hover_pressed_mirrored;
		Ref<StyleBox> disabled;
		Ref<StyleBox> disabled_mirrored;
		Ref<StyleBox> focus;

		Color font_color;
		Color font_focus_color;
		Color font_pressed_color;
		Color font_hover_color;
		Color font_hover_pressed_color;
		Color font_disabled_color;

		Ref<Font> font;
		int font_size = 0;
		int outline_size = 0;
		Color font_outline_color;

		Color icon_normal_color;
		Color icon_focus_color;
		Color icon_pressed_color;
		Color icon_hover_color;
		Color icon_hover_pressed_color;
		Color icon_disabled_color;

		int h_separation = 0;
		int icon_max_width = 0;
	} theme_cache;

	static const uint8_t FHT_constant = 0;
    static const uint8_t FHT_color = 1;
	static const uint8_t FHT_stylebox = 2;
	static const uint8_t FHT_font = 3;
	static const uint8_t FHT_font_size = 4;
	static const uint8_t FHT_icon = 255;


public:
	RevisedButton();
	~RevisedButton();

	void _process(double delta);
	void on_timer_out();
	void _notification(int p_what);
	virtual Vector2 _get_minimum_size() const override;

	void find_theme(StringName type,bool check = false);
	void get_theme(bool p_bool);

	//Amplitude property
	void set_amplitude(const double p_amplitude);
	double get_amplitude() const;
	//Text property
	void set_text(const String p_text);
	String get_text() const;
	void update_text(bool recursive = false);
	//Icon property
	void set_icon(const Ref<Texture2D> p_icon);
	Ref<Texture2D> get_icon() const;
	void update_icon();
	//Autowrap property
	TextServer::AutowrapMode get_text_autowrap() const;
	void set_text_autowrap(const TextServer::AutowrapMode p_autowrap);
	//Adaptable Speed property
	void set_adaptable_speed(double p_speed);
	double get_adaptable_speed();
	//Is Text Off property
	virtual void set_is_text_off(bool p_status);
	virtual bool get_is_text_off();
	//Flat property
	void set_flat_status(bool p_status);
	bool get_flat_status();
	//Expand Icon property
	void set_icon_shrink(bool p_status);
	bool get_icon_shrink();

	// Aligment
    //Text
    HorizontalAlignment get_text_alignment() const;
    VerticalAlignment get_v_text_alignment() const;
    void set_text_alignment(const HorizontalAlignment p_alignment);
    void set_v_text_alignment(const VerticalAlignment p_alignment);
    //Icon
    HorizontalAlignment get_icon_alignment() const;
    VerticalAlignment get_vertical_icon_alignment() const;
    void set_icon_alignment(const HorizontalAlignment p_alignment);
    void set_vertical_icon_alignment(const VerticalAlignment p_alignment);
	//Order
	void set_force_vertical_alignment_before_horizontal(const int p_order);
	int get_force_vertical_alignment_before_horizontal() const;
};

}

#endif
