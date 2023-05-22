#shader vertex
#version 420

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in int  a_Type;
layout(location = 3) in int  a_EntityId;

struct VertexOutput
{
	vec4 FragColor;
};

layout(location = 0) out VertexOutput v_Output;
layout(location = 1) out flat int v_EntityId;

void main()
{
	v_Output.FragColor = a_Color;
	v_EntityId = a_EntityId;

	if (a_Type == 0)
	{
		gl_Position = u_ProjectionMatrix * u_ViewMatrix * vec4(a_Position, 0, 1.0f);
	}
	else
	{
		gl_Position = u_OrthoProjectionMatrix * u_OrthoViewMatrix * vec4(a_Position, 0, 1.0f);
	}
}

#shader fragment
#version 420

layout(location = 0) out vec4 Color;
layout(location = 1) out int Color2;

struct VertexOutput
{
	vec4 FragColor;
};

layout(location = 0) in VertexOutput v_Output;
layout(location = 1) in flat int v_EntityId;

void main()
{
	Color2 = v_EntityId;

	Color = v_Output.FragColor;
}