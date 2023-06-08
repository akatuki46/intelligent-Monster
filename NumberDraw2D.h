//////////////////////////////////////////////////////////////////////////////////////////////////
//  �����`��p�@2D�`��R���|�[�l���g
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

	//�t���[���ɑ΂���A�j���[�V�����̃J�E���g
	int m_NumCnt = 0;
	int m_Division = 0;
	
	//����
	int m_Digits = 0;

	//�����Ԃ̊Ԋu
	float m_Interval = 0;

public:
	void Init(D3DXVECTOR2 size,int Num,float interval);
	void Uninit() override;
	void Draw() override;
	void Update()override;

	void SetTexSize(D3DXVECTOR2 size) { TexSize = size; }
	D3DXVECTOR2 GetTexSize() { return TexSize; }

	//�������
	void SetNumCnt(int cnt) { m_NumCnt = cnt; }
};

