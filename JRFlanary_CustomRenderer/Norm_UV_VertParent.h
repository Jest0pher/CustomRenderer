#pragma once
#include "RenderableObject.h"

struct NormUVVert {
	float pos[3];
	float norm[3];
	float UV[2];
};

class Norm_UV_VertParent :
	public RenderableObject
{
public:
	std::vector<NormUVVert> vertices;
	std::vector<int> indices;
};