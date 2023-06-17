#include "Circle_Collider.h"
#include "Object.h"
#include "Error.h"


namespace mk
{
	Circle_Collider::Circle_Collider(Object* _gameObject)
	{
		gameObject = _gameObject;
		assignedShape = gameObject->getComponent<Circle>();
		if (!assignedShape) throw Error::COMPONENT_NOT_FOUND;
		assignedRigidbody = gameObject->getComponent<Rigidbody>();
		if (!assignedRigidbody) throw Error::COMPONENT_NOT_FOUND;
		circleColliders.push_back(this);

		closeArea = Close_Area(assignedShape);
	}
	Shape* Circle_Collider::getShape() const
	{
		return assignedShape;
	}
}