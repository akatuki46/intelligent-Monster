#include "AnimetionDraw2DVer3D.h"
#include "TextureContainer.h"
#include "Scene.h"
#include "manager.h"
#include "camera.h"

ID3D11Buffer* AnimetionDraw2DVer3D::m_VertexBuffer = NULL;

void AnimetionDraw2DVer3D::Init(bool Bilboard)
{
	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f)
		;
	vertex[2].Position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);


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
		"vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

	AniDivision = D3DXVECTOR2(1.0f / TextureContainer::GetTextureDivi(m_ParentObject->GetTag()).x,
		1.0f / TextureContainer::GetTextureDivi(m_ParentObject->GetTag()).y);

	m_Bilboard = Bilboard;
}

void AnimetionDraw2DVer3D::Uninit()
{
	m_VertexBuffer->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}

void AnimetionDraw2DVer3D::Update()
{
	if (TextureContainer::GetTextureDivi(m_ParentObject->GetTag()) != D3DXVECTOR2(1.0f, 1.0f))
	{
		m_Division = TextureContainer::GetTextureDivi(m_ParentObject->GetTag()).x * TextureContainer::GetTextureDivi(m_ParentObject->GetTag()).y;

		m_AnimetionCnt++;
		if (m_AnimetionCnt > m_Division)
		{
			m_AnimetionCnt = 0;
			m_ParentObject->SetDestroy();
			if (m_LoopFlag)
			{

			}
		}
	}
}

void AnimetionDraw2DVer3D::Draw()
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

		vertex[0].Position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
		vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].TexCoord = D3DXVECTOR2(x, y);

		vertex[1].Position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].TexCoord = D3DXVECTOR2(x + AniDivision.x, y)
			;
		vertex[2].Position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].TexCoord = D3DXVECTOR2(x, y + AniDivision.y);

		vertex[3].Position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
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

		if (m_Bilboard)
		{
			//カメラのビューマトリックス取得
			Scene* scene = Manager::GetScene();
			GameObject* camera = scene->GetGameObject("Camera", scene->CAMERA_LAYER);
			D3DXMATRIX view = camera->GetComponent<Camera>()->GetViewMatrix();

			//ビューの逆行列
			D3DXMATRIX invView;
			D3DXMatrixInverse(&invView, NULL, &view);//逆行列
			invView._41 = 0.0f;
			invView._42 = 0.0f;
			invView._43 = 0.0f;

			//ワールドマトリクス設定
			D3DXMATRIX world, scale, trans;
			D3DXMatrixScaling(&scale, m_ParentObject->GetScale().x, m_ParentObject->GetScale().y, m_ParentObject->GetScale().z);
			D3DXMatrixTranslation(&trans, m_ParentObject->GetPosition().x, m_ParentObject->GetPosition().y, m_ParentObject->GetPosition().z);
			world = scale * invView * trans;
			Renderer::SetWorldMatrix(&world);
		}
		else
		{
			//ワールドマトリクス設定
			D3DXMATRIX world, scale, rot, trans;
			D3DXMatrixScaling(&scale, m_ParentObject->GetScale().x, m_ParentObject->GetScale().y, m_ParentObject->GetScale().z);
			D3DXMatrixRotationYawPitchRoll(&rot, m_ParentObject->GetRotation().y, m_ParentObject->GetRotation().x, m_ParentObject->GetRotation().z);
			D3DXMatrixTranslation(&trans, m_ParentObject->GetPosition().x, m_ParentObject->GetPosition().y, m_ParentObject->GetPosition().z);
			world = scale * rot * trans;
			Renderer::SetWorldMatrix(&world);
		}
		
		//頂点バッファ設定
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
		
		//マテリアル設定
		MATERIAL material;
		ZeroMemory(&material, sizeof(material));
		material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		Renderer::SetMaterial(material);

		TextureContainer::ModelDraw(m_ParentObject->GetTag());
	}
}
