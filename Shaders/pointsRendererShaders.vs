#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec4 vertexColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 cameraPos;

void main() {
   gl_Position = projection * view * model * vec4(position, 1.0);
   float distanceFromCamera = sqrt((cameraPos.x - position.x) * (cameraPos.x - position.x) + (cameraPos.y - position.y) * (cameraPos.y - position.y) + (cameraPos.z - position.z) * (cameraPos.z - position.z));
   gl_PointSize = max(100 / distanceFromCamera, 3.0f);
   vertexColor = vec4(color, 1.0);
}