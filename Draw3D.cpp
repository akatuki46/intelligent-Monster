#include "Draw3D.h"
#include "Scene.h"
#include "ModelContainer.h"
#include "camera.h"
#include "Scene.h"
#include "manager.h"

void Draw3D::Init()
{
	Renderer::CreateVertexShader(&m_VertexShader[0], &m_VertexLayout,
		"vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader[0], "vertexLightingPS.cso");

	Renderer::CreateVertexShader(&m_VertexShader[1], &m_VertexLayout,
		"RimLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader[1], "RimLightingPS.cso");

	Renderer::CreateVertexShader(&m_VertexShader[2], &m_VertexLayout,
		"RimLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader[2], "SuperChargePS.cso");


	m_Name = "Draw3D";
}

void Draw3D::Uninit()
{
	m_VertexLayout->Release();

	for (int i = 0; i < 3; i++)
	{
		m_VertexShader[i]->Release();
		m_PixelShader[i]->Release();

	}
}

void Draw3D::Draw()
{
	if (m_ParentObject->GetTag() != "")
	{


		Scene* scene = Manager::GetScene();
		GameObject* camera = scene->GetGameObject("Camera", scene->CAMERA_LAYER);
		GameObject* ParentObject = scene->GetGameObject(m_ParentObject->GetParent(), scene->PLAY_LAYER);

		//if (!camera->GetComponent<Camera>()->CheckView(m_ParentObject->m_Position))
		//	return;

		//���̓��C�A�E�g�ݒ�
		Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

		//�V�F�[�_�[�ݒ�
		Renderer::GetDeviceContext()->VSSetShader(m_VertexShader[m_ShaderFlg], NULL, 0);
		Renderer::GetDeviceContext()->PSSetShader(m_PixelShader[m_ShaderFlg], NULL, 0);

		//���[���h�}�g���N�X�ݒ�
		D3DXMatrixScaling(&Scale, m_ParentObject->GetScale().x, m_ParentObject->GetScale().y, m_ParentObject->GetScale().z);
		D3DXMatrixRotationYawPitchRoll(&Rot, m_ParentObject->GetRotation().y, m_ParentObject->GetRotation().x, m_ParentObject->GetRotation().z);
		D3DXMatrixTranslation(&Trans, m_ParentObject->GetPosition().x, m_ParentObject->GetPosition().y, m_ParentObject->GetPosition().z);

		D3DXMATRIX parent;
		//�e�����邩
		if (ParentObject != nullptr)
		{
			//(�q���f���̐ݒ�)

			//Scale *= ParentObject->GetComponent<Draw3D>()->GetScaleMatrix();
			//Rot *= ParentObject->GetComponent<Draw3D>()->GetRotMatrix();
			//Trans *= ParentObject->GetComponent<Draw3D>()->GetTransMatrix();

			parent = ParentObject->GetComponent<Draw3D>()->GetWorldMatrix();

			world = Scale * Rot * Trans * parent;
		}
		else
		{
			world = Scale * Rot * Trans;
		}


		Renderer::SetWorldMatrix(&world);

		//�����ɕ`�悷�邩���Ȃ�����u���Ă���̂́A�e�q�֌W�̂��߂̍s��ϊ��͂��Ăق�������
		if (!m_DrawFlag)
			return;

		ModelContainer::Instance().ModelDraw(m_ParentObject->GetTag());
	}
}

void Draw3D::Update()
{

}