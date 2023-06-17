#pragma once
#include "Convex.h"
#include "Collider.h"


namespace mk
{
	class Convex_Collider : public Collider
	{
	public:
		Convex* assignedShape;
		Convex_Collider(Object*);
		Shape* getShape() const;
	};
}