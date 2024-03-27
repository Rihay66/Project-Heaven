import engine.Window;

import static org.lwjgl.opengl.GL45.*;

public class GameWindow extends Window {

    public GameWindow(int w, int h, String name){
        super(w, h, name);
    }

    public void init(){

    }

    public void update(){

    }

    public void stepUpdate(){

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
