#include "SizeDraw2D.h"
#include "TextureContainer.h"
#include "Scene.h"
#include "manager.h"

void SizeDraw2D::Init(D3DXVECTOR3 Size, D3DXVECTOR4 color, int mode)
{
	TexSize = Size;
	m_DrawMode = (DrawMode)mode;

	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x - (TexSize.x / 2), m_ParentObject->GetPosition().y - (TexSize.y / 2), 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = color;
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x + (TexSize.x / 2), m_ParentObject->GetPosition().y - (TexSize.y / 2), 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = color;
	vertex[1].TexCoord = D3DXVECTOR2(0.0f, 1.0f)
		;
	vertex[2].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x - (TexSize.x / 2), m_ParentObject->GetPosition().y + (TexSize.y / 2), 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = color;
	vertex[2].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[3].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x + (TexSize.x / 2), m_ParentObject->GetPosition().y + (TexSize.y / 2), 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = color;
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);


	//頂点バッファ生成
	D3D11_BUFFER_DESC bd{};
	//ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;//←ここと
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;//←ここを変えないと頂点バッファの書き換えが出来ない
											   //（テクスチャアニメーション出来ない）

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	TexSize = Size;
	m_Color = color;

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");
}

void SizeDraw2D::Uninit()
{
	m_VertexBuffer->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void SizeDraw2D::Update()
{

}

void SizeDraw2D::Draw()
{
	
	if (m_ParentObject->GetTag() != "" && TextureContainer::GetTextureDivi(m_ParentObject->GetTag()) == D3DXVECTOR2(1.0f, 1.0f))
	{
		Scene* scene = Manager::GetScene();
		GameObject* ParentObject = scene->GetGameObject(m_ParentObject->GetParent(), scene->UI_LAYER);

		if (ParentObject != nullptr)
		{
			m_ParentObject->SetPosition(ParentObject->GetPosition() - m_ParentObject->GetInteval());
		}

		//頂点データ書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0,
			D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		if (m_DrawMode == LEFT_TOP)
		{
			vertex[0].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x, m_ParentObject->GetPosition().y, 0.0f);
			vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[0].Diffuse = m_Color;
			vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

			vertex[1].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x + (TexSize.x), m_ParentObject->GetPosition().y, 0.0f);
			vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[1].Diffuse = m_Color;
			vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f)
				;
			vertex[2].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x, m_ParentObject->GetPosition().y + (TexSize.y), 0.0f);
			vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[2].Diffuse = m_Color;
			vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

			vertex[3].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x + (TexSize.x), m_ParentObject->GetPosition().y + (TexSize.y), 0.0f);
			vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[3].Diffuse = m_Color;
			vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
		}
		else if(m_DrawMode == CENTER_CENTER)
		{
			vertex[0].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x - (TexSize.x/2), m_ParentObject->GetPosition().y - (TexSize.y / 2), 0.0f);
			vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[0].Diffuse = m_Color;
			vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

			vertex[1].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x + (TexSize.x /2), m_ParentObject->GetPosition().y - (TexSize.y / 2), 0.0f);
			vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[1].Diffuse = m_Color;
			vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f)
				;
			vertex[2].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x - (TexSize.x / 2), m_ParentObject->GetPosition().y + (TexSize.y  / 2), 0.0f);
			vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[2].Diffuse = m_Color;
			vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

			vertex[3].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x + (TexSize.x / 2), m_ParentObject->GetPosition().y + (TexSize.y / 2), 0.0f);
			vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[3].Diffuse = m_Color;
			vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
		}
		else if (LEFT_CENTER)
		{
			vertex[0].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x, m_ParentObject->GetPosition().y - (TexSize.y / 2), 0.0f);
			vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[0].Diffuse = m_Color;
			vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

			vertex[1].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x + (TexSize.x), m_ParentObject->GetPosition().y - (TexSize.y / 2), 0.0f);
			vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[1].Diffuse = m_Color;
			vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f)
				;
			vertex[2].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x, m_ParentObject->GetPosition().y + (TexSize.y/2), 0.0f);
			vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[2].Diffuse = m_Color;
			vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

			vertex[3].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x + (TexSize.x), m_ParentObject->GetPosition().y + (TexSize.y/2), 0.0f);
			vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[3].Diffuse = m_Color;
			vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
		}

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

		if (!m_DrawFlag)
			return;

		TextureContainer::ModelDraw(m_ParentObject->GetTag());
	}
}

