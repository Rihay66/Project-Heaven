#version 320 es
precision highp float;
in vec2 o_TexCoords;
out vec4 color;

uniform vec4 textColor;
layout(binding = 0) uniform sampler2D text;

void main(){
    color = vec4(textColor) * vec4(1.0, 1.0, 1.0, texture(text, o_TexCoords).r);
}