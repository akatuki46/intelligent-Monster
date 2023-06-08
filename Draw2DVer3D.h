//////////////////////////////////////////////////////////////////////////////////////////////////
//  3D空間用　2D描画コンポーネント
/////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Component.h"
#include "main.h"
#include "renderer.h"

class Draw2DVer3D : public Component
{
private:
	static ID3D11Buffer* m_VertexBuffer;

	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

	bool m_Bilboard = false;

public:
	void Init(D3DXVECTOR3 size, float texcode,bool Bilboard);
	void Uninit() override;
	void Draw() override;
	void Update()override;


};

