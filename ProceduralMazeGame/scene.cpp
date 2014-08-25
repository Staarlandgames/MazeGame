#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "scene.h"

using namespace sf;
using namespace std;

struct sorting
{


	inline bool operator() (object* obj1,  object* obj2) const
	{
		if(obj1->getPosition().y!=obj2->getPosition().y)return obj1->getPosition().y<obj2->getPosition().y;
		else return obj1->getPosition().x<obj2->getPosition().x;
	}

};

//PUBLIC FUNCTIONS

//scene constructor
Scene::Scene():
	Player1(NULL),
	Player2(NULL),
	backgroundTile(NULL)
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

	//clear the background tile
	delete backgroundTile;
	backgroundTile = NULL;

	//clear blocks vector
	blocks.clear();

	//clear textures vector
	textures.clear();

	buffers.clear();
	sounds.clear();
	musicTracks.clear();

	//close the window, thus ending the game
	window.close();
}
void Scene::run(){

	sf::Clock deltaClock;

	//if the window is open, the game should be running
	while(window.isOpen())//GameLoop
	{
		sf::Time deltaTime = deltaClock.restart();
		//window events
		windowEvents();
		
		//update function
		update(deltaTime);

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
	
	greenLock = blueLock+1;
	tempTexture = new sf::Texture();
	if(tempTexture->loadFromFile("assets/Sprites/Map/lockGreen.png"))
		textures.push_back(tempTexture);
	
	redLock = greenLock+1;
	tempTexture = new sf::Texture();
	if(tempTexture->loadFromFile("assets/Sprites/Map/lockRed.png"))
		textures.push_back(tempTexture);

	yellowLock = redLock+1;
	tempTexture = new sf::Texture();
	if(tempTexture->loadFromFile("assets/Sprites/Map/lockYellow.png"))
		textures.push_back(tempTexture);

	//load keys
	blueKey = yellowLock+1;
	
	tempTexture = new sf::Texture();
	if(tempTexture->loadFromFile("assets/Sprites/Map/keyBlue.png"))
		textures.push_back(tempTexture);

	greenKey = blueKey+1;
	tempTexture = new sf::Texture();
	if(tempTexture->loadFromFile("assets/Sprites/Map/keyGreen.png"))
		textures.push_back(tempTexture);

	redKey = greenKey+1;
	tempTexture = new sf::Texture();
	if(tempTexture->loadFromFile("assets/Sprites/Map/keyRed.png"))
		textures.push_back(tempTexture);

	yellowKey = redKey+1;
	tempTexture = new sf::Texture();
	if(tempTexture->loadFromFile("assets/Sprites/Map/keyYellow.png"))
		textures.push_back(tempTexture);
	
	//load players
	bluePlayer = yellowKey+1;
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

	//load backgrounds
	terrain1 = greenPlayer+1;
	tempTexture = new sf::Texture();
	if(tempTexture->loadFromFile("assets/Sprites/Backgrounds/terrainTile1.png"))
		textures.push_back(tempTexture);
	
	tempTexture = new sf::Texture();
	
	//remove temp texture;
	delete tempTexture;
	tempTexture = NULL;

	//load in Music 
	mainTrack = 0;
	sf::Music* music;
	music = new Music();

	if(music->openFromFile("assets/Audio/The Hero_0.ogg"))
			musicTracks.push_back(music);
	
	music = new Music();
	delete music;
	music = NULL;
	//load in SFX
	sf::SoundBuffer* buffer;
	sf::Sound* sound;
	
	collectSFX = 0;
	buffer = new sf::SoundBuffer();
	if(buffer->loadFromFile("assets/Audio/SFX/Collect.ogg"))
	{
		sound = new sf::Sound(*buffer);
		buffers.push_back(buffer);
		sounds.push_back(sound);
	}
	hitSFX = collectSFX +1;
	buffer = new sf::SoundBuffer();
	if(buffer->loadFromFile("assets/Audio/SFX/Hit.ogg"))
	{
		sound = new sf::Sound(*buffer);
		buffers.push_back(buffer);
		sounds.push_back(sound);
	}
	invertSFX = hitSFX +1;
	buffer = new sf::SoundBuffer();
	if(buffer->loadFromFile("assets/Audio/SFX/Invert.ogg"))
	{
		sound = new sf::Sound(*buffer);
		buffers.push_back(buffer);
		sounds.push_back(sound);
	}
	winSFX = invertSFX +1;
	buffer = new sf::SoundBuffer();
	if(buffer->loadFromFile("assets/Audio/SFX/Win.ogg"))
	{
		sound = new sf::Sound(*buffer);
		buffers.push_back(buffer);
		sounds.push_back(sound);
	}

	buffer = new sf::SoundBuffer();
	sound = new sf::Sound();

	delete buffer;
	delete sound;

	buffer = NULL;
	sound = NULL;



}//end of load assetts function


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
			keyboardInput();
		}

	}//end of while window.pollEvent loop

} //end of windowEvents function

