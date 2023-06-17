#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Component.h"

namespace mk
{
	class Shape : public Component
	{
		static int firstLayer;
		static int lastLayer;
	protected:
		static std::vector<Shape*> listOfShapes;
		bool isDrawable = true;
		int layer = 0;
	public:
		virtual ~Shape();

		virtual void setPosition(sf::Vector2f Position) { return; };
		virtual sf::Vector2f getPosition() const { return sf::Vector2f(0, 0); };

		virtual void setRotation(float) { return; };
		virtual float getRotation() const { return 0.f; };
		virtual float getRotationRadians() const { return 0.f; };

		virtual void setColor(sf::Color) { return; };
		virtual sf::Color getColor() const { return sf::Color::White; };

		virtual void setDrawable(bool);
		virtual bool getDrawable() const;

		virtual void draw(sf::RenderWindow&) { return; };
		static void drawAll(sf::RenderWindow& _window);

		friend bool shapeLayersComp(Shape* a, Shape* b);
		void setLayer(int);
		int getLayer();
	};
}