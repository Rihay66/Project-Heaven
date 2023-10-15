#include "../inc/gameWindow.hpp"

const unsigned int WIDTH = 1280, HEIGHT = 720;

int main(int argc, char* argv[]){
	
	//create window
	GameWindow* window = new GameWindow(WIDTH, HEIGHT, "Project-Heaven");

	//init resources from files and load classes
	window->init();

	//set up vars for calculating delta time
	float deltaTime = 0, lastFrame = 0, currentFrame = 0;
	
	//update loop
	while(!glfwWindowShouldClose(window->handle)){

		//calculate delta time
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		//pass delta time to the window
		window->DeltaTime = deltaTime;
		
		//check for glfw events
		glfwPollEvents();
		//check for main window input
		window->getInput();

		//update any input, values, objects, loading etc..
		window->update();

		//Render background
		glClearColor(0.25f, 0.5f, 0.75f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//draw or render
		window->render();

		//swap buffers
		glfwSwapBuffers(window->handle);
	}

	//delete any memory
	delete window;

	printf("Exiting...\n");

	return 0;
}
