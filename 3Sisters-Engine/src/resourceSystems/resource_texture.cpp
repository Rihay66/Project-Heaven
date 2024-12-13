#include <resourceSystems/resource_texture.hpp>

Texture::Texture() : Width(0), Height(0), Internal_Format(GL_RGB), Image_Format(GL_RGB), 
Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT), Filter_Min(GL_NEAREST), Filter_Max(GL_NEAREST) 
{}

void Texture::Generate(unsigned int width, unsigned int height, unsigned char* data){
    this->Width = width;
    this->Height = height;
    // generate ID
    glGenTextures(1, &this->ID);
    // bind Texture
    glBindTexture(GL_TEXTURE_2D, this->ID);
    // set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);

    glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, width, height, 0, this->Image_Format, GL_UNSIGNED_BYTE, data);
    
    // create mipmap, when objects are far away, OpenGL will set the correct texture resolution
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::BindTexture(){
    // bind texture
    glBindTexture(GL_TEXTURE_2D, this->ID);
}

void Texture::DeleteTexture(){
    // delete the texture
    glDeleteTextures(1, &ID);
}

void Texture::SetTextureInternalFormat(unsigned int format){
    Internal_Format = format;
}

void Texture::SetTextureImageFormat(unsigned int format){
    Image_Format = format;
}

void Texture::SetTextureFilterMin(unsigned int filter){
    Filter_Min = filter;
}

void Texture::SetTextureFilterMax(unsigned int filter){
    Filter_Max = filter;
}

void Texture::SetWrapS(unsigned int mode){
    Wrap_S = mode;
}

void Texture::SetWrapT(unsigned int mode){
    Wrap_T = mode;
}

unsigned int& Texture::GetID(){
    return this->ID;
}

unsigned int Texture::GetWidth(){
    return Width;
}

unsigned int Texture::GetHeight(){
    return Height;
}