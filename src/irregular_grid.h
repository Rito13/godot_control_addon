#ifndef IRREGULAR_GRID_H
#define IRREGULAR_GRID_H

#include <godot_cpp/classes/container.hpp>
#include <godot_cpp/classes/flow_container.hpp>
#include <vector>
#include "expandable_button.h"

namespace control_plus_plus {

struct irregular_grid_element
{
	float x = 0.0;
	float aditional = 0.0;
	int count = 0;
};

class IrregularGrid : public godot::Container {
private:
	std::vector<irregular_grid_element> GRID;

protected:
	double spacing;
	double min_height;

	void Add(godot::Control *child);
	void Add_ExpandableButton(godot::ExpandableButton *child);
	void Clear();
	void rearrange_with_b();

public:
	IrregularGrid();
	~IrregularGrid();

	void rearrange(bool from_exp_button = false);
	void sort();
};

}

namespace godot {

class IrregularGridContainer : public control_plus_plus::IrregularGrid {
	GDCLASS(IrregularGridContainer, Container)

protected:
	static void _bind_methods();

public:
	IrregularGridContainer();
	~IrregularGridContainer();

	virtual Vector2 _get_minimum_size() const override;

	void _notification(int p_what);

	void set_spacing(double p_spacing);
	double get_spacing();
};

}

#endif
