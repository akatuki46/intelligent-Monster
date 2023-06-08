#pragma once
#include <string>
#include <unordered_map>
#include "main.h"
#include "renderer.h"

// モデルデータ
namespace TextureData
{
	// 3Dモデルの使用シーンに合わせたタグ
	enum class Tag
	{
		Any,		// 常時
		Title,		// タイトルシーン
		Loading,
		Game,		// ゲームシーン
		Result		// リザルトシーン
	};

	// テクスチャ情報を格納する構造体
	class Data
	{
	private:
		// モデルの名前
		std::string name = "";

		// モデルのパス
		std::string pass = "";

		D3DXVECTOR2     m_Division = D3DXVECTOR2(0.0f,0.0f);
		
		// モデルのタグ
		TextureData::Tag tag = TextureData::Tag::Any;

		ID3D11Buffer* m_VertexBuffer = NULL;
		ID3D11ShaderResourceView* m_Texture = NULL;

		// ロード済み判定
		bool loaded = false;

	public:
		// コンストラクタ
		Data(std::string modelName, std::string modelPass, D3DXVECTOR2 Divi,TextureData::Tag modelTag) : 
			name(modelName), pass(modelPass), m_Division(Divi), tag(modelTag) {}

		// モデル読み込み
		void TextureLoad()
		{
			// モデル情報の読み込み
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


			//頂点バッファ生成
			D3D11_BUFFER_DESC bd{};
			//ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DYNAMIC;//←ここと
			bd.ByteWidth = sizeof(VERTEX_3D) * 4;
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;//←ここを変えないと頂点バッファの書き換えが出来ない
													   //（テクスチャアニメーション出来ない）

			D3D11_SUBRESOURCE_DATA sd{};
			sd.pSysMem = vertex;

			Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);


			//テクスチャ読み込み
			D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
				TextureData::Data::pass.c_str(),
				NULL,
				NULL,
				&m_Texture,
				NULL);
			assert(m_Texture);



			// ロード済み判定を有効化
			loaded = true;
		}

		// モデルのアンロード
		void TextureUnload()
		{
			// モデル情報の破棄
			m_VertexBuffer->Release();
			m_Texture->Release();

			// ロード済み判定を無効化
			loaded = false;
		}

		// 頂点バッファの取得
		ID3D11Buffer* const* GetBuffer()
		{
			// モデルが存在する場合はモデル情報を渡す
			if (m_VertexBuffer) { return &m_VertexBuffer; }

			// モデルが存在しない場合はnullを返す
			return nullptr;
		}

		// テクスチャデータの取得
		ID3D11ShaderResourceView* const* GetTexture()
		{
			// モデルが存在する場合はモデル情報を渡す
			if (m_Texture) { return &m_Texture; }

			// モデルが存在しない場合はnullを返す
			return nullptr;
		}

		// モデルの名前を取得
		std::string GetName() { return name; }

		// モデルのタグを取得
		TextureData::Tag GetTag() { return tag; }

		// モデルの読み込み情報の取得
		bool GetLoaded() { return loaded; }

		// モデルの名前とパス名を書き換え
		void SetNameAndPass(std::string newName, std::string newPass)
		{
			// 名前とパスの書き換え
			name = newName;
			pass = newPass;

			// モデルのアンロード
			TextureUnload();
		}

		D3DXVECTOR2 GetDivision() { return m_Division; }
	};

}

class TextureContainer
{
private:
	// モデルデータ本体
	static std::unordered_map<std::string, TextureData::Data*> Texure;

public:
	// テクスチャ初期化
	static void Init();

	// テクスチャ破棄
	static void Uninit();

	// テクスチャデータ追加
	static void AddTexture(std::string modelName, std::string modelPass,D3DXVECTOR2 Division, TextureData::Tag modelTag);

	// テクスチャ読み込み
	static void Load(TextureData::Tag LoadModelTag);

	// テクスチャ破棄
	static void Unload(TextureData::Tag LoadModelTag);

	// テクスチャ描画
	static void ModelDraw(std::string name , int Vertex_Num = 4);

	// テクスチャ描画
	static void ModelDrawIndex(std::string name, int Vertex_Num = 4);

	//テクスチャ分割数データ取得
	static D3DXVECTOR2 GetTextureDivi(std::string name);

};

