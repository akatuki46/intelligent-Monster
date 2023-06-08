#pragma once
#include "Component.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"

#define WAVE_HORIZON  (10)
#define WAVE_VERTICAL  (10)

#define WAVE_PITCH       (50)
#define WAVE_AMPLITUDE   (1.0f)					// ウェーブポイントの振幅
#define WAVE_LENGTH	     (1.0f)				// ウェーブポイントの波長
#define WAVE_CYCLE		 (50.0f)					// ウェーブポイントの周期

class Wave3D :
    public Component
{
private:
	struct WAVE {
		int		        status;				// ステータス
		D3DXVECTOR3 	position;			// 位置座標 (Position)
		float	        amplitude;			// 振幅 (Amplitude)
		float	        time;				// 時間
	};

	WAVE		g_Wave[WAVE_HORIZON + 1][WAVE_VERTICAL + 1];		// ウェーブポイント
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11Buffer* m_IndexBuffer = NULL;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	VERTEX_3D vertex[WAVE_HORIZON + 1][WAVE_VERTICAL + 1];


public:
	void Init();
	void Uninit() override;
	void Update() override;
	void Draw() override;

};

