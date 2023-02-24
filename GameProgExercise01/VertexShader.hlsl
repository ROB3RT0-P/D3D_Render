//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer Constants : register(b0)
{
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProjection;
}

struct VS_INPUT
{
	float4 position     : POSITION;
	float4 color        : COLOR;
};

struct VS_OUTPUT
{
	float4 position     : SV_POSITION;
	float4 color        : COLOR;
};

VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.color = input.color;
	output.position = mul(input.position, mWorld);
	output.position = mul(output.position, mView);
	output.position = mul(output.position, mProjection);

	return output;
}