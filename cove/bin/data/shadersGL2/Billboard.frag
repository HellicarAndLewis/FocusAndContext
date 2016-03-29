uniform sampler2D tex;
uniform float alpha;

void main (void) {
    vec4 color = texture2D(tex, gl_TexCoord[0].st) * gl_Color;
    float newAlpha;
    if(color.a < 0.9) {
       newAlpha = 0.0;
    } else {
        newAlpha = alpha;
    }
    gl_FragColor = vec4(color.r, color.g, color.b, newAlpha);
}
