package engine;

import org.joml.*;
import static org.lwjgl.opengl.GL45.*;

public class Shader {
        private int ID = -1;
        String errorInfoLog;

        //* NOTE: uses default constructor

        public  Shader use(){
            if(ID == -1){
                return null;
            }

            glUseProgram(ID);
            return this;
        }

        public void setFloat(String name, float value){
            if(ID != -1)
                glUniform1f(glGetUniformLocation(ID, name), value);
        }

        public void setInteger(String name, int value){
            if(ID != -1)
                glUniform1i(glGetUniformLocation(ID, name), value);
        }

        public void setVector2f(String name, Vector2f value){
            if(ID != -1)
                glUniform2f(glGetUniformLocation(ID, name), value.x, value.y);
        }

        public void setVector3f(String name, Vector3f value){
            if(ID != -1)
                glUniform3f(glGetUniformLocation(ID, name), value.x, value.y, value.z);
        }

        public void setVector4f(String name, Vector4f value){
            if(ID != -1)
                glUniform4f(glGetUniformLocation(ID, name), value.x, value.y, value.z, value.w);
        }

        public void setMatrix4(String name, Matrix4f value){
            if(ID != -1){
                float[] data = new float[16];
                glUniformMatrix4fv(glGetUniformLocation(ID, name), false, value.get(data));
            }
        }

        public String compile(String vertexSource, String fragmentSource){
            // storage reference of the vertex,fragment, and geometry shaders
            int sVertex, sFragment;
            // vertex shader
            sVertex = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(sVertex, vertexSource, null);
            glCompileShader(sVertex);
            if(checkCompileErrors(sVertex, "VERTEX")){
                return errorInfoLog;
            }

            // fragment shader
            sFragment = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(sFragment, fragmentSource, null);
            glCompileShader(sFragment);
            if(checkCompileErrors(sFragment, "FRAGMENT")){
                return errorInfoLog;
            }

            // shader program
            ID = glCreateProgram();
            glAttachShader(ID, sVertex);
            glAttachShader(ID, sFragment);
            glLinkProgram(ID);
            if(checkCompileErrors(ID, "PROGRAM")){
                return errorInfoLog;
            }

            // delete shaders as they're linked into the program and no longer necessary to keep them
            glDeleteShader(sVertex);
            glDeleteShader(sFragment);

            // returning nothing when there isn't an error
            return null;
        }

        private boolean checkCompileErrors(int obj, String type){
            int[]  success = new int[1];
            if(!type.equals("PROGRAM")){
                glGetShaderiv(obj, GL_COMPILE_STATUS, success);
                if(success[0] == GL_FALSE){
                    errorInfoLog = "ERROR::SHADER: Compile-time error: Type: " + type + "\n" +
                            glGetShaderInfoLog(obj, 1024);
                    return true;
                }
            }else{
                glGetProgramiv(obj, GL_LINK_STATUS, success);
                if(success[0] == GL_FALSE){
                    errorInfoLog = "ERROR::SHADER: Link-time error: Type: " + type + "\n" +
                            glGetProgramInfoLog(obj, 1024);
                    return true;
                }
            }

            return false;
        }
}
