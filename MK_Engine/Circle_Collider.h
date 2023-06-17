#pragma once
#include "Circle.h"
#include "Collider.h"


namespace mk 
{
	class Circle_Collider : public Collider
	{
	public:
		Circle *assignedShape;
		Circle_Collider(Object*);
		Shape* getShape() const;
	};
}