#version 450 core
in vec2 o_TexCoords;
in vec3 o_spriteColor;
in float o_TexIndex;
out vec4 color;

uniform sampler2D image[32];

void main()
{   
    int index = int(o_TexIndex);
    color = vec4(o_spriteColor, 1.0) * texture(image[index], o_TexCoords);
}  