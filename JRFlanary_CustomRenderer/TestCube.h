#pragma once
#include "TestMesh.h"
class TestCube :
    public TestMesh
{
public:
    TestCube();
    TestCube(float x, float y, float z);
    ~TestCube();
    void Init() override;
    void Manipulate() override;
private:
    float yRot = 0;
    XMMATRIX translate;
};

