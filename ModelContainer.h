#pragma once
#include <string>
#include <unordered_map>
#include "model.h"
#include "SingletonObject.h"
#include "AnimetionModel.h"

// ���f���f�[�^
namespace ModelData
{
	// 3D���f���̎g�p�V�[���ɍ��킹���^�O
	enum class Tag
	{
		Any,		// �펞
		Title,		// �^�C�g���V�[��
		Game,		// �Q�[���V�[��
		Result		// ���U���g�V�[��
	};

	//�f�[�^�^�C�v�ɍ��킹���^�O
	enum class Type
	{
		OBJ_Data,   //obj�t�@�C��
		FBX_Skin_Data,   //fbx�t�@�C�� �X�L���f�[�^
		FBX_Anime_Data,   //fbx�t�@�C�� �A�j���[�V�����f�[�^
	};

	// 3D���f���̏����i�[����\����
	class Data
	{
	private:
		// ���f���̖��O
		std::string name = "";

		// ���f���̃p�X
		std::string pass = "";

		std::string Anime = "";

		// ���f���̃^�O
		ModelData::Tag tag = ModelData::Tag::Any;

		// ���f���̃^�O
		ModelData::Type type = ModelData::Type::OBJ_Data;

		// ���f�����
		Model* model = model = new Model();

		//�A�j���[�V�������f�����
		AnimetionModel* Animemodel = Animemodel = new AnimetionModel();

		// ���[�h�ςݔ���
		bool loaded = false;

	public:
		// �R���X�g���N�^
		Data(std::string modelName, std::string AnimeName, std::string modelPass, ModelData::Tag modelTag, ModelData::Type modeType)
			: name(modelName), Anime(AnimeName),pass(modelPass), tag(modelTag),type(modeType) {}

		// ���f���ǂݍ���
		void ModelLoad()
		{
			// ���f�����̓ǂݍ���
			model->Load(pass.c_str());

			// ���[�h�ςݔ����L����
			loaded = true;
		}

		void SkinModelLoad()
		{
			Animemodel->Load(pass.c_str());

			loaded = true;
		}

		void AnimetionLoad(std::string Pass,std::string name)
		{
			Animemodel->LoadAnimetion(Pass.c_str(),name);

			loaded = true;
		}
		// ���f���̃A�����[�h�i�ǂݍ��ݏ��j���j
		void ModelUnload()
		{
			// ���f�����̔j��
			model->Unload();

			// ���[�h�ςݔ���𖳌���
			loaded = false;
		}

		// �A�j���[�V�������f���̃A�����[�h�i�ǂݍ��ݏ��j���j
		void AnimetionModelUnload()
		{
			// ���f�����̔j��
			Animemodel->Unload();

			// ���[�h�ςݔ���𖳌���
			loaded = false;
		}

		// ���f���f�[�^�̏I������
		void ModelUninit()
		{
			// ���f����񂪑��݂���ꍇ
			if (loaded)
			{
				// ���f�����̔j��
				model->Unload();
			}

			// ���[�h�ςݔ���𖳌���
			loaded = false;

			// ���f�����𖕏�
			delete model;

			// ���f������������
			model = nullptr;
		}

		// �A�j���[�V�����f�[�^�̏I������
		void AnimetionModelUninit()
		{
			// ���f����񂪑��݂���ꍇ
			if (loaded)
			{
				// ���f�����̔j��
				Animemodel->Unload();
			}

			// ���[�h�ςݔ���𖳌���
			loaded = false;

			// ���f�����𖕏�
			delete Animemodel;

			// ���f������������
			Animemodel = nullptr;
		}

		// ���f���̎擾
		Model* GetModel()
		{
			// ���f�������݂���ꍇ�̓��f������n��
			if (model) { return model; }

			// ���f�������݂��Ȃ��ꍇ��null��Ԃ�
			return nullptr;
		}

		AnimetionModel* GetAnimetionModel()
		{
			// ���f�������݂���ꍇ�̓��f������n��
			if (Animemodel) { return Animemodel; }

			// ���f�������݂��Ȃ��ꍇ��null��Ԃ�
			return nullptr;
		}

		// ���f���̖��O���擾
		std::string GetName() { return name; }

		// ���f���̃A�j���[�V���������擾
		std::string GetAnime() { return Anime; }

		std::string GetPass() { return pass; }

		// ���f���̃^�O���擾
		ModelData::Tag GetTag() { return tag; }

		// ���f���̃^�C�v���擾
		ModelData::Type GetType() { return type; }

		// ���f���̓ǂݍ��ݏ��̎擾
		bool GetLoaded() { return loaded; }

		// ���f���̖��O�ƃp�X������������
		void SetNameAndPass(std::string newName, std::string newPass)
		{
			// ���O�ƃp�X�̏�������
			name = newName;
			pass = newPass;

			// ���f���̃A�����[�h
			ModelUnload();
		}
	};
}

// ���f���f�[�^�̊Ǘ�
class ModelContainer : public SingletonObject<ModelContainer>
{
private:
	// ���f���f�[�^�{��
	std::unordered_map<std::string, ModelData::Data*> model;

	std::unordered_map<std::string, ModelData::Data*> Anime;

public:
	// �R���X�g���N�^�̐���
	ModelContainer() {}

	// �f�X�g���N�^�̐���
	~ModelContainer() {}


	// �t�����h�N���X�̎w��
	friend class SingletonObject<ModelContainer>;

	// ���f���f�[�^������
	void Init();

	// ���f���f�[�^�I������
	void Uninit();

	// ���f���ǉ�
	void AddModel(std::string modelName, std::string AnimeName, std::string modelPass, ModelData::Tag modelTag, ModelData::Type modeType);

	// ���f���f�[�^�ǂݍ���
	void Load(ModelData::Tag LoadModelTag);

	// ���f���f�[�^�j��
	void Unload(ModelData::Tag LoadModelTag);

	// �A�j���[�V�����f�[�^�X�V
	void Update(std::string modelName,std::string Animetion1,std::string Animetion2,float BlendRate,float Frame);

	// ���f���f�[�^�`��
	void ModelDraw(std::string name);

	// ���f���f�[�^�擾
	ModelData::Data* ModelData(std::string name);
};

