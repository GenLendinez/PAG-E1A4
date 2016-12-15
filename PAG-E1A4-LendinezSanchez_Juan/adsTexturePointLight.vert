#version 400

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTextCoord;

uniform mat4 mvpMatrix;
uniform mat4 mModelView;

out vec3 position;
out vec3 normal;
out vec2 textCoord;

void main() {
  normal = vec3( mModelView * vec4(vNormal, 0.0) );
  position = vec3( mModelView * vec4(vPosition, 1.0) );
  textCoord = vec2(vTextCoord.x,(1.0 - vTextCoord.y));
  gl_Position = mvpMatrix * vec4(vPosition, 1.0);
}
