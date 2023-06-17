#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <string>

namespace mk {
	class Math {
	public:
		static sf::Vector2f normalize(const sf::Vector2f);
		static sf::Vector2f rightAngleCounterClockwise(const sf::Vector2f);
		static float dotProduct(const sf::Vector2f a, const sf::Vector2f b);
		static float crossProduct(const sf::Vector2f a, const sf::Vector2f b);
		static sf::Vector2f turnByAngle(sf::Vector2f, float );
		static float getAngle(sf::Vector2f);
		static float degToRadians(float angle);
		static float radiansToDeg(float angle);
		static float squaredDistance(sf::Vector2f);
		static float distance(sf::Vector2f);
		static bool nearlyTheSame(float, float);
		static bool nearlyTheSame(sf::Vector2f, sf::Vector2f);
	};
}