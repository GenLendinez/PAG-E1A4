#version 400

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vColor;
layout (location = 2) in float vPointSize;

uniform mat4 mvpMatrix;

out vec4 destinationColor;

void main() {
    gl_PointSize = 1.0f;
    destinationColor = vec4(vColor, 1.0);
    gl_Position = mvpMatrix * vec4(vPosition, 1.0);
}

