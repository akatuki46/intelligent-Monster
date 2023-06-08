//////////////////////////////////////////////////////////////////////////////////////////////////
//  ポジションを起点に回転　2D描画コンポーネント
/////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Component.h"
#include "main.h"
#include "renderer.h"

class Draw2DChangePivot : public Component
{
private:
	typedef enum
	{
		LEFT_TOP = 0, //左上を起点
		CENTER_CENTER, //中央を起点
		LEFT_CENTER,   //左真ん中を起点
		CENTER_BUTTOM  //真ん中下を起点
	}DrawMode;

	//描画方法の変更
	DrawMode m_DrawMode;

	ID3D11Buffer* m_VertexBuffer;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	D3DXVECTOR3 TexSize = { 100.0f,100.0f,0.0f };

	D3DXVECTOR4   m_Color = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);
public:
	void Init(D3DXVECTOR3 Size, D3DXVECTOR4 color, int mode);
	void Uninit() override;
	void Draw() override;
	void Update()override;

	void SetTexSize(D3DXVECTOR3 size) { TexSize = size; }
	D3DXVECTOR3 GetTexSize() { return TexSize; }

	void SetColor(D3DXVECTOR4 color) { m_Color = color; }
};
