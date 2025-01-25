#version 450 core
layout (location = 0) in vec4 vertex;

out vec2 o_TexCoords;

uniform mat4 projectionView;

void main(){
    gl_Position = projectionView * vec4(vertex.xy, 0.0, 1.0);
    o_TexCoords = vertex.zw;
}