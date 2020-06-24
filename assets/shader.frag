#version 330 core

in vec2		vTexCoord0;
in vec2		vTexCoord1;
in vec3		vNormal;

layout (location = 0) out vec4 oFragColor0;

void main()
{
	// draw green to attachment 0, blue to attachment 1
	vec3 colorAttachment0 = vec3( 1, 0, 0 );

	// add some basic shading
	const vec3 lightPos = vec3( 0, 0, 1 );
	float lambert = max( 0.0, dot( normalize( vNormal ), lightPos ) );

	colorAttachment0 *= lambert;

	oFragColor0 = vec4( colorAttachment0, 1.0 );
}
