#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(push_constant) uniform fragPushConstants {
    vec4 color;
} u_pushConstants;

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main() {
	//outColor = texture(texSampler, fragTexCoord); // texture colour
    //outColor = vec4(fragTexCoord, 0.0, 1.0); // uv coord as red-green
    //outColor = texture(texSampler, fragTexCoord) * ubo.color; // testing using the ubo
	outColor = texture(texSampler, fragTexCoord) * u_pushConstants.color; // texture colour
}