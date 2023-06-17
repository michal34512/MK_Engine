#include "Object.h"

namespace mk
{
	Object::Object()
	{
		allObjects.emplace_back(this);
		return;
	}
	void Object::UpdateComponents()
	{
		for (Component* c : allComponentsVector)
		{
			c->Update();
		}
	}
	void Object::removeAllComponents()
	{
		for (Component* a : allComponentsVector)
			delete(a);
		allComponents.clear();
		allComponentsVector.clear();
	}
	Object::~Object() {
		for (auto it = allObjects.begin(); it != allObjects.end(); it++)
			if (*it == this)
			{
				allObjects.erase(it);
				break;
			}
		removeAllComponents();
	}
	std::vector<Object*> Object::allObjects;
}
