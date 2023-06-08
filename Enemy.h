#pragma once
#include "Component.h"
#include "ActionBase.h"
#include "main.h"
#include "renderer.h"
#include <list>
#include "Situation.h"

class BehaviorTree;
class BehaviorData;
class NodeBase;
class Situation;



class  Enemy : public Component
{

private:
	//�t���O���e��
	enum Flag
	{
		RushActionStart = (1 << 11),
		TackleActionStart = (1 << 10),
		DownActionStart = (1 << 9),
		DieActionStart = (1 << 8),
		LongRangeStart = (1 << 7),       //�U�����n�܂�����(7�Ԗڂ̃r�b�g)
		AttackEnd = (1 << 6),         //�U�����I�������(6�Ԗڂ̃r�b�g)
		DiffenceStart = (1 << 5),     //�h�䂪�n�܂�����(5�Ԗڂ̃r�b�g)
		WaitStart = (1 << 4),         //�҂��s�����n�܂�����(4�Ԗڂ̃r�b�g)
		CloseRangeATStart = (1 << 3),       //�ߋ����U�����n�܂�����(3�Ԗڂ̃r�b�g)
		CloseDisStart = (1 << 2),       //��ъ|����U�����n�܂�����(2�Ԗڂ̃r�b�g)
		ApproachActionStart = (1 << 1),     //�ڋ߂��n�܂�����(1�Ԗڂ̃r�b�g)
	};

	enum Status
	{
		None_Status = 0,
		Normal_Status,
		Charge_Status,
		SuperCharge_Status,
	};

public:

	enum Action
	{
		Attack_Judgment = 0,
		Charge_Judgment,
		CloseRange_Judgment,
		Deffence_Judgment,
		LongRange_Judgment,

	};


	void Init();
	void Uninit() override;
	void Update() override;
	void Draw() override;

	// ���s
	void Run();

	ActionBase::STATE Attack();
	ActionBase::STATE Deffence();
	ActionBase::STATE LongRangeAT();
	ActionBase::STATE CloseRangeAT();
	ActionBase::STATE ApproachAction();
	ActionBase::STATE Wait();
	ActionBase::STATE Charge();
	ActionBase::STATE CloseDis();
	ActionBase::STATE Die();
	ActionBase::STATE Down();
	ActionBase::STATE Tackle();
	ActionBase::STATE Rush();


	//�r�w�C�r�A�c���[�̃Q�b�^�[
	BehaviorTree* getTree() { return m_AiTree; }

	//�v���C���[�𔭌�������
	bool FindPlayer() { return m_FindPlayer != NULL ? true : false; }
	GameObject* GetFindPlayer() { return m_FindPlayer; }

	//�v���C���[��������
	void LostPlayer() { m_FindPlayer = nullptr; }

	//�ʏ�̓����蔻��
	static void CollisionAction(GameObject* obj, std::string name);

	//Ray�̓����蔻��
	static void RayCollisionAction(GameObject* obj);

	//�t���O�`�F�b�N�֐�
	bool FlagCheck(unsigned int flag) {
		return ((m_flag & flag) != 0);
	}

	//�t���O�I���֐�
	void FlagOn(unsigned int flag) {
		m_flag |= flag;
	}

	//�t���O�I�t�֐�
	void FlagOff(unsigned int flag) {
		m_flag &= ~flag;
	}

	float GetLength() { return m_Length; }

	bool GetRayCollision(){ return m_WallCollision; }

	void SituationUpdate();

	void NextSituation(Situation* Next) { m_NextAction = Next; }

	int GetChargeCnt() { return m_ChargeCnt; }
	void ResetChargeCnt() { m_ChargeCnt = 0; }

	void SetEnemyHp(int Hp) { m_HP = Hp; }
	int GetEnemyHp() { return m_HP; }

	void LosHp(int Damege) { m_HP -= Damege; }

	bool GetActionFlag(Action flag) { return m_ActionFlag[flag]; }

	void SetPlayerPos(D3DXVECTOR3 pos) { m_PlayerPos = pos; }

	bool GetSceneFlag() { return m_SceneFlag; }


	void AddDamage(int Damage) { m_DamageCnt += Damage; }
	void LastAttack(bool flag) { m_LastAttack = flag; }
	bool GetFearFlag() { return m_FearFlag; }

	int GetNowStatus() { return m_NowStatus; }

	bool GetMotionStartFlag() { return m_MotionStartFlag; }

private:
	//�S�̃t���O�Ǘ��ϐ� 32�̃t���O�Ǘ�
	unsigned int m_flag = 0;

	//Enemy�s���Ǘ��t���O
	bool m_ActionFlag[5] = { false };

	//Enemy��ԊǗ��t���O
	bool m_StateFlag[3] = { false };

	int m_HP = 2000;

	//���ݔ����̂��߂̃��~�b�g
	int m_FearLimit = 300;
	//��_���[�W�𗭂߂�
	int m_DamageCnt = 0;
	//�Ō�ɍU����H�������
	bool m_LastAttack = false;
	bool m_FearFlag = false;
	int m_FearCnt = 0;

	int debagcnt = 0;

	Status m_NextSetStatus = None_Status;

	//��񂾂����s�������Ƃ��Ɏg��
	bool  DoOnce = false;
	bool  DoOnce2 = false;

	bool m_MotionStartFlag = false;

	//���[�V�������ɉ�]���Ȃ��悤��
	bool m_PlayMotion = false;

	BehaviorTree* m_AiTree;			// �r�w�C�r�A�c���[
	BehaviorData* m_BehaviorData = nullptr;	// �r�w�C�r�A�f�[�^
	NodeBase* m_ActiveNode = nullptr;			// ���s���m�[�h

	GameObject* m_FindPlayer = nullptr;       //�������v���C���[

	//�v���C���[�̃|�W�V����
	D3DXVECTOR3 m_PlayerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float m_KeepRotX = 0.0f;
	D3DXVECTOR3 m_MotionPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	bool m_CollisionFlag = false;
	bool m_RayCollision = false;
	bool m_WallCollision = false;

	//�v���C���[�܂ł̋���
	float m_Length = 0.0f;

	//	�`���[�W�񐔋L�^�p�ϐ�
	int m_ChargeCnt = 0;
	int m_ChargeFlag = 0;

	//�V�[���J�ڂ�ʒm����ϐ�
	bool   m_SceneFlag = false;

	int m_NowStatus = 0;

	//�o�H�T���p���X�g�ϐ�
	std::list<D3DXVECTOR3> m_AstarPosition;

	//�X�e�[�g�p�^�[���p�ϐ�
	Situation* m_Action = nullptr;
	Situation* m_NextAction = nullptr;
};

