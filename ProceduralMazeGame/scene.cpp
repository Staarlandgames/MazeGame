#include <SFML/Graphics.hpp>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "scene.h"

using namespace sf;
using namespace std;

//PUBLIC FUNCTIONS

//scene constructor
Scene::Scene():
	Player1(NULL),
	Player2(NULL)
{
	//load in all the assets needed for the game, specifically textures and font
	loadAssets();
	
	//initilaise the scene
	initilaiseScene();
	
}

//initilaiseScene function
//creates the window and resets the scene
void Scene::initilaiseScene(){
	
	//create and initilaise the renderWindow
	window.create(VideoMode(MaxScreenWidth,MaxScreenHeight),"#Invert! - STaarlandGames.co.uk");
	
	//set verticle sync to be enabled, for frame rate
	window.setVerticalSyncEnabled(true);
	
	//set random seed
	srand(time(NULL));

	//call reset the scene to initially set up assets
	resetScene();

}//end of initilaise scene function
void Scene::cleanup(){

	//clear players 
	delete Player1;
	delete Player2;
	Player1 = NULL;
	Player2 = NULL;

	//clear blocks
	std::vector<tile*>::iterator itTiles;
	if(blocks.size()>0)
	{
		for (itTiles = blocks.begin(); itTiles!= blocks.end();++itTiles)
		{
			//itTiles = blocks.erase(itTiles);
	
		}
	}
	blocks.clear();
	//clear keys
	
	//clear locks

	//clear liquids
	if(liquidBlocks.size()>0)
	{
		for (itTiles = liquidBlocks.begin(); itTiles!= liquidBlocks.end();++itTiles)
		{
			//itTiles = liquidBlocks.erase(itTiles);
			
		}
	}
	liquidBlocks.clear();
	
	//clear foliage
	if(foliageBlocks.size()>0){
		for (itTiles = foliageBlocks.begin(); itTiles!= foliageBlocks.end();++itTiles)
		{
			//itTiles = foliageBlocks.erase(itTiles);
			
		}
	}
	foliageBlocks.clear();
	
	//clear textures
	std::vector<sf::Texture*>::iterator itTextures;
	if(textures.size()>0){
		for (itTextures = textures.begin(); itTextures!= textures.end();++itTextures)
		{
			//itTextures =textures.erase(itTextures);
			//delete *itTextures;
		}
	}
	textures.clear();

	//close the window, thus ending the game
	window.close();
}
void Scene::run(){

	//if the window is open, the game should be running
	while(window.isOpen())//GameLoop
	{
		//window events
		windowEvents();
		
		//update function
		update();

		//window rendering
		render();
		
	}//end of while whindow.isOpen loop
	
}//end of run fucniton

//load assets function
//load in external assets, such as font or textures
void Scene::loadAssets(){

	//load font file
	if(!font.loadFromFile("Assets/Fonts/kenvector_future_thin.ttf"))
	{
		//could not load font file
		cleanup();
	}
	
	//load textures
	sf::Texture*  tempTexture;
	
	//load wall assets
	brickWall = 0;
	tempTexture = new sf::Texture();
	if(tempTexture->loadFromFile("assets/Sprites/Map/brickWall.png"))
		textures.push_back(tempTexture);
	
	grassWall = brickWall+1;
	tempTexture = new sf::Texture();
	if(tempTexture->loadFromFile("assets/Sprites/Map/grass.png"))
		textures.push_back(tempTexture);

	sandWall = grassWall+1;
	tempTexture = new sf::Texture();
	if(tempTexture->loadFromFile("assets/Sprites/Map/sand.png"))
		textures.push_back(tempTexture);
	
	dirtWall = sandWall+1;
	tempTexture = new sf::Texture();
	if(tempTexture->loadFromFile("assets/Sprites/Map/dirt.png"))
		textures.push_back(tempTexture);

	castleWall = dirtWall+1;
	tempTexture = new sf::Texture();
	if(tempTexture->loadFromFile("assets/Sprites/Map/castleWall.png"))
		textures.push_back(tempTexture);

	mudWall = castleWall+1;
	tempTexture = new sf::Texture();
	if(tempTexture->loadFromFile("assets/Sprites/Map/mud.png"))
		textures.push_back(tempTexture);
	
	snowWall = mudWall+1;
	tempTexture = new sf::Texture();
	if(tempTexture->loadFromFile("assets/Sprites/Map/snow.png"))
		textures.push_back(tempTexture);

	stoneWall = snowWall+1;
	tempTexture = new sf::Texture();
	if(tempTexture->loadFromFile("assets/Sprites/Map/stone.png"))
		textures.push_back(tempTexture);


	//load liquid assets
	liquidWater = stoneWall+1;
	tempTexture = new sf::Texture();
	if(tempTexture->loadFromFile("assets/Sprites/Map/liquidWaterTop.png"))
		textures.push_back(tempTexture);
	
	liquidLava = liquidWater+1;
	tempTexture = new sf::Texture();
	if(tempTexture->loadFromFile("assets/Sprites/Map/liquidLavaTop.png"))
		textures.push_back(tempTexture);

	//load locks
	blueLock = liquidLava+1;
	tempTexture = new sf::Texture();
	if(tempTexture->loadFromFile("assets/Sprites/Map/lockBlue.png"))
		textures.push_back(tempTexture);
	
	//load keys
	blueKey = blueLock+1;
	tempTexture = new sf::Texture();
	if(tempTexture->loadFromFile("assets/Sprites/Map/keyBlue.png"))
		textures.push_back(tempTexture);
	
	//load players
	bluePlayer = blueKey+1;
	tempTexture = new sf::Texture();
	if(tempTexture->loadFromFile("assets/Sprites/Players/p2_walk.png"))
		textures.push_back(tempTexture);
	pinkPlayer = bluePlayer+1;
	tempTexture = new sf::Texture();
	if(tempTexture->loadFromFile("assets/Sprites/Players/p3_walk.png"))
		textures.push_back(tempTexture);
	greenPlayer = pinkPlayer+1;
	tempTexture = new sf::Texture();
	if(tempTexture->loadFromFile("assets/Sprites/Players/p1_walk.png"))
		textures.push_back(tempTexture);
	//remove temp texture;
	delete tempTexture;
	tempTexture = NULL;

}//end of load seets function

