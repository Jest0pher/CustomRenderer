#pragma once
#include "RenderableObject.h"

struct TestVert {
	float pos[4];
	float color[4];
};

class TestVertParent :
    public RenderableObject
{
public:
	std::vector<TestVert> vertices;
	std::vector<int> indices;
};

