//------------------------------------------------------------------------------------
// PixelShader.hlsl
//
// Simple shader to render a triangle
//
// Advanced Technology Group (ATG)
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

struct PS_INPUT
{
    float4 position : SV_POSITION;
    float4 color    : COLOR;
};

float4 main( PS_INPUT In ) : SV_Target
{
    return In.color;
}