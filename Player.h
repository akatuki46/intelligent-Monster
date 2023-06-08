#pragma once
#include "Component.h"
#include "ItemManager.h"
#include "GameObject.h"

class  Player : public Component
{
private:
	//���g�̗̑�
	int    m_Hp = 0;
	int    m_MaxHp = 150;
	//�ԃQ�[�W
	int    m_RedHp = 0;
	//�����񕜗p�ϐ�
	int    m_RecoveryCnt = 0;

	//�X�^�~�i�p�ϐ�
	int    m_Stamina = 0;
	//�X�^�~�i�����炷�̂�x�点��
	int    m_StaminaCnt = 0;

	//���G����p�ϐ�
	int    m_InviTime = 0;

	float    m_BlendRate = 0;
	//�����X�^�[����_���[�W���󂯂��Ƃ��̃t���O
	bool   m_DamageFalg = false;

	int    m_DamegeCnt = 0;

	//�V�[���J�ډ\��ʒm����ϐ�
	bool   m_SceneFlag = false;
	bool   m_AttackFlag = false;
	int    m_AttackCnt = 0;

	bool   m_DashFlag = false;

	//�ړ��l�̕␳
	float  m_MoveValue = 0.05f;

	//�A�C�e���C���X�^���X�̊m��
	GameObject* m_HaveItem = nullptr;

	//�A�C�e�����g�����Ƃ��̃t���O�@�A���g�p��h��
	bool   m_UseItem = false;
	int    m_UseItemCnt = 0;

	//����A�j���[�V�����Đ��p�ϐ�
	bool m_DodgeFlag = false;

	//���G�t���O
	bool m_InvFlag = false;
	int m_InvCnt = 0;

public:

	void Init();
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static void CollisionAction(GameObject* obj, std::string name);

	void SetHitFlag(bool flag) { m_DamageFalg = flag; }
	bool GetHitFlag() { return m_DamageFalg; }
	
	//HP�֘A�֐�
	int getHp() { return m_Hp; }
	int GetRedHp() { return m_RedHp; }
	void LosHp(int Damege) { m_Hp -= Damege; }
	void HealHP(int Heal) { m_Hp += Heal; }
	void SetRedHp(int Damage) { m_RedHp = Damage; }
	void MaxHP() { m_Hp = m_MaxHp; }
	int GetMaxHP() { return m_MaxHp; }
	
	int GetStamina() { return m_Stamina; }

	bool GetSceneFlag() { return m_SceneFlag; }

	void SetItemInstance(GameObject* item) { m_HaveItem = item; }

	bool GetInvFlag() { return m_InvFlag; }
};

