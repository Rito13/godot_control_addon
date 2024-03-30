#ifndef ANIMATEDTABCONTAINER_H
#define ANIMATEDTABCONTAINER_H

#include <godot_cpp/classes/container.hpp>
#include "animated_bar.h"

namespace godot {

class AnimatedTabContainer : public Container {
	GDCLASS(AnimatedTabContainer, Container)

private:
	int number_of_animated_bars;
	Control *curent_tab = nullptr;
	bool is_activated = false;
	AnimatedBar *curent_animated_bar = nullptr;

protected:
	static void _bind_methods();

public:
	AnimatedTabContainer();
	~AnimatedTabContainer();

	void _notification(int p_what);
	void _process(double delta);
	void clip_child(Control* child);

	void on_focus_activated(int p_tab_id,int p_bar_id);
	void on_focus_changed(int p_tab_id,int p_bar_id);
	void on_focus_deactivated();

	virtual Vector2 _get_minimum_size() const override;
	PackedStringArray _get_configuration_warnings() const override;
};

}

#endif
