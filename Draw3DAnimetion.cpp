#include "Draw3DAnimetion.h"
#include "Scene.h"
#include "ModelContainer.h"
#include "camera.h"
#include "Scene.h"
#include "manager.h"

void Draw3DAnimetion::Init()
{
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

	m_Name = "Draw3DAnimetion";
}

void Draw3DAnimetion::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Draw3DAnimetion::Draw()
{
	if (m_ParentObject->GetTag() != "")
	{
		Scene* scene = Manager::GetScene();
		GameObject* camera = scene->GetGameObject("Camera", scene->CAMERA_LAYER);
		GameObject* ParentObject = scene->GetGameObject(m_ParentObject->GetParent(), scene->PLAY_LAYER);

		//if (!camera->GetComponent<Camera>()->CheckView(m_ParentObject->m_Position))
		//	return;

		//入力レイアウト設定
		Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

		//シェーダー設定
		Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
		Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

		//ワールドマトリクス設定
		D3DXMatrixScaling(&Scale, m_ParentObject->GetScale().x, m_ParentObject->GetScale().y, m_ParentObject->GetScale().z);
		D3DXMatrixRotationYawPitchRoll(&Rot, m_ParentObject->GetRotation().y, m_ParentObject->GetRotation().x, m_ParentObject->GetRotation().z);
		D3DXMatrixTranslation(&Trans, m_ParentObject->GetPosition().x, m_ParentObject->GetPosition().y, m_ParentObject->GetPosition().z);

		//子供がいるか
		if (ParentObject != nullptr)
		{
			//(子モデルの設定)

			Scale *= ParentObject->GetComponent<Draw3DAnimetion>()->GetScaleMatrix();
			Rot *= ParentObject->GetComponent<Draw3DAnimetion>()->GetRotMatrix();
			Trans *= ParentObject->GetComponent<Draw3DAnimetion>()->GetTransMatrix();

			world = Scale * Rot * Trans;

		}

		world = Scale * Rot * Trans;
		Renderer::SetWorldMatrix(&world);

		ModelContainer::Instance().ModelDraw(m_ParentObject->GetTag());
	}

}

void Draw3DAnimetion::Update()
{
	ModelContainer::Instance().Update(m_ParentObject->GetTag(),
		m_ParentObject->GetAnimetionName(), m_ParentObject->GetNextAnimetionName(), m_BlendRate, m_Frame);

	m_Frame++;
}
