#pragma once
#include "Component.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"

#define PARTICLE_HORIZONTAL		(15)			// ���q�@����������
#define PARTICLE_VERTICAL		(15)			// ���q�@�c��������

//\//�͉��s
#define SPRING_NUMS				(PARTICLE_HORIZONTAL*(PARTICLE_VERTICAL+1) + \
								 PARTICLE_VERTICAL*(PARTICLE_HORIZONTAL+1) + \
								 PARTICLE_VERTICAL*PARTICLE_HORIZONTAL*2)	// �X�v�����O����

#define SPRING_DEFAULT_LENGTH	(50.0f)			// �o�l���R��
#define SPRING_COEFFICIENT		(80.0f)			// �o�l�W��
#define SPRING_MASS				(2.0f)			// �o�l����

class ClothDraw :
    public Component
{
private:
	struct WINDFORCE {
		int		status;				// �X�e�[�^�X
		D3DXVECTOR3	force;				// ���̓x�N�g��
	};

	struct PARTICLE {
		bool	onLock;				// �Œ�t���O
		bool	onDrag;				// �}�E�X�h���b�O������t���O
		D3DXVECTOR3	position;			// �ʒu���W (Position)
		D3DXVECTOR3	velocity;			// ���x (Velocity)
		D3DXVECTOR3	acceleration;		// �����x (Acceleration)
		D3DXVECTOR3	resultant;			// ���� (Resultant)
		D3DXVECTOR3	gravity;			// �d�� (Gravity)
	};

	struct P_REF {
		int		horz;				// �������C���f�b�N�X
		int		vert;				// �c�����C���f�b�N�X
	};

	struct SPRING {
		P_REF	p1;					// �ڑ�����Ă��闱�q�P
		P_REF	p2;					// �ڑ�����Ă��闱�q�Q
		float	length;				// ���R��
	};

	struct CLOTH {
		int			status;														// �X�e�[�^�X
		PARTICLE	Particle[PARTICLE_VERTICAL + 1][PARTICLE_HORIZONTAL + 1];		// �\�����q
		SPRING		Spring[SPRING_NUMS];										// ���q�Ԃ̃o�l
	};

	CLOTH		g_Cloth;					// �z�I�u�W�F�N�g
	WINDFORCE	g_WindForce;				// ���̓I�u�W�F�N�g

	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11Buffer* m_IndexBuffer = NULL;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	D3DXVECTOR3 ClothPos[((PARTICLE_VERTICAL * 2 + 3) * PARTICLE_HORIZONTAL) - 1];
	VERTEX_3D vertex[PARTICLE_VERTICAL + 1][PARTICLE_HORIZONTAL + 1];
	
public:

	void Init(D3DXVECTOR3 Offset,D3DXVECTOR3 Wind);
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void AddWind(D3DXVECTOR3 add) { g_WindForce.force += add; }

};

