
Texture2D texDiffuse : register(t0);

struct PSIn
{
	float4 Pos  : SV_Position;
	float3 Normal : NORMAL;
	float2 TexCoord : TEX;
    float4 WorldPos : WorldPos;
};

cbuffer LightCamBuffer : register(b0)
{
	float4 LightPosition;   // xyz represents light position
	float4 CameraPosition;  // xyz represents camera position
}
cbuffer MaterialBuffer : register(b1)
{
    float4 AmbientColor;
    float4 DiffuseColor;
    float4 SpecularColor;
    float Shininess;
}


//-----------------------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------------------

//float4 PS_main(PSIn input) : SV_Target
//{
//	// Debug shading #1: map and return normal as a color, i.e. from [-1,1]->[0,1] per component
//	// The 4:th component is opacity and should be = 1
//	return float4(input.Normal*0.5+0.5, 1);
//	
//    //return float4(1,0,0,1);
//	
//	// Debug shading #2: map and return texture coordinates as a color (blue = 0)
////	return float4(input.TexCoord, 0, 1);
//}

// Pixel Shader
float4 PS_main(PSIn input) : SV_Target
{
    // Calculate normalized vectors
    float3 lightDir = normalize(LightPosition.xyz - input.WorldPos.xyz);
    float3 viewDir = normalize(CameraPosition.xyz - input.WorldPos.xyz);
    float3 normal = normalize(input.Normal);

    // Calculate reflection vector
    float3 reflectDir = reflect(-lightDir, normal);

    // Calculate diffuse reflection
    float diffuseIntensity = max(0.0, dot(normal, lightDir));
    float4 diffuse = (DiffuseColor / 255) * diffuseIntensity;

    // Calculate specular reflection
    float specularIntensity = pow(max(0.0, dot(reflectDir, viewDir)), Shininess);
    float4 specular = (SpecularColor / 255) * specularIntensity;

    // Combine ambient, diffuse, and specular
    float4 ambient = (AmbientColor / 255);
    float4 finalColor = ambient + diffuse + specular;

   

    // Debug shading #1: map and return normal as a color
    // return float4(normal * 0.5 + 0.5, 1);

    // Debug shading #2: map and return texture coordinates as a color (blue = 0)
    // return float4(input.TexCoord, 0, 1);

    return finalColor;
}




