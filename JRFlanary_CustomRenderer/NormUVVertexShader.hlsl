struct VertIn
{
    float3 pos : POSITION;
    float3 norm : NORMAL;
    float2 UV : UV;
};

struct VertOut
{
    float4 pos : SV_Position;
    float3 wPos : POSITIONT;
    float3 norm : NORMAL;
    float3 wNorm : NORMALT;
    float2 UV : UV;
};

cbuffer WorldMatrix : register(b0)
{
    float4x4 worldMatrix;
    float4x4 viewMatrix;
    float4x4 projMatrix;
};

VertOut main(VertIn input)
{
    VertOut output;
    output.pos = float4(input.pos, 1);
    output.pos = mul(worldMatrix, output.pos);
    output.wPos = output.pos;
    output.pos = mul(viewMatrix, output.pos);
    output.pos = mul(projMatrix, output.pos);
    output.norm = input.norm;
    output.wNorm = mul(worldMatrix, output.norm);
    output.UV = input.norm;
    return output;
}