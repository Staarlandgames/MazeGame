#include "tile.h"
#include "object.h"

tile::tile(int id,sf::Texture &newTexture, sf::Vector2f newPosition, sf::Vector2i UVPosition, sf::Vector2i dimensions):
	object(id,newTexture,newPosition)
{
	sf::IntRect newRect(UVPosition,dimensions);
	setTextureRect(newRect);
}

tile::~tile()
{

}