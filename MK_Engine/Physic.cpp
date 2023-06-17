#include "Physic.h"
#include "Object.h"

namespace mk 
{
	void Physic::Update()
	{
		deltaTime = deltaTimeClock.restart().asSeconds();
		if (deltaTime > 0.2f) deltaTime = 0; //dirty fix for freezed frame
		
		for (Object* obj : Object::allObjects)
		{
			obj->UpdateComponents();
		}
		Shape::drawAll(*window);
		Collider::collideAll();
		DebugDot::drawAll();
	}
	float Physic::getDeltaTime()
	{
		return deltaTime;
	}
	void Physic::setWindow(sf::RenderWindow& _window)
	{
		window = &_window;
	}
	sf::RenderWindow& Physic::getWindow()
	{
		return *window;
	}
	sf::Clock Physic::deltaTimeClock;
	float Physic::deltaTime = 0;
	sf::RenderWindow* Physic::window;
}
