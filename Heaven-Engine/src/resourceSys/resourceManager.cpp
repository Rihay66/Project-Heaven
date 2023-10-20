#include <resourceSys/resourceManager.hpp>

#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include <resourceSys/stb_image.h>

// Instantiate static variables
std::map<std::string, Texture2D>    ResourceManager::Textures;
std::map<std::string, Shader>       ResourceManager::Shaders;
std::vector<Texture2D>              ResourceManager::texList;

static std::string checkName(std::string str){

    // Checking if string contains special character
    for(int i=0;i<str.length();i++)
    {
        if ((str[i]>=48 && str[i]<=57)||(str[i]>=65 && str[i]<=90)||(str[i]>=97 && str[i]<=122))
            continue;
        else
            std::cout << "ERROR: No special characters when setting or getting of either Shader or Texture! STR: \"" << str << "\""<< std::endl;
            exit(-1); //When a special character is found then stop the program
    }

    //Make all characters to lower case
    for(int j=0;j<str.length();j++){
        str[j]=tolower(str[j]);
    }
    
    return str;
}

Shader ResourceManager::LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name){
    name = checkName(name);
    Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name){
    name = checkName(name);
    return Shaders[name];
}

Texture2D ResourceManager::LoadTexture(const char *file, std::string name, bool alpha){
    name = checkName(name);
    Textures[name] = loadTextureFromFile(file, alpha);
    //Add texture to list
    texList.push_back(Textures[name]);
    return Textures[name];
}

int ResourceManager::GetTexture(std::string name){

    //*NOTE: The check is used to prevent using this function when no texture was binded to OpenGL
    if(texList.size() <= 0){
        std::cout << "ERROR: No textures were binded to OpenGL!" << std::endl;
        return -1;
    }

    name = checkName(name);
    int id = Textures[name].ID;

    for(int i = 0; i < texList.size(); i++){
        //check for id on the list and return it's location by iteration 
        if(texList[i].ID == id){
            //exit out and return texture index
            return i;
        }
    }

    //Error the texture couldn't be found
    std::cout << "ERROR: Couldn't find texture: " << name << ", in storage!" << std::endl; 
    return -1;
}

bool ResourceManager::BindTextures(){

    //Check if the texure list is not zero
    if(texList.size() <= 0){
        std::cout << "ERROR: No textures were loaded!" << std::endl;
        return false;
    }

    //bind all the textures from first to last
    for(int i = 0; i < texList.size(); i++){
        //call to bind texture by their ID
        glBindTextureUnit(i, texList[i].ID);
    }

    //Check OpenGL errors
    int errorCode = glGetError();
    if(errorCode != GL_NO_ERROR){
        std::cout << "Warning: An error occured during binding texures, ERROR Code: " << errorCode << std::endl;
        return false;
    }

    return true;
}

void ResourceManager::Clear(){
    // (properly) delete all shaders	
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.ID);
    // (properly) delete all textures
    for (auto iter : Textures)
        glDeleteTextures(1, &iter.second.ID);

    //Claer out the texture vector
    texList.clear();
}

Shader ResourceManager::loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile){
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    // create interface objs to get file
    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;
    // ensure ifstream objects can throw exceptions
    vertexShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        //open files
        vertexShaderFile.open(vShaderFile);
        fragmentShaderFile.open(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // if geometry shader path is present, also load a geometry shader
        if (gShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile(gShaderFile);
            // ensure the ifstream can throw exceptions
            geometryShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << e.what() << std::endl;
        //exit with error
        exit(-1);
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();
    const char *gShaderCode = geometryCode.c_str();
    // 2. now create shader object from source code
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const char *file, bool alpha){
    // create texture object
    Texture2D texture;
    if (alpha)
    {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    }
    // load image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    //check file if it has been found
    if(!data){
        std::cout << "ERROR: Failed to load texture file!" << std::endl;
        exit(-1);
    }
    // now generate texture
    texture.Generate(width, height, data);
    // and finally free image data
    stbi_image_free(data);
    return texture;
}