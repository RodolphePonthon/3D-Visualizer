#version 330 core

layout (location = 0) in vec3 aPos;

out vec4 vertexColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 cameraPos;//does not seem to work well for now

void main() {
   gl_Position = projection * view * model * vec4(aPos, 1.0);
   gl_PointSize = 5.0;
   vertexColor = vec4(1.0, 0.0, 0.0, 1.0);
}