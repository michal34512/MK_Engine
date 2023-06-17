#include "Collider.h"
#include "Circle_Collider.h"
#include "Convex_Collider.h"
#include "DebugDot.h"

sf::Vector2f operator*(const int& a, const sf::Vector2f& b);
namespace mk
{
#pragma region Collision_Types
	/*
					*SAT collision detection*
		Shapes cast shadows along each of their face.
		If at least one cast is not intersepting, a collision is NOT detected
								^
							  / |
							/   |
						  /     |
						/       |
					  /         |
					/			|   ______________
				  ._____________|  /|            |
				/			   / /	|            |
			  /				 / /  	|            |
			-----		   / /		--------------
				 -----	 / /					/
					  -----					  /
							-----			/
								 -----	  /
									  ----
	*/


	sf::Vector2f furthestPoint(sf::Vector2f dir, Convex& a)
	{
		float  furthestDistance = -INFINITY;
		sf::Vector2f res;
		for (int i = 0; i < a.polygon.getPointCount(); i++)
		{
			float dis = Math::dotProduct(a.getAbsolutePosition(i), dir);
			if (dis > furthestDistance)
			{
				furthestDistance = dis;
				res = a.getAbsolutePosition(i);
			}
		}
		return res;
	}
	sf::Vector2f getNormal(Convex* a, unsigned int i)
	{
		if (a->polygon.getPointCount() - 1 < i) return sf::Vector2f(0, 0); //error
		if (a->polygon.getPointCount() - 1 == i) return Math::turnByAngle(Math::normalize(Math::rightAngleCounterClockwise(a->polygon.getPoint(a->polygon.getPointCount() - 1) - a->polygon.getPoint(0))), Math::degToRadians(a->getRotation()));
		return Math::turnByAngle(Math::normalize(Math::rightAngleCounterClockwise(a->polygon.getPoint(i) - a->polygon.getPoint(i + 1))), Math::degToRadians(a->getRotation()));
	}
	float distanceToSegment(sf::Vector2f a, sf::Vector2f b, sf::Vector2f point)
	{
		sf::Vector2f halfDif = (b - a) * 0.5f;
		sf::Vector2f normal = Math::normalize(halfDif);
		sf::Vector2f middlePoint = (a + b) * 0.5f;
		float abHalfDistnaceSq = Math::squaredDistance(halfDif);
		sf::Vector2f pointAlong = Math::dotProduct(normal, point - middlePoint) * normal;
		if (Math::squaredDistance(pointAlong) > abHalfDistnaceSq || Math::squaredDistance(pointAlong) < -abHalfDistnaceSq) {
			return Math::squaredDistance(point - b) < Math::squaredDistance(point - a) ? Math::distance(point - b) : Math::distance(point - a);
		}
		return Math::distance(pointAlong + middlePoint - point);
	}
	void getContactPoint(Convex* a, Convex* b, Collision& col)
	{
		sf::Vector2f cpA, cpB;
		float disA = INFINITY, disB = INFINITY;
		unsigned int contactPointCount = 0;
		for (int i = 0; i < a->polygon.getPointCount(); i++)
		{
			sf::Vector2f aVer, bVer;
			aVer = a->getAbsolutePosition(i);
			if (i + 1 != a->polygon.getPointCount())
				bVer = a->getAbsolutePosition(i + 1);
			else bVer = a->getAbsolutePosition(0);
			for (int j = 0; j < b->polygon.getPointCount(); j++)
			{
				float dis = distanceToSegment(aVer, bVer, b->getAbsolutePosition(j));
				if (contactPointCount == 1 && Math::nearlyTheSame(dis, disA))
				{
					disB = dis;
					cpB = b->getAbsolutePosition(j);
					contactPointCount = 2;
				}
				else if (dis < disA)
				{
					disA = dis;
					cpA = b->getAbsolutePosition(j);
					contactPointCount = 1;
				}
			}
		}
		for (int i = 0; i < b->polygon.getPointCount(); i++)
		{
			sf::Vector2f aVer, bVer;
			aVer = b->getAbsolutePosition(i);
			if (i + 1 != b->polygon.getPointCount())
				bVer = b->getAbsolutePosition(i + 1);
			else bVer = b->getAbsolutePosition(0);
			for (int j = 0; j < a->polygon.getPointCount(); j++)
			{
				float dis = distanceToSegment(aVer, bVer, a->getAbsolutePosition(j));
				if (contactPointCount == 1 && Math::nearlyTheSame(dis, disA))
				{
					disB = dis;
					cpB = a->getAbsolutePosition(j);
					contactPointCount = 2;
				}
				else if (dis < disA)
				{
					disA = dis;
					cpA = a->getAbsolutePosition(j);
					contactPointCount = 1;
				}
			}
		}
		if (contactPointCount == 2) {
			col.contactPoint = (cpA + cpB) * 0.5f;
			return;
		}
		col.contactPoint = cpA;
		return;
	}
	void getContactPoint(Circle* a, Convex* b, Collision& col, int faceIndex)
	{
		sf::Vector2f verA = b->getAbsolutePosition(faceIndex);
		sf::Vector2f verB;
		sf::Vector2f point = a->getPosition();
		if(faceIndex+1==b->polygon.getPointCount()) verB = b->getAbsolutePosition(0);
		else verB = b->getAbsolutePosition(faceIndex + 1);

		sf::Vector2f dif = verB - verA;
		sf::Vector2f difAP = point - verA;

		float segLen = Math::distance(dif);
		float projection = Math::dotProduct(dif, difAP) / segLen;
		if (projection < 0) {
			col.contactPoint = verA;
			return;
		}
		else if (projection > segLen)
		{
			col.contactPoint = verB;
			return;
		}
		
		col.contactPoint = verA + projection * dif / segLen;
	}

