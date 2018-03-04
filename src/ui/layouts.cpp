#include "ui.hpp"


namespace rack {


void SequentialLayout::step() {
	Widget::step();

	float offset = margin;
	for (Widget *child : children) {
		if (!child->visible)
			continue;
		// Set position
		(orientation == HORIZONTAL_ORIENTATION ? child->box.pos.x : child->box.pos.y) = offset;
		// Increment by size
		offset += (orientation == HORIZONTAL_ORIENTATION ? child->box.size.x : child->box.size.y);
		offset += padding;
	}

	// We're done if left aligned
	if (alignment == LEFT_ALIGNMENT)
		return;

	// Adjust positions based on width of the layout itself
	offset -= padding;
	offset += margin;
	if (alignment == RIGHT_ALIGNMENT)
		offset -= (orientation == HORIZONTAL_ORIENTATION ? box.size.x : box.size.y);
	else if (alignment == CENTER_ALIGNMENT)
		offset -= (orientation == HORIZONTAL_ORIENTATION ? box.size.x : box.size.y) / 2.0;
	for (Widget *child : children) {
		if (!child->visible)
			continue;
		(orientation == HORIZONTAL_ORIENTATION ? child->box.pos.x : child->box.pos.y) += offset;
	}
}


} // namespace rack
