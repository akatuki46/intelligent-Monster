//////////////////////////////////////////////////////////////////////////////////////////////////
//  UI用　移動、サイズ可能　2D描画コンポーネント
/////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Component.h"
#include "main.h"
#include "renderer.h"
class Draw2DAction :
    public Component
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	bool m_DrawFlag = true;

	D3DXVECTOR3   m_Size = D3DXVECTOR3(0.0f,0.0f,0.0f);
public:
	void Init(D3DXVECTOR3 size);
	void Uninit() override;
	void Draw() override;
	void Update()override;

	void SetDrawFlag(bool flag) { m_DrawFlag = flag; }

};

