//////////////////////////////////////////////////////////////////////////////////////////////////
//  �w�i�p�@�ړ��A�T�C�Y�Œ�@2D�`��R���|�[�l���g
/////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Component.h"
#include "main.h"
#include "renderer.h"

class Draw2D : public Component
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	bool m_DrawFlag = true;
public:
	void Init(D3DXVECTOR3 size,int texcode);
	void Uninit() override;
	void Draw() override;
	void Update()override;

	void SetDrawFlag(bool flag) { m_DrawFlag = flag; }

};

