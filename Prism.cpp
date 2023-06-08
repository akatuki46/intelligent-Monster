#include "Prism.h"
#include "main.h"
#include "renderer.h"
#include "Scene.h"
#include "camera.h"
#include "manager.h"
#include "input.h"
#include "TextureContainer.h"

#define	VALUE_MOVE		(5.0f)						// �ړ���
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)			// ��]��

//----- �v���Y���ʃ��f����`
//�@�i���Ӂj�@���x�N�g���A�e�N�X�`�����W�͌v�Z�ŋ��߂�
static VERTEX_3D prism_vertex[] = {
	//	Position						Normal				Diffuse						TexCoord
	{	{   0.0f,    0.0f, -0.5f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// ���_�O�@�ʂO�i�E��j
	{	{   2.5f,    0.0f,  0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// ���_�P
	{	{   0.0f,    2.5f,  0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// ���_�Q

	{	{   0.0f,    0.0f, -0.5f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// ���_�O�@�ʂP�i�E���j
	{	{   0.0f,    2.5f,  0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// ���_�P
	{	{  -2.5f,    0.0f,  0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// ���_�Q

	{	{   0.0f,    0.0f,  -0.5f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// ���_�O�@�ʂQ�i�����j
	{	{  -2.5f,    0.0f,   0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// ���_�P
	{	{   0.0f,   -2.5f,   0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// ���_�Q

	{	{   0.0f,    0.0f, -0.5f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// ���_�O�@�ʂR�i����j
	{	{   2.5f,    0.0f,   0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// ���_�P
	{	{   0.0f,   -2.5f,   0.0f},	{0.0f, 0.0f, 0.0f},	{1.0f, 1.0f, 1.0f, 1.0f},	{0.0f, 0.0f} },	// ���_�Q
};

void Prism::Init()
{


	//���_�o�b�t�@����
	D3D11_BUFFER_DESC bd{};
	//ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;//��������
	bd.ByteWidth = sizeof(VERTEX_3D) * 12;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;//��������ς��Ȃ��ƒ��_�o�b�t�@�̏����������o���Ȃ�

	D3D11_SUBRESOURCE_DATA sd{};
	//ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = prism_vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &g_VertexBuffer);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");

	// ���f���p�x�A�ʒu�̏�����
	g_Prism.rotation = { 0, 0, 0 };
	g_Prism.position = { 0, 0, 0 };

	D3DXVECTOR3		v0, v1, v2;				// �v���Y���ʂ̖@���x�N�g���v�Z�p

	// �v���Y���ʂ̖@���x�N�g�����v�Z�E�ݒ�
	for (int i = 0; i < 4; i++)
	{
		v0 = prism_vertex[i * 3 + 1].Position - prism_vertex[i * 3].Position;
		v1 = prism_vertex[i * 3 + 2].Position - prism_vertex[i * 3].Position;
		D3DXVec3Cross(&v2, &v0, &v1);
		D3DXVec3Normalize(&v2, &v2);	// ���K��
		prism_vertex[i * 3].Normal =
		prism_vertex[i * 3 + 1].Normal =
		prism_vertex[i * 3 + 2].Normal = v2;
	}

	m_Name = "Prism";

}

void Prism::Uninit()
{
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
}

void Prism::Update()
{
	D3DXMATRIX		matRotateX;				// �w����]�}�g���b�N�X
	D3DXMATRIX		matRotateY;				// �x����]�}�g���b�N�X
	D3DXMATRIX		matRotateZ;				// �y����]�}�g���b�N�X
	D3DXMATRIX		matTrans;				// ���s�ړ��}�g���b�N�X
	D3DXMATRIX		matRotation;			// ��]�}�g���b�N�X�i������j
	D3DXVECTOR3		v_norm;					// �@���x�N�g��
	D3DXVECTOR3		v_norm2;				// �@���x�N�g���i��]��j
	D3DXVECTOR3		v_vtx;					// ���f���̒��_�ւ̈ʒu�x�N�g��
	D3DXVECTOR3		v_vtx2;					// ���f���̒��_�ւ̈ʒu�x�N�g���i��]��j
	D3DXVECTOR3		v_view2;				// ���_���王�_�ւ̃x�N�g��
	D3DXVECTOR3		v_ref;					// ���܃x�N�g��
	D3DXVECTOR3		v_tmp;					// �e���|����
	D3DXVECTOR3		bg_norm;				// �a�f�ʂ̖@���x�N�g��
	D3DXVECTOR3		v_pos;					// ���܃x�N�g���ƃe�N�X�`���ʂƂ̌�_
	D3DXVECTOR3		v0, v1, v2;				// �v���Y���ʂ̖@���x�N�g���v�Z�p
	float		ref_rate_v, ref_rate_t;	// ���܃x�N�g���v�Z�p�ꎞ�ϐ�
	float		rrv_rrt, rrv2_rrt2;
	float		ans_InnerProduct;
	float		tmp0;
	float		n;
	int			i;

	// �L�[�ɂ�鎋�_�ʒu����уv���Y�����f���̈ړ�
	if (GetKeyboardPress(DIK_UP)) g_Prism.position[1] += 0.1f;	// �J�[�\���i��j
	if (GetKeyboardPress(DIK_DOWN)) g_Prism.position[1] -= 0.1f;	// �J�[�\���i���j
	if (GetKeyboardPress(DIK_LEFT)) g_Prism.position[0] -= 0.1f;	// �J�[�\���i���j
	if (GetKeyboardPress(DIK_RIGHT)) g_Prism.position[0] += 0.1f;	// �J�[�\���i�E�j
	// �����I�ɉ�]
	g_Prism.rotation.z += 0.01f;

	// ���[���h�}�g���b�N�X������
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixRotationX(&matRotateX, g_Prism.rotation.x);	// �w����]�}�g���b�N�X�𐶐�
	D3DXMatrixRotationY(&matRotateY, g_Prism.rotation.y);	// �x����]�}�g���b�N�X�𐶐�
	D3DXMatrixRotationZ(&matRotateZ, g_Prism.rotation.z);	// �y����]�}�g���b�N�X�𐶐�
	D3DXMatrixTranslation(&matTrans,
		g_Prism.position.x, g_Prism.position.y, g_Prism.position.z);	// ���s�ړ��}�g���b�N�X�𐶐�

	// �s��ς̍��E�֌W��OpenGL�Ƌt
	D3DXMatrixIdentity(&matRotation);
	D3DXMatrixMultiply(&matRotation, &matRotateX, &matRotation);	// ��]�}�g���b�N�X������
	D3DXMatrixMultiply(&matRotation, &matRotateY, &matRotation);	// ��]�}�g���b�N�X������
	D3DXMatrixMultiply(&matRotation, &matRotateZ, &matRotation);	// ��]�}�g���b�N�X������
	D3DXMatrixMultiply(&matWorld, &matRotation, &matTrans);			// ���[���h�}�g���b�N�X������

	Scene* scene = Manager::GetScene();
	GameObject *camera = scene->GetGameObject("Camera", scene->CAMERA_LAYER);

	for (i = 0; i < 3 * 4; i++)		// ���f���͂R���_���S��
	{
		// �v���Y�����f���̒��_�ɂ���@���x�N�g�������[���h��Ԃցu��]�v
		v_norm = prism_vertex[i].Normal;
		D3DXVec3TransformCoord(&v_norm2, &v_norm, &matRotation);
		D3DXVec3Normalize(&v_norm2, &v_norm2);	// ���K��

		// ���f���̒��_�����[���h��Ԃ֕ϊ����A���_�ւ̕����x�N�g�������߂�
		v_vtx = prism_vertex[i].Position;
		D3DXVec3TransformCoord(&v_vtx2, &v_vtx, &matWorld);
		v_view2 = camera->GetPosition() - v_vtx2;
		D3DXVec3Normalize(&v_view2, &v_view2);	// ���K��

		//========================================================================
		//
		//    �����Ɉȉ��̂悤�ȃv���O������ǉ�����
		//
		//    ���@���܂̌v�Z��������܃x�N�g�������߂�@��
		//�@�@�P�F���ܗ��i�Q�j��ϐ��ɐݒ�i 1.0 �� 1.2 ���g�p�j
		//�@�@�Q�F���܂̌v�Z�����ɂ���u���ρv�l���v�Z
		//�@�@�@�@�i�g�p����l�͐�ɋ��߂Ă��� v_norm2 �� v_view2 �𗘗p�j
		//�@�@�R�F���ܗ��A�v�Z�l���g���ċ��܃x�N�g�� v_ref �����߂�
		//
		//========================================================================
		// �i�𓚗�j*************************************************************
		// ���܂̌v�Z��������܃x�N�g�������߂�
		ref_rate_v = 1.0f;
		ref_rate_t = 1.2f;
		rrv_rrt = ref_rate_v / ref_rate_t;
		rrv2_rrt2 = (ref_rate_v * ref_rate_v) / (ref_rate_t * ref_rate_t);
		ans_InnerProduct = D3DXVec3Dot(&v_norm2, &v_view2);
		tmp0 = rrv_rrt * ans_InnerProduct - sqrtf(1.0f - rrv2_rrt2 * (1.0f - ans_InnerProduct * ans_InnerProduct));
		v_ref = tmp0 * v_norm2 - rrv_rrt * v_view2;
		//************************************************************************

		// ���܃x�N�g���̐���ƃe�N�X�`���ʂƂ̌�_�����߂�
		//
		// (����)
		// �ʒu�x�N�g��x0�̓_����x�N�g��m�̕����ɒ��������΂��Ƃ�
		// ���ʂ̖@���x�N�g����n�A���ʏ�̔C�ӂ̓_�̈ʒu�x�N�g����x�Ƃ����
		// �����ƕ��ʂ̌�_�̈ʒu�x�N�g����
		//		x0 + ((x-x0)�En / m�En)m	���u�E�v�̓x�N�g�����m�̓���
		// �ŋ��߂���
		// https://risalc.info/src/line-plane-intersection-point.html
		//
		// OpenGL(�E����W�n)��DirectX(������W�n)�̈Ⴂ(Z���t)�ɒ���
		v_tmp = D3DXVECTOR3(0.0f, 0.0f, -80.0f) - v_vtx2;	// �����̒萔�͓K��
		bg_norm = D3DXVECTOR3(0.0f, 0.0f, -1.0f);			// �a�f�̃e�N�X�`���ʂ̖@���x�N�g��
		n = D3DXVec3Dot(&v_tmp, &bg_norm) / D3DXVec3Dot(&v_ref, &bg_norm);
		v_pos = v_vtx2 + n * v_ref;

		// ��_���W�����ۂ̃e�N�X�`�����W�ɕϊ�
		prism_vertex[i].TexCoord.x = 0.5f + v_pos.x * 0.001f;
		prism_vertex[i].TexCoord.y = 0.5f + v_pos.y * 0.001f;

		// �e�N�X�`�����W��OpenGL�Ə㉺���t
		prism_vertex[i].TexCoord.y = 1 - prism_vertex[i].TexCoord.y;
	}
}

void Prism::Draw()
{
	// �`��
// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;

	// ���_�o�b�t�@(�e�N�X�`�����W)�X�V
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	Renderer::GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	memcpy(mappedResource.pData, prism_vertex, sizeof(VERTEX_3D) * 12);
	Renderer::GetDeviceContext()->Unmap(g_VertexBuffer, 0);

	//���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//�V�F�[�_�[�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// ���[���h�}�g���b�N�X�̐ݒ�
	Renderer::SetWorldMatrix(&matWorld);

	TextureContainer::ModelDraw("Prism",12);
}
