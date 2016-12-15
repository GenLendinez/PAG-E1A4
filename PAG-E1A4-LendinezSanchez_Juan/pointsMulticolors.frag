#version 400

in vec4 destinationColor;

layout (location = 0) out vec4 fColor;

void main() {
    fColor = destinationColor;
}
