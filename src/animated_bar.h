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
	BaseButton *left;
	BaseButton *right;
	bool focus = false;
	Control *first_child = nullptr;
	int first_child_id = 0;
	int subtracted_value = 0;

protected:
	static void _bind_methods();

public:
	AnimatedBar();
	~AnimatedBar();

	void _notification(int p_what);
	void _process(double delta);

	void on_button_pressed(int id,BaseButton *status);
	void on_right_pressed();
	void on_left_pressed();

	PackedStringArray _get_configuration_warnings() const override;
};

}

#endif
