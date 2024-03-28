package engine;

import org.joml.*;
public class GameObject {
    public Vector2f position, size;
    public Vector4f color;
    public float rotation;
    public int textureIndex;

    public GameObject(int texture, Vector2f pos, Vector2f siz, Vector4f clr){
        textureIndex = texture;
        position = pos;
        size = siz;
        color = clr;
        rotation = 0.0f;
    }
}
