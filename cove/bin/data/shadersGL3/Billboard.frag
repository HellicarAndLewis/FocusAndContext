#version 150

uniform sampler2D tex;
uniform float alpha;

in vec4 colorVarying;

out vec4 fragColor;

void main (void) {
	vec4 color = texture(tex, gl_PointCoord) * colorVarying;
    if(color.a == 0.) alpha = color.a;
    fragColor = vec4(color.r, color.g, color.b, alpha);
}
