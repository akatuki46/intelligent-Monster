#pragma once
#include "Component.h"
#include "main.h"
#include "renderer.h"

class Transform :
    public Component
{
private:
	typedef enum
	{
		Not_Back = 0,
		Come_Back,
		Move_Loop,
		Interval_Loop,
		Come_Back_Interval
	}TransMode;

	TransMode m_Mode;

	int m_TransFlame = 0;

	D3DXVECTOR3  m_ChangePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3  m_ChangeScale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3  m_Rad = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3  m_ChangeSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	int m_TransDire = 1;
	int m_TransCnt = 0;

	bool m_Once = false;

	bool m_EndFlag = false;

	int m_IntervalCnt = 0;
	bool m_Intervalflag = false;
	
	int m_Cnt = 0;

	bool m_Playflag = true;


public:

	void Init(D3DXVECTOR3 EndPos, int mode, int MoveFlame,int Interval);
	void Init(D3DXVECTOR3 EndScale, int mode, int MoveFlame, int Interval,int None);
	void Init(D3DXVECTOR3 angle, int mode, int MoveFlame, int Interval,float None);
	void Init(D3DXVECTOR3 EndSize, D3DXVECTOR3 StartSize,int mode, int MoveFlame, int Interval, float None);

	void Uninit() override;
	void Update() override;
	void Draw() override {};

	bool GetEndFlag() { return m_EndFlag; }

	//transformコンポーネントから加算は大変
	D3DXVECTOR3 GetChangeSize() { return m_ChangeScale; }

	void SetPlayFlag(bool flag) { m_Playflag = flag; }

	//1は下方向に、-1は上方向に移動
	void SetTransDire(int Dire) { m_TransDire = Dire; }


};

