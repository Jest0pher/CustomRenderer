#include "TestTriangularPrism.h"

TestTriangularPrism::TestTriangularPrism() {
	translate = XMMatrixIdentity();
}

TestTriangularPrism::TestTriangularPrism(float x, float y, float z) {
	translate = XMMatrixTranslation(x, y, z);
}

TestTriangularPrism::~TestTriangularPrism() {

}

void TestTriangularPrism::Manipulate() {
	yRot += .01f;
	XMMATRIX temp = translate;
	temp = XMMatrixMultiply(XMMatrixRotationY(yRot * (3.14f / 180.0f)), temp);

	XMStoreFloat4x4(&wvp.wMatrix, temp);

	(*GetContextPointer())->UpdateSubresource(constantBuffer, 0, nullptr, &wvp, 0, 0);
}

void TestTriangularPrism::Init() {
	vertices.resize(4);

	vertices[0] = { {-.25f, -.25f, -.25f, 1}, {0,1,0,1} };
	vertices[1] = { {.25f, -.25f, -.25f, 1}, {1,0,0,1} };
	vertices[2] = { {0.0f, -.25f, .25f, 1}, {0,0,1,1} };
	vertices[3] = { {0.0f, .25f, 0.0f, 1}, {1,0,0,1} };

	indices.resize(12);
	indices = { 0,1,2, 2,3,0, 0,3,1, 1,3,2};

	TestMesh::Init();
}
