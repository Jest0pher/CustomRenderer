#include "NormUVOBJLoad.h"
#include <fstream>
#include <string>

NormUVOBJLoad::NormUVOBJLoad() {
	drawIndices = false;
	translate = XMMatrixIdentity();
}

NormUVOBJLoad::NormUVOBJLoad(float x, float y, float z) {
	drawIndices = false;
	translate = XMMatrixTranslation(x, y, z);
}

NormUVOBJLoad::~NormUVOBJLoad() {

}

void NormUVOBJLoad::Manipulate() {
	yRot += .01f;
	XMMATRIX temp = translate;
	temp = XMMatrixMultiply(XMMatrixScaling(.01f, .01f, .01f), temp);
	temp = XMMatrixMultiply(XMMatrixRotationY(yRot * (3.14f / 180.0f)), temp);

	XMStoreFloat4x4(&wvp.wMatrix, temp);

	(*GetContextPointer())->UpdateSubresource(constantBuffer, 0, nullptr, &wvp, 0, 0);
}

void NormUVOBJLoad::Init() {
	struct temp {
		float tempVert[4];
	};
	struct temp2 {
		float tempVert[3];
	};
	std::vector<temp> verts;
	std::vector<temp> norms;
	std::vector<temp2> UVs;
	std::ifstream file;

	file.open("Old Fence.txt", std::ios_base::in);
	if (file.is_open()) {
		char buffer[256];
		while (!file.eof()) {
			file.getline(buffer, 256);
			if (buffer[0] == 'v' && buffer[1] == ' ') {
				std::string text(&buffer[2]);
				std::string floatNum;
				temp vert;
				int l = 0;
				for (int i = 0; i < text.size(); i++) {
					if (text[i] != ' ' && text[i] != '\n') {
						floatNum.push_back(text[i]);
					}
					else {
						if (floatNum.size() > 1) {
							vert.tempVert[l] = std::stof(floatNum);
							l++;
							floatNum.clear();
						}
					}
				}
				if (floatNum.size() > 1) {
					vert.tempVert[l] = std::stof(floatNum);
					l++;
					floatNum.clear();
				}
				verts.push_back(vert);
				continue;
			}
			else if (buffer[0] == 'v' && buffer[1] == 'n' && buffer[2] == ' ') {
				std::string text(&buffer[3]);
				std::string floatNum;
				temp vert;
				int l = 0;
				for (int i = 0; i < text.size(); i++) {
					if (text[i] != ' ' && text[i] != '\n') {
						floatNum.push_back(text[i]);
					}
					else {
						if (floatNum.size() > 1) {
							vert.tempVert[l] = std::stof(floatNum);
							l++;
							floatNum.clear();
						}
					}
				}
				if (floatNum.size() > 1) {
					vert.tempVert[l] = std::stof(floatNum);
					l++;
					floatNum.clear();
				}
				norms.push_back(vert);
				continue;
			}
			else if (buffer[0] == 'v' && buffer[1] == 't' && buffer[2] == ' ') {
				std::string text(&buffer[3]);
				std::string floatNum;
				temp2 vert;
				int l = 0;
				for (int i = 0; i < text.size(); i++) {
					if (text[i] != ' ' && text[i] != '\n') {
						floatNum.push_back(text[i]);
					}
					else {
						if (floatNum.size() > 1) {
							vert.tempVert[l] = std::stof(floatNum);
							l++;
							floatNum.clear();
						}
					}
				}
				if (floatNum.size() > 1) {
					vert.tempVert[l] = std::stof(floatNum);
					l++;
					floatNum.clear();
				}
				UVs.push_back(vert);
				continue;
			}
			else if (buffer[0] == 'f' && buffer[1] == ' ') {
				std::string text(&buffer[2]);
				std::string floatNum;
				int type = 0;
				NormUVVert vert;
				for (int i = 0; i < text.size(); i++) {
					if (text[i] != '/' && text[i] != '\n' && text[i] != ' ') {
						floatNum.push_back(text[i]);
					}
					else {
						int num = std::stoi(floatNum) - 1;
						floatNum.clear();
						if (type == 0) {
							vert.pos[0] = verts[num].tempVert[0];
							vert.pos[1] = verts[num].tempVert[1];
							vert.pos[2] = verts[num].tempVert[2];
							type++;
						}
						else if (type == 1) {
							vert.UV[0] = UVs[num].tempVert[0];
							vert.UV[1] = UVs[num].tempVert[1];
							type++;
						}
						else {
							vert.norm[0] = norms[num].tempVert[0];
							vert.norm[1] = norms[num].tempVert[1];
							vert.norm[2] = norms[num].tempVert[2];
							type = 0;
							vertices.push_back(vert);
						}
					}
				}
			}
		}
	}
	file.close();
	vertices.shrink_to_fit();
	verts.clear();
	norms.clear();
	UVs.clear();

	NormUVMesh::Init();
}