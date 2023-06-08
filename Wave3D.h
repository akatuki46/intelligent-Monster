#pragma once
#include "Component.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"

#define WAVE_HORIZON  (10)
#define WAVE_VERTICAL  (10)

#define WAVE_PITCH       (50)
#define WAVE_AMPLITUDE   (1.0f)					// �E�F�[�u�|�C���g�̐U��
#define WAVE_LENGTH	     (1.0f)				// �E�F�[�u�|�C���g�̔g��
#define WAVE_CYCLE		 (50.0f)					// �E�F�[�u�|�C���g�̎���

class Wave3D :
    public Component
{
private:
	struct WAVE {
		int		        status;				// �X�e�[�^�X
		D3DXVECTOR3 	position;			// �ʒu���W (Position)
		float	        amplitude;			// �U�� (Amplitude)
		float	        time;				// ����
	};

	WAVE		g_Wave[WAVE_HORIZON + 1][WAVE_VERTICAL + 1];		// �E�F�[�u�|�C���g
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11Buffer* m_IndexBuffer = NULL;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	VERTEX_3D vertex[WAVE_HORIZON + 1][WAVE_VERTICAL + 1];


public:
	void Init();
	void Uninit() override;
	void Update() override;
	void Draw() override;

};

