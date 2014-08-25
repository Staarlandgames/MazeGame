#ifndef _lock_H_
#define _lock_H_

#include "object.h"

#include <SFML/Graphics.hpp>

//lock class definition
//defines the class, and it's functions
class lock: public object
{

public://public functions

	//constructor
	lock::lock(int id,sf::Texture &newTexture, sf::Vector2f newPosition, sf::Vector2i UVPosition, sf::Vector2i dimensions);
	// deconstructor
	lock::~lock();
	//
	inline void setMapCoordinates(sf::Vector2i input){mapCoordinates = input;}
	inline sf::Vector2i getMapCoordinates(){return mapCoordinates;}

public://public variables

private://private functions	

private://private variables

	sf::Vector2i mapCoordinates;


};

#endif