//////////////////////////////////////////////////////////////////////////////////////////////////
//  アニメーション用　2D描画コンポーネント
/////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Component.h"
#include "main.h"
#include "renderer.h"

class AnimetionDraw : public Component
{
private:
	ID3D11Buffer* m_VertexBuffer;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	D3DXVECTOR2 TexSize = { 100.0f,100.0f };
	D3DXVECTOR2 AniDivision = D3DXVECTOR2(0.0f, 0.0f);

	//フレームに対するアニメーションのカウント
	int m_AnimetionCnt = 0;
	int m_Division = 0;

	bool m_LoopFlag = false;

	//アニメーションをしないための変数（主にタイマーや個数表示で使用）
	bool m_NotAnimetion = false;

public:
	void Init();
	void Uninit() override;
	void Draw() override;
	void Update()override;

	void SetTexSize(D3DXVECTOR2 size) { TexSize = size; }
	D3DXVECTOR2 GetTexSize() { return TexSize; }

	void SetLoopFlag(bool flag) { m_LoopFlag = flag; }
	bool GetLoopFlag() { return m_LoopFlag; }

	void SetNotAnimetion(bool flag) { m_NotAnimetion = flag; }
	void SetAnimeCnt(int cnt) { m_AnimetionCnt = cnt; }
};

