#version 450 core
layout (location = 0) in vec2 vertex; // <vec2 position, vec2 texCoords>
layout (location = 1) in vec2 texCoords;
layout (location = 2) in float texIndex;

out vec2 o_TexCoords;
out float o_TexIndex;

uniform mat4 transform;
uniform mat4 projectionView;

void main()
{
    gl_Position = projectionView * transform * vec4(vertex, 0.0, 1.0);
    o_TexCoords = texCoords;
    o_TexIndex = texIndex;
}