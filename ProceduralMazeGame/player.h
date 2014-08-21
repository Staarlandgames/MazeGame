#ifndef _player_H_
#define _player_H_

#include "object.h"

#include <SFML/Graphics.hpp>

enum direction{horizontal,vertical};

//player class definition
//defines the class, and it's functions
class player: public object
{

public://public functions
	//function that inverts the direction of the player object
	void invertDirection();
	//function to set the direction of the player object
	inline void setDirection(direction input){ currentDirection = input;}
	//function to check the direction of the player
	inline direction getDirection(){return currentDirection;}
	//function to move the player, specifiying the new position to set the player too 
	bool move(sf::Vector2f newPosition);
	//snap posiiton of the player so it is the same as the tile it is colliding with
	void snapPosition(object snapPosition);


public://public variables

private://private functions

private://private variables
	sf::Vector2f velocity;
	direction currentDirection;
	sf::Vector2f previousPosition;
};

#endif