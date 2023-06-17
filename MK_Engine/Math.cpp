#include "Math.h"
#include <SFML/System/Vector2.hpp>



namespace mk {

	sf::Vector2f Math::normalize(sf::Vector2f a) {
		return a / sqrt(a.x * a.x + a.y * a.y);
	}
	sf::Vector2f Math::rightAngleCounterClockwise(sf::Vector2f a) {
		return sf::Vector2f(-a.y,a.x);
	}
	float Math::dotProduct(sf::Vector2f a, sf::Vector2f b) {
		return a.x*b.x+a.y*b.y;
	}
	float Math::crossProduct(sf::Vector2f a, sf::Vector2f b) {
		return a.x * b.y - a.y * b.x;
	}
	sf::Vector2f Math::turnByAngle(sf::Vector2f vec, float angle)
	{
		/*

		   *Rotation Matrix*
			 [ cos(a)   -sin(a)]
		R =  [ sin(a)    cos(a)]

		*/
		return sf::Vector2f(vec.x * cos(angle) - vec.y * sin(angle), vec.x * sin(angle) + vec.y * cos(angle));
	}
	float Math::getAngle(sf::Vector2f vec)
	{
		return radiansToDeg(atan2(vec.y, vec.x));
	}
	float Math::degToRadians(float angle)
	{
		return angle * 0.0174533f;
	}
	float Math::radiansToDeg(float angle)
	{
		return angle * 57.29578f;
	}
	float Math::squaredDistance(sf::Vector2f a)
	{
		return a.x * a.x + a.y * a.y;
	}
	float Math::distance(sf::Vector2f a)
	{
		return sqrt(a.x * a.x + a.y * a.y);
	}
	bool Math::nearlyTheSame(float a, float b)
	{
		return abs(a - b) < 0.5f;
	}
	bool Math::nearlyTheSame(sf::Vector2f a, sf::Vector2f b)
	{
		return abs(a.x - b.x) < 0.05f && abs(a.y - b.y) < 0.05f;
	}
}
sf::Vector2f operator*(const int& a, const sf::Vector2f& b) {
	return sf::Vector2f(b.x * a, b.y * a);
}