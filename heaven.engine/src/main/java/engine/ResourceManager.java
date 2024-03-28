package engine;

import org.lwjgl.stb.STBImage;
import java.util.HashMap;
public class ResourceManager {
    private static ResourceManager instance = null;
    private HashMap<String, Shader> shaders;
    private HashMap<String, Texture> textures;

    private ResourceManager(){}

    public static synchronized ResourceManager getInstance(){
        if(instance == null)
            instance = new ResourceManager();

        return instance;
    }

    public Shader LoadShader(String vShaderFile, String fShaderFile, String name){
        return null;
    }

    public Shader getShader(String name){
        return null;
    }

    public Texture loadTexture(String file, String name, boolean alpha){
        return null;
    }

    public Texture getTexture(String name){
        return null;
    }

    public void cleanUp(){

    }

    private Shader loadShaderFromFile(String vShaderFile, String fShaderFile, String name){
        return null;
    }

    private Texture loadTextureFromFile(String file, boolean alpha){
        return null;
    }

}
