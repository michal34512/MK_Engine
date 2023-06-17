#include "Sprite.h"
#include "Error.h"
#include "Object.h"

namespace mk
{
	Sprite::Sprite(Object* _gameObject)
	{
		gameObject = _gameObject;
		assignedShape = gameObject->getComponent<Shape>();
		if (assignedShape) {
			assignedShape->setDrawable(false);
		}
		listOfShapes.push_back(this);
	}
	void Sprite::setFilePath(std::string _path)
	{
		if (!texture.loadFromFile(_path))
		{
			throw Error(Error::ERROR_LOADING_TEXTURE);
		}
		texture.setSmooth(true);
		sprite.setTexture(texture);
		if(!dontSetOriginAutomatically) sprite.setOrigin((sf::Vector2f)texture.getSize() * 0.5f);
	}
	void Sprite::draw(sf::RenderWindow &_window)
	{
		if (assignedShape)
		{
			sprite.setPosition(assignedShape->getPosition());
			sprite.setRotation(assignedShape->getRotation());
		}
		_window.draw(sprite);
	}
	void Sprite::setPosition(sf::Vector2f _pos)
	{
		sprite.setPosition(_pos);
	}
	sf::Vector2f Sprite::getPosition() const
	{
		return sprite.getPosition();
	}
	void Sprite::setRotation(float _rotation)
	{
		sprite.setRotation(_rotation);
	}
	float Sprite::getRotation() const
	{
		return sprite.getRotation();
	}
	void Sprite::setOrigin()
	{
		sprite.setOrigin((sf::Vector2f)texture.getSize() * 0.5f);
	}
	void Sprite::setOrigin(sf::Vector2f _origin)
	{
		sprite.setOrigin(_origin);
	}

	void Sprite::setScale(sf::Vector2f _scale)
	{
		sprite.setScale(_scale);
	}
	void Sprite::setScale(float _scale)
	{
		sprite.setScale(sf::Vector2f(_scale,_scale));
	}
	sf::Vector2f Sprite::getScale() const
	{
		return sprite.getScale();
	}
	void Sprite::setColor(sf::Color _col)
	{
		sprite.setColor(_col);
	}
	sf::Color Sprite::getColor() const
	{
		return sprite.getColor();
	}
}