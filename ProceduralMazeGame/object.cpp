#include "object.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

object::object(int id,sf::Texture &newTexture, sf::Vector2f newPosition):
	idNumber(id)
{
	setTexture(newTexture);
	setPosition(newPosition);
}

