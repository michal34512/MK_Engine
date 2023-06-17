#include "DebugDot.h"
namespace mk
{
	void DebugDot::init(sf::RenderWindow* w)
	{
		window = w;
		circle.setRadius(3);
		circle.setOutlineThickness(1.f);
		circle.setFillColor(sf::Color::Blue);
		circle.setOrigin(circle.getRadius(), circle.getRadius());

		// Set the line color
		line = sf::VertexArray(sf::Lines, 2);
		line[0].color = sf::Color::Red;
		line[1].color = sf::Color::Red;
	}
	void DebugDot::add(sf::Vector2f ver)
	{
		verticies.emplace_back(ver);
	}
	void DebugDot::drawAll()
	{
		for (int i = 0; i < verticies.size(); i++)
		{
			circle.setPosition(verticies[i]);
			window->draw(circle);
		}
		verticies.clear();

		for (int i = 0; i < linePoints.size(); i++)
		{
			line[0].position = linePoints[i].first;
			line[1].position = linePoints[i].second;

			window->draw(line);
		}
		linePoints.clear();
	}
	void DebugDot::addLine(sf::Vector2f a, sf::Vector2f b)
	{
		linePoints.emplace_back(std::make_pair(a,b));
	}
	sf::CircleShape DebugDot::circle;
	sf::RenderWindow* DebugDot::window;
	std::vector<sf::Vector2f> DebugDot::verticies;
	sf::VertexArray DebugDot::line;
	std::vector<std::pair<sf::Vector2f, sf::Vector2f>> DebugDot::linePoints;
}
