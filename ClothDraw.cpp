#include "ClothDraw.h"
#include "TextureContainer.h"
#include "main.h"
#include "manager.h"
#include "Scene.h"
#include "input.h"

//----- �}�N����`
#define F_ZERO(v)			v.x=v.y=v.z=0.0f
#define F_SET(v,px,py,pz)	v.x=px;v.y=py;v.z=pz
#define ATT_COEFFICIENT			(0.5f)			// �����W��(Attenuation)
#define DELTA_TIME				(0.1f)			// �ϕ��P�ʎ���

#define WIND_FORCE_DEF_X		(40.0f)			// ���͂w����
#define WIND_FORCE_DEF_Y		(20.0f)			// ���͂x����
#define WIND_FORCE_DEF_Z		(30.0f)			// ���͂y����

void ClothDraw::Init(D3DXVECTOR3 Offset, D3DXVECTOR3 Wind)
{
	float	xx, yy, zz;				// ���q�Ԃ̋����i�������j
	int		count;					// �o�l�J�E���g�p
	int		i, j;					// ���[�v�J�E���^

	//�e�N�X�`�����W�pfloat�ϐ�
	float texX = PARTICLE_HORIZONTAL;
	float texY = PARTICLE_VERTICAL;

	// ���q�̏�����
	{
		for (j = 0; j <= PARTICLE_HORIZONTAL; j++) {
			for (i = 0; i <= PARTICLE_VERTICAL; i++) {
				// ���W��ݒ�
				g_Cloth.Particle[j][i].position.x = SPRING_DEFAULT_LENGTH * (j + PARTICLE_HORIZONTAL / 2) + Offset.x;
				g_Cloth.Particle[j][i].position.y = SPRING_DEFAULT_LENGTH * (i + 1) + Offset.y;
				g_Cloth.Particle[j][i].position.z = 0.0f;
				F_ZERO(g_Cloth.Particle[j][i].velocity);									// ���x������
				F_ZERO(g_Cloth.Particle[j][i].acceleration);								// �����x������
				F_ZERO(g_Cloth.Particle[j][i].resultant);									// ���͏�����
				F_SET(g_Cloth.Particle[j][i].gravity, 0.0f, SPRING_MASS * -9.8f, 0.0f);		// �d�͏�����
				// ����̗��q�̓��b�N��Ԃ�
				g_Cloth.Particle[j][i].onLock = (j == 0 && (i == 0 || i == PARTICLE_VERTICAL));	// ���b�N
				g_Cloth.Particle[j][i].onDrag = false;					// �h���b�O����ĂȂ�

				vertex[j][i].Position = g_Cloth.Particle[j][i].position;
				vertex[j][i].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				vertex[j][i].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				vertex[j][i].TexCoord = D3DXVECTOR2((float)(j / texX), (float)(i / texY));
			}
		}

		//���_�o�b�t�@����
		D3D11_BUFFER_DESC bd{};
		//ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;//��������
		bd.ByteWidth = sizeof(VERTEX_3D) * ((PARTICLE_VERTICAL + 1) * (PARTICLE_HORIZONTAL + 1));
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;//��������ς��Ȃ��ƒ��_�o�b�t�@�̏����������o���Ȃ�

		D3D11_SUBRESOURCE_DATA sd{};
		//ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = vertex;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	}

	// �o�l�̏�����
	count = 0;
	for (j = 0; j <= PARTICLE_HORIZONTAL; j++) {
		for (i = 0; i <= PARTICLE_VERTICAL; i++) {
			// �o�l�Q�ƃC���f�b�N�X�̐ݒ�
			if (i < PARTICLE_HORIZONTAL) {
				g_Cloth.Spring[count].p1.horz = i;		// �P�ڂ̎Q�Ɨ��q�C���f�b�N�X��ݒ�
				g_Cloth.Spring[count].p1.vert = j;
				g_Cloth.Spring[count].p2.horz = i + 1;	// �Q�ڂ̎Q�Ɨ��q�C���f�b�N�X��ݒ�
				g_Cloth.Spring[count].p2.vert = j;
				// �Q�̗��q�Ԃ̋��������߁A�o�l�̎��R���Ƃ���
				xx = g_Cloth.Particle[j][i].position.x - g_Cloth.Particle[j][i + 1].position.x;
				yy = g_Cloth.Particle[j][i].position.y - g_Cloth.Particle[j][i + 1].position.y;
				zz = g_Cloth.Particle[j][i].position.z - g_Cloth.Particle[j][i + 1].position.z;
				g_Cloth.Spring[count].length = sqrtf(xx * xx + yy * yy + zz * zz);
				count++;
			}
			if (j < PARTICLE_VERTICAL) {
				g_Cloth.Spring[count].p1.horz = i;
				g_Cloth.Spring[count].p1.vert = j;
				g_Cloth.Spring[count].p2.horz = i;
				g_Cloth.Spring[count].p2.vert = j + 1;
				xx = g_Cloth.Particle[j][i].position.x - g_Cloth.Particle[j + 1][i].position.x;
				yy = g_Cloth.Particle[j][i].position.y - g_Cloth.Particle[j + 1][i].position.y;
				zz = g_Cloth.Particle[j][i].position.z - g_Cloth.Particle[j + 1][i].position.z;
				g_Cloth.Spring[count].length = sqrtf(xx * xx + yy * yy + zz * zz);
				count++;
			}
			if (i < PARTICLE_HORIZONTAL && j < PARTICLE_VERTICAL) {
				g_Cloth.Spring[count].p1.horz = i;
				g_Cloth.Spring[count].p1.vert = j;
				g_Cloth.Spring[count].p2.horz = i + 1;
				g_Cloth.Spring[count].p2.vert = j + 1;
				xx = g_Cloth.Particle[j][i].position.x - g_Cloth.Particle[j + 1][i + 1].position.x;
				yy = g_Cloth.Particle[j][i].position.y - g_Cloth.Particle[j + 1][i + 1].position.y;
				zz = g_Cloth.Particle[j][i].position.z - g_Cloth.Particle[j + 1][i + 1].position.z;
				g_Cloth.Spring[count].length = sqrtf(xx * xx + yy * yy + zz * zz);
				count++;
			}
			if (i > 0 && j < PARTICLE_VERTICAL) {
				g_Cloth.Spring[count].p1.horz = i;
				g_Cloth.Spring[count].p1.vert = j;
				g_Cloth.Spring[count].p2.horz = i - 1;
				g_Cloth.Spring[count].p2.vert = j + 1;
				xx = g_Cloth.Particle[j][i].position.x - g_Cloth.Particle[j + 1][i - 1].position.x;
				yy = g_Cloth.Particle[j][i].position.y - g_Cloth.Particle[j + 1][i - 1].position.y;
				zz = g_Cloth.Particle[j][i].position.z - g_Cloth.Particle[j + 1][i - 1].position.z;
				g_Cloth.Spring[count].length = sqrtf(xx * xx + yy * yy + zz * zz);
				count++;
			}
		}
	}

	//���͂̏�����
	{
		g_WindForce.force.x = Wind.x;		// ���͂̏����l��ݒ�
		g_WindForce.force.y = Wind.y;
		g_WindForce.force.z = Wind.z;
	}


	//�C���f�b�N�X�o�b�t�@����
	//�`�揇�Ԃ̎w��
	{
		unsigned int Index[(((PARTICLE_VERTICAL * 2 + 3) * PARTICLE_HORIZONTAL) + (PARTICLE_HORIZONTAL - 2))];

		int i = 0;
		for (int x = 0; x < PARTICLE_HORIZONTAL; x++) {
			for (int y = 0; y <= PARTICLE_VERTICAL; y++) {

				Index[i] = x * (PARTICLE_VERTICAL + 1) + y;
				i++;
				Index[i] = (x + 1) * (PARTICLE_VERTICAL + 1) + y;
				i++;
			}
			if (x == PARTICLE_HORIZONTAL -1)
				break;
			
			Index[i] = (x + 1) * (PARTICLE_VERTICAL + 1) + PARTICLE_VERTICAL;
			i++;
			Index[i] = (x + 1) * (PARTICLE_VERTICAL + 1);
			i++;
			
		}


		//���_�o�b�t�@����
		D3D11_BUFFER_DESC bd{};
		//ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(unsigned int) * (((PARTICLE_VERTICAL * 2 + 3) * PARTICLE_HORIZONTAL) + (PARTICLE_HORIZONTAL - 2));
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA sd{};
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = Index;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer);
	}

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");

	m_Name = "ClothDraw";
}