//update function
void Scene::update(sf::Time dT)
{
	float deltaTime = dT.asSeconds();
	
	//Check for player collisions
	if(Player1==NULL||Player2 ==NULL)
		return;
	if(intersection(*Player1,*Player2))
	{
		//the two players are colliding
		//play audio 
		sounds.at(winSFX)->play();
		//create a new maze
		resetScene();

	}
	

	//update on screen information
	Player1->update(deltaTime);
	Player2->update(deltaTime);
	
	//check key collisions
	std::vector<key*>::iterator itKeys;
	for(itKeys = keys.begin();itKeys!=keys.end();++itKeys)
	{
		if(intersection(*Player1,**itKeys)||intersection(*Player2,**itKeys))
		{
			
			(*itKeys)->getLock()->setActive(false);
			(*itKeys)->setActive(false);
			sf::Vector2i mapcoordinates = (*itKeys)->getLock()->getMapCoordinates();
			map[mapcoordinates.x][mapcoordinates.y] = 0;
		}

	}

	//sort the blocks vector for rendering 
	std::sort(blocks.begin(),blocks.end(),sorting());

	//remove the rubbish from the blocks list
	std::vector<object*>::iterator itTiles;
	if(blocks.size()>0)
	{
		for (itTiles = blocks.begin(); itTiles!= blocks.end();++itTiles)
		{
			if((*itTiles)->getActive()==false)
			{
				itTiles = blocks.erase(itTiles);
				sounds.at(collectSFX)->play();
			}

		}
	}

	std::vector<enemy*>::iterator itEnemies;
	if(enemies.size()>0)
	{
		for (itEnemies = enemies.begin(); itEnemies!= enemies.end();++itEnemies)
		{
			//check collision with players
			if(intersection(*Player1,**itEnemies))
			{
				//set player back to start position
			}
			if(intersection(*Player2,**itEnemies))
			{
				//set player to start position
			}

		}
		//if the enemy is not already moving...
		if(!(*itEnemies)->getMoving())
		{
			//...make the enemy move
			(*itEnemies)->setMoving(true);
			//get the enemies position
			int newX = (*itEnemies)->getMapCoordinates().x;
			int newY = (*itEnemies)->getMapCoordinates().y;

			if ((*itEnemies)->getDirection()==horizontal)
			{

			}
			else if ((*itEnemies)->getDirection()==vertical)
			{


			}

		}

	
	}

	if (Player2->getDirection()==horizontal&&!Player2->getMoving())//the player is not currently moving and the direction is correct
	{
		if(Player2->getMapCoordinates().x+1<mazeWidth-1)
		{	
			int newX = Player2->getMapCoordinates().x+1;
			int newY = Player2->getMapCoordinates().y;

			int mapCoordinate = map[newX][newY];

			//check if next tile is valid
			if(mapCoordinate!=1&&mapCoordinate!=4&&mapCoordinate!=6)
			{
				//set the player so they move to the next tile
				Player2->setMoving(true);
				Player2->setMapCoordinates(sf::Vector2i(newX,newY));
				Player2->setGoalPosition(sf::Vector2f(newX*(70*scale), newY*(70*scale)));
			}
		}
	}


	//Vertical Controls
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W))||(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
	{
		if (Player1->getDirection()==vertical&&!Player1->getMoving())//the player is not currently moving and the direction is correct
		{
			if(Player1->getMapCoordinates().y-1>0)
			{	
				int newX = Player1->getMapCoordinates().x;
				int newY = Player1->getMapCoordinates().y-1;

				int mapCoordinate = map[newX][newY];

				//check if next tile is valid
				if(mapCoordinate!=1&&mapCoordinate!=4&&mapCoordinate!=6)
				{
					//set the player so they move to the next tile
					Player1->setMoving(true);
					Player1->setMapCoordinates(sf::Vector2i(newX,newY));
					Player1->setGoalPosition(sf::Vector2f(newX*(70*scale), newY*(70*scale)));
				}
			}
		}
	}
	 
}//end of update function

