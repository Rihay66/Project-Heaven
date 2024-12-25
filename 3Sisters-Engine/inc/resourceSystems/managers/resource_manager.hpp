#pragma once

#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

// include standard libraries
#include <map>
#include <string>
#include <vector>
#include <array>

// include necessary classes such as texture and shader classes
#include <resourceSystems/resource_texture.hpp>
#include <resourceSystems/resource_shader.hpp>

// include resource definitions
#include <resourceSystems/resource_types.hpp>

/* A static singleton Resource Manager class that hosts several
 functions to load Textures and Shaders. Each loaded texture
 and/or shader is also stored for future reference by string
 handles. All functions and resources are static and no
 public constructor is defined.
*/
class ResourceManager{
    public:
        //* loader functions

        /*  loads (and generates) a shader program from file along with a name, loads the files in this order of vertex, fragment (and geometry) and extracts the shader's source code
        * @NOTE: it is optional to load a geometry shader file, if there is no geometry shader then set as nullptr
        */
        static Shader& LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name);

        /* loads (and generates) a texture from file along with a name and optional texture filter option
        * @NOTE: depending on the file type alpha is automatically set
        * @NOTE: by default the texture's filter is set to be nearest and it is optional to set it to true which sets to be linear
        */
        static Texture& LoadTexture(const char *file, std::string name, bool linearFilter = false);

        /* loads (and generates) a font from file with a font size along with a name and optional texture filter option
        * @NOTE: by default the texture's filter is set to be nearest and it is optional to set it to true which sets to be linear
        */
        static std::map<char, Character>& LoadFontTexture(const char *file, unsigned int fontsize, std::string name, bool linearFilter = true);

        // use a loaded texture to create a sub texture along with a name
        static std::array<glm::vec2, 4>& GenerateSubTexture(std::string name, Texture& texture, glm::uvec2 coordinates, glm::uvec2 cellSize, glm::uvec2 spriteSize = {1, 1});
        
        // create a white texture that is named "default"
        static void GenerateWhiteTexture();

        //* getter functions

        // retrieves a stored shader
        static Shader& GetShader(std::string name);

        // retrieves a stored texture's ID index
        static int GetTextureIndex(std::string name);

        // retrieves a stored texture
        static Texture& GetTexture(std::string name);

        // retrieves a stored font texture map that contains characters and associated font character
        static std::map<char, Character>& GetFontTexture(std::string name);

        // retrieve a stored sub texture
        static std::array<glm::vec2, 4>& GetSubTexture(std::string name);

        //* helper functions

        /* binds all textures (not fonts) from the texture list to be used by OpenGL
        * @NOTE: is automatically called by LoadTexture()
        */
        static bool BindTextures();
        
    private:
        // private resource storage
        static std::map<std::string, Shader> Shaders;
        //TODO: Switch to use std::array
        static std::map<std::string, Texture> Textures;
        static std::map<std::string, std::map<char, Character>> Fonts;
        static std::map<std::string, SubTexture> SubTextures;
        static std::vector<unsigned int> texIDList;
        // (caveman way) track if the white texture has been generated 
        static bool doesWhiteTexExist;
        
        // private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
        ResourceManager() {}
        // loads and generates a shader from file
        static Shader loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile = nullptr);
        // loads a single texture from file
        static Texture loadTextureFromFile(const char *file, bool alpha, bool isLinear);
        // properly de-allocates all loaded resources
        static void clear();
        
        //! Currently EXPERIMENTAL, may cause exceptions or segfaults
        // private boolean to track automatic clear()
        static bool isAutoClearSet;
        // set up automatic de-allocation of loaded resources
        static void setUpAutoClear();
};

#endif
