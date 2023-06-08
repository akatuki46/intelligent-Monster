//////////////////////////////////////////////////////////////////////////////////////////////////
//  フェード用　2D描画コンポーネント
/////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Component.h"
#include "main.h"
#include "renderer.h"

#define FADE_RATE float(1.0f/60.0f)

class FadeDraw2D : public Component
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	typedef enum
	{
		None = 0,
		Alfa,
		Move,
	}FALDEMODE;

	FALDEMODE m_mode;

	int m_Count = 99999;
	float alfa = 1.0f;
	float AlfaRot = 0.0f;

	D3DXVECTOR2  m_MovePos = D3DXVECTOR2(0.0f, 0.0f);

	D3DXVECTOR3 m_FadeColor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

public:
	void Init(int mode,D3DXVECTOR3 color);
	void Uninit() override;
	void Draw() override;
	void Update()override;


};

