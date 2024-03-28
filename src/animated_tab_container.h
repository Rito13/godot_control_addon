#ifndef ANIMATEDTABCONTAINER_H
#define ANIMATEDTABCONTAINER_H

#include <godot_cpp/classes/container.hpp>

namespace godot {

class AnimatedTabContainer : public Container {
	GDCLASS(AnimatedTabContainer, Container)

private:
	double time_passed;

protected:
	static void _bind_methods();

public:
	AnimatedTabContainer();
	~AnimatedTabContainer();

	void _process(double delta);
};

}

#endif
