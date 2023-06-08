#pragma once
#include "Component.h"
#include "GameObject.h"

class Camera : public Component
{
private:
	float m_Point = 0;

	D3DXVECTOR3    m_Positions;			// ÉJÉÅÉâÇÃéãì_(à íu)

	D3DXVECTOR3    m_Target;	
	D3DXVECTOR3    m_Targets;

	D3DXMATRIX     m_ViewMatrix;
	D3DXMATRIX     m_InvViewMatrix;

	D3DXMATRIX m_ProjectionMatrix;

	bool  m_FreeFlag = false;
	bool  m_TestFlag = false;
	bool  m_TargetFlag = false;

	GameObject* m_TargetInstance = nullptr;

	int m_Cnt = 0;

	bool m_DethCameraFlag = false;

public:
	void Init(bool FleeFlag);
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetTestFlag(bool flag) { m_TestFlag = flag; }

	bool CheckView(D3DXVECTOR3 pos);

	D3DXMATRIX GetViewMatrix() { return m_ViewMatrix; }
};

 