#pragma once
#include "Component.h"
#include "main.h"
#include "renderer.h"

class Prism :
    public Component
{
private:
	ID3D11Buffer* g_VertexBuffer = NULL;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	typedef struct {
		int			status;		// �X�e�[�^�X
		D3DXVECTOR3	position;	// ���W
		D3DXVECTOR3	rotation;	// ��]�p
	} PRISM;

	PRISM g_Prism;

	D3DXMATRIX		matWorld;				// ���[���h�ϊ��}�g���b�N�X
public:

	void Init();
	void Uninit() override;
	void Update() override;
	void Draw() override;

};

