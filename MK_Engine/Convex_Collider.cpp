#include "Convex_Collider.h"
#include "Circle_Collider.h"
#include "Object.h"
#include "Error.h"

namespace mk
{
	Convex_Collider::Convex_Collider(Object* _gameObject)
	{
		gameObject = _gameObject;
		assignedShape = gameObject->getComponent<Convex>();
		if (!assignedShape) throw Error::COMPONENT_NOT_FOUND;
		assignedRigidbody = gameObject->getComponent<Rigidbody>();
		if (!assignedRigidbody) throw Error::COMPONENT_NOT_FOUND;
		convexColliders.push_back(this);

		closeArea = Close_Area(assignedShape);
	}
	Shape* Convex_Collider::getShape() const
	{
		return assignedShape;
	}
}