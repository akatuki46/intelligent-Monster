#include "MeshFieldDraw.h"
#include "TextureContainer.h"
#include "Scene.h"
#include "manager.h"

float g_FieldHeight[MeshFieldDraw::Field_Z_Size + 1][MeshFieldDraw::Field_X_Size + 1] =
{ {0.0f,1.0f,2.0f,4.0f,2.0f,1.0f,0.0f,1.0f,2.0f,4.0f,2.0f,1.0f,0.0f,1.0f,2.0f,4.0f,2.0f,1.0f,0.0f,1.0f,2.0f},
  {0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f},
  {0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f},
  {0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f},
  {0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f},
  {0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f},
  {0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f},
  {0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f},
  {0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f},
  {0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f},
  {0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f},
  {0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f},
  {0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f},
  {0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f},
  {0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f},
  {0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f},
  {0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f},
  {0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f},
  {0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f},
  {0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f,0.0f,0.5f,1.0f,0.0f,1.0f,0.5f},
  {0.0f,1.0f,2.0f,4.0f,2.0f,1.0f,0.0f,1.0f,2.0f,4.0f,2.0f,1.0f,0.0f,1.0f,2.0f,4.0f,2.0f,1.0f,0.0f,1.0f,2.0f}, };


void MeshFieldDraw::Init(int Direction)
{
	m_Direction = Direction;

	for (int x = 0; x <= FIELD_X_SIZE; x++)
	{
		for (int z = 0; z <= FIELD_Z_SIZE; z++)
		{
			g_FieldHeight[x][z] = Manager::randomfloat(-0.5f, 0.5f);
			
			if ((x == 0 || x == FIELD_X_SIZE) ||
				(z == 0 || z == FIELD_Z_SIZE))
			{
				g_FieldHeight[x][z] = 4.0f;
			}
			

		}
	}


	//���_�o�b�t�@����
	{
		for (int x = 0; x <= FIELD_X_SIZE; x++)
		{
			for (int z = 0; z <= FIELD_Z_SIZE; z++)
			{
				float y = g_FieldHeight[x][z];
				m_Vertex[x][z].Position = D3DXVECTOR3((x - (FIELD_X_SIZE/2)) * m_Direction, y, (z - (FIELD_Z_SIZE/2)) * -m_Direction);
				m_Vertex[x][z].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				m_Vertex[x][z].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				m_Vertex[x][z].TexCoord = D3DXVECTOR2(x * 0.5f, z * 0.5f);


			}
		}


		D3D11_BUFFER_DESC bd{};
		//ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3D) * ((FIELD_X_SIZE + 1) * (FIELD_Z_SIZE + 1));
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd{};
		//ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = m_Vertex;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	}

	//�@���x�N�g���Z�o
	{
		for (int x = 1; x < FIELD_X_SIZE; x++)
		{
			for (int z = 1; z < FIELD_Z_SIZE; z++)
			{
				D3DXVECTOR3 vx, vz, vn;
				vx = m_Vertex[x + 1][z].Position - m_Vertex[x - 1][z].Position;
				vz = m_Vertex[x][z - 1].Position - m_Vertex[x][z + 1].Position;

				D3DXVec3Cross(&vn, &vz, &vx);//�O��
				D3DXVec3Normalize(&vn, &vn);//���K���i����1�ɂ���j
				m_Vertex[x][z].Normal = vn;
			}
		}
	}

	//�C���f�b�N�X�o�b�t�@����
	//�`�揇�Ԃ̎w��
	{
		unsigned int index[(((FIELD_Z_SIZE * 2 + 3) * FIELD_X_SIZE) + (FIELD_X_SIZE - 2))];

		int i = 0;
		for (int x = 0; x < FIELD_X_SIZE; x++)
		{
			for (int z = 0; z <= FIELD_Z_SIZE ; z++)
			{
				index[i] = x * (FIELD_Z_SIZE + 1) + z;
				i++;

				index[i] = (x + 1) * (FIELD_Z_SIZE + 1) + z;
				i++;
			}

			if (x == FIELD_X_SIZE - 1)
				break;

			index[i] = (x + 1) * (FIELD_Z_SIZE + 1) + FIELD_Z_SIZE;
			i++;

			index[i] = (x + 1) * (FIELD_Z_SIZE + 1);
			i++;
		}


		//���_�o�b�t�@����
		D3D11_BUFFER_DESC bd{};
		//ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned int) * (((FIELD_Z_SIZE * 2 + 3) * FIELD_X_SIZE) + (FIELD_X_SIZE - 2));
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd{};
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = index;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer);
	}



	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

}

