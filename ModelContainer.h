#pragma once
#include <string>
#include <unordered_map>
#include "model.h"
#include "SingletonObject.h"
#include "AnimetionModel.h"

// モデルデータ
namespace ModelData
{
	// 3Dモデルの使用シーンに合わせたタグ
	enum class Tag
	{
		Any,		// 常時
		Title,		// タイトルシーン
		Game,		// ゲームシーン
		Result		// リザルトシーン
	};

	//データタイプに合わせたタグ
	enum class Type
	{
		OBJ_Data,   //objファイル
		FBX_Skin_Data,   //fbxファイル スキンデータ
		FBX_Anime_Data,   //fbxファイル アニメーションデータ
	};

	// 3Dモデルの情報を格納する構造体
	class Data
	{
	private:
		// モデルの名前
		std::string name = "";

		// モデルのパス
		std::string pass = "";

		std::string Anime = "";

		// モデルのタグ
		ModelData::Tag tag = ModelData::Tag::Any;

		// モデルのタグ
		ModelData::Type type = ModelData::Type::OBJ_Data;

		// モデル情報
		Model* model = model = new Model();

		//アニメーションモデル情報
		AnimetionModel* Animemodel = Animemodel = new AnimetionModel();

		// ロード済み判定
		bool loaded = false;

	public:
		// コンストラクタ
		Data(std::string modelName, std::string AnimeName, std::string modelPass, ModelData::Tag modelTag, ModelData::Type modeType)
			: name(modelName), Anime(AnimeName),pass(modelPass), tag(modelTag),type(modeType) {}

		// モデル読み込み
		void ModelLoad()
		{
			// モデル情報の読み込み
			model->Load(pass.c_str());

			// ロード済み判定を有効化
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
		// モデルのアンロード（読み込み情報破棄）
		void ModelUnload()
		{
			// モデル情報の破棄
			model->Unload();

			// ロード済み判定を無効化
			loaded = false;
		}

		// アニメーションモデルのアンロード（読み込み情報破棄）
		void AnimetionModelUnload()
		{
			// モデル情報の破棄
			Animemodel->Unload();

			// ロード済み判定を無効化
			loaded = false;
		}

		// モデルデータの終了処理
		void ModelUninit()
		{
			// モデル情報が存在する場合
			if (loaded)
			{
				// モデル情報の破棄
				model->Unload();
			}

			// ロード済み判定を無効化
			loaded = false;

			// モデル情報を抹消
			delete model;

			// モデル情報を初期化
			model = nullptr;
		}

		// アニメーションデータの終了処理
		void AnimetionModelUninit()
		{
			// モデル情報が存在する場合
			if (loaded)
			{
				// モデル情報の破棄
				Animemodel->Unload();
			}

			// ロード済み判定を無効化
			loaded = false;

			// モデル情報を抹消
			delete Animemodel;

			// モデル情報を初期化
			Animemodel = nullptr;
		}

		// モデルの取得
		Model* GetModel()
		{
			// モデルが存在する場合はモデル情報を渡す
			if (model) { return model; }

			// モデルが存在しない場合はnullを返す
			return nullptr;
		}

		AnimetionModel* GetAnimetionModel()
		{
			// モデルが存在する場合はモデル情報を渡す
			if (Animemodel) { return Animemodel; }

			// モデルが存在しない場合はnullを返す
			return nullptr;
		}

		// モデルの名前を取得
		std::string GetName() { return name; }

		// モデルのアニメーション名を取得
		std::string GetAnime() { return Anime; }

		std::string GetPass() { return pass; }

		// モデルのタグを取得
		ModelData::Tag GetTag() { return tag; }

		// モデルのタイプを取得
		ModelData::Type GetType() { return type; }

		// モデルの読み込み情報の取得
		bool GetLoaded() { return loaded; }

		// モデルの名前とパス名を書き換え
		void SetNameAndPass(std::string newName, std::string newPass)
		{
			// 名前とパスの書き換え
			name = newName;
			pass = newPass;

			// モデルのアンロード
			ModelUnload();
		}
	};
}

// モデルデータの管理
class ModelContainer : public SingletonObject<ModelContainer>
{
private:
	// モデルデータ本体
	std::unordered_map<std::string, ModelData::Data*> model;

	std::unordered_map<std::string, ModelData::Data*> Anime;

public:
	// コンストラクタの制限
	ModelContainer() {}

	// デストラクタの制限
	~ModelContainer() {}


	// フレンドクラスの指定
	friend class SingletonObject<ModelContainer>;

	// モデルデータ初期化
	void Init();

	// モデルデータ終了処理
	void Uninit();

	// モデル追加
	void AddModel(std::string modelName, std::string AnimeName, std::string modelPass, ModelData::Tag modelTag, ModelData::Type modeType);

	// モデルデータ読み込み
	void Load(ModelData::Tag LoadModelTag);

	// モデルデータ破棄
	void Unload(ModelData::Tag LoadModelTag);

	// アニメーションデータ更新
	void Update(std::string modelName,std::string Animetion1,std::string Animetion2,float BlendRate,float Frame);

	// モデルデータ描画
	void ModelDraw(std::string name);

	// モデルデータ取得
	ModelData::Data* ModelData(std::string name);
};