	float axisOfLeastPenetration(sf::Vector2f& collisionNormal, Convex& a, Convex& b)
	{
		float minimalPenetration = INFINITY;
		for (int i = 0; i < a.polygon.getPointCount(); i++)
		{
			sf::Vector2f nor = getNormal(&a, i);
			sf::Vector2f point = furthestPoint(-nor, b);
			sf::Vector2f vec = a.getAbsolutePosition(i);
			float dis = Math::dotProduct(-nor, point - vec);
			if (dis < minimalPenetration)
			{
				minimalPenetration = dis;
				collisionNormal = nor;
			}
		}
		return minimalPenetration;
	}
	void applyForce(Collider& a, const sf::Vector2f impulseAlongNormal, const sf::Vector2f contactPoint)
	{
		a.assignedRigidbody->setVelocity(a.assignedRigidbody->getVelocity() + a.assignedRigidbody->getInverseMass() * impulseAlongNormal);
		a.assignedRigidbody->setAngularVelocity(a.assignedRigidbody->getAngularVelocity() + Math::radiansToDeg(Math::crossProduct(contactPoint - a.getShape()->getPosition(), impulseAlongNormal) * a.assignedRigidbody->getInverseInertia()));
	}
	void Collider::collisionResolution(Collider &a, Collider &b, float &_sumMass)
	{
		//Collision resolution
		sf::Vector2f impulse;
		float e = std::min(a.assignedRigidbody->restitution, b.assignedRigidbody->restitution);

		sf::Vector2f rA = collisionInfo.contactPoint - a.getShape()->getPosition();
		sf::Vector2f rB = collisionInfo.contactPoint - b.getShape()->getPosition();
		
		sf::Vector2f rAperp = Math::rightAngleCounterClockwise(rA);
		sf::Vector2f rBperp = Math::rightAngleCounterClockwise(rB);

		sf::Vector2f velA = (a.assignedRigidbody->getVelocity() + rAperp * Math::degToRadians(a.assignedRigidbody->getAngularVelocity()));
		sf::Vector2f velB = (b.assignedRigidbody->getVelocity() + rBperp * Math::degToRadians(b.assignedRigidbody->getAngularVelocity()));

		sf::Vector2f relativeVelocity = velB - velA;

		if (Math::dotProduct(relativeVelocity, collisionInfo.collisionNormal) > 0) return;

		float rAperpDot = Math::dotProduct(rAperp, collisionInfo.collisionNormal);
		float rBperpDot = Math::dotProduct(rBperp, collisionInfo.collisionNormal);

		float divider = 1 / (_sumMass + (
			((rAperpDot * rAperpDot) * a.assignedRigidbody->getInverseInertia()) +
			((rBperpDot * rBperpDot) * b.assignedRigidbody->getInverseInertia())
			));

		collisionInfo.impulseScalar = -(1 + e) * (Math::dotProduct(relativeVelocity, collisionInfo.collisionNormal)) * divider;
		impulse = collisionInfo.collisionNormal * collisionInfo.impulseScalar;

		applyForce(a, -impulse, collisionInfo.contactPoint);
		applyForce(b, impulse, collisionInfo.contactPoint);

		//Calculate collision force
		float relativeVelocityScalar = Math::distance(relativeVelocity);
		if(b.assignedRigidbody->getInverseMass()!=0)
			a.maximumImpactForce = std::max(a.maximumImpactForce, relativeVelocityScalar * b.assignedRigidbody->getMass());
		else a.maximumImpactForce =  std::max(a.maximumImpactForce, relativeVelocityScalar * a.assignedRigidbody->getMass());

		if (a.assignedRigidbody->getInverseMass() != 0)
			b.maximumImpactForce = std::max(b.maximumImpactForce, relativeVelocityScalar * a.assignedRigidbody->getMass());
		else b.maximumImpactForce = std::max(b.maximumImpactForce, relativeVelocityScalar * b.assignedRigidbody->getMass());


		//Friction resolution
		velA = (a.assignedRigidbody->getVelocity() + rAperp * Math::degToRadians(a.assignedRigidbody->getAngularVelocity()));
		velB = (b.assignedRigidbody->getVelocity() + rBperp * Math::degToRadians(b.assignedRigidbody->getAngularVelocity()));

		relativeVelocity = velB - velA;

		//Calculate tangent perpendicular to collision normal
		sf::Vector2f tangent = Math::rightAngleCounterClockwise(collisionInfo.collisionNormal);
		if (Math::dotProduct(tangent, relativeVelocity) < 0) tangent = -tangent;

		if (Math::nearlyTheSame(Math::dotProduct(relativeVelocity, collisionInfo.collisionNormal), 0.f)) return;

		rAperpDot = Math::dotProduct(rAperp, tangent);
		rBperpDot = Math::dotProduct(rBperp, tangent);

		divider = 1 / (_sumMass + (
			((rAperpDot * rAperpDot) * a.assignedRigidbody->getInverseInertia()) +
			((rBperpDot * rBperpDot) * b.assignedRigidbody->getInverseInertia())
			));

		float frictionImpulse = -(Math::dotProduct(relativeVelocity, tangent)) * divider;

		//Coulomb's law of friction
		if (abs(frictionImpulse) <= collisionInfo.impulseScalar * std::max(a.staticFriction, b.staticFriction))
		{
			impulse = frictionImpulse * tangent;
		}
		else
		{
			impulse = -collisionInfo.impulseScalar * tangent * std::max(a.dynamicFriction, b.dynamicFriction);
		}
		applyForce(a, -impulse, collisionInfo.contactPoint);
		applyForce(b, impulse, collisionInfo.contactPoint);
		return;
	}

