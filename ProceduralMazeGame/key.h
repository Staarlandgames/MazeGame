#ifndef _key_H_
#define _key_H_

#include "object.h"
#include "lock.h"

#include <SFML/Graphics.hpp>

//key class definition
//defines the class, and it's functions
class key: public object
{

public://public functions

	//constructor
	key::key(int id,sf::Texture &newTexture, sf::Vector2f newPosition, sf::Vector2i UVPosition, sf::Vector2i dimensions);
	// deconstructor
	key::~key();
	//
	inline void setLock(lock *input){lock = input;}
	inline lock* getLock(){return lock;}

	//hit function to open 
	
public://public variables

private://private functions	

private://private variables

	//the object
	lock* lock;
	
};

#endif