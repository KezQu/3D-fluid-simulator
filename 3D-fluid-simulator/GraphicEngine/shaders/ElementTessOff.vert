#version 460 core
#extension GL_NV_gpu_shader5 : enable

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColor;

layout(location = 0) out vec4 outColor;
layout(location = 1) out vec3 normal;

const uint KernelRadius = 4;
const uint MaxNeighbours =  uint32_t(4 * pow(KernelRadius, 3));

struct PhysicsProperties {
	vec4 forceMass;
	vec4 velocity;
	vec4 position;	
	vec4 VolumeDensityPressureMass;
	uint16_t neighbours[MaxNeighbours];
};

layout(std430, binding = 0) buffer dataBuffer{
	PhysicsProperties particle[];
};

vec4 CalculateNDC(in vec3 position, in vec4 offset);

void main(){
	outColor = inColor / 255.;
	normal = -inPosition;
	gl_Position = CalculateNDC(inPosition, particle[gl_InstanceID].position);
	gl_PointSize = 10;
}