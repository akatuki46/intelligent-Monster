//////////////////////////////////////////////////////////////////////////////////////////////////
//  3Dモデル描画コンポーネント
/////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Component.h"
#include "main.h"
#include "renderer.h"

class Draw3D : public Component
{
private:
	ID3D11VertexShader* m_VertexShader[3];
	ID3D11PixelShader* m_PixelShader[3];
	ID3D11InputLayout* m_VertexLayout;

	D3DXMATRIX  world, Trans, Scale, Rot;

	int m_ShaderFlg = 0;

	//描画しないときに使う
	bool m_DrawFlag = true;

public:
	void Init();
	void Uninit() override;
	void Draw() override;
	void Update()override;

	D3DXMATRIX GetWorldMatrix() { return world; }
	D3DXMATRIX GetTransMatrix() { return Trans; }
	D3DXMATRIX GetScaleMatrix() { return Scale; }
	D3DXMATRIX GetRotMatrix() { return Rot; }

	void SetShaderFlag(int flag) { m_ShaderFlg = flag; }
	void SetNotDraw(bool flag) { m_DrawFlag = flag; }
};

