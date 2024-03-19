#ifndef EXPANDABLE_BUTTON_H
#define EXPANDABLE_BUTTON_H

#include "button.h"

namespace godot {

class ExpandableButton : public RevisedButton {
	GDCLASS(ExpandableButton, RevisedButton)

private:
    bool is_text_off = false;
    Timer *idle_time_timer;
	// Control *expansion_parent;
	// RevisedButton *expansion;
	// Button *base;
	int expansion_size = 70;
	int expansion_size_full = 70;
	int expansion_indentation = 0;
	Vector2 old_size = Vector2(0,0);
	double added_size = 0.0;
	bool is_expanded = false;
	double speed = 25;
	StringName theme_type_variation;

protected:
	static void _bind_methods();
	void update_base_size();

public:
	ExpandableButton();
	~ExpandableButton();

	virtual Vector2 _get_minimum_size() const override;

	void _process(double delta);
	void _notification(int p_what);
	void on_timer_out2();
	void on_self_down();
	void on_self_up();
	void on_self_toggled(bool p_state);

	void set_expansion_size(int p_size);
	int get_expansion_size();

	void set_expansion_indentation(int p_indentation);
	int get_expansion_indentation();

	void expand();
	void reduce();

	void set_expansion_speed(double p_speed);
	double get_expansion_speed();

	// void set_theme_childs_type_variation(const StringName &p_theme_type);
	StringName get_theme_childs_type_variation() const;
};

}

#endif