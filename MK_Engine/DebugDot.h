#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace mk
{
	class DebugDot
	{
		static sf::CircleShape circle;
		static sf::RenderWindow* window;
		static std::vector<sf::Vector2f> verticies;

		static sf::VertexArray line;
		static std::vector<std::pair<sf::Vector2f, sf::Vector2f>> linePoints;
	public:
		static void init(sf::RenderWindow* w);
		static void drawAll();
		static void add(sf::Vector2f);
		static void addLine(sf::Vector2f, sf::Vector2f);

	};
}