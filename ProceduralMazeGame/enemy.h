#ifndef _enemy_H_
#define _enemy_H_

#include "object.h"
#include "player.h"

#include <SFML/Graphics.hpp>

//enemy class definition
//defines the class, and it's functions
class enemy: public player
{

public://public functions

	//constructor
	enemy::enemy(int id,sf::Texture &newTexture, sf::Vector2f newPosition, direction dir, sf::Vector2i UVPosition, sf::Vector2i dimensions);
	// deconstructor
	enemy::~enemy();

	
public://public variables

private://private functions	

	
private://private variables


};

#endif