//render function
//used for drawing game objects to the screen
//also calls the draw hud functions
void Scene::render()
{
	//clear the screen
	window.clear(Color::White);
	
	//Draw Assets
	//draw the background 
	if(backgroundTile!=NULL)
		window.draw(*backgroundTile);
	std::vector<object*>::iterator itTiles;

	if(blocks.size()>0)
	{
		for (itTiles = blocks.begin(); itTiles!= blocks.end();++itTiles)
		{
			if(*itTiles!=NULL)
				window.draw(**itTiles);
			
		}
	}

	
	drawHUD();
	//display window
	window.display();

}//end of windowRender function

//draw HUD function
//render GUI text and objects
void Scene::drawHUD()
{	
	//create title text object to be used for in game text
	Text tTitle;
	string titleText;
	tTitle.setFont(font);
	tTitle.setCharacterSize(40);
	
	if (Player1!=NULL&&Player1->getDirection()==horizontal)
		tTitle.setColor(Color::Black);
	else
		tTitle.setColor(Color::White);

	//set the title text for the title screen
	titleText = "#Invert!";
	tTitle.setString(titleText);
	tTitle.setPosition((MaxScreenWidth/2)-tTitle.getLocalBounds().width/2,0.0f);
	window.draw(tTitle);

}//end of drawHUD function


void Scene::resetScene()
{
	//Set gamestate
	state = Title;
	
	//generate Tiles
	GenerateTiles();
	//select background	
	backgroundID = terrain1;

	//stop background audio
	musicTracks.at(mainTrack)->stop();

	musicTracks.at(mainTrack)->setLoop(true);
	musicTracks.at(mainTrack)->play();

	
	//clear the vectors so any pre-existing data is cleared out
	blocks.clear();
	keys.clear();

	int randBackground = rand()%3;

	backgroundTile = new tile(0,*textures.at(backgroundID),sf::Vector2f(0,0),sf::Vector2i(64*randBackground,0),sf::Vector2i(64,64));
	backgroundTile->setScale(MaxScreenWidth,MaxScreenHeight);
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
	lock* newLock;
	key* newKey;

	for (int i = 0; i<mazeWidth;i++)
	{
		for (int j = 0; j<mazeHeight;j++)
		{
			switch (map[i][j])
			{
			case 0:
				{
					
					break;
				}
			case 1:// walls
				{
					newTile = new tile((i+j),(*textures.at(brickMainID)),sf::Vector2f(i*(70*scale),j*(70*scale)),sf::Vector2i(0,0),sf::Vector2i(70,105));
					newTile->scale(scale,scale);
					blocks.push_back(newTile);
					//map[i][j] = 0;
					
					break;
				}
			case 2: // player 1
				{
					Player1 = new player(1,(*textures.at(greenPlayer)),sf::Vector2f(i*(70*scale),j*(70*scale)),horizontal,sf::Vector2i(0,0),sf::Vector2i(64,90));
					Player1->scale(scale,scale);
					Player1->setStartPosiiton(sf::Vector2f(i*(70*scale),j*(70*scale)));
					Player1->setMapCoordinates(sf::Vector2i(i,j));
					Player1->setDirection(horizontal);
					blocks.push_back(Player1);
					break;
				}
			case 3://player 2
				{
					Player2 = new player(2,(*textures.at(pinkPlayer)),sf::Vector2f(i*(70*scale),j*(70*scale)),vertical,sf::Vector2i(0,0),sf::Vector2i(64,90));
					Player2->scale(scale,scale);
					Player2->setStartPosiiton(sf::Vector2f(i*(70*scale),j*(70*scale)));
					Player2->setMapCoordinates(sf::Vector2i(i,j));
					Player2->setDirection(vertical);
					blocks.push_back(Player2);
					break;
				}
			case 4://locks and keys
				{
					//create lock
					newLock = new lock((i+j),(*textures.at(lockID)),sf::Vector2f(i*(70*scale),j*(70*scale)),sf::Vector2i(0,0),sf::Vector2i(70,105));
					newLock->scale(scale,scale);
					newLock->setMapCoordinates(sf::Vector2i(i,j));
					blocks.push_back(newLock);
					//create key
					sf::Vector2i keyLocation =GenerateMapCoordinate(); 
					newKey = new key(i+j,*textures.at(keyID),sf::Vector2f(keyLocation.x*(70*scale),keyLocation.y*(70*scale)),sf::Vector2i(0,0),sf::Vector2i(70,105));
					newKey->scale(scale,scale);
					newKey->setLock(newLock);
					blocks.push_back(newKey);
					keys.push_back(newKey);
					//update textures
					lockID++;
					keyID++;
				}
			default:
				{
					
					break;
				}
				
			}
		}
	}
	
	newTile = NULL;
	newLock = NULL;
	newKey = NULL;


}

