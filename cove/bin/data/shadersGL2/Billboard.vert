
uniform vec4 posData;

void main() {
	gl_TexCoord[0] = gl_MultiTexCoord0;
	vec4 eyeCoord = gl_ModelViewMatrix * gl_Vertex;
	gl_Position = gl_ProjectionMatrix * eyeCoord;
	float dist = sqrt(eyeCoord.x*eyeCoord.x + eyeCoord.y*eyeCoord.y + eyeCoord.z*eyeCoord.z);
	float att	 = 1.0;//800.0 / dist;
	
	gl_PointSize = gl_Normal.x * att;
	gl_FrontColor = gl_Color;

	// vec4 wpos = vec4(posData.xyz, 1.0);
 //    vec4 epos = gl_ModelViewMatrix * wpos;
 //    epos.xy += gl_Vertex.xy * posData.w; 
 //    gl_Position = gl_ProjectionMatrix * epos;
 //    gl_TexCoord[0] = gl_Vertex*0.5 + vec4(0.5);
 //    gl_FrontColor = gl_Color;
}





