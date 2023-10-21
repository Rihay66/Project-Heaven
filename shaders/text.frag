#version 450 core
in vec2 o_TexCoords;

uniform vec4 textColor;
uniform sampler2D text;

void main(){
    gl_FragColor = vec4(1, 1, 1, texture(text, o_TexCoords).a) * textColor;
}