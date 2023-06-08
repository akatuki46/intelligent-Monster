//////////////////////////////////////////////////////////////////////////////////////////////////
//  3D空間用　2D描画コンポーネント
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "Draw2DVer3D.h"
#include "TextureContainer.h"
#include "Scene.h"
#include "manager.h"
#include "camera.h"

ID3D11Buffer* Draw2DVer3D::m_VertexBuffer = NULL;

void Draw2DVer3D::Init(D3DXVECTOR3 size, float texcode, bool Bilboard)
{
	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x - size.x, m_ParentObject->GetPosition().y, size.z);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x + size.x, m_ParentObject->GetPosition().y, size.z);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(texcode, 0.0f)
		;
	vertex[2].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x - size.x, m_ParentObject->GetPosition().y + size.y, -size.z);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, texcode);

	vertex[3].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x + size.x, m_ParentObject->GetPosition().y + size.y, -size.z);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(texcode, texcode);


	//頂点バッファ生成
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);


	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

	m_Bilboard = Bilboard;
}

void Draw2DVer3D::Uninit()
{
	m_VertexBuffer->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}

void Draw2DVer3D::Update()
{
}

void Draw2DVer3D::Draw()
{
	if (m_ParentObject->GetTag() != "" && TextureContainer::GetTextureDivi(m_ParentObject->GetTag()) == D3DXVECTOR2(1.0f, 1.0f))
	{

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

		//マテリアル設定
		MATERIAL material;
		ZeroMemory(&material, sizeof(material));
		material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		Renderer::SetMaterial(material);

		//頂点バッファ設定
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);


		TextureContainer::ModelDraw(m_ParentObject->GetTag());
	}
}