	void Collider::collide(Circle_Collider& a, Circle_Collider& b)
	{
		//Collision found
		a.isColliding = true;
		b.isColliding = true;
		if (!a.isResponding || !b.isResponding) return;
		collisionInfo.isDetected = true;

		//Getting penetration
		sf::Vector2f dif = b.assignedShape->getPosition() - a.assignedShape->getPosition();
		collisionInfo.penetratrion = Math::distance(dif) - ( a.assignedShape->getRadius() + b.assignedShape->getRadius() );

		//Getting collision normal
		collisionInfo.collisionNormal = Math::normalize(dif);

		//Position correction 
		float sumMass = (a.assignedRigidbody->getInverseMass() + b.assignedRigidbody->getInverseMass());
		float invSumMass = 1 / sumMass;

		//If both objects are static, return
		if (a.assignedRigidbody->getMass() == 0 && b.assignedRigidbody->getMass() == 0) return;


		a.assignedShape->setPosition(a.assignedShape->getPosition() + collisionInfo.collisionNormal * collisionInfo.penetratrion * invSumMass * a.assignedRigidbody->getInverseMass());
		b.assignedShape->setPosition(b.assignedShape->getPosition() - collisionInfo.collisionNormal * collisionInfo.penetratrion * invSumMass * b.assignedRigidbody->getInverseMass());

		//Calculating contact point
		collisionInfo.contactPoint = a.assignedShape->getPosition() + collisionInfo.collisionNormal * a.assignedShape->getRadius();
		
		//Collision resolution
		collisionResolution(a, b, sumMass);
	}

