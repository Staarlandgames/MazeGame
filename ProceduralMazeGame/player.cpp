#include "player.h"
#include "object.h"

player::player(int id,sf::Texture &newTexture, sf::Vector2f newPosition, direction dir, sf::Vector2i UVPosition, sf::Vector2i dimensions):
	object(id,newTexture,newPosition),
	currentDirection(dir),
	isMoving(false),
	previousPosition(newPosition),
	goalPosition(newPosition),
	mapCoordinates(0,0),
	velocity(100)
{
	sf::IntRect newRect(UVPosition,dimensions);
	setTextureRect(newRect);
}

player::~player()
{
	
}

void player::invertDirection()
{
	if (currentDirection==horizontal)
	{
		setDirection(vertical);
	}
	else
	{
		setDirection(horizontal);
	}
}
void player::update(float deltaTime)
{

	//move the players position
	if (isMoving)
	{
		isMoving =move(goalPosition,deltaTime);
	}
	else
	{
		snapPosition(goalPosition);
		isMoving = false;
	}
}

bool player::move(sf::Vector2f newPosition, float deltaTime)
{

	sf::Vector2f currentPos = getPosition();

	float displacement; 
	displacement = velocity*deltaTime;
	bool finishedMoving = false;

	if (currentDirection == horizontal) // move in X axis
	{
		if(currentPos.x>newPosition.x)
			if(currentPos.x-displacement<newPosition.x)
				finishedMoving = true;
			else
				currentPos.x-=displacement;
		else
			if(currentPos.x+displacement>newPosition.x)
				finishedMoving = true;
			else
				currentPos.x+=displacement;

	}
	if ( currentDirection == vertical)
	{
		if(currentPos.y>newPosition.y)
			if(currentPos.y-displacement<newPosition.y)
				finishedMoving = true;
			else
				currentPos.y-=displacement;
		else
			if(currentPos.y+displacement>newPosition.y)
				finishedMoving = true;
			else
				currentPos.y+=displacement;
	}

	//set the current position

	if (finishedMoving)
	{
		return false;
	}	
	setPosition(currentPos);
	return true;
}

void player::snapPosition(sf::Vector2f input)
{
	setPosition(input);
}

void player::animateWalk(float deltaTime)
{
	const float animationDelay = 5.0f;
}


