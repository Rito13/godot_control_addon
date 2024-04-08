#ifndef ANIMATEDTABCONTAINER_H
#define ANIMATEDTABCONTAINER_H

#include <godot_cpp/classes/container.hpp>
#include "animated_bar.h"

namespace godot {

class AnimatedTabContainer : public Container {
	GDCLASS(AnimatedTabContainer, Container)

private:
	int number_of_animated_bars;
	double speed = 4;
	double focus_status = 0;
	Control *curent_tab = nullptr;
	Control *next_tab = nullptr;
	bool is_activated = false;
	AnimatedBar *curent_animated_bar = nullptr;
	double _y = 0;

protected:
	static void _bind_methods();
	void process(double delta);

public:
	AnimatedTabContainer();
	~AnimatedTabContainer();

	void _notification(int p_what);
	void clip_child(Control* child);

	void on_focus_activated(int p_tab_id,int p_bar_id);
	void on_focus_changed(int p_tab_id,int p_bar_id);
	void on_focus_deactivated();

	double get_speed();
	void set_speed(double p_speed);

	virtual Vector2 _get_minimum_size() const override;
	PackedStringArray _get_configuration_warnings() const override;
};

}

#endif