void ClothDraw::Uninit()
{
	m_VertexBuffer->Release();
	m_IndexBuffer->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void ClothDraw::Update()
{
	D3DXVECTOR3	vec_spr;				// ���q�Q�_�Ԃ̃x�N�g��
	D3DXVECTOR3	resistance;				// ��R�̓x�N�g��
	D3DXVECTOR3	windforce;				// ���̓x�N�g��
	float	f1, f2;					// �o�l�����q�ɗ^����́i�Q��j
	int		h1, v1, h2, v2;			// �o�l�[�ɂ��闱�q�̃C���f�b�N�X�i���A�c�ʂQ���j
	float	f1x, f1y, f1z;			// ��������o�l�ɔ��������
	float	f2x, f2y, f2z;
	float	length;					// ���q�Ԃ̋���
	float	xx, yy, zz;				// ���q�Ԃ̋����i�������j
	int		count;					// �o�l�J�E���g�p
	int		i, j;					// ���[�v�J�E���^

	//���͕����̕ύX
	if (GetKeyboardPress(DIK_UP)) g_WindForce.force.y -= 1.0f;	// �J�[�\���L�[�ŕ��͂�ς���
	if (GetKeyboardPress(DIK_DOWN)) g_WindForce.force.y += 1.0f;
	if (GetKeyboardPress(DIK_LEFT)) g_WindForce.force.x -= 1.0f;
	if (GetKeyboardPress(DIK_RIGHT)) g_WindForce.force.x += 1.0f;


	// ���q�̏���
	for (j = 0; j <= PARTICLE_VERTICAL; j++) {
		for (i = 0; i <= PARTICLE_HORIZONTAL; i++) {
			// ���͂��O�ɂ���
			g_Cloth.Particle[j][i].resultant.x = 0;
			g_Cloth.Particle[j][i].resultant.y = 0;
			g_Cloth.Particle[j][i].resultant.z = 0;

			if (!g_Cloth.Particle[j][i].onLock && !g_Cloth.Particle[j][i].onDrag) {
				// �d�͂����߂�
				F_SET(g_Cloth.Particle[j][i].gravity, 0.0f, SPRING_MASS * -9.8f, 0.0f);	// �d��

				// ��R�͂����߂�
				resistance.x = -g_Cloth.Particle[j][i].velocity.x * ATT_COEFFICIENT;
				resistance.y = -g_Cloth.Particle[j][i].velocity.y * ATT_COEFFICIENT;
				resistance.z = -g_Cloth.Particle[j][i].velocity.z * ATT_COEFFICIENT;

				// ���͂����߂�
				windforce.x = g_WindForce.force.x + (float)(rand() % 30 - 15);		// �w����
				windforce.y = g_WindForce.force.y + (float)(rand() % 30 - 15);		// �x����
				windforce.z = g_WindForce.force.z + (float)(rand() % 30 - 15);		// �y����
				
				// ���́��d�́{��R�́{����
				g_Cloth.Particle[j][i].resultant.x = g_Cloth.Particle[j][i].gravity.x + resistance.x + windforce.x;
				g_Cloth.Particle[j][i].resultant.y = g_Cloth.Particle[j][i].gravity.y + resistance.y + windforce.y;
				g_Cloth.Particle[j][i].resultant.z = g_Cloth.Particle[j][i].gravity.z + resistance.z + windforce.z;
			}
		}
	}

	// �o�l�̏���
	for (i = 0; i < SPRING_NUMS; i++) {
		// �o�l�̎Q�Ɨ��q�i�Q�j���擾
		h1 = g_Cloth.Spring[i].p1.horz;
		v1 = g_Cloth.Spring[i].p1.vert;
		h2 = g_Cloth.Spring[i].p2.horz;
		v2 = g_Cloth.Spring[i].p2.vert;
		// �Q�̗��q�Ԃ̃x�N�g�������߂�
		vec_spr.x = g_Cloth.Particle[v1][h1].position.x - g_Cloth.Particle[v2][h2].position.x;
		vec_spr.y = g_Cloth.Particle[v1][h1].position.y - g_Cloth.Particle[v2][h2].position.y;
		vec_spr.z = g_Cloth.Particle[v1][h1].position.z - g_Cloth.Particle[v2][h2].position.z;
		// ���q�Ԃ̋��������߂�
		length = sqrtf(vec_spr.x * vec_spr.x + vec_spr.y * vec_spr.y + vec_spr.z * vec_spr.z);
		// �����A���R���A�o�l�W�����炩����͂����߂�i�Q�ڂ͋t�����j
		f1 = -SPRING_COEFFICIENT * (length - g_Cloth.Spring[i].length);
		f2 = -f1;
		// �x�N�g���̐����ɗ͂�������
		f1x = f1 * (vec_spr.x / length);
		f1y = f1 * (vec_spr.y / length);
		f1z = f1 * (vec_spr.z / length);
		f2x = f2 * (vec_spr.x / length);
		f2y = f2 * (vec_spr.y / length);
		f2z = f2 * (vec_spr.z / length);
		// ���߂��͂����͂ɉ�����
		g_Cloth.Particle[v1][h1].resultant.x += f1x;
		g_Cloth.Particle[v1][h1].resultant.y += f1y;
		g_Cloth.Particle[v1][h1].resultant.z += f1z;
		g_Cloth.Particle[v2][h2].resultant.x += f2x;
		g_Cloth.Particle[v2][h2].resultant.y += f2y;
		g_Cloth.Particle[v2][h2].resultant.z += f2z;
	}

	for (j = 0; j <= PARTICLE_VERTICAL; j++) {
		for (i = 0; i <= PARTICLE_HORIZONTAL; i++) {
			// �Œ肳��Ă���΃X�L�b�v
			if (g_Cloth.Particle[j][i].onLock || g_Cloth.Particle[j][i].onDrag) continue;

			// ���͂Ǝ��ʂ�������x�����߂�
			g_Cloth.Particle[j][i].acceleration.x = g_Cloth.Particle[j][i].resultant.x / SPRING_MASS;
			g_Cloth.Particle[j][i].acceleration.y = g_Cloth.Particle[j][i].resultant.y / SPRING_MASS;
			//g_Cloth.Particle[j][i].acceleration.z = g_Cloth.Particle[j][i].resultant.z / SPRING_MASS;

			// ���x�ɉ����x��������
			g_Cloth.Particle[j][i].velocity.x += g_Cloth.Particle[j][i].acceleration.x * DELTA_TIME;
			g_Cloth.Particle[j][i].velocity.y += g_Cloth.Particle[j][i].acceleration.y * DELTA_TIME;
			//g_Cloth.Particle[j][i].velocity.z += g_Cloth.Particle[j][i].acceleration.z * DELTA_TIME;

			// ���x������W���ړ�
			g_Cloth.Particle[j][i].position.x += g_Cloth.Particle[j][i].velocity.x * DELTA_TIME;
			g_Cloth.Particle[j][i].position.y += g_Cloth.Particle[j][i].velocity.y * DELTA_TIME;
			//g_Cloth.Particle[j][i].position.z += g_Cloth.Particle[j][i].velocity.z * DELTA_TIME;

			vertex[j][i].Position = g_Cloth.Particle[j][i].position;
		}
	}
}

void ClothDraw::Draw()
{

//#ifdef _DEBUG
//
//	if (!m_ImGuiDrawFlag)
//		return;
//
//	ImGui::Begin("Test ImGui", &m_ImGuiDrawFlag);
//	ImGui::Text("TestrComplete");
//	if (ImGui::TreeNode("TestPosition"))
//	{
//
//		for (int j = 0; j <= PARTICLE_HORIZONTAL; j++) {
//			for (int i = 0; i <= PARTICLE_VERTICAL; i++) {
//				ImGui::Text("(%d:%d)  x:%f  y:%f  z;%f", j,i, g_Cloth.Particle[j][i].position.x, g_Cloth.Particle[j][i].position.y, g_Cloth.Particle[j][i].position.z);
//
//			}
//		}
//
//		ImGui::TreePop();
//		ImGui::Separator();
//	}
//
//
//	ImGui::End();
//
//#endif // !_DEBUG

	//���_�f�[�^��������
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0,
		D3D11_MAP_WRITE_DISCARD, 0, &msr);

	//VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;
	memcpy(msr.pData, vertex, sizeof(VERTEX_3D) * ((PARTICLE_VERTICAL + 1) * (PARTICLE_HORIZONTAL + 1)));


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

	//�C���f�b�N�X�o�b�t�@�ݒ�
	Renderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	TextureContainer::ModelDrawIndex(m_ParentObject->GetTag(), (((PARTICLE_VERTICAL * 2 + 3) * PARTICLE_HORIZONTAL) + (PARTICLE_HORIZONTAL - 2)));
}
