#shader vertex
#version 420

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoords;

layout (location = 0) out vec2 TexCoords;

void main()
{
    TexCoords = aTexCoords;
    gl_Position = vec4(aPos.x, aPos.y, 0.0f, 1.0f);
}

#shader fragment
#version 420

layout (location = 0) out vec4 Color;

layout (location = 0) in vec2 TexCoords;

layout(binding = 0) uniform sampler2D samplingTexture;
layout(binding = 1) uniform sampler2DArray samplingArrayTexture;

//const float near = 0.01f;
//const float far = 100.0f;
const float near = 0.1f;
const float far = 500.0f;

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));
}

void main()
{
    vec3 linearColor = vec3(0);

    vec4 textureColor = vec4(0);
    if (u_samplingLayer >= 0)
    {
        textureColor = texture(samplingArrayTexture, vec3(TexCoords, u_samplingLayer));
    }
    else
    {
        textureColor = texture(samplingTexture, TexCoords);
    }

    if (u_samplingType == 0) // Linear Color Transfer
    {
        linearColor = textureColor.rgb;
    }
    else if (u_samplingType == 1) // Single R-Channel Transfer
    {
        linearColor = vec3(textureColor.r);
    }
    else if (u_samplingType == 2) // Linearize R-Channel Transfer
    {
        linearColor = vec3(LinearizeDepth(textureColor.r) / far);
    }
    else if (u_samplingType == 3) // HDR + Gamma Correction Transfer
    {
        linearColor = vec3(1.0f) - exp(-(textureColor.rgb) * u_Exposure);
        linearColor = pow(linearColor, u_GammaAdjustment.rgb);
    }
    else if (u_samplingType == 4) // Simple Gamma Correction Transfer
    {
        linearColor = pow(textureColor.rgb, u_GammaAdjustment.rgb);
    }
    else if (u_samplingType == 5)
    {
        if (textureColor.a < 0.1f) { discard; }
        linearColor = textureColor.rgb;
    }
    else if (u_samplingType == 6)
    {
        gl_FragDepth = LinearizeDepth(textureColor.r);
    }
    Color = vec4(linearColor, 1.0f);
}