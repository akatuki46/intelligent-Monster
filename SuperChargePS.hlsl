#include "Common.hlsl"
//�����̂��

Texture2D g_Texture : register(t0); //�e�N�X�`���O��

SamplerState g_SamplerState : register(s0); //�T���v���[�O��

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	//�s�N�Z���̖@���𐳋K��
	//���_�V�F�[�_�[����o�͂��ꂽ�@���͒�����ԁi�@���̒������Ⴄ�j
	//��ԂȂ̂Ő��K�����Ĉ��̒����ɂ���K�v������
    float4 normal = normalize(In.Normal);

	//�����v�Z������
    float light = -dot(normal.xyz, Light.Direction.xyz);

	//�����x�N�g���̍쐬
	//�J��������s�N�Z���֌������x�N�g��
    float3 eyev = In.WorldPosition - CameraPosition;
    eyev = normalize(eyev); //���K������

	//�����Ɩ@���̓��ς𖾂邳�ɕϊ�����
    float rim = 1.0 + dot(eyev, normal.xyz);
    rim = pow(rim, 2) * 2.0f;
    rim = saturate(rim); //�l���T�`�����[�g


	//�e�N�X�`���̃s�N�Z���F���擾
    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
    outDiffuse.rgb *= In.Diffuse.rgb * light; //���邳����Z
    outDiffuse.b += rim; //�X�y�L�����l���f�t���[�Y�Ƃ��đ�������
    outDiffuse.a = In.Diffuse.a; //���ɖ��邳�͊֌W�Ȃ��̂ŕʌv�Z

}