#version 320 es
in vec2 o_TexCoords;
in vec4 o_spriteColor;
in float o_TexIndex;

out vec4 color;

uniform sampler2D image[32];

void main(){   
    int index = int(o_TexIndex);
    color = vec4(o_spriteColor) * texture(image[index], o_TexCoords);
}