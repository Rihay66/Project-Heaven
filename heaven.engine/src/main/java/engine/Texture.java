package engine;

import java.nio.FloatBuffer;

import static org.lwjgl.opengl.GL45.*;

public class Texture {
    private int ID;
    private int width, height;
    private int internal_format;
    private int image_format;
    private int wrap_s;
    private int wrap_t;
    private int filter_min;
    private int filter_max;
    public Texture(){
        ID = -1;
        width = 0;
        height = 0;
        internal_format = GL_RGB;
        image_format = GL_RGB;
        wrap_s = GL_REPEAT;
        wrap_t = GL_REPEAT;
        filter_min = GL_NEAREST;
        filter_max = GL_NEAREST;
    }

    public int getTextureID(){
        if(ID != -1){
            return ID;
        }
        return -1;
    }

    public void generate(int w, int h, FloatBuffer data){
        if(ID == -1){
            ID = glGenTextures();

            width = w;
            height = h;

            // create texture
            glBindTexture(GL_TEXTURE_2D, ID);
            // set texture wrap and filter modes
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_min);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_max);

            // generate the image
            glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height,0, image_format, GL_UNSIGNED_BYTE, data);

            // create MipMap, when objects are far away, OpenGL will set the correct texture resolution
            glGenerateMipmap(GL_TEXTURE_2D);
        }else{
            // delete previous texture
            glDeleteTextures(ID);
            ID = -1;
            // recall generate to make a new texture
            generate(w, h, data);
        }
    }
}