	void Collider::collide(Circle_Collider& a, Convex_Collider &b)
	{
		collisionInfo.isDetected = false;

		//Checking for collision
		collisionInfo.penetratrion = INFINITY;
		int faceIndex = 0;
		for (int i = 0; i < b.assignedShape->polygon.getPointCount(); i++)
		{
			float dist;
			if (i != b.assignedShape->polygon.getPointCount() - 1) dist = distanceToSegment(b.assignedShape->getAbsolutePosition(i), b.assignedShape->getAbsolutePosition(i + 1), a.assignedShape->getPosition());
			else dist = distanceToSegment(b.assignedShape->getAbsolutePosition(b.assignedShape->polygon.getPointCount() - 1), b.assignedShape->getAbsolutePosition(0), a.assignedShape->getPosition());

			if (dist < collisionInfo.penetratrion)
			{
				collisionInfo.penetratrion = dist;
				faceIndex = i;
			}
		}
		if (collisionInfo.penetratrion > a.assignedShape->getRadius()) return;

		//Collision found
		collisionInfo.isDetected = true;
		a.isColliding = true;
		b.isColliding = true;
		if (!a.isResponding || !b.isResponding) return;

		//Getting penetration
		collisionInfo.penetratrion -= a.assignedShape->getRadius();
		
		//Getting collision normal
		collisionInfo.collisionNormal = -getNormal(b.assignedShape, faceIndex);

		//Position correction 
		float sumMass = (a.assignedRigidbody->getInverseMass() + b.assignedRigidbody->getInverseMass());
		float invSumMass = 1 / sumMass;

		//If both objects are static, return
		if (a.assignedRigidbody->getMass() == 0 && b.assignedRigidbody->getMass() == 0) return;

		a.assignedShape->setPosition(a.assignedShape->getPosition() + collisionInfo.collisionNormal * collisionInfo.penetratrion * invSumMass * a.assignedRigidbody->getInverseMass());
		b.assignedShape->setPosition(b.assignedShape->getPosition() - collisionInfo.collisionNormal * collisionInfo.penetratrion * invSumMass * b.assignedRigidbody->getInverseMass());

		getContactPoint(a.assignedShape, b.assignedShape, collisionInfo, faceIndex);
		
		//Collision normal correction
		collisionInfo.collisionNormal = Math::normalize(collisionInfo.contactPoint - a.assignedShape->getPosition());

		//Collision resolution
		collisionResolution(a, b, sumMass);
	}
	void Collider::collide(Convex_Collider& a, Convex_Collider& b)
	{
		collisionInfo.isDetected = false;

		//Checking for collision. Getting penetration & normal
		sf::Vector2f aNormal, bNormal;
		float penA = axisOfLeastPenetration(aNormal, *a.assignedShape, *b.assignedShape);
		float penB = axisOfLeastPenetration(bNormal, *b.assignedShape, *a.assignedShape);
		if (penA < 0 || penB < 0) return; // No collision
		if (penA < penB) {
			collisionInfo.penetratrion = penA;
			collisionInfo.collisionNormal = aNormal;
		}
		else {
			collisionInfo.penetratrion = penB;
			collisionInfo.collisionNormal = -bNormal;
		}

		//Collision found
		collisionInfo.isDetected = true;
		a.isColliding = true;
		b.isColliding = true;
		if (!a.isResponding || !b.isResponding) return;
		float sumMass = (a.assignedRigidbody->getInverseMass() + b.assignedRigidbody->getInverseMass());
		float invSumMass = 1 / sumMass;

		//If both objects are static, return
		if (a.assignedRigidbody->getMass() == 0 && b.assignedRigidbody->getMass() == 0) return;

		//Position correction 
		a.assignedShape->setPosition(a.assignedShape->getPosition() - collisionInfo.collisionNormal * collisionInfo.penetratrion * invSumMass * a.assignedRigidbody->getInverseMass());
		b.assignedShape->setPosition(b.assignedShape->getPosition() + collisionInfo.collisionNormal * collisionInfo.penetratrion * invSumMass * b.assignedRigidbody->getInverseMass());

		getContactPoint(a.assignedShape, b.assignedShape, collisionInfo);
		
		//Collision resolution
		collisionResolution(a,b,sumMass);
	}
#pragma endregion

