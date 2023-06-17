#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Component.h"
#include "Shape.h"
#include "Math.h"
#include "Rigidbody.h"
#include "Close_Area.h"

namespace mk
{
	class Convex_Collider;
	class Circle_Collider;
	struct Collision
	{
		bool isDetected = false;
		sf::Vector2f collisionNormal = sf::Vector2f(0, 0);
		float penetratrion = 0;
		sf::Vector2f contactPoint;
		float impulseScalar;
	};
	class Collider : public Component
	{
	private:
		static Collision collisionInfo;
	protected:
		static std::vector<Convex_Collider*> convexColliders;
		static std::vector<Circle_Collider*> circleColliders;
	public:
		bool isColliding;
		bool isEnabled = true;
		bool isResponding = true;

		Rigidbody* assignedRigidbody;
		Close_Area closeArea;
		float maximumImpactForce = 0;
		float staticFriction = 0.6f;
		float dynamicFriction = 0.4f;
		
		virtual ~Collider();

		static void collideAll();
		static void collide(Convex_Collider&, Convex_Collider&);
		static void collide(Circle_Collider&, Circle_Collider&);
		static void collide(Circle_Collider&, Convex_Collider&);
		static void collisionResolution(Collider&, Collider&, float&);

		static bool isCollidingWithAnything(Collider*);
		bool isCollidingWithAnything();

		virtual Shape* getShape() const { return nullptr; };
		friend void collideAll();
	};
}