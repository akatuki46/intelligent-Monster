#pragma once
#include "Component.h"
#include "main.h"
#include "renderer.h"

class Draw2DParticleVer3D :
    public Component
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	D3DXVECTOR3 m_Size;
	D3DXVECTOR3 m_Acceleration;
	D3DXVECTOR4 m_Color;
	int         m_Life;
	int         m_LifeCnt;
public:
	void Init(D3DXVECTOR3 size, D3DXVECTOR3 acc, D3DXVECTOR4 color, int life);
	void Uninit() override;
	void Update() override;
	void Draw() override;
};

