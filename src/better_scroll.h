#ifndef better_scroll_H
#define better_scroll_H

#include <godot_cpp/classes/range.hpp>
#include <godot_cpp/classes/translation.hpp>

namespace godot {

class AutoScroll : public Control {
	GDCLASS(AutoScroll, Control);

private:
    double minus_step = 0;
    void a_slide(Range *range_object, double step=1.0);
    double end_value = 0;
    bool scrolling = false;
    double custom_min = 0;
    double speed = 10;
    bool use_custom_min = false;
    bool custom_min_to_reset = false;

protected:
	static void _bind_methods();

public:
	AutoScroll();
    ~AutoScroll();
    void scroll_to(double p_value);
    void set_auto_min_value(double p_value);
    double get_auto_min_value();
    void set_speed(double p_speed);
    double get_speed();
    void _process(double delta);
    PackedStringArray _get_configuration_warnings() const override;
    bool is_scrolling();
    //String get_configuration_warnings_as_string() const;
};

}

#endif
