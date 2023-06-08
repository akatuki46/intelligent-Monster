#pragma once
#include "Component.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"

#define PARTICLE_MAX		(100000)				// パーティクルの数

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
	
	//パーティクル発生させるか
	bool m_Use = false;

	//生成間隔
	int m_Interval = 0;
	int m_IntervalCnt = 0;

	//ループ
	bool m_Loop = false;
	//ループしない場合のフラグ
	bool m_End = false;

	//サイズ
	D3DXVECTOR3 m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//生存時間
	int m_LifeTime = 0;

	//生成量
	int m_Amount = 0;

	//3D描画するか
	bool m_3Dmode = false;

	//加速度
	D3DXVECTOR3 m_Acc = D3DXVECTOR3(0.0f, 0.001f, 0.0f);

	//スピード
	float m_spd = 0.001f;

	//色
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