	Collider::~Collider()
	{
		for (auto i = convexColliders.begin(); i != convexColliders.end(); ++i)
		{
			if (*i == this)
			{
				convexColliders.erase(i);
				return;
			}
		}
		for (auto i = circleColliders.begin(); i != circleColliders.end(); ++i)
		{
			if (*i == this)
			{
				circleColliders.erase(i);
				return;
			}
		}
	}

	void Collider::collideAll()
	{
		for (int i = 0; i < (int)circleColliders.size() - 1; i++)
			circleColliders[i]->isColliding = false;
		for (int i = 0; i < (int)convexColliders.size() - 1; i++)
			convexColliders[i]->isColliding = false;

		for (int t = 0; t < 5; t++)
		{
			//Circles_vs_circles
			for (int i = 0; i < (int)circleColliders.size() - 1; i++)
			{
				for (size_t j = i + 1; j < circleColliders.size(); j++)
				{
					if(circleColliders[i]->isEnabled && circleColliders[j]->isEnabled)
						if ((circleColliders[i]->closeArea) == (circleColliders[j]->closeArea))
							collide(*circleColliders[i], *circleColliders[j]);
				}
			}
			//Convex_vs_Convex
			for (int i = 0; i < (int)convexColliders.size() - 1; i++)
			{
				for (size_t j = i + 1; j < convexColliders.size(); j++)
				{
					if (convexColliders[i]->isEnabled && convexColliders[j]->isEnabled)
						if((convexColliders[i]->closeArea) == (convexColliders[j]->closeArea))
							collide(*convexColliders[i], *convexColliders[j]);
				}
			}
			//Circle_vs_Convex
			for (int i = 0; i < (int)circleColliders.size(); i++)
			{
				for (size_t j = 0; j < convexColliders.size(); j++)
				{
					if (circleColliders[i]->isEnabled && convexColliders[j]->isEnabled)
						if ((circleColliders[i]->closeArea) == (convexColliders[j]->closeArea))
							collide(*circleColliders[i], *convexColliders[j]);
				}
			}
		}
	}
	bool Collider::isCollidingWithAnything()
	{
		return Collider::isCollidingWithAnything(this);
	}
	bool Collider::isCollidingWithAnything(Collider* a)
	{
		return a->isColliding;
	}
	std::vector<Convex_Collider*> Collider::convexColliders;
	std::vector<Circle_Collider*> Collider::circleColliders;
	Collision Collider::collisionInfo;
};