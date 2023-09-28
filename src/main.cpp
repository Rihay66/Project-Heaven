#include "../inc/gameWindow.hpp"

const unsigned int WIDTH = 1280, HEIGHT = 720;

int main(){
	
	//create window
	GameWindow* window = new GameWindow(WIDTH, HEIGHT, "Project-Heaven");

	//init resources from files and load classes
	window->init();

	//set up vars for calculating delta time
	float deltaTime = 1.0f / 60.0f;
	int w, h;
	//Set delta time
	window->DeltaTime = deltaTime;
	
	//update loop
	while(!window->quit){

		//Get event
		SDL_PollEvent(&window->eventHandle);

		//Get a frame time for performance profiling
		//window->getFrameTime();
		
		//TODO: Multithreading the input and update and having rendering on it's own thread
		//check for main window input
		window->window_input();

		//update any input, values, objects, loading etc..
		window->update();

		//Render background
		//update gl viewport

		//Clear color buffer
		glClearColor(0.25f, 0.5f, 0.75f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//draw or render
		window->render();

		//swap buffers
		SDL_GL_SwapWindow(window->window);
		//avoid cpu idle
		usleep(1);
	}

	//delete any memory
	delete window;

	printf("Exiting...\n");

	return 0;
}
