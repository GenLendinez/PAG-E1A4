#version 400

layout (location = 0) in vec3 vPosition;

uniform mat4 mvpMatrix;
uniform float pointSize;

void main() {
    gl_PointSize = pointSize;
    gl_Position = mvpMatrix * vec4(vPosition, 1.0);
}