void Scene::mouseInput(Vector2i mousePosition)
{
	Vector2f newVector((float)mousePosition.x,(float)mousePosition.y);
	
}

void Scene::keyboardInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		resetScene();
	}

	if(Player1==NULL|| Player2==NULL)
		return;
	//Horizontal Controls
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A))||(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
	{
		if (Player1->getDirection()==horizontal&&!Player1->getMoving())//the player is not currently moving and the direction is correct
		{
			if(Player1->getMapCoordinates().x-1>0)
			{	
				int newX = Player1->getMapCoordinates().x-1;
				int newY = Player1->getMapCoordinates().y;
				
				int mapCoordinate = map[newX][newY];

				//check if next tile is valid
				if(mapCoordinate!=1&&mapCoordinate!=4&&mapCoordinate!=6)
				{
					//set the player so they move to the next tile
					Player1->setMoving(true);
					Player1->setMapCoordinates(sf::Vector2i(newX,newY));
					Player1->setGoalPosition(sf::Vector2f(newX*(70*scale), newY*(70*scale)));
				}
			}
		}

		if (Player2->getDirection()==horizontal&&!Player2->getMoving())//the player is not currently moving and the direction is correct
		{
			if(Player2->getMapCoordinates().x-1>0)
			{	
				int newX = Player2->getMapCoordinates().x-1;
				int newY = Player2->getMapCoordinates().y;

				int mapCoordinate = map[newX][newY];

				//check if next tile is valid
				if(mapCoordinate!=1&&mapCoordinate!=4&&mapCoordinate!=6)
				{
					//set the player so they move to the next tile
					Player2->setMoving(true);
					Player2->setMapCoordinates(sf::Vector2i(newX,newY));
					Player2->setGoalPosition(sf::Vector2f(newX*(70*scale), newY*(70*scale)));
				}
			}
		}
	}//end of if Left

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D))||(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
	{
		if (Player1->getDirection()==horizontal&&!Player1->getMoving())//the player is not currently moving and the direction is correct
		{
			if(Player1->getMapCoordinates().x+1<mazeWidth-1)
			{	
				int newX = Player1->getMapCoordinates().x+1;
				int newY = Player1->getMapCoordinates().y;

				int mapCoordinate = map[newX][newY];

				//check if next tile is valid
				if(mapCoordinate!=1&&mapCoordinate!=4&&mapCoordinate!=6)
				{
					//set the player so they move to the next tile
					Player1->setMoving(true);
					Player1->setMapCoordinates(sf::Vector2i(newX,newY));
					Player1->setGoalPosition(sf::Vector2f(newX*(70*scale), newY*(70*scale)));
				}
			}
		}

		if (Player2->getDirection()==horizontal&&!Player2->getMoving())//the player is not currently moving and the direction is correct
		{
			if(Player2->getMapCoordinates().x+1<mazeWidth-1)
			{	
				int newX = Player2->getMapCoordinates().x+1;
				int newY = Player2->getMapCoordinates().y;

				int mapCoordinate = map[newX][newY];

				//check if next tile is valid
				if(mapCoordinate!=1&&mapCoordinate!=4&&mapCoordinate!=6)
				{
					//set the player so they move to the next tile
					Player2->setMoving(true);
					Player2->setMapCoordinates(sf::Vector2i(newX,newY));
					Player2->setGoalPosition(sf::Vector2f(newX*(70*scale), newY*(70*scale)));
				}
			}
		}
	}//end of if right

	//Vertical Controls
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W))||(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
	{
		if (Player1->getDirection()==vertical&&!Player1->getMoving())//the player is not currently moving and the direction is correct
		{
			if(Player1->getMapCoordinates().y-1>0)
			{	
				int newX = Player1->getMapCoordinates().x;
				int newY = Player1->getMapCoordinates().y-1;

				int mapCoordinate = map[newX][newY];

				//check if next tile is valid
				if(mapCoordinate!=1&&mapCoordinate!=4&&mapCoordinate!=6)
				{
					//set the player so they move to the next tile
					Player1->setMoving(true);
					Player1->setMapCoordinates(sf::Vector2i(newX,newY));
					Player1->setGoalPosition(sf::Vector2f(newX*(70*scale), newY*(70*scale)));
				}
			}
		}

		if (Player2->getDirection()==vertical&&!Player2->getMoving())//the player is not currently moving and the direction is correct
		{
			if(Player2->getMapCoordinates().y-1>0)
			{	
				int newX = Player2->getMapCoordinates().x;
				int newY = Player2->getMapCoordinates().y-1;

				int mapCoordinate = map[newX][newY];

				//check if next tile is valid
				if(mapCoordinate!=1&&mapCoordinate!=4&&mapCoordinate!=6)
				{
					//set the player so they move to the next tile
					Player2->setMoving(true);
					Player2->setMapCoordinates(sf::Vector2i(newX,newY));
					Player2->setGoalPosition(sf::Vector2f(newX*(70*scale), newY*(70*scale)));
				}
			}
		}
	}//end of if Left

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S))||(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
	{
		if (Player1->getDirection()==vertical&&!Player1->getMoving())//the player is not currently moving and the direction is correct
		{
			if(Player1->getMapCoordinates().y+1<mazeHeight-1)
			{	
				int newX = Player1->getMapCoordinates().x;
				int newY = Player1->getMapCoordinates().y+1;

				int mapCoordinate = map[newX][newY];

				//check if next tile is valid
				if(mapCoordinate!=1&&mapCoordinate!=4&&mapCoordinate!=6)
				{
					//set the player so they move to the next tile
					Player1->setMoving(true);
					Player1->setMapCoordinates(sf::Vector2i(newX,newY));
					Player1->setGoalPosition(sf::Vector2f(newX*(70*scale), newY*(70*scale)));
				}
			}
		}

		if (Player2->getDirection()==vertical&&!Player2->getMoving())//the player is not currently moving and the direction is correct
		{
			if(Player2->getMapCoordinates().y+1<mazeHeight-1)
			{	
				int newX = Player2->getMapCoordinates().x;
				int newY = Player2->getMapCoordinates().y+1;

				int mapCoordinate = map[newX][newY];

				//check if next tile is valid
				if(mapCoordinate!=1&&mapCoordinate!=4&&mapCoordinate!=6)
				{
					//set the player so they move to the next tile
					Player2->setMoving(true);
					Player2->setMapCoordinates(sf::Vector2i(newX,newY));
					Player2->setGoalPosition(sf::Vector2f(newX*(70*scale), newY*(70*scale)));
				}
			}
		}
	}//end of if right

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space))||(sf::Keyboard::isKeyPressed(sf::Keyboard::E)))
	{
		Player1->invertDirection();
		Player2->invertDirection();
		sounds.at(invertSFX)->play();
	}
}

