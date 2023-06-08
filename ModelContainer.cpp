#include "ModelContainer.h"
#include <tchar.h> 

void ModelContainer::Init()
{
	// �o���b�g�̃��f����ǉ�
	AddModel("Bullet","", "asset\\model\\Bullet.obj", ModelData::Tag::Game,ModelData::Type::OBJ_Data);

	// �G�l�~�[�̃��f����ǉ�
	AddModel("Enemy", "", "asset\\model\\cube.obj",ModelData::Tag::Game, ModelData::Type::OBJ_Data);

	// �v���C���[�̃��f����ǉ�
	AddModel("Player", "", "asset\\model\\Erika_Archer.fbx", ModelData::Tag::Game, ModelData::Type::FBX_Skin_Data);

	// �v���C���[�̃��f����ǉ�
	AddModel("Player", "Idle", "asset\\model\\Idle.fbx", ModelData::Tag::Game, ModelData::Type::FBX_Anime_Data);

	// �v���C���[�̃��f����ǉ�
	AddModel("Player", "Run", "asset\\model\\Standing_Run_Forward.fbx", ModelData::Tag::Game, ModelData::Type::FBX_Anime_Data);

	// �v���C���[�̃��f����ǉ�
	AddModel("Player", "Hit", "asset\\model\\Rifle_Hit_To_Back.fbx", ModelData::Tag::Game, ModelData::Type::FBX_Anime_Data);

	// �v���C���[�̃��f����ǉ�
	AddModel("Player", "Attack", "asset\\model\\Standing_Torch_Melee_Attack_Stab.fbx", ModelData::Tag::Game, ModelData::Type::FBX_Anime_Data);

	// �v���C���[�̃��f����ǉ�
	AddModel("Player", "Die", "asset\\model\\Dying.fbx", ModelData::Tag::Game, ModelData::Type::FBX_Anime_Data);

	// �v���C���[�̃��f����ǉ�
	AddModel("Player", "Walk", "asset\\model\\Standing_Walk_Forward.fbx", ModelData::Tag::Game, ModelData::Type::FBX_Anime_Data);

	// �v���C���[�̃��f����ǉ�
	AddModel("Player", "dodge", "asset\\model\\Falling To Roll.fbx", ModelData::Tag::Game, ModelData::Type::FBX_Anime_Data);

	//�W���I�E�K���f��
	{
		// �G�l�~�[�̃��f����ǉ�
		AddModel("UpBody", "", "asset\\model\\zinouga\\UpBody.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("LowBody", "", "asset\\model\\zinouga\\LowBody.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("Ueago", "", "asset\\model\\zinouga\\Ueago.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("Sitaago", "", "asset\\model\\zinouga\\Sitaago.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("Rkata", "", "asset\\model\\zinouga\\Rkata.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("Lkata", "", "asset\\model\\zinouga\\Lkata.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("Rude", "", "asset\\model\\zinouga\\Rude.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("Lude", "", "asset\\model\\zinouga\\Lude.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("Rte", "", "asset\\model\\zinouga\\Rte.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("Lte", "", "asset\\model\\zinouga\\Lte.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("Ryubi1", "", "asset\\model\\zinouga\\Ryubi1.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("Ryubi2", "", "asset\\model\\zinouga\\Ryubi2.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("Ryubi3", "", "asset\\model\\zinouga\\Ryubi3.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("Ryubi4", "", "asset\\model\\zinouga\\Ryubi4.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("Ryubi5", "", "asset\\model\\zinouga\\Ryubi5.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("Lyubi1", "", "asset\\model\\zinouga\\Lyubi1.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("Lyubi2", "", "asset\\model\\zinouga\\Lyubi2.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("Lyubi3", "", "asset\\model\\zinouga\\Lyubi3.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("Lyubi4", "", "asset\\model\\zinouga\\Lyubi4.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("Lyubi5", "", "asset\\model\\zinouga\\Lyubi5.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("RBmomo", "", "asset\\model\\zinouga\\RBmomo.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("LBmomo", "", "asset\\model\\zinouga\\LBmomo.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("RBsune", "", "asset\\model\\zinouga\\RBsune.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("LBsune", "", "asset\\model\\zinouga\\LBsune.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("RBankle", "", "asset\\model\\zinouga\\RBankle.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("LBankle", "", "asset\\model\\zinouga\\LBankle.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("RBte", "", "asset\\model\\zinouga\\RBte.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("LBte", "", "asset\\model\\zinouga\\LBte.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("RByubi1", "", "asset\\model\\zinouga\\RByubi1.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("RByubi2", "", "asset\\model\\zinouga\\RByubi2.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("RByubi3", "", "asset\\model\\zinouga\\RByubi3.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("RByubi4", "", "asset\\model\\zinouga\\RByubi4.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("RByubi5", "", "asset\\model\\zinouga\\RByubi5.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("LByubi1", "", "asset\\model\\zinouga\\LByubi1.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("LByubi2", "", "asset\\model\\zinouga\\LByubi2.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("LByubi3", "", "asset\\model\\zinouga\\LByubi3.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("LByubi4", "", "asset\\model\\zinouga\\LByubi4.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("LByubi5", "", "asset\\model\\zinouga\\LByubi5.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("Tail1", "", "asset\\model\\zinouga\\Tail1.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("Tail2", "", "asset\\model\\zinouga\\Tail2.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("Tail3", "", "asset\\model\\zinouga\\Tail3.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("Tail4", "", "asset\\model\\zinouga\\Tail4.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("Tail5", "", "asset\\model\\zinouga\\Tail5.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// �G�l�~�[�̃��f����ǉ�
		AddModel("Tail6", "", "asset\\model\\zinouga\\Tail6.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);
	}

	// ��̃��f����ǉ�
	AddModel("Sky", "", "asset\\model\\Sky_2.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);


	//�ǂ̃��f����ǉ�
	AddModel("Wall", "", "asset\\model\\cube.obj",ModelData::Tag::Game, ModelData::Type::OBJ_Data);

	//�ǂ̃��f����ǉ�
	AddModel("Wall2", "", "asset\\model\\cube.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);


	// �G�l�~�[�̃��f����ǉ�
	AddModel("Core", "", "asset\\model\\core.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);


}

// ���f���f�[�^�`��
void ModelContainer::ModelDraw(std::string name)
{
	// ���f���f�[�^���擾
	ModelData::Data* data = model[name];

	// ���f���ǂݍ��ݑO�̏ꍇ�͏������I��
	if (!data->GetLoaded()) { return; }

	if (data->GetType() == ModelData::Type::OBJ_Data)
	{
		// ���f����`��
		data->GetModel()->Draw();
	}
	else
	{
		data->GetAnimetionModel()->Draw();
	}

}

// ���f���f�[�^��j��
void ModelContainer::Uninit()
{
	// ���f���f�[�^�{�̂�����
	for (auto data : model)
	{
		if (data.second->GetType() == ModelData::Type::OBJ_Data)
		{
			// ���f���̔j���������s��
			data.second->ModelUninit();
		}
		else
		{
			// ���f���̔j���������s��
			data.second->AnimetionModelUninit();
		}

		// ���f���f�[�^�̔p��
		delete data.second;

		// ���f���f�[�^�̏�����
		data.second = nullptr;
	}

	// �C���X�^���X�̔j��
	SingletonObject<ModelContainer>::InstanceRelease();
}

// ���f���f�[�^�擾
ModelData::Data* ModelContainer::ModelData(std::string name)
{
	return model[name];
}

// ���f���f�[�^�ǂݍ���
void ModelContainer::Load(ModelData::Tag LoadModelTag)
{
	// ���f���f�[�^�{�̂�����
	for (auto data : model)
	{
		// �ǂݍ��ރ^�O�ƈ�v����ꍇ
		if (data.second->GetTag() == LoadModelTag)
		{
			// ���f���ǂݍ��ݍς݂̏ꍇ�͏������I��
			if (data.second->GetLoaded()) { continue; }

			switch (data.second->GetType())
			{
			case ModelData::Type::OBJ_Data:
				// ���f���̓ǂݍ��ݏ������s��
				data.second->ModelLoad();
				break;

			case ModelData::Type::FBX_Skin_Data:
				// ���f���̓ǂݍ��ݏ������s��
				data.second->SkinModelLoad();

				for (auto anime : Anime)
				{
					if (anime.second->GetName() == data.second->GetName())
					{
						data.second->AnimetionLoad(anime.second->GetPass(), anime.second->GetAnime());
					}
				}
				break;
			default:
				break;
			}
		}
	}
}

// ���f���f�[�^�I������
void ModelContainer::Unload(ModelData::Tag LoadModelTag)
{
	// ���f���f�[�^�{�̂�����
	for (auto data : model)
	{
		// �ǂݍ��ރ^�O�ƈ�v����ꍇ
		if (data.second->GetTag() == LoadModelTag)
		{
			// ���f���ǂݍ��ݑO�̏ꍇ�͏������I��
			if (!data.second->GetLoaded()) { continue; }

			if (data.second->GetType() == ModelData::Type::OBJ_Data)
			{
				// ���f���̓ǂݍ��ݏ��j�����s��
				data.second->ModelUnload();
			}
			else
			{
				// ���f���̓ǂݍ��ݏ��j�����s��
				data.second->AnimetionModelUnload();
			}

		}
	}
}

void ModelContainer::Update(std::string modelName, std::string Animetion1, std::string Animetion2, float BlendRate, float Frame)
{
	// ���f���f�[�^���擾
	ModelData::Data* data = model[modelName];

	// ���f���ǂݍ��ݑO�̏ꍇ�͏������I��
	if (!data->GetLoaded()) { return; }

	data->GetAnimetionModel()->Update(Animetion1, Animetion2, BlendRate, Frame);
}

// ���f���ǉ�
void ModelContainer::AddModel(std::string modelName, std::string AnimeName,std::string modelPass, ModelData::Tag modelTag, ModelData::Type modeType)
{
	//�܂����f�������[�h���Ă��Ȃ��Ȃ�
	if (model[modelName] == nullptr)
	{
		// ���f���f�[�^��o�^
		model[modelName] = new ModelData::Data(modelName, AnimeName, modelPass, modelTag, modeType);
	}
	//���f���ɕR�Â���ꂽ�A�j���[�V�����������
	if (ModelData::Type::FBX_Anime_Data == modeType)
	{
		// ���f���f�[�^��o�^
		Anime[AnimeName] = new ModelData::Data(modelName, AnimeName, modelPass, modelTag, modeType);
	}
}
