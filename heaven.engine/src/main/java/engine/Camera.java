package engine;


import org.joml.Matrix4f;
import org.joml.Vector3f;

public class Camera {
    protected Matrix4f projection, view, projectionView, transform;
    protected int width, height;

    protected Shader shader;

    public Vector3f position = new Vector3f(0.0f);

    public Camera(int w, int h, Shader s){
        if(s != null){
            shader = s;
        }
        width = w;
        height = h;
        // calculate the projectionView
        calculateProjectionView();
    }

    public void calculateProjectionView(){
        // set up projection
        projection = projection.ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f);

        // set up the transform
        transform = transform.translate(position).rotate(0.0f, 0.0f, 0.0f, 1.0f);

        view = view.invert(transform);

        projectionView = projection.mul(view);

        shader.use();
        shader.setMatrix4("projectionView", projectionView);
    }
}
