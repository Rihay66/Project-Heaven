#version 450 core
in vec2 o_TexCoords;
in float o_TexIndex;
out vec4 color;

uniform vec4 textColor;
uniform sampler2D text[128];

void main(){
    int index = int(o_TexIndex);
    color = vec4(textColor) * texture(text[index], o_TexCoords);
}