#pragma once
#include "Component.h"
#include "main.h"
#include "renderer.h"

//�����i�G�l�~�[�̒����_�Ɏg�p�j
class Ray:public Component
{
private:
	D3DXVECTOR3 m_StartPos;   //�n�_
	D3DXVECTOR3 m_EndPos;  //�I�_(���`��̂��߂ɕK�v)
	D3DXVECTOR3 m_Dire;  //����

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