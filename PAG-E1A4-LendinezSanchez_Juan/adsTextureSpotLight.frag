#version 400

in vec3 position;
in vec3 normal;
in vec2 textCoord;

uniform vec3 direction;
uniform vec3 lightPosition;
uniform float angleMax;
uniform sampler2D TexSamplerColor; 
uniform vec3 Ks;
uniform vec3 Ia;
uniform vec3 Id;
uniform vec3 Is;
uniform float Shininess;

layout (location = 0) out vec4 FragColor;

vec3 ads(vec4 texColor)
{
	vec3 n;
	if (gl_FrontFacing){
		n = normalize( normal );
	}else{
		n = normalize( -normal );
	}
	vec3 Kad = texColor.rgb;
	vec3 l = normalize( lightPosition-position );
	vec3 d = normalize( direction );
	vec3 v = normalize( -position );
	vec3 r = reflect( -l, n );
	float angleM = (angleMax * 3.14) / 180;
	float sf = pow(dot(-l, direction), 1.5);
	if (dot(-l,direction) < cos(angleM)) {
		sf = 0.0;
	}
	vec3 ambient = (Ia * Kad);
	vec3 diffuse = (Id * Kad * max( dot(l,n), 0.0));
	vec3 specular;
	if (dot(l,n) < 0.0) {
		specular = vec3(0.0);
	}else{
		specular = (Is * Ks * pow( max( dot(r,v), 0.0), Shininess));
	}
	return ambient + (sf * (diffuse + specular)) ;
}

void main() {

	vec4 texColor = texture(TexSamplerColor, textCoord);
	FragColor = vec4(ads(texColor), 1.0);
}

