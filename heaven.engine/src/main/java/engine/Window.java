package engine;

import org.lwjgl.*;
import org.lwjgl.glfw.*;
import org.lwjgl.opengl.*;
import org.lwjgl.system.*;

import java.util.Objects;

import static org.lwjgl.glfw.Callbacks.*;
import static org.lwjgl.glfw.GLFW.*;
import static org.lwjgl.opengl.GL45.*;
import static org.lwjgl.system.MemoryUtil.*;

public abstract class Window {

    private double last_frame;
    private double current_frame;
    private double accumulator;
    private int width;
    private int height;
    private double fixed_timeStep = 1.0f/60.0f;
    private double deltaTime;
    private long windowHandle;

    public Window(int w, int h, String name){
        // store the passed width and height
        width = w;
        height = h;
        // set up the rest of the variables to a default value
        last_frame = 0;
        current_frame = 0;
        accumulator = 0;
        deltaTime = 0;

        // initialize the window
        initializeWindow(name);
    }

    public double getDeltaTime(){
        current_frame = glfwGetTime();
        deltaTime = current_frame - last_frame;
        if(deltaTime > 0.25){
            deltaTime = 0.25;
        }
        last_frame = current_frame;
        return deltaTime;
    }

    private void initializeWindow(String name){
        // setup the GLFW error callback
        // by default print error messages in System.err
        GLFWErrorCallback.createPrint(System.err).set();

        // initialize glfw
        if(!glfwInit())
            throw new IllegalStateException("ERROR: Unable to initialize GLFW");

        // configure GLFW
        glfwDefaultWindowHints(); // the current window hints are already the defaults
        glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);

        // create the window context and store into the "windowHandle" attribute
        windowHandle = glfwCreateWindow(width, height, name, NULL, NULL);
        // check the window handle
        if(windowHandle == NULL)
            throw new RuntimeException("ERROR: Failed to create the GLFW window");

        // make the OpenGL context
        glfwMakeContextCurrent(windowHandle);

        // create the OpenGL capabilities
        GL.createCapabilities();

        // set up OpenGL for 2D rendering
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    public abstract void init();

    public abstract void update();

    public abstract void stepUpdate();

    public abstract void render();

    public void runtime(){
        // main loop of the window
        while(!glfwWindowShouldClose(windowHandle)){
            // get the deltaTime
            getDeltaTime();

            // check for any glfw events
            glfwPollEvents();

            // accumulate time and do stepUpdate()
            accumulator += deltaTime;
            while(accumulator >= fixed_timeStep){
                stepUpdate();
                accumulator -= fixed_timeStep;
            }

            //update any  values, objects, loading, etc..
            update();

            // clear the color buffer
            glClear(GL_COLOR_BUFFER_BIT);

            // draw or render
            render();

            // swap buffers
            glfwSwapBuffers(windowHandle);
        }
        // exit the window
        cleanUp();
    }

    private void cleanUp(){
        // Free the window callbacks and destroy the window
        glfwFreeCallbacks(windowHandle);
        glfwDestroyWindow(windowHandle);

        // Terminate GLFW and free the error callback
        glfwTerminate();
        Objects.requireNonNull(glfwSetErrorCallback(null)).free();
    }

    //unit test for window

}
