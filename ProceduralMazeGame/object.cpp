#include "object.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

object::object(int id,sf::Texture &newTexture, sf::Vector2f newPosition):
	Sprite(newTexture),
	idNumber(id),
	isActive(true)
{
	setPosition(newPosition);
	
}

void object::update(float deltaTime)
{

}



