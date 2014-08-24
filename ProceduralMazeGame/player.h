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
	
	//constructor
	player::player(int id,sf::Texture &newTexture, sf::Vector2f newPosition, direction dir, sf::Vector2i UVPosition, sf::Vector2i dimensions);
	// deconstructor
	player::~player();

	
	//function to set the direction of the player object
	inline void setDirection(direction input){ currentDirection = input;}
	//function to check the direction of the player
	inline direction getDirection(){return currentDirection;}
	//function to set the veloicty of the player
	inline void setVelocity(float input){velocity = input;}
	//set wether the player should be mooving
	inline void setMoving(bool input){isMoving = true;}
	//set the goal position, and set the previous position
	inline void setGoalPosition(sf::Vector2f input) {goalPosition = input;previousPosition = getPosition();}
	//check wether the player is moving
	inline bool getMoving(){return isMoving;}

	inline void setMapCoordinates(sf::Vector2i input){mapCoordinates = input;}
	inline sf::Vector2i getMapCoordinates(){return mapCoordinates;}

	inline void setStartPosiiton(sf::Vector2f input){startPosition = input;}
	inline sf::Vector2f getStartPosiiton(){return startPosition;}
	
	//function that inverts the direction of the player object
	void invertDirection();
	//snap posiiton of the player so it is the same as the tile it is colliding with
	void snapPosition(sf::Vector2f input);
	//update game object
	void update(float deltaTime);

public://public variables

private://private functions	
	
	//function to move the player, specifying the new position to set the player too 
	bool move(sf::Vector2f newPosition, float deltaTime);
	void animateWalk(float deltaTime);


private://private variables
	
	float velocity;//players movement velocity
	bool isMoving;
	direction currentDirection; // the current direction of the player
	sf::Vector2i mapCoordinates;
	sf::Vector2f startPosition;
	sf::Vector2f previousPosition; // the stored previous position of the player
	sf::Vector2f goalPosition; // the stored goal position of the player
};

#endif