#pragma once
#include "NormUVMesh.h"
class NormUVCube :
    public NormUVMesh
{
public:
    NormUVCube();
    NormUVCube(float x, float y, float z);
    ~NormUVCube();
    void Init() override;
    void Manipulate() override;
private:
    float yRot = 0;
    XMMATRIX translate;
};

