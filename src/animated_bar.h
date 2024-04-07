#ifndef ANIMATEDBAR_H
#define ANIMATEDBAR_H

#include <godot_cpp/classes/container.hpp>
#include <godot_cpp/classes/button.hpp>

godot::String RTR(const godot::String &p_text, const godot::String &p_context = godot::String());
// Body of this function is writen in better_scroll.cpp file.
// To compile only this class please copy body of this function to animated_bar.cpp file.

namespace godot {

class AnimatedBar : public Container {
	GDCLASS(AnimatedBar, Container)
	
protected:
	double spacing;
	double spacing2;
	double speed = 4;
	BaseButton *left;
	BaseButton *right;
	BaseButton *custom_left = nullptr;
	BaseButton *custom_right = nullptr;
	int number_of_children = 0;
	bool focus = false;
	bool lr_visibility = true;
	bool custom_lr = false;
	Control *first_child = nullptr;
	int first_child_id = 0;
	double subtracted_value = 0.0;
	int to_subtract_value = 0;
	bool after_ready = false;
	bool lr_auto_visibility = true;
	bool do_expand = true;
	bool is_process = false;
	bool deactivate_process = true;

	struct Labels {
		String left = "L";
		String right = "R";
	} _labels;

	struct ForReady {
		NodePath left_path;
		NodePath right_path;
		bool custom_lr = false;
		int lr_visibility = 3;
	} for_ready;

protected:
	static void _bind_methods();
	void set_to_subtract_value(int p_value);
	void process(double delta);
	void ready();

public:
	AnimatedBar();
	~AnimatedBar();

	void _notification(int p_what);

	int get_options_quantity() const;
	virtual Vector2 get_lr_size() const;
	virtual Vector2 get_right_size() const;
	virtual Vector2 get_left_size() const;
	void deactivate_focus();

	void on_button_pressed(int id,BaseButton *status);
	//void on_right_pressed();
	//void on_left_pressed();

	//void clip_child(Control* child);

	double get_spacing();
	void set_spacing(double p_spacing);

	double get_spacing2();
	void set_spacing2(double p_spacing);

	double get_speed();
	void set_speed(double p_speed);

	bool get_lr_visibility();
	int get_lr_visibility_v2();
	void set_lr_visibility(int p_state);

	bool get_custom_lr();
	void set_custom_lr(bool is_enabled);

	bool is_remaining_space_filled();
	void set_fill_remaining_space(bool is_enabled);

	bool get_deactivate_process();
	void set_deactivate_process(bool is_enabled);

	NodePath get_custom_left();
	void set_custom_left(NodePath p_path);

	NodePath get_custom_right();
	void set_custom_right(NodePath p_path);

	//virtual Vector2 _get_minimum_size() const override;
	PackedStringArray _get_configuration_warnings() const override;
};

class HAnimatedBar : public AnimatedBar {
	GDCLASS(HAnimatedBar, AnimatedBar)

protected:
	static void _bind_methods();

public:
	HAnimatedBar();
	~HAnimatedBar();

	void _notification(int p_what);

	virtual Vector2 get_lr_size() const;
	virtual Vector2 get_right_size() const;
	virtual Vector2 get_left_size() const;

	void on_right_pressed();
	void on_left_pressed();

	void clip_child(Control* child);

	virtual Vector2 _get_minimum_size() const override;
};

class VAnimatedBar : public AnimatedBar {
	GDCLASS(VAnimatedBar, AnimatedBar)

protected:
	static void _bind_methods();

public:
	VAnimatedBar();
	~VAnimatedBar();

	void _notification(int p_what);

	virtual Vector2 get_lr_size() const;
	virtual Vector2 get_right_size() const;
	virtual Vector2 get_left_size() const;

	void on_right_pressed();
	void on_left_pressed();

	void clip_child(Control* child);

	virtual Vector2 _get_minimum_size() const override;
};

}

#endif
