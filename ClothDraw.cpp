#include "ClothDraw.h"
#include "TextureContainer.h"
#include "main.h"
#include "manager.h"
#include "Scene.h"
#include "input.h"

//----- マクロ定義
#define F_ZERO(v)			v.x=v.y=v.z=0.0f
#define F_SET(v,px,py,pz)	v.x=px;v.y=py;v.z=pz
#define ATT_COEFFICIENT			(0.5f)			// 減衰係数(Attenuation)
#define DELTA_TIME				(0.1f)			// 積分単位時間

#define WIND_FORCE_DEF_X		(40.0f)			// 風力Ｘ成分
#define WIND_FORCE_DEF_Y		(20.0f)			// 風力Ｙ成分
#define WIND_FORCE_DEF_Z		(30.0f)			// 風力Ｚ成分

void ClothDraw::Init(D3DXVECTOR3 Offset, D3DXVECTOR3 Wind)
{
	float	xx, yy, zz;				// 粒子間の距離（成分毎）
	int		count;					// バネカウント用
	int		i, j;					// ループカウンタ

	//テクスチャ座標用float変数
	float texX = PARTICLE_HORIZONTAL;
	float texY = PARTICLE_VERTICAL;

	// 粒子の初期化
	{
		for (j = 0; j <= PARTICLE_HORIZONTAL; j++) {
			for (i = 0; i <= PARTICLE_VERTICAL; i++) {
				// 座標を設定
				g_Cloth.Particle[j][i].position.x = SPRING_DEFAULT_LENGTH * (j + PARTICLE_HORIZONTAL / 2) + Offset.x;
				g_Cloth.Particle[j][i].position.y = SPRING_DEFAULT_LENGTH * (i + 1) + Offset.y;
				g_Cloth.Particle[j][i].position.z = 0.0f;
				F_ZERO(g_Cloth.Particle[j][i].velocity);									// 速度初期化
				F_ZERO(g_Cloth.Particle[j][i].acceleration);								// 加速度初期化
				F_ZERO(g_Cloth.Particle[j][i].resultant);									// 合力初期化
				F_SET(g_Cloth.Particle[j][i].gravity, 0.0f, SPRING_MASS * -9.8f, 0.0f);		// 重力初期化
				// 特定の粒子はロック状態へ
				g_Cloth.Particle[j][i].onLock = (j == 0 && (i == 0 || i == PARTICLE_VERTICAL));	// ロック
				g_Cloth.Particle[j][i].onDrag = false;					// ドラッグされてない

				vertex[j][i].Position = g_Cloth.Particle[j][i].position;
				vertex[j][i].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				vertex[j][i].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				vertex[j][i].TexCoord = D3DXVECTOR2((float)(j / texX), (float)(i / texY));
			}
		}

		//頂点バッファ生成
		D3D11_BUFFER_DESC bd{};
		//ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;//←ここと
		bd.ByteWidth = sizeof(VERTEX_3D) * ((PARTICLE_VERTICAL + 1) * (PARTICLE_HORIZONTAL + 1));
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;//←ここを変えないと頂点バッファの書き換えが出来ない

		D3D11_SUBRESOURCE_DATA sd{};
		//ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = vertex;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	}

	// バネの初期化
	count = 0;
	for (j = 0; j <= PARTICLE_HORIZONTAL; j++) {
		for (i = 0; i <= PARTICLE_VERTICAL; i++) {
			// バネ参照インデックスの設定
			if (i < PARTICLE_HORIZONTAL) {
				g_Cloth.Spring[count].p1.horz = i;		// １個目の参照粒子インデックスを設定
				g_Cloth.Spring[count].p1.vert = j;
				g_Cloth.Spring[count].p2.horz = i + 1;	// ２個目の参照粒子インデックスを設定
				g_Cloth.Spring[count].p2.vert = j;
				// ２個の粒子間の距離を求め、バネの自然長とする
				xx = g_Cloth.Particle[j][i].position.x - g_Cloth.Particle[j][i + 1].position.x;
				yy = g_Cloth.Particle[j][i].position.y - g_Cloth.Particle[j][i + 1].position.y;
				zz = g_Cloth.Particle[j][i].position.z - g_Cloth.Particle[j][i + 1].position.z;
				g_Cloth.Spring[count].length = sqrtf(xx * xx + yy * yy + zz * zz);
				count++;
			}
			if (j < PARTICLE_VERTICAL) {
				g_Cloth.Spring[count].p1.horz = i;
				g_Cloth.Spring[count].p1.vert = j;
				g_Cloth.Spring[count].p2.horz = i;
				g_Cloth.Spring[count].p2.vert = j + 1;
				xx = g_Cloth.Particle[j][i].position.x - g_Cloth.Particle[j + 1][i].position.x;
				yy = g_Cloth.Particle[j][i].position.y - g_Cloth.Particle[j + 1][i].position.y;
				zz = g_Cloth.Particle[j][i].position.z - g_Cloth.Particle[j + 1][i].position.z;
				g_Cloth.Spring[count].length = sqrtf(xx * xx + yy * yy + zz * zz);
				count++;
			}
			if (i < PARTICLE_HORIZONTAL && j < PARTICLE_VERTICAL) {
				g_Cloth.Spring[count].p1.horz = i;
				g_Cloth.Spring[count].p1.vert = j;
				g_Cloth.Spring[count].p2.horz = i + 1;
				g_Cloth.Spring[count].p2.vert = j + 1;
				xx = g_Cloth.Particle[j][i].position.x - g_Cloth.Particle[j + 1][i + 1].position.x;
				yy = g_Cloth.Particle[j][i].position.y - g_Cloth.Particle[j + 1][i + 1].position.y;
				zz = g_Cloth.Particle[j][i].position.z - g_Cloth.Particle[j + 1][i + 1].position.z;
				g_Cloth.Spring[count].length = sqrtf(xx * xx + yy * yy + zz * zz);
				count++;
			}
			if (i > 0 && j < PARTICLE_VERTICAL) {
				g_Cloth.Spring[count].p1.horz = i;
				g_Cloth.Spring[count].p1.vert = j;
				g_Cloth.Spring[count].p2.horz = i - 1;
				g_Cloth.Spring[count].p2.vert = j + 1;
				xx = g_Cloth.Particle[j][i].position.x - g_Cloth.Particle[j + 1][i - 1].position.x;
				yy = g_Cloth.Particle[j][i].position.y - g_Cloth.Particle[j + 1][i - 1].position.y;
				zz = g_Cloth.Particle[j][i].position.z - g_Cloth.Particle[j + 1][i - 1].position.z;
				g_Cloth.Spring[count].length = sqrtf(xx * xx + yy * yy + zz * zz);
				count++;
			}
		}
	}

	//風力の初期化
	{
		g_WindForce.force.x = Wind.x;		// 風力の初期値を設定
		g_WindForce.force.y = Wind.y;
		g_WindForce.force.z = Wind.z;
	}


	//インデックスバッファ生成
	//描画順番の指定
	{
		unsigned int Index[(((PARTICLE_VERTICAL * 2 + 3) * PARTICLE_HORIZONTAL) + (PARTICLE_HORIZONTAL - 2))];

		int i = 0;
		for (int x = 0; x < PARTICLE_HORIZONTAL; x++) {
			for (int y = 0; y <= PARTICLE_VERTICAL; y++) {

				Index[i] = x * (PARTICLE_VERTICAL + 1) + y;
				i++;
				Index[i] = (x + 1) * (PARTICLE_VERTICAL + 1) + y;
				i++;
			}
			if (x == PARTICLE_HORIZONTAL -1)
				break;
			
			Index[i] = (x + 1) * (PARTICLE_VERTICAL + 1) + PARTICLE_VERTICAL;
			i++;
			Index[i] = (x + 1) * (PARTICLE_VERTICAL + 1);
			i++;
			
		}


		//頂点バッファ生成
		D3D11_BUFFER_DESC bd{};
		//ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(unsigned int) * (((PARTICLE_VERTICAL * 2 + 3) * PARTICLE_HORIZONTAL) + (PARTICLE_HORIZONTAL - 2));
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA sd{};
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = Index;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer);
	}

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");

	m_Name = "ClothDraw";
}

