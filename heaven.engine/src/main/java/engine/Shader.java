package engine;

import org.joml.*;
import static org.lwjgl.opengl.GL45.*;

public class Shader {
        private int ID = -1;
        String errorInfoLog;

        //* NOTE: uses default constructor

        public  Shader use(){
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



        public String compile(String vertexSource, String fragmentSource, String geometrySource){
            // storage reference of the vertex,fragment, and geometry shaders
            int sVertex, sFragment, gShader = 0;
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

            // optionally check for geometry shader
            if(geometrySource != null){
                gShader = glCreateShader(GL_GEOMETRY_SHADER);
                glShaderSource(gShader, geometrySource, null);
                glCompileShader(gShader);
                if(checkCompileErrors(gShader, "GEOMETRY")) {
                    return errorInfoLog;
                }
            }

            // shader program
            ID = glCreateProgram();
            glAttachShader(ID, sVertex);
            glAttachShader(ID, sFragment);
            if(geometrySource != null)
                glAttachShader(ID, gShader);
            glLinkProgram(ID);
            if(checkCompileErrors(ID, "PROGRAM")){
                return errorInfoLog;
            }

            // delete shaders as they're linked into the program and no longer necessary to keep them
            glDeleteShader(sVertex);
            glDeleteShader(sFragment);
            if(geometrySource != null){
                glDeleteShader(gShader);
            }

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
