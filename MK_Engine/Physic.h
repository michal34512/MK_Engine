#pragma once
#include "Shape.h"
#include "Convex.h"
#include "Circle.h"
#include "Sprite.h"
#include "Rigidbody.h"

#include "Collider.h"
#include "Circle_Collider.h"
#include "Convex_Collider.h"

#include "Error.h"

#include "Object.h"
#include "Component.h"

#include "DebugDot.h"

namespace mk
{
	class Physic
	{
		static sf::Clock deltaTimeClock;
		static float deltaTime;
		static sf::RenderWindow* window;
	public:
		static void Update();
		static float getDeltaTime();
		static void setWindow(sf::RenderWindow&);
		static sf::RenderWindow& getWindow();
	};
}
