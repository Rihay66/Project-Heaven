#include "../inc/gameWindow.hpp"

const unsigned int WIDTH = 1280, HEIGHT = 720;

int main(int argc, char* argv[]){
	
	//create window
	GameWindow* window = new GameWindow(WIDTH, HEIGHT, "Project-Heaven");

	//init resources from files and load classes
	window->init();

	//set up static delta time
	window->DeltaTime = 1.0f / 60.0f;
	//Set up vars for perfomance counters
	Uint64 start, end;
	
	//update loop
	while(!window->quit){
		start = SDL_GetPerformanceCounter();

		//Get event
		SDL_PollEvent(&window->eventHandle);
		
		//TODO: Multithreading the input and update and having rendering on it's own thread
		//check for main window input
		window->window_input();

		//update any input, values, objects, loading etc..
		window->update();

		//Render background
		glClearColor(0.25f, 0.5f, 0.75f, 1.0f);
		//Clear color buffer
		glClear(GL_COLOR_BUFFER_BIT);

		//draw or render
		window->render();

		//swap buffers
		SDL_GL_SwapWindow(window->window);

		end = SDL_GetPerformanceCounter();

		//Calculate frametime
		float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
		//*Will not use this function in the future
		//window->getFrameTime(elapsed);

		//avoid cpu idle
		usleep(1);
	}

	//delete any memory
	delete window;

	printf("Exiting...\n");

	return 0;
}
