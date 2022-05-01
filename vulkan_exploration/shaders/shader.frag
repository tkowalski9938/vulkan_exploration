#version 450

layout(location = 0) in vec3 fragColour;

// modifies the only framebuffer at index 0
layout(location = 0) out vec4 outColor;

void main() {
    // the 1.0 is the alpha channels
    outColor = vec4(fragColour, 1.0);
}