void ClothDraw::Uninit()
{
	m_VertexBuffer->Release();
	m_IndexBuffer->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void ClothDraw::Update()
{
	D3DXVECTOR3	vec_spr;				// 粒子２点間のベクトル
	D3DXVECTOR3	resistance;				// 抵抗力ベクトル
	D3DXVECTOR3	windforce;				// 風力ベクトル
	float	f1, f2;					// バネが粒子に与える力（２種）
	int		h1, v1, h2, v2;			// バネ端にある粒子のインデックス（横、縦別２個分）
	float	f1x, f1y, f1z;			// 長さからバネに発生する力
	float	f2x, f2y, f2z;
	float	length;					// 粒子間の距離
	float	xx, yy, zz;				// 粒子間の距離（成分毎）
	int		count;					// バネカウント用
	int		i, j;					// ループカウンタ

	//風力方向の変更
	if (GetKeyboardPress(DIK_UP)) g_WindForce.force.y -= 1.0f;	// カーソルキーで風力を変える
	if (GetKeyboardPress(DIK_DOWN)) g_WindForce.force.y += 1.0f;
	if (GetKeyboardPress(DIK_LEFT)) g_WindForce.force.x -= 1.0f;
	if (GetKeyboardPress(DIK_RIGHT)) g_WindForce.force.x += 1.0f;


	// 粒子の処理
	for (j = 0; j <= PARTICLE_VERTICAL; j++) {
		for (i = 0; i <= PARTICLE_HORIZONTAL; i++) {
			// 合力を０にする
			g_Cloth.Particle[j][i].resultant.x = 0;
			g_Cloth.Particle[j][i].resultant.y = 0;
			g_Cloth.Particle[j][i].resultant.z = 0;

			if (!g_Cloth.Particle[j][i].onLock && !g_Cloth.Particle[j][i].onDrag) {
				// 重力を求める
				F_SET(g_Cloth.Particle[j][i].gravity, 0.0f, SPRING_MASS * -9.8f, 0.0f);	// 重力

				// 抵抗力を求める
				resistance.x = -g_Cloth.Particle[j][i].velocity.x * ATT_COEFFICIENT;
				resistance.y = -g_Cloth.Particle[j][i].velocity.y * ATT_COEFFICIENT;
				resistance.z = -g_Cloth.Particle[j][i].velocity.z * ATT_COEFFICIENT;

				// 風力を求める
				windforce.x = g_WindForce.force.x + (float)(rand() % 30 - 15);		// Ｘ成分
				windforce.y = g_WindForce.force.y + (float)(rand() % 30 - 15);		// Ｙ成分
				windforce.z = g_WindForce.force.z + (float)(rand() % 30 - 15);		// Ｚ成分
				
				// 合力＝重力＋抵抗力＋風力
				g_Cloth.Particle[j][i].resultant.x = g_Cloth.Particle[j][i].gravity.x + resistance.x + windforce.x;
				g_Cloth.Particle[j][i].resultant.y = g_Cloth.Particle[j][i].gravity.y + resistance.y + windforce.y;
				g_Cloth.Particle[j][i].resultant.z = g_Cloth.Particle[j][i].gravity.z + resistance.z + windforce.z;
			}
		}
	}

	// バネの処理
	for (i = 0; i < SPRING_NUMS; i++) {
		// バネの参照粒子（２個）を取得
		h1 = g_Cloth.Spring[i].p1.horz;
		v1 = g_Cloth.Spring[i].p1.vert;
		h2 = g_Cloth.Spring[i].p2.horz;
		v2 = g_Cloth.Spring[i].p2.vert;
		// ２個の粒子間のベクトルを求める
		vec_spr.x = g_Cloth.Particle[v1][h1].position.x - g_Cloth.Particle[v2][h2].position.x;
		vec_spr.y = g_Cloth.Particle[v1][h1].position.y - g_Cloth.Particle[v2][h2].position.y;
		vec_spr.z = g_Cloth.Particle[v1][h1].position.z - g_Cloth.Particle[v2][h2].position.z;
		// 粒子間の距離を求める
		length = sqrtf(vec_spr.x * vec_spr.x + vec_spr.y * vec_spr.y + vec_spr.z * vec_spr.z);
		// 距離、自然長、バネ係数からかかる力を求める（２つ目は逆方向）
		f1 = -SPRING_COEFFICIENT * (length - g_Cloth.Spring[i].length);
		f2 = -f1;
		// ベクトルの成分に力をかける
		f1x = f1 * (vec_spr.x / length);
		f1y = f1 * (vec_spr.y / length);
		f1z = f1 * (vec_spr.z / length);
		f2x = f2 * (vec_spr.x / length);
		f2y = f2 * (vec_spr.y / length);
		f2z = f2 * (vec_spr.z / length);
		// 求めた力を合力に加える
		g_Cloth.Particle[v1][h1].resultant.x += f1x;
		g_Cloth.Particle[v1][h1].resultant.y += f1y;
		g_Cloth.Particle[v1][h1].resultant.z += f1z;
		g_Cloth.Particle[v2][h2].resultant.x += f2x;
		g_Cloth.Particle[v2][h2].resultant.y += f2y;
		g_Cloth.Particle[v2][h2].resultant.z += f2z;
	}

	for (j = 0; j <= PARTICLE_VERTICAL; j++) {
		for (i = 0; i <= PARTICLE_HORIZONTAL; i++) {
			// 固定されていればスキップ
			if (g_Cloth.Particle[j][i].onLock || g_Cloth.Particle[j][i].onDrag) continue;

			// 合力と質量から加速度を求める
			g_Cloth.Particle[j][i].acceleration.x = g_Cloth.Particle[j][i].resultant.x / SPRING_MASS;
			g_Cloth.Particle[j][i].acceleration.y = g_Cloth.Particle[j][i].resultant.y / SPRING_MASS;
			//g_Cloth.Particle[j][i].acceleration.z = g_Cloth.Particle[j][i].resultant.z / SPRING_MASS;

			// 速度に加速度を加える
			g_Cloth.Particle[j][i].velocity.x += g_Cloth.Particle[j][i].acceleration.x * DELTA_TIME;
			g_Cloth.Particle[j][i].velocity.y += g_Cloth.Particle[j][i].acceleration.y * DELTA_TIME;
			//g_Cloth.Particle[j][i].velocity.z += g_Cloth.Particle[j][i].acceleration.z * DELTA_TIME;

			// 速度から座標を移動
			g_Cloth.Particle[j][i].position.x += g_Cloth.Particle[j][i].velocity.x * DELTA_TIME;
			g_Cloth.Particle[j][i].position.y += g_Cloth.Particle[j][i].velocity.y * DELTA_TIME;
			//g_Cloth.Particle[j][i].position.z += g_Cloth.Particle[j][i].velocity.z * DELTA_TIME;

			vertex[j][i].Position = g_Cloth.Particle[j][i].position;
		}
	}
}

void ClothDraw::Draw()
{

//#ifdef _DEBUG
//
//	if (!m_ImGuiDrawFlag)
//		return;
//
//	ImGui::Begin("Test ImGui", &m_ImGuiDrawFlag);
//	ImGui::Text("TestrComplete");
//	if (ImGui::TreeNode("TestPosition"))
//	{
//
//		for (int j = 0; j <= PARTICLE_HORIZONTAL; j++) {
//			for (int i = 0; i <= PARTICLE_VERTICAL; i++) {
//				ImGui::Text("(%d:%d)  x:%f  y:%f  z;%f", j,i, g_Cloth.Particle[j][i].position.x, g_Cloth.Particle[j][i].position.y, g_Cloth.Particle[j][i].position.z);
//
//			}
//		}
//
//		ImGui::TreePop();
//		ImGui::Separator();
//	}
//
//
//	ImGui::End();
//
//#endif // !_DEBUG

	//頂点データ書き換え
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0,
		D3D11_MAP_WRITE_DISCARD, 0, &msr);

	//VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;
	memcpy(msr.pData, vertex, sizeof(VERTEX_3D) * ((PARTICLE_VERTICAL + 1) * (PARTICLE_HORIZONTAL + 1)));


	//これを書くことにより頂点バッファの書き換えが完了する
	Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);



	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//マトリクス設定
	Renderer::SetWorldViewProjection2D();

	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//インデックスバッファ設定
	Renderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	TextureContainer::ModelDrawIndex(m_ParentObject->GetTag(), (((PARTICLE_VERTICAL * 2 + 3) * PARTICLE_HORIZONTAL) + (PARTICLE_HORIZONTAL - 2)));
}
