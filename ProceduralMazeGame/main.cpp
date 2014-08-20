#include "scene.h"


int main()//Start of main function
{
	//create the game scene
	Scene* myScene = new Scene();
	//run the scene, this will run until the prohram is ended in the scene
	myScene->run();

	return 0;

}//end of main function
