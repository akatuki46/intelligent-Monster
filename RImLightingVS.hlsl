#include "common.hlsl"
//�����̂��

//In�͓��͂��ꂽ�f�[�^
//Out�͏o�͂���f�[�^

void main(in VS_IN In, out PS_IN Out)
{
	//�P���_���̃f�[�^���󂯎��A�������āA�o�͂���
	//���_�ϊ����� ���̏����͕K���K�v
	matrix wvp; //�s��ϐ����쐬
	wvp = mul(World, View); //wvp = ���[���h�s�񁖃J�����s��
	wvp = mul(wvp, Projection); //wvp = wvp *�v���W�F�N�V�����s��
	Out.Position = mul(In.Position, wvp); //�ϊ����ʂ��o�͂���

	//���_�@�������[���h�s��ŉ�]������(���_�Ɠ�����]��������)
	float4 worldNormal, normal; //���[�J���ϐ����쐬
	normal = float4(In.Normal.xyz, 0.0);//�@���x�N�g����w��0�Ƃ��ăR�s�[�i���s�ړ����Ȃ�����)
	worldNormal = mul(normal, World); //�@�������[���h�s��ŉ�]����
	worldNormal = normalize(worldNormal); //��]��̖@���𐳋K������
	Out.Normal = worldNormal; //��]��̖@���o�� In.Normal�łȂ���]��̖@�����o��


	//�����v�Z�̓s�N�Z���V�F�[�_�[�ōs���̂�
	//�����v�Z�܂ł̍ޗ����s�N�Z���V�F�[�_�[�ɓn��
	//���_�F���o��
	Out.Diffuse = In.Diffuse;
	//�e�N�X�`�����W�o��
	Out.TexCoord = In.TexCoord;

	//���_�x�N�g�������߂邽�߂ɂ̓s�N�Z�����W���K�v
	//�s�N�Z�����W�����߂邽�߂ɂ̓��[���h�ϊ��܂ł������_���W���o��
	Out.WorldPosition = mul(In.Position, World);
}