#version 460 core

layout(location = 0) in vec4 inColorTesc[];
layout(location = 3) in vec3 inShapeOffset[];

layout(vertices = 3) out;
layout(location = 0) out vec4 outColorTesc[];
layout(location = 3) out vec3 outShapeOffset[];

uniform uint subdivision;

void main()
{
  outColorTesc[gl_InvocationID] = inColorTesc[gl_InvocationID];
  outShapeOffset[gl_InvocationID] = inShapeOffset[gl_InvocationID];
  gl_TessLevelOuter[gl_InvocationID] = subdivision;
  gl_TessLevelInner[0] = subdivision;
  gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
  barrier();
}