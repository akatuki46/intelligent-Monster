//////////////////////////////////////////////////////////////////////////////////////////////////
//  数字描画用　2D描画コンポーネント
/////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Component.h"
#include "main.h"
#include "renderer.h"

class NumberDraw2D : public Component
{
private:

	ID3D11Buffer* m_VertexBuffer;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	D3DXVECTOR2 TexSize = { 100.0f,100.0f };
	D3DXVECTOR2 AniDivision = D3DXVECTOR2(0.0f, 0.0f);

	//フレームに対するアニメーションのカウント
	int m_NumCnt = 0;
	int m_Division = 0;
	
	//桁数
	int m_Digits = 0;

	//数字間の間隔
	float m_Interval = 0;

public:
	void Init(D3DXVECTOR2 size,int Num,float interval);
	void Uninit() override;
	void Draw() override;
	void Update()override;

	void SetTexSize(D3DXVECTOR2 size) { TexSize = size; }
	D3DXVECTOR2 GetTexSize() { return TexSize; }

	//数字代入
	void SetNumCnt(int cnt) { m_NumCnt = cnt; }
};

