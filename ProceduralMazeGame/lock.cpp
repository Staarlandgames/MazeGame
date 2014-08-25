#include "lock.h"
#include "object.h"
lock::lock(int id,sf::Texture &newTexture, sf::Vector2f newPosition, sf::Vector2i UVPosition, sf::Vector2i dimensions):
	object(id,newTexture,newPosition)
{

}

lock::~lock()
{

}

