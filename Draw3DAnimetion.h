#pragma once
#include "Component.h"
#include "main.h"
#include "renderer.h"
#include "ModelContainer.h"

class Draw3DAnimetion :
    public Component
{
private:
	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	D3DXMATRIX  world, Trans, Scale, Rot;

	float m_Frame = 0.0f;
	float m_BlendRate = 0.0f;

	ModelContainer* m_Container = nullptr;

public:
	void Init();
	void Uninit() override;
	void Draw() override;
	void Update()override;

	D3DXMATRIX GetWorldMatrix() { return world; }
	D3DXMATRIX GetTransMatrix() { return Trans; }
	D3DXMATRIX GetScaleMatrix() { return Scale; }
	D3DXMATRIX GetRotMatrix() { return Rot; }

	void SetBlendRate(float BlendRate) { m_BlendRate = BlendRate; }

	void ResetFlame() { m_Frame = 0; }
	void SetFlame(int flame) { m_Frame = flame; }
};

