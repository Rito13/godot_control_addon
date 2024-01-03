#ifndef EXPANDABLE_BUTTON_H
#define EXPANDABLE_BUTTON_H

#include "button.h"

namespace godot {

class ExpandableButton : public RevisedButton {
	GDCLASS(ExpandableButton, RevisedButton)

private:
    bool is_text_off = false;
    Timer *idle_time_timer;
	Control *expand_parent;
	RevisedButton *expand;
	int expand_size = 30;

protected:
	static void _bind_methods();

public:
	ExpandableButton();
	~ExpandableButton();

	void _process(double delta);

	void set_is_text_off(bool p_status)override;
	bool get_is_text_off()override;

	void set_expand_size(int p_size);
	int get_expand_size();
};

}

#endif
