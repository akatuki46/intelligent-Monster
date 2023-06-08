#pragma once
#include "Component.h"
#include "ItemManager.h"
#include "GameObject.h"

class  Player : public Component
{
private:
	//自身の体力
	int    m_Hp = 0;
	int    m_MaxHp = 150;
	//赤ゲージ
	int    m_RedHp = 0;
	//自動回復用変数
	int    m_RecoveryCnt = 0;

	//スタミナ用変数
	int    m_Stamina = 0;
	//スタミナを減らすのを遅らせる
	int    m_StaminaCnt = 0;

	//無敵判定用変数
	int    m_InviTime = 0;

	float    m_BlendRate = 0;
	//モンスターからダメージを受けたときのフラグ
	bool   m_DamageFalg = false;

	int    m_DamegeCnt = 0;

	//シーン遷移可能を通知する変数
	bool   m_SceneFlag = false;
	bool   m_AttackFlag = false;
	int    m_AttackCnt = 0;

	bool   m_DashFlag = false;

	//移動値の補正
	float  m_MoveValue = 0.05f;

	//アイテムインスタンスの確保
	GameObject* m_HaveItem = nullptr;

	//アイテムを使ったときのフラグ　連続使用を防ぐ
	bool   m_UseItem = false;
	int    m_UseItemCnt = 0;

	//回避アニメーション再生用変数
	bool m_DodgeFlag = false;

	//無敵フラグ
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
	
	//HP関連関数
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

