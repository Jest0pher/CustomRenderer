#pragma pack_matrix(  row_major )

struct VertIn
{
    float4 pos : POSITION;
    float4 color : COLOR;
};

struct VertOut
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
    float4 wPos : POSITIONT;
};

cbuffer WorldMatrix : register(b0)
{
    float4x4 worldMatrix;
    float4x4 viewMatrix;
    float4x4 projMatrix;
};

VertOut main( VertIn input)
{
    
    VertOut output;
    output.pos = mul(input.pos, worldMatrix);
    output.wPos = output.pos;
    output.pos = mul(output.pos, viewMatrix);
    output.pos = mul(output.pos, projMatrix);
    output.color = input.color;
    return output;
}