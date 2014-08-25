#ifndef _SCENE_H_
#define _SCENE_H_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <fstream>

//parent classes in case they are needed

//player, powers, and races
#include "player.h"
#include "tile.h"
#include "key.h"
#include "lock.h"
#include "enemy.h"

//Declerations
enum State{Title,Play,Instructions,Paused,End}; //The game states
static const char * EnumStrings[] = { "Title","Play","Instructions","Paused","End"};

const int MaxScreenWidth = 1024;
const int MaxScreenHeight = 576;

const int mazeWidth = 30;
const int mazeHeight = 15;

const int noEnemies = 5;

const int noLocks = 4;

const float scale = 0.5;
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
	void update(sf::Time deltaTime);//the game update function
	void render();//render in game objects 
	void resetScene();//reset all things in the scene

	sf::Vector2i GenerateMapCoordinate();

	void GenerateTiles();


	//setup game objects
	void generateMap();
	
	//Gameplay Functions
	void mouseInput(sf::Vector2i mousePosition);//check if the mouse button has hit any active objects
	void keyboardInput() ;
	//generare maze
	void mazeDevision(int tileX,int tileY);
	//check if two objects are intersecting
	bool intersection(object (& r1), object (& r2));


//private variables
private:

	//Decelerations of Variables
	State state;
	sf::RenderWindow window;
	sf::Font font;
	//file IO objects
	std::vector<std::string*> vectorStrings;
	
	//objects
	//Map
	int map[mazeWidth][mazeHeight];
	//players
	player* Player1;
	player* Player2;
	sf::Vector2i Player1Pos;
	sf::Vector2i Player2Pos;
	
	//tiles
	tile* backgroundTile;
	std::vector<object*> blocks;
	std::vector<key*> keys;
	std::vector<enemy*> enemies;
	// Textures
	std::vector<sf::Texture*> textures;

	//numbers for textures
	int brickMainID;
	int backgroundID;
	int lockID;
	int keyID;

	//id's for textures
	int brickWall;
	int grassWall;
	int dirtWall;
	int sandWall;

	int castleWall;
	int mudWall;
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

	int greenPlayer;
	int bluePlayer;
	int pinkPlayer;

	int terrain1;

	//sfx buffers
	std::vector<sf::SoundBuffer*> buffers;
	std::vector<sf::Sound*> sounds;

	std::vector<sf::Music*> musicTracks;
	//sfx audio ID Numbers

	int collectSFX;
	int hitSFX;
	int invertSFX;
	int winSFX;

	//music audio ID number

	int mainTrack;

};

 
#endif