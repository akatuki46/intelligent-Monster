#pragma once
#include <list>     //リスト利用のためには必要
#include <vector> //vector型利用のためには必要
#include <typeinfo>   //型を調べるためには必要
#include "GameObject.h"
#include <functional>
#include <map>

class Scene
{
protected:
	std::list<GameObject*>   m_GameObject[3];  //STLのリスト構造

public:
	Scene() {}
	virtual ~Scene() {}

	virtual void Init() = 0;//純粋仮想関数
	virtual void InitLoad(std::function<void(void)> function) = 0;//純粋仮想関数


	typedef enum
	{
		CAMERA_LAYER = 0,
		PLAY_LAYER,
		UI_LAYER,
		LAYER_MAX,
	}OBJECTLAYER;

	GameObject* AddGameObject(GameObject* obj,OBJECTLAYER Layer)
	{
		m_GameObject[Layer].push_back(obj);

		return obj;
	}

	//tagが一致していて、レイヤーにGameObjectが存在しているか
	//存在していればその中身を持ってくる
	GameObject* GetGameObject(std::string tag,OBJECTLAYER Layer)
	{
		//objectの中にm_GameObjectをループごとに先頭から代入
		//終わるまで繰り返す
		for (GameObject* object : m_GameObject[Layer])
		{
			//<typeinfo>必要
			//型が同じか調べる
			if (object->GetTag() == tag)
			{
				//同じなら型を返す
				return object;
			}
		}
		return NULL;
	}

	//GetGameObject関数とは違い、複数のオブジェクトの情報をもらってくる関数
	//vecter型で配列を作り、その中にT型と同じ型の情報を入れていく
	//Enemy型ならすべてのEnemyの情報を得られる(Bullet,Itemも同様)
	std::vector<GameObject*>GetGameObjects(std::string tag,OBJECTLAYER Layer)
	{
		//STLの配列
		std::vector<GameObject*>objects;
		for (GameObject* object : m_GameObject[Layer])
		{
			if (object->GetTag() == tag)
			{
				objects.push_back(object);
			}
		}
		return objects;
	}

	//レイヤーごとにすべてのオブジェクトを代入
	std::vector<GameObject*> GetAllGameObjects(int layar)
	{
		std::vector<GameObject*> object;
		for (int i = 0; i < LAYER_MAX; i++)
		{
			if (layar == i)
			{
				for (GameObject* obj : m_GameObject[layar])
				{
					object.push_back(obj);
				}
			}
		}
		return object;
	}

	//レイヤー関係なくすべてのオブジェクトを代入
	std::vector<GameObject> AllObject()
	{
		std::vector<GameObject> object;
		for (int i = 0; i < LAYER_MAX; i++)
		{
			for (GameObject* obj : m_GameObject[i])
			{
				object.push_back(*obj);
			}

		}
		return object;
	}

	//親の名前から子供を検索
	std::vector<GameObject*> GetChildren(std::string ParentName,int layar)
	{
		std::vector<GameObject*> object;

		if (ParentName == "")
			return object;

		for (GameObject* obj : m_GameObject[layar])
		{
			if (obj->GetParent() == ParentName)
			{
				object.push_back(obj);
			}

		}

		return object;
	}



	virtual void Uninit()
	{
		for (int i = 0; i < 3; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{				
				object->Uninit();         //頂点バッファやテクスチャの解放
				delete object;            //オブジェクトのポインタや入れ物を消す
			}
			m_GameObject[i].clear();         //リストのクリア  3段階で消していく
		}

	}

	virtual void Update()
	{
		for (int i = 0; i < 3; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{

				object->Update();

			}

			//ラムダ式
			m_GameObject[i].remove_if([](GameObject* object)
				{return object->Destroy(); });
		}
	}

	virtual void Draw()
	{
		for (int i = 0; i < LAYER_MAX; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				object->Draw();
			}
		}
	}
	
};

