#ifndef ANIMATEDBAR_H
#define ANIMATEDBAR_H

#include <godot_cpp/classes/control.hpp>

namespace godot {

class AnimatedBar : public Control {
	GDCLASS(AnimatedBar, Control)

private:
	double time_passed;

protected:
	static void _bind_methods();

public:
	AnimatedBar();
	~AnimatedBar();

	void _process(double delta);
};

}

#endif
