#version 450 core
in vec2 o_TexCoords;
in float o_TexIndex;
out vec4 color;

uniform sampler2D image[32];
uniform vec3 spriteColor;

void main()
{   
    int index = int(o_TexIndex);
    color = vec4(spriteColor, 1.0) * texture(image[index], o_TexCoords);
}  