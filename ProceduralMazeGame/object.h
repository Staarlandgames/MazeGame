#ifndef _object_H_
#define _object_H_

#include <SFML/Graphics.hpp>

#include "label.h"

//object class definition
//defines teh class, and it's functions
class object: public sf::Sprite
{
public:	
	
	object::object(int id,sf::Texture &newTexture, sf::Vector2f newPosition,sf::Font &newFont, std::string newString);
	
	//set functons
	void setColor(sf::Color newColor);//set the color of the object
	void setActive(bool input);//set wether the object is active
	void setLabel(std::string newString);

	//get funsions
	inline int getIDNumber(){return idNumber;}//return the id number
	
	//Game Functions
	bool onClick(sf::Vector2f hitPosition);//check to see if th eobject is pressed

public:
	
private:

private:

	bool isActive; // boolean to determine wether the object is active or not
	sf::Color defaultColor; // the default colour of the object
	sf::Color inactiveColor; // the inactive colour of the object
	int idNumber;//id number for the object
};

#endif