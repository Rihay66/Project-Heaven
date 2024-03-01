#pragma once

#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

// include standard libraries
#include <map>
#include <string>
#include <vector>

// include necessary classes such as texture and shader classes
#include <resourceSys/texture.hpp>
#include <resourceSys/shader.hpp>

/* A static singleton ResourceManager class that hosts several
 functions to load Textures and Shaders. Each loaded texture
 and/or shader is also stored for future reference by string
 handles. All functions and resources are static and no 
 public constructor is defined. 
*/
class ResourceManager{
    public:
        // holds all state information relevant to a character as loaded using FreeType
        struct Character{
            unsigned int TextureID; // ID handle of the glyph texture
            glm::ivec2 Size;        // size of glyph
            glm::ivec2 Bearing;     // offset from baseline to left/top of glyph
            unsigned int Advance;   // horizontal offset to advance to next glyph
        };

        // resource storage

        static std::map<std::string, Shader> Shaders;
        static std::map<std::string, Texture2D> Textures;
        static std::map<char, Character> Characters;

        // loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
        static Shader LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name);
        // retrieves a stored sader
        static Shader GetShader(std::string name);
        // loads (and generates) a texture from file
        static Texture2D LoadTexture(const char *file, std::string name, bool alpha = false);
        // loads (and generates) a text texture from file
        static int LoadFontTexture(const char *file, unsigned int fontsize, bool isLinear = true);
        // retrieves a stored texture on the texList vector
        static int GetTexture(std::string name);
        // binds all textures from the texture list to be used by OpenGL
        static bool BindTextures();
        // properly de-allocates all loaded resources
        static void Clear();

    private:
        // private resource storage
        static std::vector<unsigned int> texIDList;

        // private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
        ResourceManager() {}
        // loads and generates a shader from file
        static Shader loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile = nullptr);
        // loads a single texture from file
        static Texture2D loadTextureFromFile(const char *file, bool alpha);
};

#endif