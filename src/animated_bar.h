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

private:
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

	struct ForReady {
		NodePath left_path;
		NodePath right_path;
		bool custom_lr = false;
		bool lr_visibility = true;
	} for_ready;

protected:
	static void _bind_methods();

public:
	AnimatedBar();
	~AnimatedBar();

	void _notification(int p_what);
	void _process(double delta);
	void _ready();

	int get_options_quantity() const;
	Vector2 get_lr_size() const;
	Vector2 get_right_size() const;
	Vector2 get_left_size() const;
	void deactivate_focus();

	void on_button_pressed(int id,BaseButton *status);
	void on_right_pressed();
	void on_left_pressed();

	double get_spacing();
	void set_spacing(double p_spacing);

	double get_spacing2();
	void set_spacing2(double p_spacing);

	double get_speed();
	void set_speed(double p_speed);

	bool get_lr_visibility();
	void set_lr_visibility(bool is_enabled);

	bool get_custom_lr();
	void set_custom_lr(bool is_enabled);

	NodePath get_custom_left();
	void set_custom_left(NodePath p_path);

	NodePath get_custom_right();
	void set_custom_right(NodePath p_path);

	virtual Vector2 _get_minimum_size() const override;
	PackedStringArray _get_configuration_warnings() const override;
};

}

#endif
