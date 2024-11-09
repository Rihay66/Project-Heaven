#pragma once

#ifndef RESOURCE_SHADER_HPP
#define RESOURCE_SHADER_HPP

// include standard libraries
#include <string>

// include GLAD and GLM
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

/* The Shader class allows for to compiles from file, generates
 compile/link-time error messages and hosts several utility 
 functions for easy management of a shader.
*/
class Shader{
    private:
        // checks if compilation or linking failed and if so, print the error logs
        void    checkCompileErrors(unsigned int object, std::string type); 
    public:
        // state
        unsigned int ID; 
        // constructor
        Shader() { }
        // sets the current shader as active
        Shader  &Use();
        // compiles the shader from given source code
        void    Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr); // note: geometry source code is optional 
    
        /* utility functions
        * NOTE: Allow for setting variables in the loaded shader
        */

        void    SetFloat    (const char* name, float value, bool useShader = false);
        void    SetInteger  (const char* name, int value, bool useShader = false);
        void    SetVector2f (const char* name, float x, float y, bool useShader = false);
        void    SetVector2f (const char* name, const glm::vec2& value, bool useShader = false);
        void    SetVector3f (const char* name, float x, float y, float z, bool useShader = false);
        void    SetVector3f (const char* name, const glm::vec3& value, bool useShader = false);
        void    SetVector4f (const char* name, float x, float y, float z, float w, bool useShader = false);
        void    SetVector4f (const char* name, const glm::vec4& value, bool useShader = false);
        void    SetMatrix4  (const char* name, const glm::mat4& matrix, bool useShader = false);
};


#endif