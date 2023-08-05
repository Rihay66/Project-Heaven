#version 330 core
layout (location = 0) in vec2 vertex; // <vec2 position, vec2 texCoords>
layout (location = 1) in vec2 tex;

out vec2 TexCoords;

uniform mat4 transform;
uniform mat4 projectionView;

void main()
{
    gl_Position = projectionView * transform * vec4(vertex, 0.0, 1.0);
    TexCoords = tex;
}