#version 450

layout(location = 0) out vec3 fragColour;

// coordinates of the triangle in normalized coordinates
vec2 positions[3] = vec2[](
                           vec2(0.0, -0.5),
                           vec2(0.5, 0.5),
                           vec2(-0.5, 0.5)
                           );

// colours of the coordinates in RGB
vec3 colours[3] = vec3[](
                         vec3(1.0, 0.0, 0.0),
                         vec3(0.0, 1.0, 0.0),
                         vec3(0.0, 0.0, 1.0)
                         );
void main() {
    // creates pseudo clip coordinates
    gl_Position = vec4(positions[gl_VertexIndex], 0.0, 1.0);
    fragColour = colours[gl_VertexIndex];
}

