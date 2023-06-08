#include "Wave3D.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "TextureContainer.h"

#define M_PI 3.14159

void Wave3D::Init()
{
	//テクスチャ座標用float変数
	float texX = WAVE_HORIZON;
	float texY = WAVE_VERTICAL;

	for (int x = 0; x <= WAVE_HORIZON; x++)
	{
		for (int z = 0; z <= WAVE_VERTICAL; z++){
			g_Wave[x][z].position.x = (float)((x + WAVE_HORIZON / 2) * WAVE_PITCH) + 200;	// Ｘ座標
			g_Wave[x][z].position.y = (float)((1 + z) * WAVE_PITCH) + 200;										// Ｙ座標
			g_Wave[x][z].position.z = 0.0f;	// Ｚ座標
				   
			g_Wave[x][z].amplitude = WAVE_AMPLITUDE;	// 振幅
			g_Wave[x][z].time = 0.0f;

			vertex[x][z].Position = g_Wave[x][z].position;
			vertex[x][z].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[x][z].Diffuse = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
			vertex[x][z].TexCoord = D3DXVECTOR2((float)(x / texX), (float)(z / texY));

		}
	}
	//頂点バッファ生成
	D3D11_BUFFER_DESC bd{};
	//ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;//←ここと
	bd.ByteWidth = sizeof(VERTEX_3D) * ((WAVE_HORIZON + 1) * (WAVE_PITCH + 1));
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;//←ここを変えないと頂点バッファの書き換えが出来ない

	D3D11_SUBRESOURCE_DATA sd{};
	//ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//インデックスバッファ生成
//描画順番の指定
	{
		unsigned int Index[(((WAVE_VERTICAL * 2 + 3) * WAVE_HORIZON) + (WAVE_HORIZON - 2))];

		int i = 0;
		for (int x = 0; x < WAVE_HORIZON; x++) {
			for (int y = 0; y <= WAVE_VERTICAL; y++) {

				Index[i] = x * (WAVE_VERTICAL + 1) + y;
				i++;
				Index[i] = (x + 1) * (WAVE_VERTICAL + 1) + y;
				i++;
			}
			if (x == WAVE_HORIZON - 1)
				break;

			Index[i] = (x + 1) * (WAVE_VERTICAL + 1) + WAVE_VERTICAL;
			i++;
			Index[i] = (x + 1) * (WAVE_VERTICAL + 1);
			i++;

		}

		//頂点バッファ生成
		D3D11_BUFFER_DESC bd{};
		//ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(unsigned int) * (((WAVE_VERTICAL * 2 + 3) * WAVE_HORIZON) + (WAVE_HORIZON - 2));
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

	//m_ParentObject->m_Position = D3DXVECTOR3(10.0f, 2.0f, 0.0f);
	//m_ParentObject->m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_ParentObject->m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);



	m_Name = "Wave";
}

void Wave3D::Uninit()
{
	m_VertexBuffer->Release();
	m_IndexBuffer->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Wave3D::Update()
{
	float	dx, dz, length;
	float	px, py;

	// 波の中心インデックス
	int center_x, center_z;

	// 波の中心インデックス
	center_x = WAVE_HORIZON / 2;
	center_z = WAVE_VERTICAL / 2;	// 水面中央

	for (int x = 0; x <= WAVE_HORIZON; x++)
	{
		for (int z = 0; z <= WAVE_VERTICAL; z++) {
			//// 振動原点からの距離を求める
			//dx = g_Wave[x][z].position.x - g_Wave[center_x][center_z].position.x;
			//dz = g_Wave[x][z].position.z - g_Wave[center_x][center_z].position.z;
			//length = sqrtf(dx * dx + dz * dz);

			//// 距離を元に振動の式から変位を求める
			//g_Wave[x][z].position.y = g_Wave[x][z].amplitude * sinf(2.0f * (float)M_PI * ((length / WAVE_LENGTH) - (g_Wave[x][z].time / WAVE_CYCLE)));

			//////ずれた位置からもう一つ波を発生
			////center_z += 15;

			////// 振動原点からの距離を求める
			////dx = g_Wave[x][z].position.x - g_Wave[center_x][center_z].position.x;
			////dz = g_Wave[x][z].position.z - g_Wave[center_x][center_z].position.z;
			////length = sqrtf(dx * dx + dz * dz);

			////// 距離を元に振動の式から変位を求める
			////g_Wave[x][z].position.y = g_Wave[x][z].amplitude * sinf(2.0f * (float)M_PI * ((length / WAVE_LENGTH) - (g_Wave[x][z].time / WAVE_CYCLE)));

			//// 時間を進める
			//g_Wave[x][z].time += 0.1f;

			//vertex[x][z].Position = g_Wave[x][z].position;
		}
	}
}

void Wave3D::Draw()
{
#ifdef _DEBUG

	if (!m_ImGuiDrawFlag)
		return;

	ImGui::Begin("Test ImGui", &m_ImGuiDrawFlag);
	ImGui::Text("TestrComplete");
	if (ImGui::TreeNode("TestPosition"))
	{

		for (int j = 0; j <= WAVE_HORIZON; j++) {
			for (int i = 0; i <= WAVE_VERTICAL; i++) {
				ImGui::Text("g_Wave  (%d:%d)  x:%f  y:%f  z;%f", j, i, g_Wave[j][i].position.x, g_Wave[j][i].position.y, g_Wave[j][i].position.z);

				//ImGui::Text("vertex  (%d:%d)  x:%f  y:%f  z;%f", j, i, vertex[j][i].Position.x, vertex[j][i].Position.y, vertex[j][i].Position.z);
			}
		}

		ImGui::TreePop();
		ImGui::Separator();
	}

	ImGui::End();

#endif // !_DEBUG

	//頂点データ書き換え
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0,
		D3D11_MAP_WRITE_DISCARD, 0, &msr);

	memcpy(msr.pData, vertex, sizeof(VERTEX_3D) * ((WAVE_HORIZON + 1) * (WAVE_PITCH + 1)));

	//これを書くことにより頂点バッファの書き換えが完了する
	Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	////ワールドマトリクス設定
	//D3DXMATRIX world, scale, rot, trans;
	//D3DXMatrixScaling(&scale, m_ParentObject->m_Scale.x, m_ParentObject->m_Scale.y, m_ParentObject->m_Scale.z);
	//D3DXMatrixRotationYawPitchRoll(&rot, m_ParentObject->m_Rotation.y, m_ParentObject->m_Rotation.x, m_ParentObject->m_Rotation.z);
	//D3DXMatrixTranslation(&trans, m_ParentObject->m_Position.x, m_ParentObject->m_Position.y, m_ParentObject->m_Position.z);
	//world = scale * rot * trans;
	//Renderer::SetWorldMatrix(&world);


	//マトリクス設定
	Renderer::SetWorldViewProjection2D();

	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//インデックスバッファ設定
	Renderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	////マテリアル設定
	//MATERIAL material;
	//ZeroMemory(&material, sizeof(material));
	//material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//Renderer::SetMaterial(material);

	TextureContainer::ModelDrawIndex(m_ParentObject->GetTag(), (((WAVE_VERTICAL * 2 + 3) * WAVE_HORIZON) + (WAVE_HORIZON - 2)));


}
