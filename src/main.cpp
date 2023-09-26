#include "../inc/gameWindow.hpp"

const unsigned int WIDTH = 1280, HEIGHT = 720;

int main(){
	
	//create window
	GameWindow* window = new GameWindow(WIDTH, HEIGHT, "Project-Heaven");

	//init resources from files and load classes
	window->init();

	//set up vars for calculating delta time
	//set up vars for calculating delta time
	float deltaTime = 0;
	Uint32 mTicksCount = 0;
	int w, h;
	
	//update loop
	while(!window->quit){

		//calculate delta time
		// Wait until 16ms has elapsed since last frame
   		while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

   		// Delta time is the difference in ticks from last frame
   		// (converted to seconds)
   		deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
		// Update tick counts (for next frame)
   		mTicksCount = SDL_GetTicks();

		//Get event
		SDL_PollEvent(&window->eventHandle);

		//pass delta time to the window
		window->DeltaTime = deltaTime;

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
