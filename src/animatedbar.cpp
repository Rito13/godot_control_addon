#include "animatedbar.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void AnimatedBar::_bind_methods() {
}

AnimatedBar::AnimatedBar() {
	// Initialize any variables here.
	time_passed = 0.0;
}

AnimatedBar::~AnimatedBar() {
	// Add your cleanup here.
}

void AnimatedBar::_process(double delta) {
	// Do Something
}
