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
Scene::Scene()
{
	//load in all the assets needed for the game, specififcally textures and font
	loadAssets();
	
	//initilaise the scene
	initilaiseScene();
	
}

//initilaiseScene function
//creates the window and resets the scene
void Scene::initilaiseScene(){
	//create and initilaise the renderWindow
	window.create(VideoMode(MaxScreenWidth,MaxScreenHeight),"STaarlandGames Presents: PCGMazeGam");
	//set verticle sync to be enabled, for frame rate
	window.setVerticalSyncEnabled(true);
	
	//set random seed
	srand(time(NULL));
	//call reset the scene to initilally set up assets
	resetScene();

}//end of initilaise scene function
void Scene::cleanup(){
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


//PRIVATE FUNCTIONS

//load assets function
//load in external assets, such as font or textures
//if any of the functions fail the program will end
void Scene::loadAssets(){

	//load font file
	if(!font.loadFromFile("Assets/Fonts/Biko_Regular.otf"))
	{
		//could not load font file
		cleanup();
	}
	
	//load textures

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
	tTitle.setColor(Color::Blue);
	//set the title text foir the titile screen
	titleText = "STaarland Present's: Small World Race Selection!";
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

		}//end of while window.pollEvent loop

} //end of windowEvents function

//update function
void Scene::update()
{
	//update on screen information


}//end of update fucntion

//render function
//used for drawing game objets to the screen
//also calls the draw hud functions
void Scene::render()
{
	//clear the screen
	window.clear(Color::White);
	
	//Draw Assets
	
	//window.draw(**itRaceButton);
				
	drawHUD();
	//display window
	window.display();

}//end of windowRender fucntion
void Scene::resetScene(){
	
	//Setup Objects
	state = Title;

	//clear the vectrors so any pre exisitig data is cleared out

}

void Scene::mouseInput(Vector2i mousePosition){
	Vector2f newVector((float)mousePosition.x,(float)mousePosition.y);
	

}