//draw HUD function
//render GUI text and objects
void Scene::drawHUD()
{	
	//create title text object to be used for in game text
	Text tTitle;
	string titleText;
	tTitle.setFont(font);
	tTitle.setCharacterSize(40);
	tTitle.setColor(Color::Black);
	//set the title text for the title screen
	titleText = "#Invert!";
	tTitle.setString(titleText);
	tTitle.setPosition((MaxScreenWidth/2)-tTitle.getLocalBounds().width/2,0.0f);
	window.draw(tTitle);
	
}//end of drawHUD function

//start of windowEvents function
void Scene::windowEvents(){

	//The function handles window events and calls appropriate functions based on the polled events.
	Event event;

	while(window.pollEvent(event))
	{
		if(event.type == Event::Closed)//if the window is closed, call the cleanup function 
		{
			cleanup();
		}
		
		if(event.type==Event::MouseButtonPressed)
		{
			mouseInput(Mouse::getPosition(window));
		}

		if(event.type==Event::KeyPressed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				resetScene();
			}
			keyboardInput();
		}

	}//end of while window.pollEvent loop

} //end of windowEvents function

//update function
void Scene::update()
{
	//update on screen information


}//end of update function

//render function
//used for drawing game objects to the screen
//also calls the draw hud functions
void Scene::render()
{
	//clear the screen
	window.clear(Color::White);
	
	//Draw Assets
	std::vector<tile*>::iterator itTiles;
	if(blocks.size()>0)
	{
		for (itTiles = blocks.begin(); itTiles!= blocks.end();++itTiles)
		{
			window.draw(**itTiles);
			
		}
	}
	
	drawHUD();
	//display window
	window.display();

}//end of windowRender function

