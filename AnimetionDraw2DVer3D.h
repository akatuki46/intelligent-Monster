//////////////////////////////////////////////////////////////////////////////////////////////////
//  アニメション用　3D空間での2D描画コンポーネント
/////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Component.h"
#include "main.h"
#include "renderer.h"

class AnimetionDraw2DVer3D :
    public Component
{
private:
	static ID3D11Buffer* m_VertexBuffer;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	D3DXVECTOR2 AniDivision = D3DXVECTOR2(0.0f, 0.0f);

	int m_AnimetionCnt = 0;
	int m_Division = 0;

	bool m_LoopFlag = false;

	bool m_Bilboard = false;

public:

	void Init(bool Bilboard);
	void Uninit() override;
	void Update() override;
	void Draw() override;
};

