//////////////////////////////////////////////////////////////////////////////////////////////////
//  �w�i�p�@�ړ��A�T�C�Y�Œ�@2D�`��R���|�[�l���g
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "Draw2DAction.h"
#include "TextureContainer.h"
#include "Scene.h"
#include "manager.h"

void Draw2DAction::Init(D3DXVECTOR3 size)
{
	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x, m_ParentObject->GetPosition().y, size.z);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x + size.x, m_ParentObject->GetPosition().y, size.z);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f)
		;
	vertex[2].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x, m_ParentObject->GetPosition().y + size.y, -size.z);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x + size.x, m_ParentObject->GetPosition().y + size.y, -size.z);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);


	//���_�o�b�t�@����
	D3D11_BUFFER_DESC bd{};
	//ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;//��������
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;//��������ς��Ȃ��ƒ��_�o�b�t�@�̏����������o���Ȃ�

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);


	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");

	m_Size = size;

	m_Name = "Draw2DAction";
}

void Draw2DAction::Uninit()
{
	m_VertexBuffer->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Draw2DAction::Update()
{
}

void Draw2DAction::Draw()
{



	if (m_ParentObject->GetTag() != "" && TextureContainer::GetTextureDivi(m_ParentObject->GetTag()) == D3DXVECTOR2(1.0f, 1.0f) && m_DrawFlag)
	{
		Scene* scene = Manager::GetScene();
		GameObject* ParentObject = scene->GetGameObject(m_ParentObject->GetParent(), scene->UI_LAYER);
		if (ParentObject != nullptr)
		{
			//�e������@�Ǐ]�`��

			D3DXVECTOR3 childPos = ParentObject->GetPosition() - m_ParentObject->GetInteval();
			m_ParentObject->GetPosition() = childPos;
			//���_�f�[�^��������
			D3D11_MAPPED_SUBRESOURCE msr;
			Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0,
				D3D11_MAP_WRITE_DISCARD, 0, &msr);

			VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

			vertex[0].Position = D3DXVECTOR3(childPos.x, childPos.y, m_Size.z);
			vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

			vertex[1].Position = D3DXVECTOR3(childPos.x + m_Size.x, childPos.y, m_Size.z);
			vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f)
				;
			vertex[2].Position = D3DXVECTOR3(childPos.x, childPos.y + m_Size.y, -m_Size.z);
			vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

			vertex[3].Position = D3DXVECTOR3(childPos.x + m_Size.x, childPos.y + m_Size.y, -m_Size.z);
			vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);


			//������������Ƃɂ�蒸�_�o�b�t�@�̏�����������������
			Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

#ifdef _DEBUG

			if (!m_ImGuiDrawFlag)
				return;

			ImGui::Begin("Test ImGui", &m_ImGuiDrawFlag);
			ImGui::Text("TestrComplete");
			if (ImGui::TreeNode("TestPosition"))
			{
				ImGui::Text("X:%f Y:%f Z:%f", childPos.x, childPos.y, childPos.z);

				ImGui::TreePop();
				ImGui::Separator();
			}


			ImGui::End();

#endif // !_DEBUG

		}
		else //�e�����Ȃ��@�ʏ�̕`��
		{
			//���_�f�[�^��������
			D3D11_MAPPED_SUBRESOURCE msr;
			Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0,
				D3D11_MAP_WRITE_DISCARD, 0, &msr);

			VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

			vertex[0].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x, m_ParentObject->GetPosition().y, m_Size.z);
			vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

			vertex[1].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x + m_Size.x, m_ParentObject->GetPosition().y, m_Size.z);
			vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f)
				;
			vertex[2].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x, m_ParentObject->GetPosition().y + m_Size.y, -m_Size.z);
			vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

			vertex[3].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x + m_Size.x, m_ParentObject->GetPosition().y + m_Size.y, -m_Size.z);
			vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);


			//������������Ƃɂ�蒸�_�o�b�t�@�̏�����������������
			Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

		}



		//���̓��C�A�E�g�ݒ�
		Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

		//�V�F�[�_�[�ݒ�
		Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
		Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

		//�}�g���N�X�ݒ�
		Renderer::SetWorldViewProjection2D();

		//���_�o�b�t�@�ݒ�
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);


		TextureContainer::ModelDraw(m_ParentObject->GetTag());
	}



}

