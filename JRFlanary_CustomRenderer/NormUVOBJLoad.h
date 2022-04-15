#pragma once
#include "NormUVMesh.h"
class NormUVOBJLoad :
    public NormUVMesh
{
public:
    NormUVOBJLoad();
    NormUVOBJLoad(float x, float y, float z);
    ~NormUVOBJLoad();
    void Init() override;
    void Manipulate() override;
private:
    float yRot = 0;
    XMMATRIX translate;
};

