
#define Math_PI 3.1415926535897932384626433
#define Math_TAU 6.2831853071795864769252867666

layout(std140, binding = 0) uniform Camera
{
	mat4 u_ViewMatrix;
	mat4 u_OrthoViewMatrix;
	mat4 u_ProjectionMatrix;
	mat4 u_OrthoProjectionMatrix;
	vec4 u_CameraPosition;
	vec4 u_Viewport;
};

layout(std140, binding = 1) uniform TimeData
{
	float u_Time;
	float u_DeltaTime;
};

layout(std140, binding = 2) uniform PostProcess
{
	vec4 u_GammaAdjustment;
	float u_Exposure;
	int u_samplingType;
    int u_samplingLayer;
};
