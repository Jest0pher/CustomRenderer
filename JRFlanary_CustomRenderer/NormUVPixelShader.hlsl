struct PixelIn
{
    float4 pos : SV_Position;
    float3 wPos : POSITIONT;
    float3 norm : NORMAL;
    float3 wNorm : NORMALT;
    float2 UV : UV;
};

float4 main(PixelIn input) : SV_TARGET
{
    float maxDist = .4f;
    return lerp(float4(0, 1, 0, 1), float4(.5f, .5f, .5f, 1.0f), saturate(distance(float3(0, 0, 0), float3(0,input.wPos.y, 0)) / maxDist));

}