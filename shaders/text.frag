#version 450 core
in vec2 o_TexCoords;
out vec4 color;

uniform vec4 textColor;
uniform sampler2D text;

void main(){
    color = vec4(textColor) * texture(text, o_TexCoords);
}