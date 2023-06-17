#pragma once
#include <SFML/Graphics.hpp>
#include "Shape.h"

namespace mk
{
	class Sprite : public Shape
	{
		sf::Sprite sprite;
		sf::Texture texture;
		Shape* assignedShape;
	public:
		bool dontSetOriginAutomatically = false;
		Sprite(Object*);
		void setFilePath(std::string);

		void setPosition(sf::Vector2f);
		sf::Vector2f getPosition() const;

		void setRotation(float);
		float getRotation() const;

		void setOrigin();
		void setOrigin(sf::Vector2f);

		void setScale(sf::Vector2f);
		void setScale(float);
		sf::Vector2f getScale() const;

		void setColor(sf::Color) override;
		sf::Color getColor() const override;


		void draw(sf::RenderWindow&);
	};
}