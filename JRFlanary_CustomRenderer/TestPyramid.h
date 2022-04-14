#pragma once
#include "TestMesh.h"
class TestPyramid :
    public TestMesh
{
public:
    TestPyramid();
    TestPyramid(float x, float y, float z);
    ~TestPyramid();
    void Init() override;
    void Manipulate() override;
private:
    float yRot = 0;
    XMMATRIX translate;
};

