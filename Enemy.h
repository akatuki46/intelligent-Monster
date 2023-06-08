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
	//フラグ内容列挙
	enum Flag
	{
		RushActionStart = (1 << 11),
		TackleActionStart = (1 << 10),
		DownActionStart = (1 << 9),
		DieActionStart = (1 << 8),
		LongRangeStart = (1 << 7),       //攻撃が始まったか(7番目のビット)
		AttackEnd = (1 << 6),         //攻撃が終わったか(6番目のビット)
		DiffenceStart = (1 << 5),     //防御が始まったか(5番目のビット)
		WaitStart = (1 << 4),         //待ち行動が始まったか(4番目のビット)
		CloseRangeATStart = (1 << 3),       //近距離攻撃が始まったか(3番目のビット)
		CloseDisStart = (1 << 2),       //飛び掛かり攻撃が始まったか(2番目のビット)
		ApproachActionStart = (1 << 1),     //接近が始まったか(1番目のビット)
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

	// 実行
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


	//ビヘイビアツリーのゲッター
	BehaviorTree* getTree() { return m_AiTree; }

	//プレイヤーを発見したか
	bool FindPlayer() { return m_FindPlayer != NULL ? true : false; }
	GameObject* GetFindPlayer() { return m_FindPlayer; }

	//プレイヤーを見失う
	void LostPlayer() { m_FindPlayer = nullptr; }

	//通常の当たり判定
	static void CollisionAction(GameObject* obj, std::string name);

	//Rayの当たり判定
	static void RayCollisionAction(GameObject* obj);

	//フラグチェック関数
	bool FlagCheck(unsigned int flag) {
		return ((m_flag & flag) != 0);
	}

	//フラグオン関数
	void FlagOn(unsigned int flag) {
		m_flag |= flag;
	}

	//フラグオフ関数
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
	//全体フラグ管理変数 32個のフラグ管理
	unsigned int m_flag = 0;

	//Enemy行動管理フラグ
	bool m_ActionFlag[5] = { false };

	//Enemy状態管理フラグ
	bool m_StateFlag[3] = { false };

	int m_HP = 2000;

	//怯み発生のためのリミット
	int m_FearLimit = 300;
	//被ダメージを溜める
	int m_DamageCnt = 0;
	//最後に攻撃を食らったか
	bool m_LastAttack = false;
	bool m_FearFlag = false;
	int m_FearCnt = 0;

	int debagcnt = 0;

	Status m_NextSetStatus = None_Status;

	//一回だけ実行したいときに使う
	bool  DoOnce = false;
	bool  DoOnce2 = false;

	bool m_MotionStartFlag = false;

	//モーション中に回転しないように
	bool m_PlayMotion = false;

	BehaviorTree* m_AiTree;			// ビヘイビアツリー
	BehaviorData* m_BehaviorData = nullptr;	// ビヘイビアデータ
	NodeBase* m_ActiveNode = nullptr;			// 実行中ノード

	GameObject* m_FindPlayer = nullptr;       //見つけたプレイヤー

	//プレイヤーのポジション
	D3DXVECTOR3 m_PlayerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float m_KeepRotX = 0.0f;
	D3DXVECTOR3 m_MotionPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	bool m_CollisionFlag = false;
	bool m_RayCollision = false;
	bool m_WallCollision = false;

	//プレイヤーまでの距離
	float m_Length = 0.0f;

	//	チャージ回数記録用変数
	int m_ChargeCnt = 0;
	int m_ChargeFlag = 0;

	//シーン遷移を通知する変数
	bool   m_SceneFlag = false;

	int m_NowStatus = 0;

	//経路探索用リスト変数
	std::list<D3DXVECTOR3> m_AstarPosition;

	//ステートパターン用変数
	Situation* m_Action = nullptr;
	Situation* m_NextAction = nullptr;
};

