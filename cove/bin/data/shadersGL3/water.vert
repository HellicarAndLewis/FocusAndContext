uniform float tme;
varying vec4 glPos;
 
void main() {
     gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
     glPos = gl_Vertex;
}