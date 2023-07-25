#include "../inc/window.h"

const int WIDTH = 1280, HEIGHT = 720;

int main(){
	
	//create window
	Window window(WIDTH, HEIGHT, "Project-Heaven");
	
	//update loop
	while(!glfwWindowShouldClose(window.handle)){

		//process input

		//check for window input
		window.window_input();

		//Render background
		glClearColor(0.25f, 0.5f, 0.75f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//swap buffers
		glfwSwapBuffers(window.handle);
		//check for glfw events
		glfwPollEvents();
		//avoid cpu idle
		usleep(1);
	}

	return 0;
}
