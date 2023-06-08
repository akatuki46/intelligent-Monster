#include "AnimetionDraw2D.h"
#include "TextureContainer.h"
#include "Scene.h"

void AnimetionDraw::Init()
{
	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(SCREEN_RESOLUTION_WIDTH, 0.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f)
		;
	vertex[2].Position = D3DXVECTOR3(0.0f, SCREEN_RESOLUTION_HEIGHT, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(SCREEN_RESOLUTION_WIDTH, SCREEN_RESOLUTION_HEIGHT, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
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
	

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");

	AniDivision = D3DXVECTOR2(1.0f / TextureContainer::GetTextureDivi(m_ParentObject->GetTag()).x,
		1.0f / TextureContainer::GetTextureDivi(m_ParentObject->GetTag()).y);
}

void AnimetionDraw::Uninit()
{
	m_VertexBuffer->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void AnimetionDraw::Update()
{
	if (TextureContainer::GetTextureDivi(m_ParentObject->GetTag()) != D3DXVECTOR2(1.0f, 1.0f))
	{
		//何コマあるか
		m_Division = TextureContainer::GetTextureDivi(m_ParentObject->GetTag()).x * TextureContainer::GetTextureDivi(m_ParentObject->GetTag()).y;

		if (!m_NotAnimetion)
		{
			m_AnimetionCnt++;
			if (m_AnimetionCnt > m_Division)
			{
				m_AnimetionCnt = 0;
				//ループしないなら
				if (m_LoopFlag)
				{
					SetDestroy();
				}
			}
		}
	}
}

void AnimetionDraw::Draw()
{
	if (m_ParentObject->GetTag() != "" && TextureContainer::GetTextureDivi(m_ParentObject->GetTag()) != D3DXVECTOR2(1.0f, 1.0f))
	{
		//テクスチャ座標算出
		float x = m_AnimetionCnt % (int)TextureContainer::GetTextureDivi(m_ParentObject->GetTag()).x * AniDivision.x;
		float y = m_AnimetionCnt / (int)TextureContainer::GetTextureDivi(m_ParentObject->GetTag()).y * AniDivision.y;

		//頂点データ書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0,
			D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		vertex[0].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x, m_ParentObject->GetPosition().y, 0.0f);
		vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].TexCoord = D3DXVECTOR2(x, y);

		vertex[1].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x + TexSize.x, m_ParentObject->GetPosition().y, .0f);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].TexCoord = D3DXVECTOR2(x + AniDivision.x, y)
			;
		vertex[2].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x, m_ParentObject->GetPosition().y + TexSize.y, 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].TexCoord = D3DXVECTOR2(x, y + AniDivision.y);

		vertex[3].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x + TexSize.x, m_ParentObject->GetPosition().y + TexSize.y, 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].TexCoord = D3DXVECTOR2(x + AniDivision.x, y + AniDivision.y);

		//これを書くことにより頂点バッファの書き換えが完了する
		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);


		//入力レイアウト設定
		Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

		//シェーダー設定
		Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
		Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

		//マトリクス設定
		Renderer::SetWorldViewProjection2D();

		TextureContainer::ModelDraw(m_ParentObject->GetTag());
	}
}

