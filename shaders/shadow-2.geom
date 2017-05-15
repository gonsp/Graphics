#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewProjectionMatrixInverse;

uniform vec3 boundingBoxMax;
uniform vec3 boundingBoxMin;

const vec4 BLACK = vec4(0, 0, 0, 1);
const vec4 CYAN = vec4(0, 1, 1, 1);

void main( void ) {
	for(int i = 0; i < 3; ++i) {
		gfrontColor = vfrontColor[i];
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
    for(int i = 0; i < 3; ++i) {
    	gfrontColor = BLACK;
    	gl_Position = modelViewProjectionMatrixInverse * gl_in[i].gl_Position;
    	gl_Position.y = boundingBoxMin.y;
    	gl_Position = modelViewProjectionMatrix* gl_Position;
    	EmitVertex();
    }
    EndPrimitive();
    if(gl_PrimitiveIDIn == 0) {
    	float R = distance(boundingBoxMin, boundingBoxMax)/2;
    	vec3 C = (boundingBoxMax + boundingBoxMin)/2;
    	C.y = boundingBoxMin.y - 0.01;
    	vec4 points[] = vec4[] (
    		vec4(C.x-R, C.y, C.z-R, 1),
    		vec4(C.x+R, C.y, C.z-R, 1),
    		vec4(C.x-R, C.y, C.z+R, 1),
    		vec4(C.x+R, C.y, C.z+R, 1)
    	);
    	for(int i = 0; i < 4; ++i) {
    		gl_Position = modelViewProjectionMatrix*points[i];
    		gfrontColor = CYAN;
    		EmitVertex();
    	}
    	EndPrimitive();
    }
}
