#pragma once
#include "Component.h"
#include <map>
class Item;
class GameObject;

class ItemManager :
    public Component
{
private:
	typedef struct
	{
		int   m_Quantity;     //個数
		std::string m_ItemName;        //名前
		std::string m_TexName;         //アイテム名テクスチャ用タグ
	}ItemData;

	//持ってるアイテム数
	int  m_AllItem = 0;

	std::map<int, ItemData> m_HaveItem;
	std::map<std::string, Item*> m_ItemContainer;

	int  m_CurrentItemNum = 0;
	int  m_NextItemNum = 0;
	int  m_BackItemNum = 0;
	bool m_ItemListDraw = false;

	GameObject* CurrentItem = nullptr;

	//アイテム名
	GameObject* ItemName = nullptr;
	//アイテム所持数
	GameObject* ItemNum = nullptr;

	GameObject* NextItem = nullptr;
	GameObject* BackItem = nullptr;


	Item* item = nullptr;
public:
	void Init();
	void Uninit() override;
	void Draw() override;
	void Update()override;

	void SetItemNum(int Num) { m_CurrentItemNum = Num; }

	void UseItem();
	bool GetListDraw() { return m_ItemListDraw; }
};

