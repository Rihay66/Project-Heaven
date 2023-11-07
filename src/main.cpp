#include "../inc/gameWindow.hpp"

const unsigned int WIDTH = 960, HEIGHT = 540;

int main(int argc, char* argv[]){
	
	//create window
	GameWindow* window = new GameWindow(WIDTH, HEIGHT, "Project-Heaven");

	//init resources from files and load classes
	window->init();

	window->threadedRuntime();

	//delete any memory
	delete window;

	printf("Exiting...\n");

	return 0;
}
