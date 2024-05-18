#pragma once

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

//include GLAD
#include <glad/glad.h>

/* Texture2D is able to store and configure a 2D texture in OpenGL.
 It also hosts utility variables for easy management and modifiability.
 The class requires an image size and a path to the texture.
*/
class Texture2D{
public:
    // holds the ID of the texture object, used for all texture operations to reference to this particular texture
    unsigned int ID;
    // texture image dimensions
    unsigned int Width, Height; // width and height of loaded image in pixels
    // texture Format
    unsigned int Internal_Format; // format of texture object
    unsigned int Image_Format; // format of loaded image
    // texture configuration
    unsigned int Wrap_S; // wrapping mode on S axis
    unsigned int Wrap_T; // wrapping mode on T axis
    unsigned int Filter_Min; // filtering mode if texture pixels < screen pixels
    unsigned int Filter_Max; // filtering mode if texture pixels > screen pixels
    // constructor (sets default texture modes)
    Texture2D();
    // generates texture from image data
    void Generate(unsigned int width, unsigned int height, unsigned char* data);
};

#endif