#include "Draw2DParticle.h"
#include "main.h"
#include "manager.h"
#include "Scene.h"

void Draw2DParticle::Init(D3DXVECTOR3 size, D3DXVECTOR3 acc, D3DXVECTOR4 color, int life)
{
	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x, m_ParentObject->GetPosition().y, size.z);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = color;
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x + size.x, m_ParentObject->GetPosition().y, size.z);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = color;
	vertex[1].TexCoord = D3DXVECTOR2(0.0f, 0.0f)
		;
	vertex[2].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x, m_ParentObject->GetPosition().y + size.y, -size.z);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = color;
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[3].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x + size.x, m_ParentObject->GetPosition().y + size.y, -size.z);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = color;
	vertex[3].TexCoord = D3DXVECTOR2(0.0f, 0.0f);


	//頂点バッファ生成
	D3D11_BUFFER_DESC bd{};
	//ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;//←ここと
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;//←ここを変えないと頂点バッファの書き換えが出来ない

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);


	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");

	m_Size = size;

	m_Life = life;

	m_Color = color;

	m_Acceleration = acc;

	m_Name = "Draw2DParticle";
}

void Draw2DParticle::Uninit()
{
	m_VertexBuffer->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Draw2DParticle::Update()
{
	m_ParentObject->SetVelocity(m_ParentObject->GetVelocity() + m_Acceleration);
	m_ParentObject->SetPosition(m_ParentObject->GetPosition() + m_ParentObject->GetVelocity());

	if (m_Life < m_LifeCnt)
	{
		m_ParentObject->SetDestroy();
	}
	else
	{
		m_LifeCnt++;
	}

	if (m_ParentObject->GetPosition().x > SCREEN_RESOLUTION_WIDTH ||
		m_ParentObject->GetPosition().x < 0 ||
		m_ParentObject->GetPosition().y > SCREEN_RESOLUTION_HEIGHT ||
		m_ParentObject->GetPosition().y < 0)
	{
		m_ParentObject->SetDestroy();
	}

}

void Draw2DParticle::Draw()
{
//
//#ifdef _DEBUG
//
//	if (!m_ImGuiDrawFlag)
//		return;
//
//	ImGui::Begin("Test ImGui", &m_ImGuiDrawFlag);
//	ImGui::Text("TestrComplete");
//	if (ImGui::TreeNode("TestPosition"))
//	{
//		//ImGui::Text("X:%f Y:%f Z:%f", childPos.x, childPos.y, childPos.z);
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

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	vertex[0].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x, m_ParentObject->GetPosition().y, m_Size.z);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = m_Color;
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x + m_Size.x, m_ParentObject->GetPosition().y, m_Size.z);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = m_Color;
	vertex[1].TexCoord = D3DXVECTOR2(0.0f, 0.0f)
		;
	vertex[2].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x, m_ParentObject->GetPosition().y + m_Size.y, -m_Size.z);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = m_Color;
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[3].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x + m_Size.x, m_ParentObject->GetPosition().y + m_Size.y, -m_Size.z);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = m_Color;
	vertex[3].TexCoord = D3DXVECTOR2(0.0f, 0.0f);


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

	//プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描画
	Renderer::GetDeviceContext()->Draw(4, 0);


}
