#ifndef _tile_H_
#define _tile_H_

#include "object.h"

#include <SFML/Graphics.hpp>

//tile class definition
//defines the class, and it's functions
class tile: public object
{

public://public functions

	//constructor
	tile::tile(int id,sf::Texture &newTexture, sf::Vector2f newPosition, sf::Vector2i UVPosition, sf::Vector2i dimensions);
	// deconstructor
	tile::~tile();

public://public variables

private://private functions	

private://private variables


};

#endif