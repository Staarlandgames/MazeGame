#ifndef _SCENE_H_
#define _SCENE_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>

//parent classes in case they are needed

//player, powers, and races


//Declerations
enum State{Title,Play,Instructions,Paused,End}; //The game states
static const char * EnumStrings[] = { "Title","Play","Instructions","Paused","End"};

const int MaxScreenWidth = 1024;
const int MaxScreenHeight = 576;

class Scene
{
//public functions
public:
	Scene();
	void initilaiseScene();//the initialise function
	void cleanup();//the cleanup funtion
	void run();

//public variables
public:
	
//private functions
private:
	void loadAssets(); // load the font file, and texture files
	void drawHUD(); //draw labels to the screen
	void windowEvents();//function to handle window events
	void update();//the game update function TODO: Split this up into seperate functions
	void render();//render in game objects 
	void resetScene();//reset all things in the scene
	
	//setup game objects
	void generateMap();
	
	//Gameplay Functions
	void mouseInput(sf::Vector2i mousePosition);//check if the mouse button has hit any active objects

//private variables
private:

	//Decelerations of Variables
	State state;
	sf::RenderWindow window;
	sf::Font font;
	//file IO objects
	std::vector<std::string*> vectorStrings;
	// Textures
	sf::Vector2<sf::Texture> textures;
	
	//id's for textures
	int brickWall;
	int grassWall;
	int magicWall;
	int mudWall;
	int sandWall;
	int snowWall;
	int stoneWall;

	int liquidLava;
	int liquidWater;

	int blueLock;
	int greenLock;
	int redLock;
	int yellowLock;

	int blueKey;
	int greenKey;
	int redKey;
	int yellowKey;

};

 
#endif