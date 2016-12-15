#version 400



layout (location = 0) out vec4 fColor;

void main() {
	vec3 vColor;
	if (gl_FrontFacing){
		vColor = vec3(0,1,0);
	}else{
		vColor = vec3(1,0,0);
	}
    fColor = vec4(vColor, 1.0);
}
