#ifndef _object_H_
#define _object_H_

#include <SFML/Graphics.hpp>

//object class definition
//defines the class, and it's functions
class object: public sf::Sprite
{
public://public functions	
	
	object::object(int id,sf::Texture &newTexture, sf::Vector2f newPosition);
	
	//set functions
	inline void setColor(sf::Color newColor = sf::Color::White){defaultColor = newColor;}//set the color of the object
	inline void setActive(bool input = true){isActive = input;}//set wether the object is active
	
	//get functions
	inline int getIDNumber(){return idNumber;}//return the id number
	
	//Game Functions
	//virtual bool onHit() = 0;//react to collision with object
	virtual void update(float deltaTime);

public://public variables
	
private://private functions

private://private variables

	bool isActive; // boolean to determine weather the object is active or not
	sf::Color defaultColor; // the default color of the object
	int idNumber;//id number for the object
};

#endif