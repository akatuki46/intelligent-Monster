//////////////////////////////////////////////////////////////////////////////////////////////////
//  �|�W�V�������N�_�ɉ�]�@2D�`��R���|�[�l���g
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
		LEFT_TOP = 0, //������N�_
		CENTER_CENTER, //�������N�_
		LEFT_CENTER,   //���^�񒆂��N�_
		CENTER_BUTTOM  //�^�񒆉����N�_
	}DrawMode;

	//�`����@�̕ύX
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
