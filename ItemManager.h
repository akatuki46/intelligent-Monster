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
		int   m_Quantity;     //��
		std::string m_ItemName;        //���O
		std::string m_TexName;         //�A�C�e�����e�N�X�`���p�^�O
	}ItemData;

	//�����Ă�A�C�e����
	int  m_AllItem = 0;

	std::map<int, ItemData> m_HaveItem;
	std::map<std::string, Item*> m_ItemContainer;

	int  m_CurrentItemNum = 0;
	int  m_NextItemNum = 0;
	int  m_BackItemNum = 0;
	bool m_ItemListDraw = false;

	GameObject* CurrentItem = nullptr;

	//�A�C�e����
	GameObject* ItemName = nullptr;
	//�A�C�e��������
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

