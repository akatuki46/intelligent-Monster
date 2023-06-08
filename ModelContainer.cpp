#include "ModelContainer.h"
#include <tchar.h> 

void ModelContainer::Init()
{
	// バレットのモデルを追加
	AddModel("Bullet","", "asset\\model\\Bullet.obj", ModelData::Tag::Game,ModelData::Type::OBJ_Data);

	// エネミーのモデルを追加
	AddModel("Enemy", "", "asset\\model\\cube.obj",ModelData::Tag::Game, ModelData::Type::OBJ_Data);

	// プレイヤーのモデルを追加
	AddModel("Player", "", "asset\\model\\Erika_Archer.fbx", ModelData::Tag::Game, ModelData::Type::FBX_Skin_Data);

	// プレイヤーのモデルを追加
	AddModel("Player", "Idle", "asset\\model\\Idle.fbx", ModelData::Tag::Game, ModelData::Type::FBX_Anime_Data);

	// プレイヤーのモデルを追加
	AddModel("Player", "Run", "asset\\model\\Standing_Run_Forward.fbx", ModelData::Tag::Game, ModelData::Type::FBX_Anime_Data);

	// プレイヤーのモデルを追加
	AddModel("Player", "Hit", "asset\\model\\Rifle_Hit_To_Back.fbx", ModelData::Tag::Game, ModelData::Type::FBX_Anime_Data);

	// プレイヤーのモデルを追加
	AddModel("Player", "Attack", "asset\\model\\Standing_Torch_Melee_Attack_Stab.fbx", ModelData::Tag::Game, ModelData::Type::FBX_Anime_Data);

	// プレイヤーのモデルを追加
	AddModel("Player", "Die", "asset\\model\\Dying.fbx", ModelData::Tag::Game, ModelData::Type::FBX_Anime_Data);

	// プレイヤーのモデルを追加
	AddModel("Player", "Walk", "asset\\model\\Standing_Walk_Forward.fbx", ModelData::Tag::Game, ModelData::Type::FBX_Anime_Data);

	// プレイヤーのモデルを追加
	AddModel("Player", "dodge", "asset\\model\\Falling To Roll.fbx", ModelData::Tag::Game, ModelData::Type::FBX_Anime_Data);

	//ジンオウガモデル
	{
		// エネミーのモデルを追加
		AddModel("UpBody", "", "asset\\model\\zinouga\\UpBody.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("LowBody", "", "asset\\model\\zinouga\\LowBody.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("Ueago", "", "asset\\model\\zinouga\\Ueago.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("Sitaago", "", "asset\\model\\zinouga\\Sitaago.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("Rkata", "", "asset\\model\\zinouga\\Rkata.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("Lkata", "", "asset\\model\\zinouga\\Lkata.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("Rude", "", "asset\\model\\zinouga\\Rude.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("Lude", "", "asset\\model\\zinouga\\Lude.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("Rte", "", "asset\\model\\zinouga\\Rte.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("Lte", "", "asset\\model\\zinouga\\Lte.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("Ryubi1", "", "asset\\model\\zinouga\\Ryubi1.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("Ryubi2", "", "asset\\model\\zinouga\\Ryubi2.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("Ryubi3", "", "asset\\model\\zinouga\\Ryubi3.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("Ryubi4", "", "asset\\model\\zinouga\\Ryubi4.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("Ryubi5", "", "asset\\model\\zinouga\\Ryubi5.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("Lyubi1", "", "asset\\model\\zinouga\\Lyubi1.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("Lyubi2", "", "asset\\model\\zinouga\\Lyubi2.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("Lyubi3", "", "asset\\model\\zinouga\\Lyubi3.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("Lyubi4", "", "asset\\model\\zinouga\\Lyubi4.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("Lyubi5", "", "asset\\model\\zinouga\\Lyubi5.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("RBmomo", "", "asset\\model\\zinouga\\RBmomo.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("LBmomo", "", "asset\\model\\zinouga\\LBmomo.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("RBsune", "", "asset\\model\\zinouga\\RBsune.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("LBsune", "", "asset\\model\\zinouga\\LBsune.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("RBankle", "", "asset\\model\\zinouga\\RBankle.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("LBankle", "", "asset\\model\\zinouga\\LBankle.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("RBte", "", "asset\\model\\zinouga\\RBte.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("LBte", "", "asset\\model\\zinouga\\LBte.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("RByubi1", "", "asset\\model\\zinouga\\RByubi1.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("RByubi2", "", "asset\\model\\zinouga\\RByubi2.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("RByubi3", "", "asset\\model\\zinouga\\RByubi3.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("RByubi4", "", "asset\\model\\zinouga\\RByubi4.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("RByubi5", "", "asset\\model\\zinouga\\RByubi5.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("LByubi1", "", "asset\\model\\zinouga\\LByubi1.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("LByubi2", "", "asset\\model\\zinouga\\LByubi2.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("LByubi3", "", "asset\\model\\zinouga\\LByubi3.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("LByubi4", "", "asset\\model\\zinouga\\LByubi4.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("LByubi5", "", "asset\\model\\zinouga\\LByubi5.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("Tail1", "", "asset\\model\\zinouga\\Tail1.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("Tail2", "", "asset\\model\\zinouga\\Tail2.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("Tail3", "", "asset\\model\\zinouga\\Tail3.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("Tail4", "", "asset\\model\\zinouga\\Tail4.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("Tail5", "", "asset\\model\\zinouga\\Tail5.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);

		// エネミーのモデルを追加
		AddModel("Tail6", "", "asset\\model\\zinouga\\Tail6.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);
	}

	// 空のモデルを追加
	AddModel("Sky", "", "asset\\model\\Sky_2.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);


	//壁のモデルを追加
	AddModel("Wall", "", "asset\\model\\cube.obj",ModelData::Tag::Game, ModelData::Type::OBJ_Data);

	//壁のモデルを追加
	AddModel("Wall2", "", "asset\\model\\cube.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);


	// エネミーのモデルを追加
	AddModel("Core", "", "asset\\model\\core.obj", ModelData::Tag::Game, ModelData::Type::OBJ_Data);


}

// モデルデータ描画
void ModelContainer::ModelDraw(std::string name)
{
	// モデルデータを取得
	ModelData::Data* data = model[name];

	// モデル読み込み前の場合は処理を終了
	if (!data->GetLoaded()) { return; }

	if (data->GetType() == ModelData::Type::OBJ_Data)
	{
		// モデルを描画
		data->GetModel()->Draw();
	}
	else
	{
		data->GetAnimetionModel()->Draw();
	}

}

// モデルデータを破棄
void ModelContainer::Uninit()
{
	// モデルデータ本体を検索
	for (auto data : model)
	{
		if (data.second->GetType() == ModelData::Type::OBJ_Data)
		{
			// モデルの破棄処理を行う
			data.second->ModelUninit();
		}
		else
		{
			// モデルの破棄処理を行う
			data.second->AnimetionModelUninit();
		}

		// モデルデータの廃棄
		delete data.second;

		// モデルデータの初期化
		data.second = nullptr;
	}

	// インスタンスの破棄
	SingletonObject<ModelContainer>::InstanceRelease();
}

// モデルデータ取得
ModelData::Data* ModelContainer::ModelData(std::string name)
{
	return model[name];
}

// モデルデータ読み込み
void ModelContainer::Load(ModelData::Tag LoadModelTag)
{
	// モデルデータ本体を検索
	for (auto data : model)
	{
		// 読み込むタグと一致する場合
		if (data.second->GetTag() == LoadModelTag)
		{
			// モデル読み込み済みの場合は処理を終了
			if (data.second->GetLoaded()) { continue; }

			switch (data.second->GetType())
			{
			case ModelData::Type::OBJ_Data:
				// モデルの読み込み処理を行う
				data.second->ModelLoad();
				break;

			case ModelData::Type::FBX_Skin_Data:
				// モデルの読み込み処理を行う
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

// モデルデータ終了処理
void ModelContainer::Unload(ModelData::Tag LoadModelTag)
{
	// モデルデータ本体を検索
	for (auto data : model)
	{
		// 読み込むタグと一致する場合
		if (data.second->GetTag() == LoadModelTag)
		{
			// モデル読み込み前の場合は処理を終了
			if (!data.second->GetLoaded()) { continue; }

			if (data.second->GetType() == ModelData::Type::OBJ_Data)
			{
				// モデルの読み込み情報破棄を行う
				data.second->ModelUnload();
			}
			else
			{
				// モデルの読み込み情報破棄を行う
				data.second->AnimetionModelUnload();
			}

		}
	}
}

void ModelContainer::Update(std::string modelName, std::string Animetion1, std::string Animetion2, float BlendRate, float Frame)
{
	// モデルデータを取得
	ModelData::Data* data = model[modelName];

	// モデル読み込み前の場合は処理を終了
	if (!data->GetLoaded()) { return; }

	data->GetAnimetionModel()->Update(Animetion1, Animetion2, BlendRate, Frame);
}

// モデル追加
void ModelContainer::AddModel(std::string modelName, std::string AnimeName,std::string modelPass, ModelData::Tag modelTag, ModelData::Type modeType)
{
	//まだモデルをロードしていないなら
	if (model[modelName] == nullptr)
	{
		// モデルデータを登録
		model[modelName] = new ModelData::Data(modelName, AnimeName, modelPass, modelTag, modeType);
	}
	//モデルに紐づけられたアニメーションがあれば
	if (ModelData::Type::FBX_Anime_Data == modeType)
	{
		// モデルデータを登録
		Anime[AnimeName] = new ModelData::Data(modelName, AnimeName, modelPass, modelTag, modeType);
	}
}
