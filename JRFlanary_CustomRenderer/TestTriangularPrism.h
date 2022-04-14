#pragma once
#include "TestMesh.h"
class TestTriangularPrism :
    public TestMesh
{
public:
    TestTriangularPrism();
    TestTriangularPrism(float x, float y, float z);
    ~TestTriangularPrism();
    void Init() override;
    void Manipulate() override;
private:
    float yRot = 0;
    XMMATRIX translate;
};


