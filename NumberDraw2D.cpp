#include "NumberDraw2D.h"
#include "TextureContainer.h"
#include "Scene.h"
#include "manager.h"

void NumberDraw2D::Init(D3DXVECTOR2 size,int Num, float interval)
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


	//���_�o�b�t�@����
	D3D11_BUFFER_DESC bd{};
	//ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;//��������
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;//��������ς��Ȃ��ƒ��_�o�b�t�@�̏����������o���Ȃ�
											   //�i�e�N�X�`���A�j���[�V�����o���Ȃ��j

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);


	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");

	AniDivision = D3DXVECTOR2(1.0f / TextureContainer::GetTextureDivi(m_ParentObject->GetTag()).x,
		1.0f / TextureContainer::GetTextureDivi(m_ParentObject->GetTag()).y);

	m_Digits = Num;
	m_Interval = interval;
	TexSize = size;
}

void NumberDraw2D::Uninit()
{
	m_VertexBuffer->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void NumberDraw2D::Draw()
{
	if (m_ParentObject->GetTag() != "" && TextureContainer::GetTextureDivi(m_ParentObject->GetTag()) != D3DXVECTOR2(1.0f, 1.0f))
	{
		//�����������ĂȂ���Ε`�悵�Ȃ�
		if (m_NumCnt < 0)
			return;

		int keepNum = m_NumCnt;

		for (int i = 0; i < m_Digits; i++)
		{
			int n = 0;
			n = keepNum % 10;     //���ꌅ�������o

			//�e�N�X�`�����W�Z�o
			float x = n % (int)TextureContainer::GetTextureDivi(m_ParentObject->GetTag()).x * AniDivision.x;
			float y = n / (int)TextureContainer::GetTextureDivi(m_ParentObject->GetTag()).y * AniDivision.y;

			keepNum /= 10;

			//���_�f�[�^��������
			D3D11_MAPPED_SUBRESOURCE msr;
			Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0,
				D3D11_MAP_WRITE_DISCARD, 0, &msr);

			VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

			vertex[0].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x - (m_Interval * i), m_ParentObject->GetPosition().y, 0.0f);
			vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[0].TexCoord = D3DXVECTOR2(x, y);

			vertex[1].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x + TexSize.x - (m_Interval * i), m_ParentObject->GetPosition().y, .0f);
			vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[1].TexCoord = D3DXVECTOR2(x + AniDivision.x, y)
				;
			vertex[2].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x - (m_Interval * i), m_ParentObject->GetPosition().y + TexSize.y, 0.0f);
			vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[2].TexCoord = D3DXVECTOR2(x, y + AniDivision.y);

			vertex[3].Position = D3DXVECTOR3(m_ParentObject->GetPosition().x + TexSize.x - (m_Interval * i), m_ParentObject->GetPosition().y + TexSize.y, 0.0f);
			vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[3].TexCoord = D3DXVECTOR2(x + AniDivision.x, y + AniDivision.y);

			//������������Ƃɂ�蒸�_�o�b�t�@�̏�����������������
			Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);


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

}

void NumberDraw2D::Update()
{
}
