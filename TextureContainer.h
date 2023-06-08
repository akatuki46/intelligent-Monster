#pragma once
#include <string>
#include <unordered_map>
#include "main.h"
#include "renderer.h"

// ���f���f�[�^
namespace TextureData
{
	// 3D���f���̎g�p�V�[���ɍ��킹���^�O
	enum class Tag
	{
		Any,		// �펞
		Title,		// �^�C�g���V�[��
		Loading,
		Game,		// �Q�[���V�[��
		Result		// ���U���g�V�[��
	};

	// �e�N�X�`�������i�[����\����
	class Data
	{
	private:
		// ���f���̖��O
		std::string name = "";

		// ���f���̃p�X
		std::string pass = "";

		D3DXVECTOR2     m_Division = D3DXVECTOR2(0.0f,0.0f);
		
		// ���f���̃^�O
		TextureData::Tag tag = TextureData::Tag::Any;

		ID3D11Buffer* m_VertexBuffer = NULL;
		ID3D11ShaderResourceView* m_Texture = NULL;

		// ���[�h�ςݔ���
		bool loaded = false;

	public:
		// �R���X�g���N�^
		Data(std::string modelName, std::string modelPass, D3DXVECTOR2 Divi,TextureData::Tag modelTag) : 
			name(modelName), pass(modelPass), m_Division(Divi), tag(modelTag) {}

		// ���f���ǂݍ���
		void TextureLoad()
		{
			// ���f�����̓ǂݍ���
			VERTEX_3D vertex[4];

			vertex[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

			vertex[1].Position = D3DXVECTOR3(200.0f, 0.0f, 0.0f);
			vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f)
				;
			vertex[2].Position = D3DXVECTOR3(0.0f, 200.0f, 0.0f);
			vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

			vertex[3].Position = D3DXVECTOR3(200.0f, 200.0f, 0.0f);
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


			//�e�N�X�`���ǂݍ���
			D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
				TextureData::Data::pass.c_str(),
				NULL,
				NULL,
				&m_Texture,
				NULL);
			assert(m_Texture);



			// ���[�h�ςݔ����L����
			loaded = true;
		}

		// ���f���̃A�����[�h
		void TextureUnload()
		{
			// ���f�����̔j��
			m_VertexBuffer->Release();
			m_Texture->Release();

			// ���[�h�ςݔ���𖳌���
			loaded = false;
		}

		// ���_�o�b�t�@�̎擾
		ID3D11Buffer* const* GetBuffer()
		{
			// ���f�������݂���ꍇ�̓��f������n��
			if (m_VertexBuffer) { return &m_VertexBuffer; }

			// ���f�������݂��Ȃ��ꍇ��null��Ԃ�
			return nullptr;
		}

		// �e�N�X�`���f�[�^�̎擾
		ID3D11ShaderResourceView* const* GetTexture()
		{
			// ���f�������݂���ꍇ�̓��f������n��
			if (m_Texture) { return &m_Texture; }

			// ���f�������݂��Ȃ��ꍇ��null��Ԃ�
			return nullptr;
		}

		// ���f���̖��O���擾
		std::string GetName() { return name; }

		// ���f���̃^�O���擾
		TextureData::Tag GetTag() { return tag; }

		// ���f���̓ǂݍ��ݏ��̎擾
		bool GetLoaded() { return loaded; }

		// ���f���̖��O�ƃp�X������������
		void SetNameAndPass(std::string newName, std::string newPass)
		{
			// ���O�ƃp�X�̏�������
			name = newName;
			pass = newPass;

			// ���f���̃A�����[�h
			TextureUnload();
		}

		D3DXVECTOR2 GetDivision() { return m_Division; }
	};

}

class TextureContainer
{
private:
	// ���f���f�[�^�{��
	static std::unordered_map<std::string, TextureData::Data*> Texure;

public:
	// �e�N�X�`��������
	static void Init();

	// �e�N�X�`���j��
	static void Uninit();

	// �e�N�X�`���f�[�^�ǉ�
	static void AddTexture(std::string modelName, std::string modelPass,D3DXVECTOR2 Division, TextureData::Tag modelTag);

	// �e�N�X�`���ǂݍ���
	static void Load(TextureData::Tag LoadModelTag);

	// �e�N�X�`���j��
	static void Unload(TextureData::Tag LoadModelTag);

	// �e�N�X�`���`��
	static void ModelDraw(std::string name , int Vertex_Num = 4);

	// �e�N�X�`���`��
	static void ModelDrawIndex(std::string name, int Vertex_Num = 4);

	//�e�N�X�`���������f�[�^�擾
	static D3DXVECTOR2 GetTextureDivi(std::string name);

};

