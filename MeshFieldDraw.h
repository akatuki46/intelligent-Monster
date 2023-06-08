#pragma once
#include "Component.h"
#include "main.h"
#include "renderer.h"

#define FIELD_X_SIZE 10
#define FIELD_Z_SIZE 10
#define FIELD_DIS 5

class MeshFieldDraw :
    public Component
{
public:
	//フィールドのXサイズ
	static const int Field_X_Size = 20;

	//フィールドのZサイズ
	static const int Field_Z_Size = 20;

private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11Buffer* m_IndexBuffer = NULL;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;
	
	VERTEX_3D  m_Vertex[FIELD_Z_SIZE + 1][FIELD_X_SIZE + 1];

	int      m_Direction = 0;

public:
	void Init(int Direction) ;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	float GetHeight(D3DXVECTOR3 pos);
};

