#version 330 core

uniform mat4 u_ModelViewMatrix;

layout (location = 0) in vec3 aVertexPosition;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 v_TexCoord;

void main()
{
   /// gl_Position = aVertexPosition; //vec4(aVertexPosition;
   gl_Position = u_ModelViewMatrix * vec4( aVertexPosition, 1.0); //vec4(aVertexPosition;
    ourColor = aColor;
    v_TexCoord = aTexCoord;
}