#ifndef EXPANDABLE_BUTTON_H
#define EXPANDABLE_BUTTON_H

#include "button.h"

namespace godot {

class ExpandableButton : public RevisedButton {
	GDCLASS(ExpandableButton, RevisedButton)

private:
    bool is_text_off = false;
    Timer *idle_time_timer;
	Control *expansion_parent;
	RevisedButton *expansion;
	Button *base;
	int expansion_size = 70;
	int expansion_size_full = 70;
	int expansion_indentation = 0;
	Vector2 old_size = Vector2(0,0);
	bool is_expanded = false;
	double speed = 25;

protected:
	static void _bind_methods();
	void update_base_size();

public:
	ExpandableButton();
	~ExpandableButton();

	void _process(double delta);

	void set_is_text_off(bool p_status)override;
	bool get_is_text_off()override;

	void set_expansion_size(int p_size);
	int get_expansion_size();

	void set_expansion_indentation(int p_indentation);
	int get_expansion_indentation();

	void expand();
	void reduce();

	void set_expansion_speed(double p_speed);
	double get_expansion_speed();
};

}

#endif
