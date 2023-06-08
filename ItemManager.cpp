#include "ItemManager.h"
#include "Potion.h"
#include "Scene.h"
#include "manager.h"
#include "input.h" 
#include "MaxPotion.h"
#include "NumberDraw2D.h"
#include "SizeDraw2D.h"
#include "PotionG.h"
#include "Padinput.h"

void ItemManager::Init()
{
	//ここでアイテムの順番とインスタンス、名前、個数を指定
	Scene* scene = Manager::GetScene();

	item = new Potion;

	//アイテムコンテナ アイテムを順番気にせず追加
	m_ItemContainer["Potion"] = new Potion;
	m_ItemContainer["MaxPotion"] = new MaxPotion;
	m_ItemContainer["PotionG"] = new PotionG;


	//HaveItemで個数と名前、順番を指定
	//回復薬
	m_HaveItem[0].m_ItemName = "Potion";
	m_HaveItem[0].m_Quantity = 10;
	m_HaveItem[0].m_TexName = "Potion_Name";

	//回復薬G
	m_HaveItem[1].m_ItemName = "PotionG";
	m_HaveItem[1].m_Quantity = 10;
	m_HaveItem[1].m_TexName = "PotionG_Name";

	//秘薬
	m_HaveItem[2].m_ItemName = "MaxPotion";
	m_HaveItem[2].m_Quantity = 2;
	m_HaveItem[2].m_TexName = "MaxPotion_Name";




	for (auto data : m_HaveItem)
	{
		if (data.first == m_CurrentItemNum)
		{
			CurrentItem = new GameObject;
			CurrentItem->SetPosition(D3DXVECTOR3(1700.0f, 850.0f, 0.0f));
			CurrentItem->AddComponent<SizeDraw2D>()->Init(D3DXVECTOR3(100.0f, 100.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), 1);
			CurrentItem->SetTag(data.second.m_ItemName);
			scene->AddGameObject(CurrentItem, scene->UI_LAYER);

		}
	}




	ItemNum = new GameObject;
	ItemNum->SetTag("Number");
	ItemNum->SetPosition(D3DXVECTOR3(1780.0f, 900.0f, 0.0f));
	ItemNum->AddComponent<NumberDraw2D>()->Init(D3DXVECTOR2(50.0f,50.0f), 2, 30.0f);
	scene->AddGameObject(ItemNum, scene->UI_LAYER);

	GameObject* Next = new GameObject;
	Next->SetPosition(D3DXVECTOR3(1800.0f, 850.0f, 0.0f));
	Next->AddComponent<SizeDraw2D>()->Init(D3DXVECTOR3(80.0f, 80.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), 1);
	Next->GetComponent<SizeDraw2D>()->SetDrawFlag(false);
	Next->SetTag("None");
	NextItem = scene->AddGameObject(Next, scene->UI_LAYER);

	GameObject* Back = new GameObject;
	Back->SetPosition(D3DXVECTOR3(1600.0f, 850.0f, 0.0f));
	Back->AddComponent<SizeDraw2D>()->Init(D3DXVECTOR3(80.0f, 80.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), 1);
	Back->GetComponent<SizeDraw2D>()->SetDrawFlag(false);
	Back->SetTag("None");
	BackItem = scene->AddGameObject(Back, scene->UI_LAYER);

	ItemName = new GameObject;
	ItemName->SetPosition(D3DXVECTOR3(1700.0f, 970.0f, 0.0f));
	ItemName->AddComponent<SizeDraw2D>()->Init(D3DXVECTOR3(200.0f, 100.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), 1);
	ItemName->SetTag("None");
	scene->AddGameObject(ItemName, scene->UI_LAYER);
}

void ItemManager::Uninit()
{

}

void ItemManager::Draw(){}

void ItemManager::Update()
{
	Scene* scene = Manager::GetScene();
	int ListSize = m_HaveItem.size() - 1;

	if (GetKeyboardPress(DIK_LCONTROL) || IsButtonXinputPressed(0, XINPUT_GAMEPAD_LEFT_SHOULDER))
	{
		m_ItemListDraw = true;
		if (GetKeyboardTrigger(DIK_LEFT) || IsButtonXinputTriggered(0, XINPUT_GAMEPAD_X))
		{
			m_CurrentItemNum--;

		}
		if (GetKeyboardTrigger(DIK_RIGHT) || IsButtonXinputTriggered(0, XINPUT_GAMEPAD_B))
		{
			m_CurrentItemNum++;
		}
		
		m_NextItemNum = m_CurrentItemNum + 1;
		m_BackItemNum = m_CurrentItemNum - 1;

		if (m_CurrentItemNum >= ListSize)
		{
			m_NextItemNum = 0;

			if (m_CurrentItemNum > ListSize)
			{
				m_CurrentItemNum = 0;
				m_NextItemNum = m_CurrentItemNum + 1;
				m_BackItemNum = ListSize;
			}

		}

		if (m_CurrentItemNum <= 0)
		{
			m_BackItemNum = ListSize;

			if (m_CurrentItemNum < 0)
			{
				m_CurrentItemNum = ListSize;
				m_NextItemNum = 0;
				m_BackItemNum = m_CurrentItemNum - 1;

			}
		}

		NextItem->GetComponent<SizeDraw2D>()->SetDrawFlag(true);
		NextItem->SetTag(m_HaveItem[m_NextItemNum].m_ItemName);

		BackItem->GetComponent<SizeDraw2D>()->SetDrawFlag(true);
		BackItem->SetTag(m_HaveItem[m_BackItemNum].m_ItemName);
	}
	else
	{
		NextItem->GetComponent<SizeDraw2D>()->SetDrawFlag(false);
		BackItem->GetComponent<SizeDraw2D>()->SetDrawFlag(false);
		m_ItemListDraw = false;
	}
	CurrentItem->SetTag(m_HaveItem[m_CurrentItemNum].m_ItemName);
	ItemNum->GetComponent<NumberDraw2D>()->SetNumCnt(m_HaveItem[m_CurrentItemNum].m_Quantity);
	ItemName->SetTag(m_HaveItem[m_CurrentItemNum].m_TexName);
}

void ItemManager::UseItem()
{
	if (m_HaveItem[m_CurrentItemNum].m_Quantity > 0)
	{
		m_ItemContainer[m_HaveItem[m_CurrentItemNum].m_ItemName]->UseAction();
		m_HaveItem[m_CurrentItemNum].m_Quantity--;
	}

}

