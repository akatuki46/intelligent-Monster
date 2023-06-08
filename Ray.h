#pragma once
#include "Component.h"
#include "main.h"
#include "renderer.h"

//線分（エネミーの注視点に使用）
class Ray:public Component
{
private:
	D3DXVECTOR3 m_StartPos;   //始点
	D3DXVECTOR3 m_EndPos;  //終点(線描画のために必要)
	D3DXVECTOR3 m_Dire;  //向き

	static ID3D11Buffer* m_VertexBuffer;

	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;
public:
	void Init();
	void Uninit() override;
	void Draw() override;
	void Update()override;

	D3DXVECTOR3 GetRayStart() { return m_StartPos; }
	D3DXVECTOR3 GetRayDire() { return m_Dire; }
	void SetRayStart(D3DXVECTOR3 pos) { m_StartPos = pos; }
	void SetRayDire(D3DXVECTOR3 Dire) { m_Dire = Dire; }

};