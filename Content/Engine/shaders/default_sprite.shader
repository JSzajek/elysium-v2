#shader vertex
#version 420
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TextureCoords;
layout(location = 3) in int  a_TextureIndex;
layout(location = 4) in int  a_IsFont;
layout(location = 5) in int  a_EntityId;
			
struct VertexOutput
{
	vec4 Color;
	vec2 TexCoordinates;
};

uniform mat4 projMatrix;

layout(location = 0) out VertexOutput v_Output;
layout(location = 2) out flat int v_IsFont;
layout(location = 3) out flat int v_TexIndex;
layout(location = 4) out flat int v_EntityId;

void main()
{
	v_Output.Color = a_Color;
	v_Output.TexCoordinates = a_TextureCoords;
	
	v_IsFont = a_IsFont;
	v_TexIndex = a_TextureIndex;
	v_EntityId = a_EntityId;
	
	mat4 view =  mat4(1);

	gl_Position = u_OrthoProjectionMatrix * u_OrthoViewMatrix * vec4(a_Position, 1.0f);
}

#shader fragment
#version 420
			
layout(location = 0) out vec4 Color;
layout(location = 1) out int Color2;

struct VertexOutput
{
	vec4 Color;
	vec2 TexCoordinates;
};

layout (location = 0) in VertexOutput v_Output;
layout (location = 2) in flat int v_IsFont;
layout (location = 3) in flat int v_TexIndex;
layout (location = 4) in flat int v_EntityId;

layout (binding = 0) uniform sampler2D textureMaps[16];

vec4 Texture(int index, vec2 coords);

void main()
{
	Color2 = v_EntityId;
	Color = vec4(1);
	vec4 textureColor = v_Output.Color;
	if (v_IsFont == 1)
	{
		textureColor.a *= Texture(v_TexIndex, v_Output.TexCoordinates).r;
	}
	else
	{
		textureColor *= Texture(v_TexIndex, v_Output.TexCoordinates);
	}
	
	if (textureColor.a < 0.1f) { discard; }
	Color = vec4(textureColor.rgb, textureColor.a);
}

vec4 Texture(int index, vec2 coords)
{
	switch (index)
	{
	case 0:  return texture(textureMaps[0], coords);
	case 1:  return texture(textureMaps[1], coords);
	case 2:  return texture(textureMaps[2], coords);
	case 3:  return texture(textureMaps[3], coords);
	case 4:  return texture(textureMaps[4], coords);
	case 5:  return texture(textureMaps[5], coords);
	case 6:  return texture(textureMaps[6], coords);
	case 7:  return texture(textureMaps[7], coords);
	case 8:  return texture(textureMaps[8], coords);
	case 9:  return texture(textureMaps[9], coords);
	case 10: return texture(textureMaps[10], coords);
	case 11: return texture(textureMaps[11], coords);
	case 12: return texture(textureMaps[12], coords);
	case 13: return texture(textureMaps[13], coords);
	case 14: return texture(textureMaps[14], coords);
	case 15: return texture(textureMaps[15], coords);
	}
	return vec4(0);
}