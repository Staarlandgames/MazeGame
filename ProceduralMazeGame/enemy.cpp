#include "enemy.h"
enemy::enemy(int id,sf::Texture &newTexture, sf::Vector2f newPosition, direction dir, sf::Vector2i UVPosition, sf::Vector2i dimensions):
	player(id,newTexture,newPosition, dir,UVPosition,dimensions),
	offset(-1)
{

}

enemy::~enemy()
{

}




