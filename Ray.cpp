#include "Ray.h"
#include "GameObject.h"
#include "Enemy.h"
#include "manager.h"

ID3D11Buffer* Ray::m_VertexBuffer = NULL;

void Ray::Init()
{
	m_StartPos = m_ParentObject->GetPosition();
	//m_EndPos = D3DXVECTOR3(0.0f, 0.0f, 100.0f);

	VERTEX_3D vertex[2];

	vertex[0].Position = D3DXVECTOR3(m_StartPos.x,m_StartPos.y,m_StartPos.z);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(m_EndPos.x, m_EndPos.y, m_EndPos.z);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファ生成
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 2;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;//←ここを変えないと頂点バッファの書き換えが出来ない

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);


	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

}

void Ray::Uninit()
{
	m_VertexBuffer->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Ray::Draw()
{
	//頂点データ書き換え
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0,
		D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	vertex[0].Position = D3DXVECTOR3(m_StartPos.x, m_StartPos.y, m_StartPos.z);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(m_EndPos.x, m_EndPos.y, m_EndPos.z);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	//これを書くことにより頂点バッファの書き換えが完了する
	Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);


	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//ワールドマトリクス設定
	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);
	Renderer::SetWorldMatrix(&world);

	//マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Renderer::SetMaterial(material);

	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);

	//ポリゴン描画
	Renderer::GetDeviceContext()->Draw(2, 0);


}

void Ray::Update()
{
	m_StartPos = m_ParentObject->GetPosition();

	if (m_ParentObject->GetComponent<Enemy>()->FindPlayer())
	{
		m_EndPos = m_ParentObject->GetComponent<Enemy>()->GetFindPlayer()->GetPosition();
	}
	else
	{
		m_EndPos = D3DXVECTOR3(m_ParentObject->GetForward().x * 10.0f,1.0f, m_ParentObject->GetForward().z * 10.0f);
	}

	m_Dire = m_ParentObject->GetForward();
}
