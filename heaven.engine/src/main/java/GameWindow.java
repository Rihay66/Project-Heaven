import engine.*;

import static org.lwjgl.opengl.GL45.*;

public class GameWindow extends Window {
    private Camera cam;
    public GameWindow(int w, int h, String name){
        super(w, h, name);
    }

    public void init(){
        // create an instance of the resource manager
        ResourceManager.getInstance();
        cam = new Camera(getWidth(), getHeight(), null);

    }

    public void update(){

    }

    public void stepUpdate(double ts){

    }

    public void render(){
        glClearColor(0.8f, 0.0f, 1.0f, 1.0f);
    }

    public static void main(String[] args){
        GameWindow win = new GameWindow(800, 600, "test");
        win.init();
        win.runtime();
    }
}
