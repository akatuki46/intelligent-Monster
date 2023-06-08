#pragma once
#include "Component.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"

#define PARTICLE_HORIZONTAL		(15)			// 粒子　横方向総数
#define PARTICLE_VERTICAL		(15)			// 粒子　縦方向総数

//\//は改行
#define SPRING_NUMS				(PARTICLE_HORIZONTAL*(PARTICLE_VERTICAL+1) + \
								 PARTICLE_VERTICAL*(PARTICLE_HORIZONTAL+1) + \
								 PARTICLE_VERTICAL*PARTICLE_HORIZONTAL*2)	// スプリング総数

#define SPRING_DEFAULT_LENGTH	(50.0f)			// バネ自然長
#define SPRING_COEFFICIENT		(80.0f)			// バネ係数
#define SPRING_MASS				(2.0f)			// バネ質量

class ClothDraw :
    public Component
{
private:
	struct WINDFORCE {
		int		status;				// ステータス
		D3DXVECTOR3	force;				// 風力ベクトル
	};

	struct PARTICLE {
		bool	onLock;				// 固定フラグ
		bool	onDrag;				// マウスドラッグ中判定フラグ
		D3DXVECTOR3	position;			// 位置座標 (Position)
		D3DXVECTOR3	velocity;			// 速度 (Velocity)
		D3DXVECTOR3	acceleration;		// 加速度 (Acceleration)
		D3DXVECTOR3	resultant;			// 合力 (Resultant)
		D3DXVECTOR3	gravity;			// 重力 (Gravity)
	};

	struct P_REF {
		int		horz;				// 横方向インデックス
		int		vert;				// 縦方向インデックス
	};

	struct SPRING {
		P_REF	p1;					// 接続されている粒子１
		P_REF	p2;					// 接続されている粒子２
		float	length;				// 自然長
	};

	struct CLOTH {
		int			status;														// ステータス
		PARTICLE	Particle[PARTICLE_VERTICAL + 1][PARTICLE_HORIZONTAL + 1];		// 構成粒子
		SPRING		Spring[SPRING_NUMS];										// 粒子間のバネ
	};

	CLOTH		g_Cloth;					// 布オブジェクト
	WINDFORCE	g_WindForce;				// 風力オブジェクト

	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11Buffer* m_IndexBuffer = NULL;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	D3DXVECTOR3 ClothPos[((PARTICLE_VERTICAL * 2 + 3) * PARTICLE_HORIZONTAL) - 1];
	VERTEX_3D vertex[PARTICLE_VERTICAL + 1][PARTICLE_HORIZONTAL + 1];
	
public:

	void Init(D3DXVECTOR3 Offset,D3DXVECTOR3 Wind);
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void AddWind(D3DXVECTOR3 add) { g_WindForce.force += add; }

};

