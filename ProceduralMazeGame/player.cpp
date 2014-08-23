#include "player.h"
#include "object.h"

player::player(int id,sf::Texture &newTexture, sf::Vector2f newPosition, direction dir, sf::Vector2i UVPosition, sf::Vector2i dimensions):
	object(id,newTexture,newPosition),
	currentDirection(dir),
	isMoving(false),
	previousPosition(newPosition),
	goalPosition(newPosition)	
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
		snapPosition(goalPosition);
}

bool player::move(sf::Vector2f newPosition, float deltaTime)
{

	sf::Vector2f currentPos = getPosition();

	if (currentDirection = horizontal) // move in X axis
	{
		if(currentPos.x>newPosition.x)
			currentPos.x-= velocity*deltaTime;
		else
			currentPos.x+= velocity*deltaTime;
	}
	if ( currentDirection = vertical)
	{
		if(currentPos.y>newPosition.y)
			currentPos.y-= velocity*deltaTime;
		else
			currentPos.y+= velocity*deltaTime;
	}

	//set the current position
	setPosition(currentPos);
	bool finishedMoving = (currentPos.x>newPosition.x&&currentPos.x>previousPosition.x)||(currentPos.x<newPosition.x&&currentPos.x<previousPosition.x)||(currentPos.y>newPosition.y&&currentPos.y>previousPosition.y)||(currentPos.y<newPosition.y&&currentPos.y<previousPosition.y);
	
	if (finishedMoving)
	{
		return false;
	}

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


