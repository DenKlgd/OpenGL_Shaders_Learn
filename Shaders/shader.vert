#version 330

layout (location = 0) in vec3 pos;
out vec3 localCoords;
out vec4 worldCoords;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(pos, 1.0);
    
    localCoords = pos;
    worldCoords = gl_Position;
}