void MeshFieldDraw::Uninit()
{
	m_VertexBuffer->Release();
	m_IndexBuffer->Release();


	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void MeshFieldDraw::Update()
{
}

void MeshFieldDraw::Draw()
{
	//���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//�V�F�[�_�[�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);


	//���[���h�}�g���N�X�ݒ�
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_ParentObject->GetScale().x, m_ParentObject->GetScale().y, m_ParentObject->GetScale().z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_ParentObject->GetRotation().y, m_ParentObject->GetRotation().x, m_ParentObject->GetRotation().z);
	D3DXMatrixTranslation(&trans, m_ParentObject->GetPosition().x, m_ParentObject->GetPosition().y, m_ParentObject->GetPosition().z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);


	//���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//�C���f�b�N�X�o�b�t�@�ݒ�
	Renderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	//�}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Renderer::SetMaterial(material);

	//�v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//
	TextureContainer::ModelDrawIndex(m_ParentObject->GetTag(), (((FIELD_Z_SIZE * 2 + 3) * FIELD_X_SIZE) + (FIELD_X_SIZE - 2)));
}

//���b�V���t�B�[���h�Փ˔���
float MeshFieldDraw::GetHeight(D3DXVECTOR3 pos)
{
	int x, z;

	//�u���b�N�ԍ��Z�o
	//�ǂ��̃u���b�N�Ƀv���C���[�͂��邩
	x = pos.x / m_Direction + (FIELD_X_SIZE / 2);
	z = pos.z / -m_Direction + (FIELD_Z_SIZE / 2);

	//�u���b�N�͊m��
	//�u���b�N��2�̎O�p�`�|���S���̂ǂ���ɂ��邩
	//�u���b�N�̒��_�ʒu���
	D3DXVECTOR3 pos0, pos1, pos2, pos3;

	pos0 = m_Vertex[x][z].Position;
	pos1 = m_Vertex[x + 1][z].Position;
	pos2 = m_Vertex[x][z + 1].Position;
	pos3 = m_Vertex[x + 1][z + 1].Position;

	//2�̎O�p�`�̂ǂ���ɂ��邩�O�ς�p���ċ��߂�
	D3DXVECTOR3 v12, v1p, c;

	//2�̎O�p�`�𕪂��x�N�g��
	v12 = pos2 - pos1;

	//pos���璸�_�܂ł̃x�N�g��
	v1p = pos - pos1;

	//�O�όv�Z���Ăǂ���ɂ��邩����
	D3DXVec3Cross(&c, &v12, &v1p);

	float py;

	D3DXVECTOR3 n;

	//���茋��
	if (c.y > 0.0f)
	{
		//����|���S��
		D3DXVECTOR3 v10;
		v10 = pos0 - pos1;
		D3DXVec3Cross(&n, &v10, &v12);
	}
	else
	{

		//�E���|���S��
		D3DXVECTOR3 v13;
		v13 = pos3 - pos1;
		D3DXVec3Cross(&n, &v12, &v13);

	}

	//�����擾
	py = -((pos.x - pos1.x) * n.x
		+ (pos.z - pos1.z) * n.z) / n.y + pos1.y;

	return py;

}