void Scene::resetScene()
{
	//Setup Objects
	state = Title;
	
	//numbers for textures
	int liquidID;
	int brickMainID;
	int brickSubID;

	//select liquid and blocks
	int liquidRan = rand()%100;

	if(liquidRan >50)
		liquidID = liquidLava;
	else
		liquidID = liquidWater;

	int brickMainRan = rand()%100;
	
	if(brickMainRan >50)
		brickMainID = brickWall;
	else
		brickMainID = castleWall;

	int brickSubRan = rand()%100;
	if(brickMainID==brickWall)
	{
		if(brickSubRan <=30)
			brickSubID = dirtWall;
		else if (brickSubRan>30 && brickSubRan<=60)
			brickSubID = sandWall;
		else
			brickSubID = grassWall;
	}
	else
	{
		if(brickSubRan <=30)
			brickSubID = stoneWall;
		else if (brickSubRan>30 && brickSubRan<=60)
			brickSubID = mudWall;
		else
			brickSubID = snowWall;
	}

	brickSubID = grassWall;
	blocks.clear();
	//liquidBlocks.clear();
	//foliageBlocks.clear();
	//textures.clear();
	
	//clear the map
	for (int i = 0; i<mazeWidth;i++)
	{
		for (int j = 0; j<mazeHeight;j++)
		{
			map[i][j]=0;
		}
	}

	//generate the maze 
	mazeDevision(mazeWidth, mazeHeight);

	//parse through the thing, generating tiles;
	tile* newTile;

	for (int i = 0; i<mazeWidth;i++)
	{
		for (int j = 0; j<mazeHeight;j++)
		{
			switch (map[i][j])
			{
			case 0:
				{
					newTile = new tile((i+j),(*textures.at(liquidID)),sf::Vector2f(i*(70*scale),j*(70*scale)),sf::Vector2i(0,0),sf::Vector2i(70,105));
					newTile->scale(scale,scale);
					blocks.push_back(newTile);

					break;
				}
			case 1:
				{
					newTile = new tile((i+j),(*textures.at(brickMainID)),sf::Vector2f(i*(70*scale),j*(70*scale)),sf::Vector2i(0,0),sf::Vector2i(70,105));
					newTile->scale(scale,scale);
					blocks.push_back(newTile);
					break;
				}
			case 2:
				{
					newTile = new tile((i+j),(*textures.at(brickSubID)),sf::Vector2f(i*(70*scale),j*(70*scale)),sf::Vector2i(0,0),sf::Vector2i(70,105));
					newTile->scale(scale,scale);
					newTile->setColor(sf::Color::Magenta);
					blocks.push_back(newTile);
					break;
				}
			case 3:
				{
					newTile = new tile((i+j),(*textures.at(brickSubID)),sf::Vector2f(i*(70*scale),j*(70*scale)),sf::Vector2i(0,0),sf::Vector2i(70,105));
					newTile->scale(scale,scale);
					newTile->setColor(sf::Color::Magenta);
					blocks.push_back(newTile);
					break;
				}
			default:
				{
					

				}
				
			}
		}
	}
	


	//Player1 = new player()
	//clear the vectors so any pre-existing data is cleared out


}

void Scene::mouseInput(Vector2i mousePosition)
{
	Vector2f newVector((float)mousePosition.x,(float)mousePosition.y);
	
}

void Scene::keyboardInput()
{

}

void Scene::mazeDevision(int tileX,int tileY)
{
	const int walkable = 0;
	const int liquid = 1;
	const int player1Start = 2;
	const int player2start = 3;

	float CaptureX = 0.0f;
	float CaptureY = 0.0f;
	float offset = 400.0f;
	float iter = 0;
	int tileID = 0;

	for (int x = 0; x<tileX; x++){
		for (int y = 0; y<tileY; y++){
			if (y == 0 || x == 0 || y == tileY - 1 || x == tileX - 1 || y % 2 == 0 && x % 2 == 0){
				map[x][y] = liquid;
			}
			else{
				map[x][y] = walkable;
			}
			//-------------Starting Tile Spawn---------------
			if (CaptureX == offset && CaptureY == offset){

				map[1][1] = player1Start;
			}
			//-------------Ending Tile Spawn---------------
			if (y == tileY - 1 && x == tileX - 1){

				map[x - 1][y - 1] = player2start;
			}
			CaptureY += offset;
			if (CaptureY >= offset * tileY){ CaptureY = 0; }
		}
		CaptureX += offset;
		if (CaptureX >= offset * tileX){ CaptureX = 0; }
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	//return;
	for (int y = 2; y < tileY - 1; y += 2) {
		int dx = 2;
		int dy = y;
		int rnd4;

		switch (rnd4 = rand() % 4){
		case 0: dx++; break;
		case 1: dx--; break;
		case 2: dy++; break;
		case 3: dy--; break;
		}
		
		if (map[dx][dy] != liquid) {
			map[dx][dy] = liquid;
		}
		else{
			y -= 2;
		}
	}
	for (int x = 4; x < tileX - 1; x += 2) {
		for (int y = 2; y < tileY - 1; y += 2) {
			int dx = x;
			int dy = y;
			int rnd3;

			switch (rnd3 = rand() % 3){
			case 0: dy++; break;
			case 1: dy--; break;
			case 2: dx++; break;
			}
			
			if (map[dx][dy] != liquid) {
				map[dx][dy] = liquid;
			}
			else{
				y -= 2;
			}
		}
	}

	//-------------Starting Tile Spawn---------------
	map[1][1] = player1Start;
	//-------------Ending Tile Spawn---------------
	map[tileX-2][tileY - 2] = player2start;

}
