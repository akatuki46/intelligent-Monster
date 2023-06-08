#pragma once
#include "Component.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"

#define PARTICLE_MAX		(100000)				// �p�[�e�B�N���̐�

class Particle :
    public Component
{
private:
	enum Type
	{
		Hanabi = 0,
		Hunsui,
	};

	unsigned	g_uOnClick;
	
	//�p�[�e�B�N�����������邩
	bool m_Use = false;

	//�����Ԋu
	int m_Interval = 0;
	int m_IntervalCnt = 0;

	//���[�v
	bool m_Loop = false;
	//���[�v���Ȃ��ꍇ�̃t���O
	bool m_End = false;

	//�T�C�Y
	D3DXVECTOR3 m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//��������
	int m_LifeTime = 0;

	//������
	int m_Amount = 0;

	//3D�`�悷�邩
	bool m_3Dmode = false;

	//�����x
	D3DXVECTOR3 m_Acc = D3DXVECTOR3(0.0f, 0.001f, 0.0f);

	//�X�s�[�h
	float m_spd = 0.001f;

	//�F
	D3DXVECTOR4 m_Color = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);

	int  m_PosRot = 0.0f;

	int m_Type = 0;


public:
	void Init(bool Is3D);
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetInterval(int interval) { m_Interval = interval; }
	void SetLoop(bool loop) { m_Loop = loop; }
	void SetSize(D3DXVECTOR3 Size) { m_Size = Size; }
	void SetLife(int Life) { m_LifeTime = Life; }
	void SetAmount(int Amount) { m_Amount = Amount; }
	void SetColor(D3DXVECTOR4 color) { m_Color = color; }
	void SetAcc(D3DXVECTOR3 acc) { m_Acc = acc; }
	void SetType(int type) { m_Type = type; }
	void SetSpd(float spd) { m_spd = spd; }


	void SetUse(bool flag) { m_Use = flag; }
};