void Scene::mazeDevision(int tileX,int tileY)
{
	const int walkable = 0;
	const int liquid = 1;
	const int player1Start = 2;
	const int player2start = 3;
	const int lock = 4;
	const int enemy = 5;

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

	//Starting Tile Spawn
	map[1][1] = player1Start;
	//Ending Tile Spawn
	map[tileX-2][tileY - 2] = player2start;

	int Locks = rand()%noLocks;
	if(Locks == 0)Locks=1;

	for(int i = 0; i<Locks;i++)
	{
		sf::Vector2i lockPos = GenerateMapCoordinate();

		map[lockPos.x][lockPos.y] = lock;
		int z = 0;

	}

	int Enemies = rand()%noEnemies;
	if(Enemies == 0)Enemies=1;

	for(int i = 0; i<Enemies;i++)
	{
		sf::Vector2i Pos = GenerateMapCoordinate();

		map[Pos.x][Pos.y] = enemy;

	}

}

void Scene::GenerateTiles()
{
	int brickMainRan = rand()%10;

	switch (brickMainRan)
	{
	case 0: brickMainID = brickWall; break;
	case 1: brickMainID = grassWall; break;
	case 2: brickMainID = dirtWall; break;
	case 3: brickMainID = sandWall; break;
	case 4: brickMainID = castleWall; break;
	case 5: brickMainID = mudWall; break;
	case 6: brickMainID = snowWall; break;
	case 7: brickMainID = stoneWall; break;
	case 8: brickMainID = liquidLava; break;
	case 9: brickMainID = liquidWater; break;

	default:brickMainID = brickWall; break;		
	}

	lockID = blueLock;
	keyID = blueKey;
}

bool Scene::intersection(object (& r1), object (& r2))
{
	//function uses the rectangle objects attached to sprites to check if they are intersecting, retuns true if they are.
	if(r1.getGlobalBounds().intersects(r2.getGlobalBounds()))
		return true;

	return false;

}

sf::Vector2i Scene::GenerateMapCoordinate()
{
	 sf::Vector2i keyPostion;
	
	int x = keyPostion.x = rand()%mazeWidth;
	int y = keyPostion.y = rand()%mazeHeight;
	

	if(map[keyPostion.x][keyPostion.y] !=0 )
		return GenerateMapCoordinate();
	else
		return keyPostion;

}
