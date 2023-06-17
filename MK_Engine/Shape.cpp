#include "Shape.h"
#include <iostream>

namespace mk
{
	Shape::~Shape()
	{
		for (auto i = listOfShapes.begin(); i != listOfShapes.end(); ++i)
		{
			if (*i == this)
			{
				listOfShapes.erase(i);
				return;
			}
		}
	}

	void Shape::setDrawable(bool _isDrawable)
	{
		isDrawable = _isDrawable;
	}
	bool Shape::getDrawable() const
	{
		return isDrawable;
	}

	void Shape::drawAll(sf::RenderWindow &_window)
	{
		for (size_t i = 0; i < listOfShapes.size(); i++)
		{
			if(listOfShapes[i]->isDrawable)
				listOfShapes[i]->draw(_window);
		}
	}

	//Layers 
	bool shapeLayersComp(Shape* a, Shape* b)
	{
		return a->layer < b->layer;
	}
	void Shape::setLayer(int _layer)
	{
		layer = _layer;
		std::sort(listOfShapes.begin(), listOfShapes.end(), shapeLayersComp);
	}
	int Shape::getLayer()
	{
		return layer;
	}

	std::vector<Shape*> Shape::listOfShapes;
}
