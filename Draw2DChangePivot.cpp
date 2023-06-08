#include "Draw2DChangePivot.h"
#include "TextureContainer.h"
#include "Scene.h"
#include "manager.h"

void Draw2DChangePivot::Init(D3DXVECTOR3 Size, D3DXVECTOR4 color, int mode)
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

void Draw2DChangePivot::Uninit()
{
	m_VertexBuffer->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Draw2DChangePivot::Update()
{

}

void Draw2DChangePivot::Draw()
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

		switch (m_DrawMode)
		{
		case LEFT_TOP:
			vertex[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[0].Diffuse = m_Color;
			vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

			vertex[1].Position = D3DXVECTOR3(+(TexSize.x), 0.0f, 0.0f);
			vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[1].Diffuse = m_Color;
			vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f)
				;
			vertex[2].Position = D3DXVECTOR3(0.0f, + (TexSize.y), 0.0f);
			vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[2].Diffuse = m_Color;
			vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

			vertex[3].Position = D3DXVECTOR3(+(TexSize.x), + (TexSize.y), 0.0f);
			vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[3].Diffuse = m_Color;
			vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
			break;
		case LEFT_CENTER:
			vertex[0].Position = D3DXVECTOR3(0.0f, - (TexSize.y / 2), 0.0f);
			vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[0].Diffuse = m_Color;
			vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

			vertex[1].Position = D3DXVECTOR3(+(TexSize.x),  - (TexSize.y / 2), 0.0f);
			vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[1].Diffuse = m_Color;
			vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f)
				;
			vertex[2].Position = D3DXVECTOR3(0.0f, + (TexSize.y / 2), 0.0f);
			vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[2].Diffuse = m_Color;
			vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

			vertex[3].Position = D3DXVECTOR3(+(TexSize.x),+ (TexSize.y / 2), 0.0f);
			vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[3].Diffuse = m_Color;
			vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
			break;
		case CENTER_CENTER:
			vertex[0].Position = D3DXVECTOR3(- (TexSize.x / 2), -(TexSize.y / 2), 0.0f);
			vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[0].Diffuse = m_Color;
			vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

			vertex[1].Position = D3DXVECTOR3(+ (TexSize.x / 2), -(TexSize.y / 2), 0.0f);
			vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[1].Diffuse = m_Color;
			vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f)
				;
			vertex[2].Position = D3DXVECTOR3(- (TexSize.x / 2), +(TexSize.y / 2), 0.0f);
			vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[2].Diffuse = m_Color;
			vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

			vertex[3].Position = D3DXVECTOR3(+ (TexSize.x / 2), +(TexSize.y / 2), 0.0f);
			vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[3].Diffuse = m_Color;
			vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
			break;
		case CENTER_BUTTOM:
			vertex[0].Position = D3DXVECTOR3(- (TexSize.x / 2), - (TexSize.y), 0.0f);
			vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[0].Diffuse = m_Color;
			vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

			vertex[1].Position = D3DXVECTOR3(+ (TexSize.x / 2), - (TexSize.y), 0.0f);
			vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[1].Diffuse = m_Color;
			vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f)
				;
			vertex[2].Position = D3DXVECTOR3(- (TexSize.x / 2),0.0f , 0.0f);
			vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[2].Diffuse = m_Color;
			vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

			vertex[3].Position = D3DXVECTOR3(+ (TexSize.x / 2), 0.0f , 0.0f);
			vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[3].Diffuse = m_Color;
			vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
			break;
		default:
			break;
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

		//ワールドマトリクス設定
		//vertexの数値にポジションを加算するイメージ
		D3DXMATRIX world, rot, trans;
		D3DXMatrixRotationYawPitchRoll(&rot, m_ParentObject->GetRotation().y, m_ParentObject->GetRotation().x, m_ParentObject->GetRotation().z);
		D3DXMatrixTranslation(&trans, m_ParentObject->GetPosition().x, m_ParentObject->GetPosition().y, m_ParentObject->GetPosition().z);
		world = rot * trans;
		Renderer::SetWorldMatrix(&world);

		//頂点バッファ設定
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);


		TextureContainer::ModelDraw(m_ParentObject->GetTag());
	}
}

