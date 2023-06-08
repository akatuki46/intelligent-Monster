#include "FadeDraw2D.h"
#include "manager.h"
#include "Scene.h"
#include "Transition.h"
#include "TextureContainer.h"

void FadeDraw2D::Init(int mode, D3DXVECTOR3 color)
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

	m_mode = (FALDEMODE)mode;
	m_FadeColor = color;

}

void FadeDraw2D::Uninit()
{
	m_VertexBuffer->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void FadeDraw2D::Update()
{
	Scene* scene = Manager::GetScene();
	Transition* trans = m_ParentObject->GetComponent<Transition>();

	float cnt = trans->GetCount();
	float max = trans->GetTransMax();


	if (trans)
	{
		if (trans->GetStart() && !trans->GetInFinish())
		{
			//だんだん明るく
			if (m_mode == FALDEMODE::Alfa)
			{				
				alfa = 1.0f;

				AlfaRot = 1.0f / trans->GetTransMax();

				m_Count = trans->GetTransMax() - trans->GetCount();

				alfa = alfa - (m_Count * AlfaRot);
				cnt++;
			}
			//紙芝居 シャッターが上がる
			else if(m_mode == FALDEMODE::Move)
			{
				m_MovePos.y = (float)((cnt / max) - 1.0f) * SCREEN_RESOLUTION_HEIGHT;
			}
		}
		else if (!trans->GetStart() && !trans->GetOutFinish())
		{
			//だんだん暗く
			if (m_mode == FALDEMODE::Alfa)
			{
				alfa = 0.0f;

				AlfaRot = 1.0f / trans->GetTransMax();

				m_Count = trans->GetTransMax() - trans->GetCount();

				alfa = m_Count * AlfaRot;

			}
			//紙芝居 シャッターが下がる
			else if (m_mode == FALDEMODE::Move)
			{
				m_MovePos.y = (1.0f - cnt / max) * -SCREEN_RESOLUTION_HEIGHT;
			}
		}
	}

}

void FadeDraw2D::Draw()
{
	if (m_ParentObject->GetTag() != "" && TextureContainer::GetTextureDivi(m_ParentObject->GetTag()) == D3DXVECTOR2(1.0f, 1.0f))
	{
		//頂点データ書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0,
			D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		vertex[0].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x + m_MovePos.x, m_ParentObject->GetPosition().y + m_MovePos.y, 0.0f);
		vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[0].Diffuse = D3DXVECTOR4(m_FadeColor.x, m_FadeColor.y, m_FadeColor.z, alfa);
		vertex[0].TexCoord = D3DXVECTOR2(0, 0);

		vertex[1].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x + m_MovePos.x + SCREEN_RESOLUTION_WIDTH, m_ParentObject->GetPosition().y + m_MovePos.y, .0f);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[1].Diffuse = D3DXVECTOR4(m_FadeColor.x, m_FadeColor.y, m_FadeColor.z, alfa);
		vertex[1].TexCoord = D3DXVECTOR2(0, 1)
			;
		vertex[2].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x + m_MovePos.x, m_ParentObject->GetPosition().y + m_MovePos.y + SCREEN_RESOLUTION_HEIGHT, 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[2].Diffuse = D3DXVECTOR4(m_FadeColor.x, m_FadeColor.y, m_FadeColor.z, alfa);
		vertex[2].TexCoord = D3DXVECTOR2(1, 0);

		vertex[3].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x + m_MovePos.x + SCREEN_RESOLUTION_WIDTH, m_ParentObject->GetPosition().y + m_MovePos.y + SCREEN_RESOLUTION_HEIGHT, 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[3].Diffuse = D3DXVECTOR4(m_FadeColor.x, m_FadeColor.y, m_FadeColor.z, alfa);
		vertex[3].TexCoord = D3DXVECTOR2(1,1);

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


		TextureContainer::ModelDraw(m_ParentObject->GetTag());
	}
}