#pragma once
#include "Component.h"
#include <unordered_map>
#include <functional>
#include "main.h"


class Motion :
    public Component
{
private:

	int m_TransChange = 0;

	//���[�V�������郂�f���ۑ��p���X�g
	std::unordered_map<std::string ,GameObject*> m_MotionModel;

	//�����l�ۑ��p�}�b�v(rotation)
	std::unordered_map<std::string, D3DXVECTOR3> m_InOutValue;

	//�����l�ۑ��p�}�b�v(Position)
	std::unordered_map<std::string, D3DXVECTOR3> m_InOutValuePos;

	//�����l�ۑ��p�}�b�v(Position)
	std::unordered_map<std::string, D3DXVECTOR3> m_KeepPos;


	int m_FlameCnt = 0;
	int m_FlameCnt2 = -5;   //�����ɂ���𔭐����������Ƃ��Ɏg���ϐ� 5�t���[�����炷
	std::string m_MotionName = "";

	bool IdleFlag = false;

	int transFlag = -1;
	int transFlag2 = -1;    //�����ɂ���𔭐����������Ƃ��Ɏg���ϐ�


	//��񂾂����s�������Ƃ��Ɏg���t���O
	bool FirstFlag = true;
	int ChangeMotion = 0;


	std::string m_OldMotion = "";

	int m_MotionFlame = 30;

	//���[�V�����Ƀf�B���C�����������Ƃ��Ɏg�p 
	bool m_MotionDelyFlag = false;

	//�����񃂁[�V���������s�������Ƃ��Ɏg���ϐ�
	int m_MotionCnt = 0;

	//���[�V�����I����ʒm����ϐ�
	bool m_MotionEnd = false;

	//�|�C���g��ł��A�C�ӂ̏ꏊ�ŃC�x���g�𔭐�������悤�ϐ�
	bool m_MotionPoint = false;

	int m_ShaderCnt = 0;

	//Imgui�pGet,Set�ϐ�
	D3DXVECTOR3 m_ImguiPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_ImguiRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


public:

	void Init();
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void MotionPlay(std::string PlayMotion);

	void SetMotion(std::string MotionName) { m_MotionName = MotionName; }

	void SetShaderCnt(int flag) { m_ShaderCnt = flag; }

	bool GetMotionEnd() { return m_MotionEnd; }
	bool GetMotionPoint() { return m_MotionPoint; }

	void SetMotionEnd(bool flag) { m_MotionEnd = flag; }
	std::string GetMotionName() { return m_MotionName; }

};

