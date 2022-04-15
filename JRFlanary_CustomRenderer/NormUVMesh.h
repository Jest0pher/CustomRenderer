#pragma once
#include "Norm_UV_VertParent.h"
#include "NormUVVertexShader.csh"
#include "NormUVPixelShader.csh"

class NormUVMesh :
    public Norm_UV_VertParent
{
public:
    ~NormUVMesh();

    ID3D11Buffer* vertexBuffer = nullptr;
    ID3D11Buffer* indexBuffer = nullptr;
    ID3D11Buffer* constantBuffer = nullptr;

    ID3D11InputLayout* inputLayout;
    ID3D11VertexShader* vertexShader;
    ID3D11PixelShader* pixelShader;

    HRESULT CreateVertexBuffer() override;
    HRESULT CreateIndexBuffer() override;
    HRESULT CreateInputLayout() override;
    HRESULT CreateVertexShader() override;
    HRESULT CreatePixelShader() override;
    void Draw() override;
    virtual void Manipulate() = 0;
    void Init() override;

    HRESULT CreateConstantBuffer();
protected:
    WVP wvp;
    bool drawIndices = true;
};

