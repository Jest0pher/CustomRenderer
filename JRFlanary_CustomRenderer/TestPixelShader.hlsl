#pragma pack_matrix(  row_major )

struct PixelIn
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
    float4 wPos : POSITIONT;
};

float4 main(PixelIn input) : SV_TARGET
{
    float maxDist = 1.2f;
    float dist = distance(float3(0, 0, 0), input.wPos.xyz);
    if (dist < .35f)
    {
        //return float4(0, 1, 0, 1);
        return lerp(float4(0, 1, 0, 1), float4(0.5f, 0.5f, 0.5f, 1.0f), dist*1.4f);
    }
    else if (dist > .5f)
    {
        return lerp(float4(0, 1, 0, 1), float4(0.5f, 0.5f, 0.5f, 1.0f), saturate(dist / maxDist));

    }
    else
    {
        return float4(0.5f, 0.5f, 0.5f, 1.0f);
    }

}