uniform float maxHeight;
uniform float posHeight;
uniform float time;

void main() {
    float m = posHeight + posHeight * sin(gl_Vertex.x + time);
    vec4 v = vec4(gl_Vertex) + vec4(0,0,m,0);
    v.z *= maxHeight;
    gl_Position = gl_ModelViewProjectionMatrix * v;
}