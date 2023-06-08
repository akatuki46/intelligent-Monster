#include "Motion.h"
#include "Scene.h"
#include "manager.h"
#include "Draw3D.h"
#include "input.h"

void Motion::Init()
{
	Scene* scene = Manager::GetScene();


	//è„îºêg
	GameObject* Core = new GameObject;
	Core->SetScale(D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	Core->SetCollsionNone(false);
	Core->AddComponent<Draw3D>()->Init();
	Core->GetComponent<Draw3D>()->SetNotDraw(false);
	Core->SetTag("Core");
	m_MotionModel["Core"] = scene->AddGameObject(Core, scene->PLAY_LAYER);

	//è„îºêg
	GameObject* UpBody = new GameObject;
	UpBody->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	UpBody->SetCollsionNone(false);
	UpBody->AddComponent<Draw3D>()->Init();
	UpBody->SetTag("UpBody");
	UpBody->SetParent("Core");
	m_MotionModel["UpBody"] = scene->AddGameObject(UpBody, scene->PLAY_LAYER);
	m_KeepPos["UpBody"] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//â∫îºêg
	GameObject* LowBody = new GameObject;
	LowBody->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	LowBody->SetCollsionNone(false);
	LowBody->AddComponent<Draw3D>()->Init();
	LowBody->SetTag("LowBody");
	LowBody->SetParent("Core");
	m_MotionModel["LowBody"] = scene->AddGameObject(LowBody, scene->PLAY_LAYER);
	m_KeepPos["LowBody"] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//è„ä{
	GameObject* Ueago = new GameObject;
	Ueago->SetPosition(D3DXVECTOR3(0.0f, 1.5f, 2.1f));
	Ueago->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	Ueago->SetCollsionNone(false);
	Ueago->AddComponent<Draw3D>()->Init();
	Ueago->SetTag("Ueago");
	Ueago->SetParent("UpBody");
	m_MotionModel["Ueago"] = scene->AddGameObject(Ueago, scene->PLAY_LAYER);
	m_KeepPos["Ueago"] = D3DXVECTOR3(0.0f, 1.5f, 2.1f);

	//â∫ä{
	GameObject* Sitaago = new GameObject;
	Sitaago->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	Sitaago->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	Sitaago->SetCollsionNone(false);
	Sitaago->AddComponent<Draw3D>()->Init();
	Sitaago->SetTag("Sitaago");
	Sitaago->SetParent("Ueago");
	m_MotionModel["Sitaago"] = scene->AddGameObject(Sitaago, scene->PLAY_LAYER);
	m_KeepPos["Sitaago"] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//âEå®
	GameObject* Rkata = new GameObject;
	Rkata->SetPosition(D3DXVECTOR3(-0.8f, 0.8f, 1.0f));
	Rkata->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	Rkata->SetCollsionNone(false);
	Rkata->AddComponent<Draw3D>()->Init();
	Rkata->SetTag("Rkata");
	Rkata->SetParent("UpBody");
	m_MotionModel["Rkata"] = scene->AddGameObject(Rkata, scene->PLAY_LAYER);
	m_KeepPos["Rkata"] = D3DXVECTOR3(-0.8f, 0.8f, 1.0f);

	//ç∂å®
	GameObject* Lkata = new GameObject;
	Lkata->SetPosition(D3DXVECTOR3(0.8f, 0.8f, 1.0f));
	Lkata->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	Lkata->SetCollsionNone(false);
	Lkata->AddComponent<Draw3D>()->Init();
	Lkata->SetTag("Lkata");
	Lkata->SetParent("UpBody");
	m_MotionModel["Lkata"] = scene->AddGameObject(Lkata, scene->PLAY_LAYER);
	m_KeepPos["Lkata"] = D3DXVECTOR3(0.8f, 0.8f, 1.0f);

	//âEòr
	GameObject* Rude = new GameObject;
	Rude->SetPosition(D3DXVECTOR3(-0.2f, -0.5f, -0.2f));
	Rude->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	Rude->SetCollsionNone(false);
	Rude->AddComponent<Draw3D>()->Init();
	Rude->SetTag("Rude");
	Rude->SetParent("Rkata");
	m_MotionModel["Rude"] = scene->AddGameObject(Rude, scene->PLAY_LAYER);
	m_KeepPos["Rude"] = D3DXVECTOR3(-0.2f, -0.5f, -0.2f);

	//ç∂òr
	GameObject* Lude = new GameObject;
	Lude->SetPosition(D3DXVECTOR3(0.2f, -0.5f, -0.2f));
	Lude->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	Lude->SetCollsionNone(false);
	Lude->AddComponent<Draw3D>()->Init();
	Lude->SetTag("Lude");
	Lude->SetParent("Lkata");
	m_MotionModel["Lude"] = scene->AddGameObject(Lude, scene->PLAY_LAYER);
	m_KeepPos["Lude"] = D3DXVECTOR3(0.2f, -0.5f, -0.2f);

	//âEéË
	GameObject* Rte = new GameObject;
	Rte->SetPosition(D3DXVECTOR3(-0.3f, -0.9f, 0.2f));
	Rte->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	Rte->SetCollsionNone(false);
	Rte->AddComponent<Draw3D>()->Init();
	Rte->SetTag("Rte");
	Rte->SetParent("Rude");
	m_MotionModel["Rte"] = scene->AddGameObject(Rte, scene->PLAY_LAYER);
	m_KeepPos["Rte"] = D3DXVECTOR3(-0.3f, -0.9f, 0.2f);

	//ç∂éË
	GameObject* Lte = new GameObject;
	Lte->SetPosition(D3DXVECTOR3(0.3f, -0.9f, 0.2f));
	Lte->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	Lte->SetCollsionNone(false);
	Lte->AddComponent<Draw3D>()->Init();
	Lte->SetTag("Lte");
	Lte->SetParent("Lude");
	m_MotionModel["Lte"] = scene->AddGameObject(Lte, scene->PLAY_LAYER);
	m_KeepPos["Lte"] = D3DXVECTOR3(0.3f, -0.9f, 0.2f);
	//âEëOéwÇP
	GameObject* Ryubi1 = new GameObject;
	Ryubi1->SetPosition(D3DXVECTOR3(0.0f, -0.4f, 0.0f));
	Ryubi1->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	Ryubi1->SetCollsionNone(false);
	Ryubi1->AddComponent<Draw3D>()->Init();
	Ryubi1->SetTag("Ryubi1");
	Ryubi1->SetParent("Rte");
	m_MotionModel["Ryubi1"] = scene->AddGameObject(Ryubi1, scene->PLAY_LAYER);
	m_KeepPos["Ryubi1"] = D3DXVECTOR3(0.0f, -0.4f, 0.0f);
	//âEëOéwÇQ
	GameObject* Ryubi2 = new GameObject;
	Ryubi2->SetPosition(D3DXVECTOR3(0.0f, -0.4f, 0.0f));
	Ryubi2->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	Ryubi2->SetCollsionNone(false);
	Ryubi2->AddComponent<Draw3D>()->Init();
	Ryubi2->SetTag("Ryubi2");
	Ryubi2->SetParent("Rte");
	m_MotionModel["Ryubi2"] = scene->AddGameObject(Ryubi2, scene->PLAY_LAYER);
	m_KeepPos["Ryubi2"] = D3DXVECTOR3(0.0f, -0.4f, 0.0f);

	//âEëOéwÇR
	GameObject* Ryubi3 = new GameObject;
	Ryubi3->SetPosition(D3DXVECTOR3(0.0f, -0.4f, 0.0f));
	Ryubi3->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	Ryubi3->SetCollsionNone(false);
	Ryubi3->AddComponent<Draw3D>()->Init();
	Ryubi3->SetTag("Ryubi3");
	Ryubi3->SetParent("Rte");
	m_MotionModel["Ryubi3"] = scene->AddGameObject(Ryubi3, scene->PLAY_LAYER);
	m_KeepPos["Ryubi3"] = D3DXVECTOR3(0.0f, -0.4f, 0.0f);
	//âEëOéwÇS
	GameObject* Ryubi4 = new GameObject;
	Ryubi4->SetPosition(D3DXVECTOR3(0.0f, -0.4f, 0.0f));
	Ryubi4->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	Ryubi4->SetCollsionNone(false);
	Ryubi4->AddComponent<Draw3D>()->Init();
	Ryubi4->SetTag("Ryubi4");
	Ryubi4->SetParent("Rte");
	m_MotionModel["Ryubi4"] = scene->AddGameObject(Ryubi4, scene->PLAY_LAYER);
	m_KeepPos["Ryubi4"] = D3DXVECTOR3(0.0f, -0.4f, 0.0f);

	//âEëOéwÇT
	GameObject* Ryubi5 = new GameObject;
	Ryubi5->SetPosition(D3DXVECTOR3(0.0f, -0.4f, 0.0f));
	Ryubi5->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	Ryubi5->SetCollsionNone(false);
	Ryubi5->AddComponent<Draw3D>()->Init();
	Ryubi5->SetTag("Ryubi5");
	Ryubi5->SetParent("Rte");
	m_MotionModel["Ryubi5"] = scene->AddGameObject(Ryubi5, scene->PLAY_LAYER);
	m_KeepPos["Ryubi5"] = D3DXVECTOR3(0.0f, -0.4f, 0.0f);

	//ç∂ëOéwÇP
	GameObject* Lyubi1 = new GameObject;
	Lyubi1->SetPosition(D3DXVECTOR3(0.0f, -0.4f, 0.0f));
	Lyubi1->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	Lyubi1->SetCollsionNone(false);
	Lyubi1->AddComponent<Draw3D>()->Init();
	Lyubi1->SetTag("Lyubi1");
	Lyubi1->SetParent("Lte");
	m_MotionModel["Lyubi1"] = scene->AddGameObject(Lyubi1, scene->PLAY_LAYER);
	m_KeepPos["Lyubi1"] = D3DXVECTOR3(0.0f, -0.4f, 0.0f);

	//ç∂ëOéwÇQ
	GameObject* Lyubi2 = new GameObject;
	Lyubi2->SetPosition(D3DXVECTOR3(0.0f, -0.4f, 0.0f));
	Lyubi2->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	Lyubi2->SetCollsionNone(false);
	Lyubi2->AddComponent<Draw3D>()->Init();
	Lyubi2->SetTag("Lyubi2");
	Lyubi2->SetParent("Lte");
	m_MotionModel["Lyubi2"] = scene->AddGameObject(Lyubi2, scene->PLAY_LAYER);
	m_KeepPos["Lyubi2"] = D3DXVECTOR3(0.0f, -0.4f, 0.0f);

	//ç∂ëOéwÇR
	GameObject* Lyubi3 = new GameObject;
	Lyubi3->SetPosition(D3DXVECTOR3(0.0f, -0.4f, 0.0f));
	Lyubi3->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	Lyubi3->SetCollsionNone(false);
	Lyubi3->AddComponent<Draw3D>()->Init();
	Lyubi3->SetTag("Lyubi3");
	Lyubi3->SetParent("Lte");
	m_MotionModel["Lyubi3"] = scene->AddGameObject(Lyubi3, scene->PLAY_LAYER);
	m_KeepPos["Lyubi3"] = D3DXVECTOR3(0.0f, -0.4f, 0.0f);

	//ç∂ëOéwÇS
	GameObject* Lyubi4 = new GameObject;
	Lyubi4->SetPosition(D3DXVECTOR3(0.0f, -0.4f, 0.0f));
	Lyubi4->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	Lyubi4->SetCollsionNone(false);
	Lyubi4->AddComponent<Draw3D>()->Init();
	Lyubi4->SetTag("Lyubi4");
	Lyubi4->SetParent("Lte");
	m_MotionModel["Lyubi4"] = scene->AddGameObject(Lyubi4, scene->PLAY_LAYER);
	m_KeepPos["Lyubi4"] = D3DXVECTOR3(0.0f, -0.4f, 0.0f);

	//ç∂ëOéwÇT
	GameObject* Lyubi5 = new GameObject;
	Lyubi5->SetPosition(D3DXVECTOR3(0.0f, -0.4f, 0.0f));
	Lyubi5->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	Lyubi5->SetCollsionNone(false);
	Lyubi5->AddComponent<Draw3D>()->Init();
	Lyubi5->SetTag("Lyubi5");
	Lyubi5->SetParent("Lte");
	m_MotionModel["Lyubi5"] = scene->AddGameObject(Lyubi5, scene->PLAY_LAYER);
	m_KeepPos["Lyubi5"] = D3DXVECTOR3(0.0f, -0.4f, 0.0f);

	//âEå„ÇÎÇ‡Ç‡
	GameObject* RBmomo = new GameObject;
	RBmomo->SetPosition(D3DXVECTOR3(-0.5f, 0.0f, -0.7f));
	RBmomo->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	RBmomo->SetCollsionNone(false);
	RBmomo->AddComponent<Draw3D>()->Init();
	RBmomo->SetTag("RBmomo");
	RBmomo->SetParent("LowBody");
	m_MotionModel["RBmomo"] = scene->AddGameObject(RBmomo, scene->PLAY_LAYER);
	m_KeepPos["RBmomo"] = D3DXVECTOR3(-0.5f, 0.0f, -0.7f);

	//ç∂å„ÇÎÇ‡Ç‡
	GameObject* LBmomo = new GameObject;
	LBmomo->SetPosition(D3DXVECTOR3(0.5f, 0.0f, -0.7f));
	LBmomo->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	LBmomo->SetCollsionNone(false);
	LBmomo->AddComponent<Draw3D>()->Init();
	LBmomo->SetTag("LBmomo");
	LBmomo->SetParent("LowBody");
	m_MotionModel["LBmomo"] = scene->AddGameObject(LBmomo, scene->PLAY_LAYER);
	m_KeepPos["LBmomo"] = D3DXVECTOR3(0.5f, 0.0f, -0.7f);

	//âEå„ÇÎ„¯
	GameObject* RBsune = new GameObject;
	RBsune->SetPosition(D3DXVECTOR3(-0.2f, -0.7f, 0.0f));
	RBsune->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	RBsune->SetCollsionNone(false);
	RBsune->AddComponent<Draw3D>()->Init();
	RBsune->SetTag("RBsune");
	RBsune->SetParent("RBmomo");
	m_MotionModel["RBsune"] = scene->AddGameObject(RBsune, scene->PLAY_LAYER);
	m_KeepPos["RBsune"] = D3DXVECTOR3(-0.2f, -0.7f, 0.0f);
	//ç∂å„ÇÎ„¯
	GameObject* LBsune = new GameObject;
	LBsune->SetPosition(D3DXVECTOR3(0.2f, -0.7f, 0.0f));
	LBsune->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	LBsune->SetCollsionNone(false);
	LBsune->AddComponent<Draw3D>()->Init();
	LBsune->SetTag("LBsune");
	LBsune->SetParent("LBmomo");
	m_MotionModel["LBsune"] = scene->AddGameObject(LBsune, scene->PLAY_LAYER);
	m_KeepPos["LBsune"] = D3DXVECTOR3(0.2f, -0.7f, 0.0f);

	//âEå„ÇÎë´éÒ
	GameObject* RBankle = new GameObject;
	RBankle->SetPosition(D3DXVECTOR3(-0.1f, -0.2f, -0.6f));
	RBankle->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	RBankle->SetCollsionNone(false);
	RBankle->AddComponent<Draw3D>()->Init();
	RBankle->SetTag("RBankle");
	RBankle->SetParent("RBsune");
	m_MotionModel["RBankle"] = scene->AddGameObject(RBankle, scene->PLAY_LAYER);
	m_KeepPos["RBankle"] = D3DXVECTOR3(-0.1f, -0.2f, -0.6f);

	//ç∂å„ÇÎë´éÒ
	GameObject* LBankle = new GameObject;
	LBankle->SetPosition(D3DXVECTOR3(0.1f, -0.2f, -0.6f));
	LBankle->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	LBankle->SetCollsionNone(false);
	LBankle->AddComponent<Draw3D>()->Init();
	LBankle->SetTag("LBankle");
	LBankle->SetParent("LBsune");
	m_MotionModel["LBankle"] = scene->AddGameObject(LBankle, scene->PLAY_LAYER);
	m_KeepPos["LBankle"] = D3DXVECTOR3(0.1f, -0.2f, -0.6f);

	//âEå„ÇÎéË
	GameObject* RBte = new GameObject;
	RBte->SetPosition(D3DXVECTOR3(0.0f, -0.1f, 0.0f));
	RBte->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	RBte->SetCollsionNone(false);
	RBte->AddComponent<Draw3D>()->Init();
	RBte->SetTag("RBte");
	RBte->SetParent("RBankle");
	m_MotionModel["RBte"] = scene->AddGameObject(RBte, scene->PLAY_LAYER);
	m_KeepPos["RBte"] = D3DXVECTOR3(0.0f, -0.1f, 0.0f);

	//ç∂å„ÇÎéË
	GameObject* LBte = new GameObject;
	LBte->SetPosition(D3DXVECTOR3(0.0f, -0.1f, 0.0f));
	LBte->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	LBte->SetCollsionNone(false);
	LBte->AddComponent<Draw3D>()->Init();
	LBte->SetTag("LBte");
	LBte->SetParent("LBankle");
	m_MotionModel["LBte"] = scene->AddGameObject(LBte, scene->PLAY_LAYER);
	m_KeepPos["LBte"] = D3DXVECTOR3(0.0f, -0.1f, 0.0f);

	//âEå„ÇÎéwÇP
	GameObject* RByubi1 = new GameObject;
	RByubi1->SetPosition(D3DXVECTOR3(0.0f, -0.3f, 0.2f));
	RByubi1->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	RByubi1->SetCollsionNone(false);
	RByubi1->AddComponent<Draw3D>()->Init();
	RByubi1->SetTag("RByubi1");
	RByubi1->SetParent("RBte");
	m_MotionModel["RByubi1"] = scene->AddGameObject(RByubi1, scene->PLAY_LAYER);
	m_KeepPos["RByubi1"] = D3DXVECTOR3(0.0f, -0.3f, 0.2f);

	//âEå„ÇÎéwÇQ
	GameObject* RByubi2 = new GameObject;
	RByubi2->SetPosition(D3DXVECTOR3(0.0f, -0.3f, 0.2f));
	RByubi2->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	RByubi2->SetCollsionNone(false);
	RByubi2->AddComponent<Draw3D>()->Init();
	RByubi2->SetTag("RByubi2");
	RByubi2->SetParent("RBte");
	m_MotionModel["RByubi2"] = scene->AddGameObject(RByubi2, scene->PLAY_LAYER);
	m_KeepPos["RByubi2"] = D3DXVECTOR3(0.0f, -0.3f, 0.2f);

	//âEå„ÇÎéwÇR
	GameObject* RByubi3 = new GameObject;
	RByubi3->SetPosition(D3DXVECTOR3(0.0f, -0.3f, 0.2f));
	RByubi3->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	RByubi3->SetCollsionNone(false);
	RByubi3->AddComponent<Draw3D>()->Init();
	RByubi3->SetTag("RByubi3");
	RByubi3->SetParent("RBte");
	m_MotionModel["RByubi3"] = scene->AddGameObject(RByubi3, scene->PLAY_LAYER);
	m_KeepPos["RByubi3"] = D3DXVECTOR3(0.0f, -0.3f, 0.2f);

	//âEå„ÇÎéwÇS
	GameObject* RByubi4 = new GameObject;
	RByubi4->SetPosition(D3DXVECTOR3(0.0f, -0.3f, 0.2f));
	RByubi4->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	RByubi4->SetCollsionNone(false);
	RByubi4->AddComponent<Draw3D>()->Init();
	RByubi4->SetTag("RByubi4");
	RByubi4->SetParent("RBte");
	m_MotionModel["RByubi4"] = scene->AddGameObject(RByubi4, scene->PLAY_LAYER);
	m_KeepPos["RByubi4"] = D3DXVECTOR3(0.0f, -0.3f, 0.2f);

	//âEå„ÇÎéwÇT
	GameObject* RByubi5 = new GameObject;
	RByubi5->SetPosition(D3DXVECTOR3(0.0f, -0.3f, 0.2f));
	RByubi5->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	RByubi5->SetCollsionNone(false);
	RByubi5->AddComponent<Draw3D>()->Init();
	RByubi5->SetTag("RByubi5");
	RByubi5->SetParent("RBte");
	m_MotionModel["RByubi5"] = scene->AddGameObject(RByubi5, scene->PLAY_LAYER);
	m_KeepPos["RByubi5"] = D3DXVECTOR3(0.0f, -0.3f, 0.2f);

	//ç∂å„ÇÎéwÇP
	GameObject* LByubi1 = new GameObject;
	LByubi1->SetPosition(D3DXVECTOR3(0.0f, -0.3f, 0.2f));
	LByubi1->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	LByubi1->SetCollsionNone(false);
	LByubi1->AddComponent<Draw3D>()->Init();
	LByubi1->SetTag("LByubi1");
	LByubi1->SetParent("LBte");
	m_MotionModel["LByubi1"] = scene->AddGameObject(LByubi1, scene->PLAY_LAYER);
	m_KeepPos["LByubi1"] = D3DXVECTOR3(0.0f, -0.3f, 0.2f);

	//ç∂å„ÇÎéwÇQ
	GameObject* LByubi2 = new GameObject;
	LByubi2->SetPosition(D3DXVECTOR3(0.0f, -0.3f, 0.2f));
	LByubi2->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	LByubi2->SetCollsionNone(false);
	LByubi2->AddComponent<Draw3D>()->Init();
	LByubi2->SetTag("LByubi2");
	LByubi2->SetParent("LBte");
	m_MotionModel["LByubi2"] = scene->AddGameObject(LByubi2, scene->PLAY_LAYER);
	m_KeepPos["LByubi2"] = D3DXVECTOR3(0.0f, -0.3f, 0.2f);

	//ç∂å„ÇÎéwÇR
	GameObject* LByubi3 = new GameObject;
	LByubi3->SetPosition(D3DXVECTOR3(0.0f, -0.3f, 0.2f));
	LByubi3->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	LByubi3->SetCollsionNone(false);
	LByubi3->AddComponent<Draw3D>()->Init();
	LByubi3->SetTag("LByubi3");
	LByubi3->SetParent("LBte");
	m_MotionModel["LByubi3"] = scene->AddGameObject(LByubi3, scene->PLAY_LAYER);
	m_KeepPos["LByubi3"] = D3DXVECTOR3(0.0f, -0.3f, 0.2f);

	//ç∂å„ÇÎéwÇS
	GameObject* LByubi4 = new GameObject;
	LByubi4->SetPosition(D3DXVECTOR3(0.0f, -0.3f, 0.2f));
	LByubi4->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	LByubi4->SetCollsionNone(false);
	LByubi4->AddComponent<Draw3D>()->Init();
	LByubi4->SetTag("LByubi4");
	LByubi4->SetParent("LBte");
	m_MotionModel["LByubi4"] = scene->AddGameObject(LByubi4, scene->PLAY_LAYER);
	m_KeepPos["LByubi4"] = D3DXVECTOR3(0.0f, -0.3f, 0.2f);

	//ç∂å„ÇÎéwÇT
	GameObject* LByubi5 = new GameObject;
	LByubi5->SetPosition(D3DXVECTOR3(0.0f, -0.3f, 0.2f));
	LByubi5->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	LByubi5->SetCollsionNone(false);
	LByubi5->AddComponent<Draw3D>()->Init();
	LByubi5->SetTag("LByubi5");
	LByubi5->SetParent("LBte");
	m_MotionModel["LByubi5"] = scene->AddGameObject(LByubi5, scene->PLAY_LAYER);
	m_KeepPos["LByubi5"] = D3DXVECTOR3(0.0f, -0.3f, 0.2f);

	//êKîˆÇP
	GameObject* Tail1 = new GameObject;
	Tail1->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -1.8f));
	Tail1->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	Tail1->SetCollsionNone(false);
	Tail1->AddComponent<Draw3D>()->Init();
	Tail1->SetTag("Tail1");
	Tail1->SetParent("LowBody");
	m_MotionModel["Tail1"] = scene->AddGameObject(Tail1, scene->PLAY_LAYER);
	m_KeepPos["Tail1"] = D3DXVECTOR3(0.0f, 0.0f, -1.8f);

	//êKîˆÇQ
	GameObject* Tail2 = new GameObject;
	Tail2->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -0.7f));
	Tail2->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	Tail2->SetCollsionNone(false);
	Tail2->AddComponent<Draw3D>()->Init();
	Tail2->SetTag("Tail2");
	Tail2->SetParent("Tail1");
	m_MotionModel["Tail2"] = scene->AddGameObject(Tail2, scene->PLAY_LAYER);
	m_KeepPos["Tail2"] = D3DXVECTOR3(0.0f, 0.0f, -0.7);

	//êKîˆÇR
	GameObject* Tail3 = new GameObject;
	Tail3->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -0.6f));
	Tail3->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	Tail3->SetCollsionNone(false);
	Tail3->AddComponent<Draw3D>()->Init();
	Tail3->SetTag("Tail3");
	Tail3->SetParent("Tail2");
	m_MotionModel["Tail3"] = scene->AddGameObject(Tail3, scene->PLAY_LAYER);
	m_KeepPos["Tail3"] = D3DXVECTOR3(0.0f, 0.0f, -0.6);

	//êKîˆÇS
	GameObject* Tail4 = new GameObject;
	Tail4->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -0.6f));
	Tail4->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	Tail4->SetCollsionNone(false);
	Tail4->AddComponent<Draw3D>()->Init();
	Tail4->SetTag("Tail4");
	Tail4->SetParent("Tail3");
	m_MotionModel["Tail4"] = scene->AddGameObject(Tail4, scene->PLAY_LAYER);
	m_KeepPos["Tail4"] = D3DXVECTOR3(0.0f, 0.0f, -0.6);

	//êKîˆÇS
	GameObject* Tail5 = new GameObject;
	Tail5->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -0.7f));
	Tail5->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	Tail5->SetCollsionNone(false);
	Tail5->AddComponent<Draw3D>()->Init();
	Tail5->SetTag("Tail5");
	Tail5->SetParent("Tail4");
	m_MotionModel["Tail5"] = scene->AddGameObject(Tail5, scene->PLAY_LAYER);
	m_KeepPos["Tail5"] = D3DXVECTOR3(0.0f, 0.0f, -0.7);

	//êKîˆÇS
	GameObject* Tail6 = new GameObject;
	Tail6->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -0.8f));
	Tail6->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	Tail6->SetCollsionNone(false);
	Tail6->AddComponent<Draw3D>()->Init();
	Tail6->SetTag("Tail6");
	Tail6->SetParent("Tail5");
	m_MotionModel["Tail6"] = scene->AddGameObject(Tail6, scene->PLAY_LAYER);
	m_KeepPos["Tail6"] = D3DXVECTOR3(0.0f, 0.0f, -0.8);

	m_Name = "Motion";
}

void Motion::Uninit()
{
	m_MotionModel.clear();
}

void Motion::Update()
{
	m_MotionModel["Core"]->SetPosition(this->m_ParentObject->GetPosition() + D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	m_MotionModel["Core"]->SetRotation(this->m_ParentObject->GetRotation());


	//àÍíUÉtÉåÅ[ÉÄìnÇ≥Ç∏Ç…é¿ëï
	MotionPlay(m_MotionName);

	for (auto data : m_MotionModel)
	{
		data.second->GetComponent<Draw3D>()->SetShaderFlag(m_ShaderCnt);
	}

	if (GetKeyboardTrigger(DIK_RETURN))
	{
		m_ShaderCnt++;
		if (m_ShaderCnt > 2)
		{
			m_ShaderCnt = 0;
		}
	}


}

void Motion::Draw()
{
#ifdef _DEBUG

	if (!m_ImGuiDrawFlag)
		return;

	ImGui::Begin("Motion ImGui", &m_ImGuiDrawFlag);
	ImGui::Text("m_TransChange : %d  0:z  1:x  2:y", m_TransChange);

	if (ImGui::Button("IdlePlay"))
		m_MotionName = "Idle";

	if (ImGui::Button("WalkPlay"))
		m_MotionName = "Walk";

	if (ImGui::Button("RunPlay"))
		m_MotionName = "Run";

	if (ImGui::Button("OtePlay"))
		m_MotionName = "OTE";

	if (ImGui::Button("RoarPlay"))
		m_MotionName = "Roar";

	if (ImGui::Button("ChargePlay"))
		m_MotionName = "Charge";

	if (ImGui::Button("ScratchPlay"))
		m_MotionName = "Scratch";

	if (ImGui::Button("JumpPlay"))
		m_MotionName = "Jump";

	if (ImGui::Button("LandPlay"))
		m_MotionName = "Land";

	if (ImGui::Button("ShotPlay"))
		m_MotionName = "Shot";
	
	if (ImGui::Button("DiePlay"))
		m_MotionName = "Die";

	//ãØÇ›
	if (ImGui::Button("FearPlay"))
		m_MotionName = "Fear";

	if (ImGui::Button("LeftOtePlay"))
		m_MotionName = "LeftOte";

	if (ImGui::Button("TacklePlay"))
		m_MotionName = "Tackle";

	for(auto data : m_MotionModel)
	{
		if (ImGui::TreeNode(data.first.c_str()))
		{
			if (ImGui::TreeNode("Rotation"))
			{
				m_ImguiRot = data.second->GetRotation();
				ImGui::InputFloat("RotationX", &m_ImguiRot.x);
				ImGui::InputFloat("RotationY", &m_ImguiRot.y);
				ImGui::InputFloat("RotationZ", &m_ImguiRot.z);
				data.second->SetRotation(m_ImguiRot);
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("Position"))
			{
				m_ImguiPos = data.second->GetPosition();
				ImGui::InputFloat("PositionX", &m_ImguiPos.x);
				ImGui::InputFloat("PositionY", &m_ImguiPos.y);
				ImGui::InputFloat("PositionZ", &m_ImguiPos.z);
				data.second->SetPosition(m_ImguiPos);

				ImGui::TreePop();
			}

			ImGui::TreePop();
		}

		ImGui::Separator();
	}


	ImGui::End();

#endif // !_DEBUG


	//for (auto data : m_MotionModel)
	//{
	//	data.second->Draw();
	//}
}

void Motion::MotionPlay(std::string PlayMotion)
{
	if (m_OldMotion != PlayMotion)
	{
		FirstFlag = true;
		m_FlameCnt = 0;
		m_FlameCnt2 = -5;
		transFlag = 1;
		transFlag2 = 1;
		m_MotionCnt = 0;
		m_MotionEnd = false;
		m_MotionPoint = false;
	}

	//ÉÇÅ[ÉVÉáÉìäJénéûÇ…rotationÇ∆PositionÇèâä˙âª
	if (m_FlameCnt == 0 && PlayMotion != "")
	{
		m_OldMotion = PlayMotion;
		m_FlameCnt = 0;
		m_MotionDelyFlag = false;
		ChangeMotion = 0;
		m_MotionEnd = false;
		m_MotionPoint = false;

		for (auto data : m_MotionModel)
		{

			data.second->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			data.second->SetPosition(m_KeepPos[data.first]);
		}

		if (PlayMotion == "Idle")
		{
			m_MotionModel["Ueago"]->SetRotation(D3DXVECTOR3(0.4f, -0.4f, 0.0f));
			m_MotionModel["Rkata"]->SetRotation(D3DXVECTOR3(-0.3f, 0.0f, -0.5f));
			m_MotionModel["Lkata"]->SetRotation(D3DXVECTOR3(-0.3f, 0.0f, 0.5f));
			m_MotionModel["Rude"]->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.3f));
			m_MotionModel["Lude"]->SetRotation(D3DXVECTOR3(0.0f, 0.0f, -0.3f));
			m_MotionModel["UpBody"]->SetRotation(D3DXVECTOR3(0.2f, 0.0f, 0.0f));

		}
		if (PlayMotion == "Walk")
		{
			m_MotionModel["UpBody"]->SetRotation(D3DXVECTOR3(0.2f, 0.0f, 0.0f));
			m_MotionModel["Rkata"]->SetRotation(D3DXVECTOR3(-0.9f, 0.5f, 0.0f));
			m_MotionModel["Lkata"]->SetRotation(D3DXVECTOR3(0.4f, 0.5f, -0.4f));
			m_MotionModel["Rte"]->SetRotation(D3DXVECTOR3(0.4f, 0.0f, -0.2f));
			m_MotionModel["Lte"]->SetRotation(D3DXVECTOR3(0.0f, -0.9f, 0.5f));
			m_MotionModel["LBmomo"]->SetRotation(D3DXVECTOR3(-0.5f, 0.0f, 0.0f));
			m_MotionModel["RBmomo"]->SetRotation(D3DXVECTOR3(0.2f, 0.0f, 0.0f));
			m_MotionModel["RBsune"]->SetRotation(D3DXVECTOR3(0.1f, 0.f, 0.0f));

			//ç≈èIìIÇ»âÒì]ílÇ©ÇÁåªç›ÇÃâÒì]ílÇà¯Ç´ÅAÉtÉåÅ[ÉÄÇ≈äÑÇÈÇ±Ç∆Ç≈1ÉtÉåÅ[ÉÄìñÇΩÇËÇÃâÒì]êîílÇãÅÇﬂÇÈ
			m_InOutValue["UpBody"] = (D3DXVECTOR3(0.15f, 0.0f, 0.0f) - m_MotionModel["UpBody"]->GetRotation()) / 30;
			m_InOutValue["LowBody"] = (D3DXVECTOR3(0.05f, 0.0f, 0.0f) - m_MotionModel["LowBody"]->GetRotation()) / 30;
			m_InOutValue["Rkata"] = (D3DXVECTOR3(0.4f, 0.5f, 0.4f) - m_MotionModel["Rkata"]->GetRotation())/30;
			m_InOutValue["Lkata"] = (D3DXVECTOR3(-0.9f, -0.5f, 0.0f) - m_MotionModel["Lkata"]->GetRotation())/30;
			m_InOutValue["Rte"] = (D3DXVECTOR3(0.0f, 0.9f, -0.5f) - m_MotionModel["Rte"]->GetRotation())/30;
			m_InOutValue["Lte"] = (D3DXVECTOR3(0.4f, 0.0f, 0.2f) - m_MotionModel["Lte"]->GetRotation())/30;
			m_InOutValue["RBmomo"] = (D3DXVECTOR3(-0.5f, 0.0f, 0.0f) - m_MotionModel["RBmomo"]->GetRotation())/30;
			m_InOutValue["LBmomo"] = (D3DXVECTOR3(0.2f, 0.0f, 0.0f) - m_MotionModel["LBmomo"]->GetRotation())/30;

		}

		if (PlayMotion == "Run")
		{
			m_MotionModel["Rkata"]->SetRotation(D3DXVECTOR3(-1.1f, 0.3f, 0.0f));
			m_MotionModel["Lkata"]->SetRotation(D3DXVECTOR3(-1.1f, -0.3f, 0.0f));
			m_MotionModel["Rude"]->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.1f));
			m_MotionModel["Lude"]->SetRotation(D3DXVECTOR3(0.0f, 0.0f, -0.1f));
			m_MotionModel["Rte"]->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_MotionModel["Lte"]->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_MotionModel["LBmomo"]->SetRotation(D3DXVECTOR3(0.6f, 0.0f, 0.0f));
			m_MotionModel["RBmomo"]->SetRotation(D3DXVECTOR3(0.6f, 0.0f, 0.0f));

			//ç≈èIìIÇ»âÒì]ílÇ©ÇÁåªç›ÇÃâÒì]ílÇà¯Ç´ÅAÉtÉåÅ[ÉÄÇ≈äÑÇÈÇ±Ç∆Ç≈1ÉtÉåÅ[ÉÄìñÇΩÇËÇÃâÒì]êîílÇãÅÇﬂÇÈ
			m_InOutValue["UpBody"] = (D3DXVECTOR3(0.2f, 0.0f, 0.0f) - m_MotionModel["UpBody"]->GetRotation()) / 10;
			m_InOutValue["LowBody"] = (D3DXVECTOR3(-0.2f, 0.0f, 0.0f) - m_MotionModel["UpBody"]->GetRotation()) / 10;

			m_InOutValue["Rkata"] = (D3DXVECTOR3(0.4f, 0.0f, 0.4f) - m_MotionModel["Rkata"]->GetRotation()) / 10;
			m_InOutValue["Lkata"] = (D3DXVECTOR3(0.4f, 0.0f, -0.4f) - m_MotionModel["Lkata"]->GetRotation()) / 10;
			m_InOutValue["Rte"] = (D3DXVECTOR3(-0.4f, 0.0f, 0.0f) - m_MotionModel["Rte"]->GetRotation()) / 10;
			m_InOutValue["Lte"] = (D3DXVECTOR3(-0.4f, 0.0f, 0.0f) - m_MotionModel["Lte"]->GetRotation()) / 10;
			m_InOutValue["RBmomo"] = (D3DXVECTOR3(-0.3f, 0.0f, 0.0f) - m_MotionModel["RBmomo"]->GetRotation()) / 10;
			m_InOutValue["LBmomo"] = (D3DXVECTOR3(-0.3f, 0.0f, 0.0f) - m_MotionModel["LBmomo"]->GetRotation()) / 10;

		}

		if (PlayMotion == "OTE")
		{
			m_InOutValue["Ueago"] = (D3DXVECTOR3(0.8f, 0.0f, 0.0f) - m_MotionModel["Ueago"]->GetRotation()) / 40;
			m_InOutValue["LowBody"] = (D3DXVECTOR3(-0.2f, 0.0f, 0.0f) - m_MotionModel["LowBody"]->GetRotation()) / 40;
			m_InOutValue["UpBody"] = (D3DXVECTOR3(-1.3f, 0.0f, 0.3f) - m_MotionModel["UpBody"]->GetRotation()) / 40;
			m_InOutValue["Rkata"] = (D3DXVECTOR3(0.4f, 0.0f, -0.1f) - m_MotionModel["Rkata"]->GetRotation()) / 40;
			m_InOutValue["Rude"] = (D3DXVECTOR3(-0.7f, 0.0f, 0.5f) - m_MotionModel["Rude"]->GetRotation()) / 40;
			m_InOutValue["Rte"] = (D3DXVECTOR3(1.3f, 0.0f, 0.0f) - m_MotionModel["Rte"]->GetRotation()) / 40;
			m_InOutValue["Lkata"] = (D3DXVECTOR3(2.5f, 0.3f, 0.1f) - m_MotionModel["Lkata"]->GetRotation()) / 40;
			m_InOutValue["Lude"] = (D3DXVECTOR3(-2.7f, 0.0f, 0.0f) - m_MotionModel["Lude"]->GetRotation()) / 40;
			m_InOutValue["Lte"] = (D3DXVECTOR3(-0.1f, 0.0f, 0.0f) - m_MotionModel["Lte"]->GetRotation()) / 40;
			m_MotionFlame = 41;

		}
		if (PlayMotion == "Roar")
		{
			m_InOutValue["Ueago"] = (D3DXVECTOR3(-0.8f, 0.0f, 0.0f) - m_MotionModel["Ueago"]->GetRotation()) / 20;
			m_InOutValue["Lkata"] = (D3DXVECTOR3(0.4f, 0.0f, 0.0f) - m_MotionModel["Lkata"]->GetRotation()) / 20;
			m_InOutValue["UpBody"] = (D3DXVECTOR3(-0.6f, 0.0f, 0.0f) - m_MotionModel["UpBody"]->GetRotation()) / 20;
			m_InOutValue["Rkata"] = (D3DXVECTOR3(0.4f, 0.0f, 0.0f) - m_MotionModel["Rkata"]->GetRotation()) / 20;
			m_InOutValue["Rude"] = (D3DXVECTOR3(0.2f, 0.0f, 0.0f) - m_MotionModel["Rude"]->GetRotation()) / 20;
			m_InOutValue["Lude"] = (D3DXVECTOR3(0.2f, 0.0f, 0.0f) - m_MotionModel["Lude"]->GetRotation()) / 20;

		}
		if (PlayMotion == "Charge")
		{
			m_MotionModel["Lkata"]->SetRotation(D3DXVECTOR3(-0.4f, 0.0f, 0.0f));
			m_MotionModel["UpBody"]->SetRotation(D3DXVECTOR3(0.3f, 0.0f, 0.0f));
			m_MotionModel["Rkata"]->SetRotation(D3DXVECTOR3(-0.4f, 0.0f, 0.0f));

			m_InOutValue["Ueago"] = (D3DXVECTOR3(0.0f, 0.0f, 0.0f) - m_MotionModel["Lkata"]->GetRotation()) / 20;

			m_InOutValue["Lkata"] = (D3DXVECTOR3(0.0f, 0.0f, 0.0f) - m_MotionModel["Lkata"]->GetRotation()) / 20;
			m_InOutValue["UpBody"] = (D3DXVECTOR3(0.0f, 0.0f, 0.0f) - m_MotionModel["UpBody"]->GetRotation()) / 20;
			m_InOutValue["Rkata"] = (D3DXVECTOR3(0.0f, 0.0f, 0.0f) - m_MotionModel["Rkata"]->GetRotation()) / 20;

		}

		if (PlayMotion == "Scratch")
		{
			m_MotionModel["Rkata"]->SetRotation(D3DXVECTOR3(-0.1f, 0.0f, 0.3f));
			m_MotionModel["Rude"]->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.2f));
			m_MotionModel["Lude"]->SetRotation(D3DXVECTOR3(0.0f, -0.2f, 0.4f));
			m_MotionModel["Rte"]->SetRotation(D3DXVECTOR3(0.0f, 0.0f, -0.44f));
			m_MotionModel["Lte"]->SetRotation(D3DXVECTOR3(0.4f, 0.8f, 0.0f));
			m_MotionModel["Lkata"]->SetRotation(D3DXVECTOR3(-1.0f, 0.0f, 0.1f));
			m_MotionModel["UpBody"]->SetRotation(D3DXVECTOR3(-0.1f, 0.0f, 0.0f));

			m_InOutValue["Lude"] = (D3DXVECTOR3(0.0f, -0.2f, -1.0f) - m_MotionModel["Lude"]->GetRotation()) / 30;
			m_InOutValue["Lkata"] = (D3DXVECTOR3(-1.0f, 0.0f, -1.0f) - m_MotionModel["Lkata"]->GetRotation()) / 30;
			m_InOutValue["UpBody"] = (D3DXVECTOR3(0.0f, 0.0f, 0.0f) - m_MotionModel["UpBody"]->GetRotation()) / 30;

		
		}

		if (PlayMotion == "Jump")
		{
			m_InOutValue["LowBody"] = (D3DXVECTOR3(0.1f, 0.0f, 0.0f) - m_MotionModel["LowBody"]->GetRotation()) / 30;
			m_InOutValue["Lkata"] = (D3DXVECTOR3(-0.3f, 0.0f, 0.1f) - m_MotionModel["Lkata"]->GetRotation()) / 30;
			m_InOutValue["UpBody"] = (D3DXVECTOR3(-0.1f, 0.0f, 0.0f) - m_MotionModel["UpBody"]->GetRotation()) / 30;
			m_InOutValue["Rkata"] = (D3DXVECTOR3(-0.3f, 0.0f, -0.1f) - m_MotionModel["Rkata"]->GetRotation()) / 30;
			m_InOutValue["Rude"] = (D3DXVECTOR3(0.0f, 0.0f, 0.0f) - m_MotionModel["Rude"]->GetRotation()) / 30;
			m_InOutValue["Lude"] = (D3DXVECTOR3(0.0f, 0.0f, 0.0f) - m_MotionModel["Lude"]->GetRotation()) / 30;
			m_InOutValue["Lte"] = (D3DXVECTOR3(0.0f, 0.0f, 0.0f) - m_MotionModel["Lte"]->GetRotation()) / 30;



			m_InOutValuePos["UpBody"] = (D3DXVECTOR3(0.0f, -0.5f, -1.2f) - m_MotionModel["UpBody"]->GetPosition()) / 30;
			m_InOutValuePos["Lkata"] = (D3DXVECTOR3(0.8f, 1.0f, 1.2f) - m_MotionModel["Lkata"]->GetPosition()) / 30;
			m_InOutValuePos["LowBody"] = (D3DXVECTOR3(0.0f, 0.0f, -0.7f) - m_MotionModel["LowBody"]->GetPosition()) / 30;
			m_InOutValuePos["Rkata"] = (D3DXVECTOR3(-0.8f, 1.0f, 1.2f) - m_MotionModel["Rkata"]->GetPosition()) / 30;

		}

		if (PlayMotion == "Land")
		{
			m_MotionModel["UpBody"]->SetRotation(D3DXVECTOR3(-0.2f, 0.0f, -0.2f));
			m_MotionModel["LowBody"]->SetRotation(D3DXVECTOR3(-0.4f, 0.0f, -0.2f));
			m_MotionModel["Lkata"]->SetRotation(D3DXVECTOR3(-0.6f, 0.0f, 0.0f));
			m_MotionModel["Rkata"]->SetRotation(D3DXVECTOR3(-0.1f, 0.0f, -0.7f));
			m_MotionModel["Rude"]->SetRotation(D3DXVECTOR3(-1.0f, 0.0f, 0.3f));
			m_MotionModel["Lude"]->SetRotation(D3DXVECTOR3(0.5f, -0.4f, -0.9f));
			m_MotionModel["Lte"]->SetRotation(D3DXVECTOR3(0.5f, 0.0f, 0.0f));

			m_MotionModel["UpBody"]->SetPosition(D3DXVECTOR3(0.0f, 1.0f, -0.2f));
			m_MotionModel["LowBody"]->SetPosition(D3DXVECTOR3(0.0f, 1.0f, -0.1f));

			m_InOutValue["LowBody"] = (D3DXVECTOR3(0.2f, 0.0f, 0.0f) - m_MotionModel["LowBody"]->GetRotation()) / 30;
			m_InOutValue["Lkata"] = (D3DXVECTOR3(0.3f, 0.0f, -0.3f) - m_MotionModel["Lkata"]->GetRotation()) / 30;
			m_InOutValue["UpBody"] = (D3DXVECTOR3(-0.1f, 0.0f, 0.0f) - m_MotionModel["UpBody"]->GetRotation()) / 30;
			m_InOutValue["Rkata"] = (D3DXVECTOR3(-0.4f, 0.3f, 0.4f) - m_MotionModel["Rkata"]->GetRotation()) / 30;
			m_InOutValue["Rude"] = (D3DXVECTOR3(0.3f, 0.0f, 0.3f) - m_MotionModel["Rude"]->GetRotation()) / 30;
			m_InOutValue["Lude"] = (D3DXVECTOR3(0.3f, 0.0f, -0.3f) - m_MotionModel["Lude"]->GetRotation()) / 30;
			m_InOutValue["Lte"] = (D3DXVECTOR3(0.0f, 0.0f, -0.1f) - m_MotionModel["Lte"]->GetRotation()) / 30;
			m_InOutValue["Rte"] = (D3DXVECTOR3(0.0f, 0.0f, -0.6f) - m_MotionModel["Rte"]->GetRotation()) / 30;
			m_InOutValue["RBmomo"] = (D3DXVECTOR3(-0.4f, 0.0f, 0.0f) - m_MotionModel["RBmomo"]->GetRotation()) / 30;
			m_InOutValue["LBmomo"] = (D3DXVECTOR3(-0.4f, 0.0f, 0.0f) - m_MotionModel["LBmomo"]->GetRotation()) / 30;
			m_InOutValue["Tail1"] = (D3DXVECTOR3(0.1f, 0.0f, 0.0f) - m_MotionModel["Tail1"]->GetRotation()) / 30;
			m_InOutValue["Tail2"] = (D3DXVECTOR3(0.1f, 0.0f, 0.0f) - m_MotionModel["Tail2"]->GetRotation()) / 30;
			m_InOutValue["Tail3"] = (D3DXVECTOR3(0.1f, 0.0f, 0.0f) - m_MotionModel["Tail3"]->GetRotation()) / 30;
			m_InOutValue["Tail4"] = (D3DXVECTOR3(0.1f, 0.0f, 0.0f) - m_MotionModel["Tail4"]->GetRotation()) / 30;
			m_InOutValue["Tail5"] = (D3DXVECTOR3(0.1f, 0.0f, 0.0f) - m_MotionModel["Tail5"]->GetRotation()) / 30;
			m_InOutValue["Tail6"] = (D3DXVECTOR3(0.1f, 0.0f, 0.0f) - m_MotionModel["Tail6"]->GetRotation()) / 30;

			m_InOutValuePos["UpBody"] = (D3DXVECTOR3(0.0f, 0.0f, 0.0f) - m_MotionModel["UpBody"]->GetPosition()) / 30;
			m_InOutValuePos["LowBody"] = (D3DXVECTOR3(0.0f, 0.0f, 0.0f) - m_MotionModel["LowBody"]->GetPosition()) / 30;


		}

		if (PlayMotion == "Shot")
		{
			m_InOutValue["LowBody"] = (D3DXVECTOR3(0.2f, 0.5f, 0.0f) - m_MotionModel["LowBody"]->GetRotation()) / 20;
			m_InOutValue["Lkata"] = (D3DXVECTOR3(0.9f, 0.0f, 0.0f) - m_MotionModel["Lkata"]->GetRotation()) / 20;
			m_InOutValue["UpBody"] = (D3DXVECTOR3(0.3f, 0.4f, 0.0f) - m_MotionModel["UpBody"]->GetRotation()) / 20;
			m_InOutValue["Rkata"] = (D3DXVECTOR3(0.5f, 0.3f, 0.0f) - m_MotionModel["Rkata"]->GetRotation()) / 20;
			m_InOutValue["Rude"] = (D3DXVECTOR3(-1.2f, -0.1f, 0.0f) - m_MotionModel["Rude"]->GetRotation()) / 20;
			m_InOutValue["Lude"] = (D3DXVECTOR3(-1.2f, 0.0f, 0.0f) - m_MotionModel["Lude"]->GetRotation()) / 20;
			m_InOutValue["Rte"] = (D3DXVECTOR3(0.3f, 0.0f, 0.0f) - m_MotionModel["Rte"]->GetRotation()) / 20;
			m_InOutValue["Ueago"] = (D3DXVECTOR3(0.0f, -0.4f, 0.0f) - m_MotionModel["Ueago"]->GetRotation()) / 20;
			m_InOutValue["Tail1"] = (D3DXVECTOR3(0.2f, -0.5f, -0.1f) - m_MotionModel["Tail1"]->GetRotation()) / 20;
			m_InOutValue["Tail2"] = (D3DXVECTOR3(0.2f, -0.2f, 0.0f) - m_MotionModel["Tail2"]->GetRotation()) / 20;
			m_InOutValue["Tail3"] = (D3DXVECTOR3(0.2f, -0.2f, -0.3f) - m_MotionModel["Tail3"]->GetRotation()) / 20;
			m_InOutValue["Tail4"] = (D3DXVECTOR3(0.3f, 0.0f, 0.0f) - m_MotionModel["Tail4"]->GetRotation()) / 20;

			m_InOutValuePos["UpBody"] = (D3DXVECTOR3(0.0f, -0.5f, 0.0f) - m_MotionModel["UpBody"]->GetPosition()) / 20;
			m_InOutValuePos["LowBody"] = (D3DXVECTOR3(0.0f, -0.4f, 0.0f) - m_MotionModel["LowBody"]->GetPosition()) / 20;

			m_MotionFlame = 21;
		}

		if (PlayMotion == "Die")
		{
			m_InOutValue["UpBody"] = (D3DXVECTOR3(0.4f, 0.0f, 0.0f) - m_MotionModel["UpBody"]->GetRotation()) / 60;
			m_InOutValue["Lkata"] = (D3DXVECTOR3(0.5f, 0.0f, 0.2f) - m_MotionModel["Lkata"]->GetRotation()) / 60;
			m_InOutValue["Ueago"] = (D3DXVECTOR3(0.6f, 0.3f, 0.0f) - m_MotionModel["Ueago"]->GetRotation()) / 60;
			m_InOutValue["Rkata"] = (D3DXVECTOR3(-0.5f, 0.0f, -0.2f) - m_MotionModel["Rkata"]->GetRotation()) / 60;
			m_InOutValue["Lude"] = (D3DXVECTOR3(-0.8f, 0.0f, 0.0f) - m_MotionModel["Lude"]->GetRotation()) / 60;

			m_MotionFlame = 61;
		}
		
		if (PlayMotion == "Fear")
		{
			m_InOutValue["UpBody"] = (D3DXVECTOR3(-0.5f, 0.0f, 0.0f) - m_MotionModel["UpBody"]->GetRotation()) / 30;
			m_InOutValue["LowBody"] = (D3DXVECTOR3(-0.2f, 0.0f, 0.0f) - m_MotionModel["LowBody"]->GetRotation()) / 30;
			m_InOutValue["Rkata"] = (D3DXVECTOR3(-1.0f, 0.0f, 0.0f) - m_MotionModel["Rkata"]->GetRotation()) / 30;
			m_InOutValue["Rte"] = (D3DXVECTOR3(0.8f, 0.0f, 0.0f) - m_MotionModel["Rte"]->GetRotation()) / 30;
			m_InOutValue["Lude"] = (D3DXVECTOR3(-0.6f, 0.0f, 0.0f) - m_MotionModel["Lude"]->GetRotation()) / 30;
			m_InOutValue["Rude"] = (D3DXVECTOR3(-0.5f, 0.0f, 0.0f) - m_MotionModel["Rude"]->GetRotation()) / 30;
			m_InOutValue["Lte"] = (D3DXVECTOR3(0.8f, 0.0f, 0.0f) - m_MotionModel["Lte"]->GetRotation()) / 30;

			m_MotionFlame = 31;
		}

		if (PlayMotion == "LeftOte")
		{
			m_InOutValue["UpBody"] = (D3DXVECTOR3(-0.7f, 0.0f, -0.5f) - m_MotionModel["UpBody"]->GetRotation()) / 30;
			m_InOutValue["LowBody"] = (D3DXVECTOR3(0.0f, 0.0f, -0.3f) - m_MotionModel["LowBody"]->GetRotation()) / 30;
			m_InOutValue["Rkata"] = (D3DXVECTOR3(0.8f, 1.0f, 0.0f) - m_MotionModel["Rkata"]->GetRotation()) / 30;
			m_InOutValue["Rte"] = (D3DXVECTOR3(0.8f, 0.0f, 0.6f) - m_MotionModel["Rte"]->GetRotation()) / 30;
			m_InOutValue["Lude"] = (D3DXVECTOR3(-0.8f, 0.3f, 0.0f) - m_MotionModel["Lude"]->GetRotation()) / 30;
			m_InOutValue["Rude"] = (D3DXVECTOR3(-0.7f, 0.0f, 0.0f) - m_MotionModel["Rude"]->GetRotation()) / 30;
			m_InOutValue["Lte"] = (D3DXVECTOR3(1.5f, 0.8f, 0.0f) - m_MotionModel["Lte"]->GetRotation()) / 30;
			m_InOutValue["Ueago"] = (D3DXVECTOR3(0.6f, 0.2f, -0.3f) - m_MotionModel["Ueago"]->GetRotation()) / 30;
			m_InOutValue["Lkata"] = (D3DXVECTOR3(0.5f, -0.6f, 0.0f) - m_MotionModel["Lkata"]->GetRotation()) / 30;

			m_MotionFlame = 31;
		}

		if (PlayMotion == "Tackle")
		{
			m_InOutValue["UpBody"] = (D3DXVECTOR3(0.4f, 0.7f, 0.3f) - m_MotionModel["UpBody"]->GetRotation()) / 40;
			m_InOutValue["LowBody"] = (D3DXVECTOR3(0.0f, 0.3f, 0.0f) - m_MotionModel["LowBody"]->GetRotation()) / 40;
			m_InOutValue["Rkata"] = (D3DXVECTOR3(0.0f, 0.0f, -0.5f) - m_MotionModel["Rkata"]->GetRotation()) / 40;
			m_InOutValue["Rte"] = (D3DXVECTOR3(0.4f, 0.0f, 0.2f) - m_MotionModel["Rte"]->GetRotation()) / 40;
			m_InOutValue["Lude"] = (D3DXVECTOR3(-0.8f, 0.0f, 0.0f) - m_MotionModel["Lude"]->GetRotation()) / 40;
			m_InOutValue["Rude"] = (D3DXVECTOR3(-0.8f, 0.0f, 0.0f) - m_MotionModel["Rude"]->GetRotation()) / 40;
			m_InOutValue["Tail1"] = (D3DXVECTOR3(0.0f, -0.3f, 0.0f) - m_MotionModel["Tail1"]->GetRotation()) / 40;
			m_InOutValue["Ueago"] = (D3DXVECTOR3(-0.3f, -0.8f, 0.0f) - m_MotionModel["Ueago"]->GetRotation()) / 40;
			m_InOutValue["Lkata"] = (D3DXVECTOR3(0.3f, 0.0f, 0.0f) - m_MotionModel["Lkata"]->GetRotation()) / 40;

			m_InOutValuePos["UpBody"] = (D3DXVECTOR3(0.0f, -0.3f, 0.0f) - m_MotionModel["UpBody"]->GetPosition()) / 40;
			m_InOutValuePos["LowBody"] = (D3DXVECTOR3(0.0f, -0.2f, 0.0f) - m_MotionModel["LowBody"]->GetPosition()) / 40;
			m_InOutValuePos["Rkata"] = (D3DXVECTOR3(-0.8f, 1.0f, 1.0f) - m_MotionModel["Rkata"]->GetPosition()) / 40;

			m_MotionFlame = 40;

		}

	}

	//////////////////////////////////Ç±Ç±Ç©ÇÁñ{èàóù/////////////////////////

	//Idle
	if (PlayMotion == "Idle")
	{

		if (m_FlameCnt < 60)
		{
			if (m_FlameCnt < 30)
			{
				m_MotionModel["Sitaago"]->AddRotationX(0.001 * transFlag);

			}
			m_MotionModel["UpBody"]->AddRotationX(0.0005 * transFlag);
			m_MotionModel["Tail1"]->AddRotationX(0.0005 * transFlag);
			m_MotionModel["Tail2"]->AddRotationX(0.0005 * transFlag);
			m_MotionModel["Tail3"]->AddRotationX(0.0005 * transFlag);
			m_MotionModel["Tail4"]->AddRotationX(0.0005 * transFlag);
			m_MotionModel["Tail5"]->AddRotationX(0.0005 * transFlag);
			m_MotionModel["Tail6"]->AddRotationX(0.0005 * transFlag);

		}
		else
		{
			transFlag *= -1;
			m_FlameCnt = 1;
		}
	}

	//ï‡çs
	if (PlayMotion == "Walk")
	{
		if (m_FlameCnt < 30)
		{
			m_MotionModel["UpBody"]->AddRotation(m_InOutValue["UpBody"] * transFlag);
			m_MotionModel["LowBody"]->AddRotation(m_InOutValue["LowBody"] * transFlag);

			m_MotionModel["Rkata"]->AddRotation(m_InOutValue["Rkata"] * transFlag);
			m_MotionModel["Lkata"]->AddRotation(m_InOutValue["Lkata"] * transFlag);
			m_MotionModel["Rte"]->AddRotation(m_InOutValue["Rte"] * transFlag);
			m_MotionModel["Lte"]->AddRotation(m_InOutValue["Lte"] * transFlag);
			m_MotionModel["RBmomo"]->AddRotation(m_InOutValue["RBmomo"] * transFlag);
			m_MotionModel["LBmomo"]->AddRotation(m_InOutValue["LBmomo"] * transFlag);
		
			m_MotionModel["Tail1"]->AddRotationX(0.001 * transFlag);
			m_MotionModel["Tail2"]->AddRotationX(0.001 * transFlag);
			m_MotionModel["Tail3"]->AddRotationX(0.001 * transFlag);
			m_MotionModel["Tail4"]->AddRotationX(0.001 * transFlag);
			m_MotionModel["Tail5"]->AddRotationX(0.001 * transFlag);
			m_MotionModel["Tail6"]->AddRotationX(0.001 * transFlag);

		}
		else
		{

			transFlag *= -1;
			m_FlameCnt = 1;
		}
	}

	if (PlayMotion == "Run")
	{
		if (m_FlameCnt < 10)
		{
			m_MotionModel["UpBody"]->AddRotation(m_InOutValue["UpBody"] * transFlag);
			m_MotionModel["LowBody"]->AddRotation(m_InOutValue["LowBody"] * transFlag);

			m_MotionModel["Lkata"]->AddRotation(m_InOutValue["Lkata"] * transFlag);
			m_MotionModel["Lte"]->AddRotation(m_InOutValue["Lte"] * transFlag);
			m_MotionModel["RBmomo"]->AddRotation(m_InOutValue["RBmomo"] * transFlag);

			m_MotionModel["Tail1"]->AddRotationX(0.001 * transFlag);
			m_MotionModel["Tail2"]->AddRotationX(0.001 * transFlag);
			m_MotionModel["Tail3"]->AddRotationX(0.001 * transFlag);
			m_MotionModel["Tail4"]->AddRotationX(0.001 * transFlag);
			m_MotionModel["Tail5"]->AddRotationX(0.001 * transFlag);
			m_MotionModel["Tail6"]->AddRotationX(0.001 * transFlag);
		}
		else
		{
			transFlag *= -1;
			m_FlameCnt = 1;
		}

		if (m_FlameCnt2 >= 0 && m_FlameCnt2 < 10)
		{
			m_MotionModel["Rkata"]->AddRotation(m_InOutValue["Rkata"] * transFlag2);
			m_MotionModel["Rte"]->AddRotation(m_InOutValue["Rte"] * transFlag2);
			m_MotionModel["LBmomo"]->AddRotation(m_InOutValue["LBmomo"] * transFlag2);

		}
		else if(m_FlameCnt2 > 10)
		{
			transFlag2 *= -1;
			m_FlameCnt2 = 1;
		}
	}


	//Ç®éË
	if (PlayMotion == "OTE")
	{
		if (m_FlameCnt < m_MotionFlame)
		{
			m_MotionModel["Ueago"]->AddRotation(m_InOutValue["Ueago"]);
			m_MotionModel["LowBody"]->AddRotation(m_InOutValue["LowBody"]);
			m_MotionModel["UpBody"]->AddRotation(m_InOutValue["UpBody"]);
			m_MotionModel["Rkata"]->AddRotation(m_InOutValue["Rkata"]);
			m_MotionModel["Lkata"]->AddRotation(m_InOutValue["Lkata"]);
			m_MotionModel["Rude"]->AddRotation(m_InOutValue["Rude"]);
			m_MotionModel["Lude"]->AddRotation(m_InOutValue["Lude"]);
			m_MotionModel["Rte"]->AddRotation(m_InOutValue["Rte"]);
			m_MotionModel["Lte"]->AddRotation(m_InOutValue["Lte"]);

		}
		else if(FirstFlag)
		{
			m_InOutValue["Ueago"] = (D3DXVECTOR3(0.4f, -0.4f, 0.0f) - m_MotionModel["Ueago"]->GetRotation()) / 10;
			m_InOutValue["UpBody"] = (D3DXVECTOR3(0.6f, -0.2f, 0.0f) - m_MotionModel["UpBody"]->GetRotation()) / 10;
			m_InOutValue["Rte"] = (D3DXVECTOR3(0.0f, 0.0f, -0.4f) - m_MotionModel["Rte"]->GetRotation()) / 10;
			m_InOutValue["Lkata"] = (D3DXVECTOR3(-1.3f, -0.5f, 0.1f) - m_MotionModel["Lkata"]->GetRotation()) / 10;
			m_InOutValue["Lude"] = (D3DXVECTOR3(0.6f, 0.0f, 0.0f) - m_MotionModel["Lude"]->GetRotation()) / 10;
			m_InOutValue["Lte"] = (D3DXVECTOR3(0.2f, 0.0f, 0.0f) - m_MotionModel["Lte"]->GetRotation()) / 10;
			FirstFlag = false;
			m_FlameCnt = 1;
			m_MotionFlame = 11;

		}
		if (!FirstFlag && m_FlameCnt > m_MotionFlame)
		{
			m_MotionEnd = true;
		}
	}

	//ôÙöK
	if (PlayMotion == "Roar")
	{
		if (m_FlameCnt < 20 && !m_MotionDelyFlag)
		{
			m_MotionModel["Ueago"]->AddRotation(m_InOutValue["Ueago"]);
			m_MotionModel["UpBody"]->AddRotation(m_InOutValue["UpBody"]);
			m_MotionModel["Rkata"]->AddRotation(m_InOutValue["Rkata"]);
			m_MotionModel["Lkata"]->AddRotation(m_InOutValue["Lkata"]);
			m_MotionModel["Rude"]->AddRotation(m_InOutValue["Rude"]);
			m_MotionModel["Lude"]->AddRotation(m_InOutValue["Lude"]);
		}
		else
		{
			m_InOutValue["Ueago"] = (D3DXVECTOR3(0.0f, 0.0f, 0.0f) - m_MotionModel["Ueago"]->GetRotation()) / 20;
			m_InOutValue["Lkata"] = (D3DXVECTOR3(0.0f, 0.0f, 0.0f) - m_MotionModel["Lkata"]->GetRotation()) / 20;
			m_InOutValue["UpBody"] = (D3DXVECTOR3(0.0f, 0.0f, 0.0f) - m_MotionModel["UpBody"]->GetRotation()) / 20;
			m_InOutValue["Rkata"] = (D3DXVECTOR3(0.0f, 0.0f, 0.0f) - m_MotionModel["Rkata"]->GetRotation()) / 20;
			m_InOutValue["Rude"] = (D3DXVECTOR3(0.0f, 0.0f, 0.0f) - m_MotionModel["Rude"]->GetRotation()) / 20;
			m_InOutValue["Lude"] = (D3DXVECTOR3(0.0f, 0.0f, 0.0f) - m_MotionModel["Lude"]->GetRotation()) / 20;

			if (FirstFlag)
			{
				m_MotionDelyFlag = true;
				FirstFlag = false;
				m_FlameCnt = 1;
			}
		}
		if (m_MotionDelyFlag)
		{
			m_FlameCnt++;
			if (m_FlameCnt > 60)
			{
				m_MotionDelyFlag = false;
				m_FlameCnt = 1;
			}
		}

	}

	//É`ÉÉÅ[ÉWÉÇÅ[ÉVÉáÉì
	if (PlayMotion == "Charge")
	{
		if (m_FlameCnt < 20 && m_MotionCnt <= 4)
		{
			m_MotionModel["Ueago"]->AddRotation(m_InOutValue["Ueago"] * transFlag);

			m_MotionModel["Rkata"]->AddRotation(m_InOutValue["Rkata"] * transFlag);
			m_MotionModel["Lkata"]->AddRotation(m_InOutValue["Lkata"] * transFlag);
			m_MotionModel["UpBody"]->AddRotation(m_InOutValue["UpBody"] * transFlag);
		}
		else
		{
			transFlag *= -1;
			m_FlameCnt = 1;
			m_MotionCnt++;
			if (m_MotionCnt == 4)
			{
				m_InOutValue["Ueago"] = (D3DXVECTOR3(-0.5f, 0.0f, 0.0f) - m_MotionModel["Lkata"]->GetRotation()) / 20;

				m_InOutValue["Lkata"] = (D3DXVECTOR3(0.3f, 0.0f, 0.0f) - m_MotionModel["Lkata"]->GetRotation()) / 20;
				m_InOutValue["UpBody"] = (D3DXVECTOR3(-0.2f, 0.0f, 0.0f) - m_MotionModel["UpBody"]->GetRotation()) / 20;
				m_InOutValue["Rkata"] = (D3DXVECTOR3(0.3f, 0.0f, 0.0f) - m_MotionModel["Rkata"]->GetRotation()) / 20;
				
			}
		}
		if (m_MotionCnt > 4)
		{
			m_MotionEnd = true;
		}
	}

	if (PlayMotion == "Scratch")
	{
		if (m_FlameCnt < 30)
		{
			m_MotionModel["Lude"]->AddRotation(m_InOutValue["Lude"]);
			m_MotionModel["Lkata"]->AddRotation(m_InOutValue["Lkata"]);
			m_MotionModel["UpBody"]->AddRotation(m_InOutValue["UpBody"]);

		}
		m_FlameCnt++;
	}

	if (PlayMotion == "Jump")
	{
		if (m_FlameCnt < 60 && !m_MotionEnd)
		{
			m_MotionModel["Rkata"]->AddRotation(m_InOutValue["Rkata"]);
			m_MotionModel["Lkata"]->AddRotation(m_InOutValue["Lkata"]);
			m_MotionModel["UpBody"]->AddRotation(m_InOutValue["UpBody"]);
			m_MotionModel["LowBody"]->AddRotation(m_InOutValue["LowBody"]);

			if (FirstFlag)
			{
				m_MotionModel["Rkata"]->AddPosition(m_InOutValuePos["Rkata"]);
				m_MotionModel["Lkata"]->AddPosition(m_InOutValuePos["Lkata"]);
				m_MotionModel["UpBody"]->AddPosition(m_InOutValuePos["UpBody"]);
				m_MotionModel["LowBody"]->AddPosition(m_InOutValuePos["LowBody"]);
			}
			else
			{
				m_MotionModel["Lude"]->AddRotation(m_InOutValue["Lude"]);
				m_MotionModel["Rude"]->AddRotation(m_InOutValue["Rude"]);
				m_MotionModel["Lte"]->AddRotation(m_InOutValue["Lte"]);


				m_MotionModel["UpBody"]->AddPosition(m_InOutValuePos["UpBody"]);
				m_MotionModel["LowBody"]->AddPosition(m_InOutValuePos["LowBody"]);

			}
		}
		else if(FirstFlag)
		{
			m_InOutValue["UpBody"] = (D3DXVECTOR3(-0.2f, 0.0f, -0.2f) - m_MotionModel["UpBody"]->GetRotation()) / 30;
			m_InOutValue["Lkata"] = (D3DXVECTOR3(-0.6f, 0.0f, 0.0f) - m_MotionModel["Lkata"]->GetRotation()) / 30;
			m_InOutValue["LowBody"] = (D3DXVECTOR3(-0.4f, 0.0f, -0.2f) - m_MotionModel["LowBody"]->GetRotation()) / 30;
			m_InOutValue["Rkata"] = (D3DXVECTOR3(-1.0f, 0.0f, -0.7f) - m_MotionModel["Rkata"]->GetRotation()) / 30;
			m_InOutValue["Rude"] = (D3DXVECTOR3(-1.0f, 0.0f, 0.0f) - m_MotionModel["Rude"]->GetRotation()) / 30;
			m_InOutValue["Lude"] = (D3DXVECTOR3(0.5f, -0.4f, -0.9f) - m_MotionModel["Lude"]->GetRotation()) / 30;
			m_InOutValue["Lte"] = (D3DXVECTOR3(0.5f, 0.0f, 0.0f) - m_MotionModel["Lte"]->GetRotation()) / 30;

			m_InOutValuePos["UpBody"] = (D3DXVECTOR3(0.0f, 2.0f, -0.2f) - m_MotionModel["UpBody"]->GetPosition()) / 30;
			m_InOutValuePos["LowBody"] = (D3DXVECTOR3(0.0f, 2.0f, -0.1f) - m_MotionModel["LowBody"]->GetPosition()) / 30;


			FirstFlag = false;
			m_FlameCnt = 0;
		}

		if (!FirstFlag && m_FlameCnt >= 60)
		{
			m_MotionEnd = true;
		}
		m_FlameCnt++;
	}

	if (PlayMotion == "Land")
	{
		if (m_FlameCnt < 60 && !m_MotionEnd && !m_MotionDelyFlag)
		{
			m_MotionModel["Rkata"]->AddRotation(m_InOutValue["Rkata"]);
			m_MotionModel["Lkata"]->AddRotation(m_InOutValue["Lkata"]);
			m_MotionModel["UpBody"]->AddRotation(m_InOutValue["UpBody"]);
			m_MotionModel["LowBody"]->AddRotation(m_InOutValue["LowBody"]);
			m_MotionModel["Lude"]->AddRotation(m_InOutValue["Lude"]);
			m_MotionModel["Rude"]->AddRotation(m_InOutValue["Rude"]);
			m_MotionModel["Lte"]->AddRotation(m_InOutValue["Lte"]);
			m_MotionModel["Rte"]->AddRotation(m_InOutValue["Rte"]);
			m_MotionModel["RBmomo"]->AddRotation(m_InOutValue["RBmomo"]);
			m_MotionModel["LBmomo"]->AddRotation(m_InOutValue["LBmomo"]);
			m_MotionModel["Tail1"]->AddRotation(m_InOutValue["Tail1"]);
			m_MotionModel["Tail2"]->AddRotation(m_InOutValue["Tail2"]);
			m_MotionModel["Tail3"]->AddRotation(m_InOutValue["Tail3"]);
			m_MotionModel["Tail4"]->AddRotation(m_InOutValue["Tail4"]);
			m_MotionModel["Tail5"]->AddRotation(m_InOutValue["Tail5"]);
			m_MotionModel["Tail6"]->AddRotation(m_InOutValue["Tail6"]);




			m_MotionModel["UpBody"]->AddPosition(m_InOutValuePos["UpBody"]);
			m_MotionModel["LowBody"]->AddPosition(m_InOutValuePos["LowBody"]);

		}
		else
		{
			if (!m_MotionDelyFlag)
			{
				m_FlameCnt = 0;
				m_MotionDelyFlag = true;
			}
			else if(m_FlameCnt > 20)
			{
				m_MotionEnd = true;
				m_MotionDelyFlag = false;
			}
		}
		m_FlameCnt++;
	}

	if (PlayMotion == "Shot")
	{
		if (m_FlameCnt < m_MotionFlame)
		{
			switch (ChangeMotion)
			{
			case 0:
				m_MotionModel["Rkata"]->AddRotation(m_InOutValue["Rkata"]);
				m_MotionModel["Lkata"]->AddRotation(m_InOutValue["Lkata"]);
				m_MotionModel["UpBody"]->AddRotation(m_InOutValue["UpBody"]);
				m_MotionModel["LowBody"]->AddRotation(m_InOutValue["LowBody"]);
				m_MotionModel["Lude"]->AddRotation(m_InOutValue["Lude"]);
				m_MotionModel["Rude"]->AddRotation(m_InOutValue["Rude"]);
				m_MotionModel["Rte"]->AddRotation(m_InOutValue["Rte"]);
				m_MotionModel["Ueago"]->AddRotation(m_InOutValue["Ueago"]);
				m_MotionModel["Tail1"]->AddRotation(m_InOutValue["Tail1"]);
				m_MotionModel["Tail2"]->AddRotation(m_InOutValue["Tail2"]);
				m_MotionModel["Tail3"]->AddRotation(m_InOutValue["Tail3"]);
				m_MotionModel["Tail4"]->AddRotation(m_InOutValue["Tail4"]);

				m_MotionModel["UpBody"]->AddPosition(m_InOutValuePos["UpBody"]);
				m_MotionModel["LowBody"]->AddPosition(m_InOutValuePos["LowBody"]);
				break;

			case 1:
				m_MotionModel["UpBody"]->AddPosition(m_InOutValuePos["UpBody"]);
				m_MotionModel["LowBody"]->AddPosition(m_InOutValuePos["LowBody"]);
				m_MotionModel["UpBody"]->AddRotation(m_InOutValue["UpBody"]);
				m_MotionModel["LowBody"]->AddRotation(m_InOutValue["LowBody"]);

				break;
			case 2:
				m_MotionModel["UpBody"]->AddRotation(m_InOutValue["UpBody"]);
				m_MotionModel["LowBody"]->AddRotation(m_InOutValue["LowBody"]);
				break;
			case 3:
				m_MotionModel["UpBody"]->AddPosition(m_InOutValuePos["UpBody"]);
				m_MotionModel["LowBody"]->AddPosition(m_InOutValuePos["LowBody"]);

				m_MotionModel["Rkata"]->AddRotation(m_InOutValue["Rkata"]);
				m_MotionModel["Ueago"]->AddRotation(m_InOutValue["Ueago"]);
				m_MotionModel["Tail1"]->AddRotation(m_InOutValue["Tail1"]);
				m_MotionModel["Tail2"]->AddRotation(m_InOutValue["Tail2"]);
				m_MotionModel["Tail3"]->AddRotation(m_InOutValue["Tail3"]);
				m_MotionModel["Tail5"]->AddRotation(m_InOutValue["Tail5"]);
				m_MotionModel["Tail6"]->AddRotation(m_InOutValue["Tail6"]);
										

				break;
			default:
				break;
			}
		}
		else if (m_FlameCnt > m_MotionFlame)
		{
			ChangeMotion++;
			m_FlameCnt = 0;

			switch (ChangeMotion)
			{
			case 1:
				m_InOutValuePos["UpBody"] = (D3DXVECTOR3(0.0f, 1.0f, 0.0f) - m_MotionModel["UpBody"]->GetPosition()) / 10;
				m_InOutValuePos["LowBody"] = (D3DXVECTOR3(0.0f, 0.9f, 0.0f) - m_MotionModel["LowBody"]->GetPosition()) / 10;
				m_InOutValue["UpBody"] = (D3DXVECTOR3(0.3f, 0.4f, -1.3f) - m_MotionModel["UpBody"]->GetRotation()) / 10;
				m_InOutValue["LowBody"] = (D3DXVECTOR3(0.2f, 0.5f, -1.3f) - m_MotionModel["LowBody"]->GetRotation()) / 10;

				m_MotionFlame = 11;
				break;

			case 2:
				m_InOutValue["UpBody"] = (D3DXVECTOR3(0.3f, -0.5f, -6.3f) - m_MotionModel["UpBody"]->GetRotation()) / 20;
				m_InOutValue["LowBody"] = (D3DXVECTOR3(0.2f, -0.6f, -6.3f) - m_MotionModel["LowBody"]->GetRotation()) / 20;

				m_MotionFlame = 21;
				break;

			case 3:
				m_InOutValuePos["UpBody"] = (D3DXVECTOR3(0.0f, -0.5f, 0.0f) - m_MotionModel["UpBody"]->GetPosition()) / 10;
				m_InOutValuePos["LowBody"] = (D3DXVECTOR3(0.0f, -0.4f, 0.0f) - m_MotionModel["LowBody"]->GetPosition()) / 10;

				m_InOutValue["Ueago"] = (D3DXVECTOR3(0.0f, 0.4f, 0.0f) - m_MotionModel["Ueago"]->GetRotation()) / 10;
				m_InOutValue["Rkata"] = (D3DXVECTOR3(0.8f, 0.3f, 0.0f) - m_MotionModel["Rkata"]->GetRotation()) / 10;
				m_InOutValue["Tail1"] = (D3DXVECTOR3(0.0f, -0.4f, 0.0f) - m_MotionModel["Tail1"]->GetRotation()) / 10;
				m_InOutValue["Tail2"] = (D3DXVECTOR3(0.0f, -0.4f,-0.2f) - m_MotionModel["Tail2"]->GetRotation()) / 10;
				m_InOutValue["Tail3"] = (D3DXVECTOR3(0.0f, -0.2f, -0.2f) - m_MotionModel["Tail3"]->GetRotation()) / 10;
				m_InOutValue["Tail5"] = (D3DXVECTOR3(0.0f, -0.2f, 0.0f) - m_MotionModel["Tail5"]->GetRotation()) / 10;
				m_InOutValue["Tail6"] = (D3DXVECTOR3(0.0f, -0.4f, 0.0f) - m_MotionModel["Tail6"]->GetRotation()) / 10;


				m_MotionFlame = 11;
				break;
			default:
				break;
			}
		}

		if (ChangeMotion == 4)
		{
			m_MotionEnd = true;
		}
	}

	if (PlayMotion == "Die")
	{
		if (m_FlameCnt < m_MotionFlame && !m_MotionDelyFlag)
		{
			switch (ChangeMotion)
			{
			case 0:
				m_MotionModel["Rkata"]->AddRotation(m_InOutValue["Rkata"]);
				m_MotionModel["Lkata"]->AddRotation(m_InOutValue["Lkata"]);
				m_MotionModel["UpBody"]->AddRotation(m_InOutValue["UpBody"]);
				m_MotionModel["Ueago"]->AddRotation(m_InOutValue["Ueago"]);
				m_MotionModel["Lude"]->AddRotation(m_InOutValue["Lude"]);
				break;

			case 1:
				m_MotionModel["Rkata"]->AddRotation(m_InOutValue["Rkata"]);
				m_MotionModel["Lkata"]->AddRotation(m_InOutValue["Lkata"]);
				m_MotionModel["UpBody"]->AddRotation(m_InOutValue["UpBody"]);
				m_MotionModel["Ueago"]->AddRotation(m_InOutValue["Ueago"]);
				m_MotionModel["Lude"]->AddRotation(m_InOutValue["Lude"]);
				m_MotionModel["Sitaago"]->AddRotation(m_InOutValue["Sitaago"]);
				m_MotionModel["Rude"]->AddRotation(m_InOutValue["Rude"]);
				break;

			case 2:
				m_MotionModel["Rkata"]->AddRotation(m_InOutValue["Rkata"]);
				m_MotionModel["Lkata"]->AddRotation(m_InOutValue["Lkata"]);
				m_MotionModel["UpBody"]->AddRotation(m_InOutValue["UpBody"]);
				m_MotionModel["Rte"]->AddRotation(m_InOutValue["Rte"]);
				m_MotionModel["Rude"]->AddRotation(m_InOutValue["Rude"]);

				break;
			case 3:
				m_MotionModel["Rkata"]->AddRotation(m_InOutValue["Rkata"]);
				m_MotionModel["LBmomo"]->AddRotation(m_InOutValue["LBmomo"]);
				m_MotionModel["UpBody"]->AddRotation(m_InOutValue["UpBody"]);
				m_MotionModel["LowBody"]->AddRotation(m_InOutValue["LowBody"]);
				m_MotionModel["Rude"]->AddRotation(m_InOutValue["Rude"]);
				m_MotionModel["Lude"]->AddRotation(m_InOutValue["Lude"]);

				break;
			default:
				break;
			
			}

		}
		else if(!m_MotionDelyFlag)
		{
			ChangeMotion++;
			m_FlameCnt = 0;

			switch (ChangeMotion)
			{
			case 1:
				m_InOutValue["UpBody"] = (D3DXVECTOR3(-0.3f, 0.0f, 0.3f) - m_MotionModel["UpBody"]->GetRotation()) / 60;
				m_InOutValue["Lkata"] = (D3DXVECTOR3(0.2f, 0.0f, -0.2f) - m_MotionModel["Lkata"]->GetRotation()) / 60;
				m_InOutValue["Ueago"] = (D3DXVECTOR3(-0.7f, 0.3f, 0.0f) - m_MotionModel["Ueago"]->GetRotation()) / 60;
				m_InOutValue["Sitaago"] = (D3DXVECTOR3(0.4f, 0.0f, 0.0f) - m_MotionModel["Sitaago"]->GetRotation()) / 60;
				m_InOutValue["Rkata"] = (D3DXVECTOR3(0.4f, 0.0f, -0.2f) - m_MotionModel["Rkata"]->GetRotation()) / 60;
				m_InOutValue["Rude"] = (D3DXVECTOR3(-0.3f, 0.0f, 0.0f) - m_MotionModel["Rude"]->GetRotation()) / 60;
				m_InOutValue["Lude"] = (D3DXVECTOR3(0.2f, 0.0f, 0.0f) - m_MotionModel["Lude"]->GetRotation()) / 60;

				break;

			case 2:
				m_InOutValue["UpBody"] = (D3DXVECTOR3(0.0f, 0.0f, 0.6f) - m_MotionModel["UpBody"]->GetRotation()) / 60;
				m_InOutValue["Lkata"] = (D3DXVECTOR3(0.0f, 0.0f, -0.4f) - m_MotionModel["Lkata"]->GetRotation()) / 60;
				m_InOutValue["Rkata"] = (D3DXVECTOR3(0.8f, 0.0f, 0.0f) - m_MotionModel["Rkata"]->GetRotation()) / 60;
				m_InOutValue["Rude"] = (D3DXVECTOR3(-0.6f, 0.0f, 0.0f) - m_MotionModel["Rude"]->GetRotation()) / 60;
				m_InOutValue["Rte"] = (D3DXVECTOR3(0.0f, 0.0f, -0.5f) - m_MotionModel["Rte"]->GetRotation()) / 60;

				break;

			case 3:
				m_InOutValue["UpBody"] = (D3DXVECTOR3(0.0f, 0.0f, 1.8f) - m_MotionModel["UpBody"]->GetRotation()) / 60;
				m_InOutValue["LowBody"] = (D3DXVECTOR3(0.0f, 0.0f, 1.5f) - m_MotionModel["LowBody"]->GetRotation()) / 60;
				m_InOutValue["Rkata"] = (D3DXVECTOR3(0.0f, 0.0f, 0.0f) - m_MotionModel["Rkata"]->GetRotation()) / 60;
				m_InOutValue["Rude"] = (D3DXVECTOR3(-0.3f, 0.0f, 0.0f) - m_MotionModel["Rude"]->GetRotation()) / 60;
				m_InOutValue["Lude"] = (D3DXVECTOR3(-0.3f, 0.0f, 0.0f) - m_MotionModel["Lude"]->GetRotation()) / 60;
				m_InOutValue["LBmomo"] = (D3DXVECTOR3(0.0f, 0.0f, -0.5f) - m_MotionModel["LBmomo"]->GetRotation()) / 60;
				break;
			case 4:
				m_MotionDelyFlag = true;
				break;
			default:
				break;
			}
		}
		if (m_MotionDelyFlag)
		{
			if (m_FlameCnt > 60)
			{
				m_MotionEnd = true;
				m_FlameCnt = 0;
			}
		}
	}

	if (PlayMotion == "Fear")
	{
		if (m_FlameCnt < m_MotionFlame && !m_MotionDelyFlag)
		{
			switch (ChangeMotion)
			{
			case 0:
				m_MotionModel["Rkata"]->AddRotation(m_InOutValue["Rkata"]);
				m_MotionModel["LowBody"]->AddRotation(m_InOutValue["LowBody"]);
				m_MotionModel["UpBody"]->AddRotation(m_InOutValue["UpBody"]);
				m_MotionModel["Lte"]->AddRotation(m_InOutValue["Lte"]);
				m_MotionModel["Rude"]->AddRotation(m_InOutValue["Rude"]);
				m_MotionModel["Lude"]->AddRotation(m_InOutValue["Lude"]);
				m_MotionModel["Rte"]->AddRotation(m_InOutValue["Rte"]);

				break;
			case 1:
				m_MotionModel["Rkata"]->AddRotation(m_InOutValue["Rkata"]);
				m_MotionModel["Lkata"]->AddRotation(m_InOutValue["Lkata"]);

				break;
			case 2:
				m_MotionModel["Rkata"]->AddRotation(m_InOutValue["Rkata"]);
				m_MotionModel["Lkata"]->AddRotation(m_InOutValue["Lkata"]);

				break;
			case 3:
				m_MotionModel["Rkata"]->AddRotation(m_InOutValue["Rkata"]);
				m_MotionModel["Ueago"]->AddRotation(m_InOutValue["Ueago"]);
				m_MotionModel["UpBody"]->AddRotation(m_InOutValue["UpBody"]);
				m_MotionModel["Lte"]->AddRotation(m_InOutValue["Lte"]);
				m_MotionModel["Rude"]->AddRotation(m_InOutValue["Rude"]);
				m_MotionModel["Lkata"]->AddRotation(m_InOutValue["Lkata"]);
				m_MotionModel["Rte"]->AddRotation(m_InOutValue["Rte"]);


				break;
			default:
				break;
			}
		}
		else if(!m_MotionDelyFlag)
		{
			ChangeMotion++;
			m_FlameCnt = 0;

			switch (ChangeMotion)
			{
			case 1:
				m_InOutValue["Lkata"] = (D3DXVECTOR3(-1.1f, 0.0f, 0.0f) - m_MotionModel["Lkata"]->GetRotation()) / 30;
				m_InOutValue["Rkata"] = (D3DXVECTOR3(-0.2f, 0.0f, 0.0f) - m_MotionModel["Rkata"]->GetRotation()) / 30;

				break;

			case 2:
				m_InOutValue["Lkata"] = (D3DXVECTOR3(-0.2f, 0.0f, 0.0f) - m_MotionModel["Lkata"]->GetRotation()) / 30;
				m_InOutValue["Rkata"] = (D3DXVECTOR3(-1.1f, 0.0f, 0.0f) - m_MotionModel["Rkata"]->GetRotation()) / 30;

				break;

			case 3:
				m_InOutValue["UpBody"] = (D3DXVECTOR3(0.3f, 0.0f, 0.0f) - m_MotionModel["UpBody"]->GetRotation()) / 30;
				m_InOutValue["Lkata"] = (D3DXVECTOR3(0.6f, 0.0f, 0.3f) - m_MotionModel["Lkata"]->GetRotation()) / 30;
				m_InOutValue["Rkata"] = (D3DXVECTOR3(-1.0f, 0.0f, -0.3f) - m_MotionModel["Rkata"]->GetRotation()) / 30;
				m_InOutValue["Ueago"] = (D3DXVECTOR3(0.4f, 0.0f, 0.0f) - m_MotionModel["Ueago"]->GetRotation()) / 30;
				m_InOutValue["Rude"] = (D3DXVECTOR3(0.0f, 0.0f, 0.5f) - m_MotionModel["Rude"]->GetRotation()) / 30;
				m_InOutValue["Rte"] = (D3DXVECTOR3(0.5f, 0.0f, -0.2f) - m_MotionModel["Rte"]->GetRotation()) / 30;
				m_InOutValue["Lte"] = (D3DXVECTOR3(0.0f, 0.0f, 0.0f) - m_MotionModel["Lte"]->GetRotation()) / 30;

				break;
			case 4:
				m_MotionDelyFlag = true;
			default:
				break;
			}
		}
		if (m_MotionDelyFlag)
		{
			if (m_FlameCnt > 60)
			{
				m_MotionEnd = true;
				m_FlameCnt = 0;
			}
		}
	}

	if (PlayMotion == "LeftOte")
	{
		if (m_FlameCnt < m_MotionFlame && !m_MotionDelyFlag)
		{
			switch (ChangeMotion)
			{
			case 0:
				m_MotionModel["Rkata"]->AddRotation(m_InOutValue["Rkata"]);
				m_MotionModel["Ueago"]->AddRotation(m_InOutValue["Ueago"]);
				m_MotionModel["UpBody"]->AddRotation(m_InOutValue["UpBody"]);
				m_MotionModel["Lte"]->AddRotation(m_InOutValue["Lte"]);
				m_MotionModel["Rude"]->AddRotation(m_InOutValue["Rude"]);
				m_MotionModel["Lkata"]->AddRotation(m_InOutValue["Lkata"]);
				m_MotionModel["Rte"]->AddRotation(m_InOutValue["Rte"]);
				m_MotionModel["LowBody"]->AddRotation(m_InOutValue["LowBody"]);
				m_MotionModel["Lude"]->AddRotation(m_InOutValue["Lude"]);


				break;
			case 1:
				m_MotionModel["Rkata"]->AddRotation(m_InOutValue["Rkata"]);
				m_MotionModel["Ueago"]->AddRotation(m_InOutValue["Ueago"]);
				m_MotionModel["UpBody"]->AddRotation(m_InOutValue["UpBody"]);
				m_MotionModel["Lte"]->AddRotation(m_InOutValue["Lte"]);
				m_MotionModel["Rude"]->AddRotation(m_InOutValue["Rude"]);
				m_MotionModel["Lkata"]->AddRotation(m_InOutValue["Lkata"]);
				m_MotionModel["Rte"]->AddRotation(m_InOutValue["Rte"]);
				m_MotionModel["LowBody"]->AddRotation(m_InOutValue["LowBody"]);
				m_MotionModel["Lude"]->AddRotation(m_InOutValue["Lude"]);


				break;
			default:
				break;
			}
		}
		else if(!m_MotionDelyFlag)
		{
			ChangeMotion++;
			m_FlameCnt = 0;

			switch (ChangeMotion)
			{
			case 1:
				m_InOutValue["UpBody"] = (D3DXVECTOR3(0.0f, 0.4f, 0.3f) - m_MotionModel["UpBody"]->GetRotation()) / 20;
				m_InOutValue["LowBody"] = (D3DXVECTOR3(0.0f, 0.0f, 0.0f) - m_MotionModel["LowBody"]->GetRotation()) / 20;
				m_InOutValue["Rkata"] = (D3DXVECTOR3(-0.5f, 0.6f, -0.3f) - m_MotionModel["Rkata"]->GetRotation()) / 20;
				m_InOutValue["Rte"] = (D3DXVECTOR3(0.5f, 0.0f, 0.0f) - m_MotionModel["Rte"]->GetRotation()) / 20;
				m_InOutValue["Lude"] = (D3DXVECTOR3(-1.0f, -0.6f, 0.0f) - m_MotionModel["Lude"]->GetRotation()) / 20;
				m_InOutValue["Rude"] = (D3DXVECTOR3(0.5f, 0.0f, 0.0f) - m_MotionModel["Rude"]->GetRotation()) / 20;
				m_InOutValue["Lte"] = (D3DXVECTOR3(1.0f, 0.0f, 0.0f) - m_MotionModel["Lte"]->GetRotation()) / 20;
				m_InOutValue["Ueago"] = (D3DXVECTOR3(0.6f, -0.5f, -0.3f) - m_MotionModel["Ueago"]->GetRotation()) / 20;
				m_InOutValue["Lkata"] = (D3DXVECTOR3(0.6f, 0.0f, 0.0f) - m_MotionModel["Lkata"]->GetRotation()) / 20;

				m_MotionFlame = 21;
				break;
			case 2:
				m_MotionDelyFlag = true;
			default:
				break;
			}
		}
		if (m_MotionDelyFlag)
		{
			if (m_FlameCnt > 60)
			{
				m_MotionEnd = true;
				m_FlameCnt = 0;
			}
		}
	}

	if (PlayMotion == "Tackle")
	{
		if (m_FlameCnt < m_MotionFlame + 1 && !m_MotionDelyFlag)
		{
			switch (ChangeMotion)
			{
			case 0:
				m_MotionModel["Rkata"]->AddRotation(m_InOutValue["Rkata"]);
				m_MotionModel["Ueago"]->AddRotation(m_InOutValue["Ueago"]);
				m_MotionModel["UpBody"]->AddRotation(m_InOutValue["UpBody"]);
				m_MotionModel["Tail1"]->AddRotation(m_InOutValue["Tail1"]);
				m_MotionModel["Rude"]->AddRotation(m_InOutValue["Rude"]);
				m_MotionModel["Lkata"]->AddRotation(m_InOutValue["Lkata"]);
				m_MotionModel["Rte"]->AddRotation(m_InOutValue["Rte"]);
				m_MotionModel["LowBody"]->AddRotation(m_InOutValue["LowBody"]);
				m_MotionModel["Lude"]->AddRotation(m_InOutValue["Lude"]);

				m_MotionModel["UpBody"]->AddPosition(m_InOutValuePos["UpBody"]);
				m_MotionModel["LowBody"]->AddPosition(m_InOutValuePos["LowBody"]);
				m_MotionModel["Rkata"]->AddPosition(m_InOutValuePos["Rkata"]);

				break;

			case 1:
				m_MotionModel["Rkata"]->AddRotation(m_InOutValue["Rkata"]);
				m_MotionModel["Ueago"]->AddRotation(m_InOutValue["Ueago"]);
				m_MotionModel["UpBody"]->AddRotation(m_InOutValue["UpBody"]);
				m_MotionModel["Tail1"]->AddRotation(m_InOutValue["Tail1"]);
				m_MotionModel["Rude"]->AddRotation(m_InOutValue["Rude"]);
				m_MotionModel["Tail2"]->AddRotation(m_InOutValue["Tail2"]);
				m_MotionModel["Rte"]->AddRotation(m_InOutValue["Rte"]);
				m_MotionModel["LowBody"]->AddRotation(m_InOutValue["LowBody"]);
				m_MotionModel["Lude"]->AddRotation(m_InOutValue["Lude"]);
				m_MotionModel["Tail3"]->AddRotation(m_InOutValue["Tail3"]);

				m_MotionModel["UpBody"]->AddPosition(m_InOutValuePos["UpBody"]);
				m_MotionModel["LowBody"]->AddPosition(m_InOutValuePos["LowBody"]);
				m_MotionModel["Lkata"]->AddPosition(m_InOutValuePos["Lkata"]);

				if (m_FlameCnt == 10)
				{
					m_MotionPoint = true;
				}
				else
				{
					m_MotionPoint = false;
				}
				break;
			default:
				break;
			}
		}
		else if(!m_MotionDelyFlag)
		{
			ChangeMotion++;
			m_FlameCnt = 0;

			switch (ChangeMotion)
			{
			case 1:
				m_InOutValue["UpBody"] = (D3DXVECTOR3(-0.3f, -0.3f, 0.3f) - m_MotionModel["UpBody"]->GetRotation()) / 30;
				m_InOutValue["LowBody"] = (D3DXVECTOR3(0.0f, 0.0f, 0.0f) - m_MotionModel["LowBody"]->GetRotation()) / 30;
				m_InOutValue["Rkata"] = (D3DXVECTOR3(0.0f, 0.0f, 0.0f) - m_MotionModel["Rkata"]->GetRotation()) / 30;
				m_InOutValue["Rte"] = (D3DXVECTOR3(0.3f, 0.0f, -0.2f) - m_MotionModel["Rte"]->GetRotation()) / 30;
				m_InOutValue["Lude"] = (D3DXVECTOR3(0.3f, 0.0f, 0.0f) - m_MotionModel["Lude"]->GetRotation()) / 30;
				m_InOutValue["Rude"] = (D3DXVECTOR3(0.0f, 0.0f, 0.0f) - m_MotionModel["Rude"]->GetRotation()) / 30;
				m_InOutValue["Tail1"] = (D3DXVECTOR3(0.0f, 0.2f, 0.0f) - m_MotionModel["Tail1"]->GetRotation()) / 30;
				m_InOutValue["Ueago"] = (D3DXVECTOR3(-0.3f, -0.5f, 0.0f) - m_MotionModel["Ueago"]->GetRotation()) / 30;
				m_InOutValue["Tail2"] = (D3DXVECTOR3(0.0f, 0.2f, 0.0f) - m_MotionModel["Tail2"]->GetRotation()) / 30;
				m_InOutValue["Tail3"] = (D3DXVECTOR3(0.0f, 0.2f, 0.0f) - m_MotionModel["Tail3"]->GetRotation()) / 30;

				m_InOutValuePos["UpBody"] = (D3DXVECTOR3(-1.0f, 0.1f, 0.3f) - m_MotionModel["UpBody"]->GetPosition()) / 30;
				m_InOutValuePos["LowBody"] = (D3DXVECTOR3(-1.0f, 0.0f, 0.3f) - m_MotionModel["LowBody"]->GetPosition()) / 30;
				m_InOutValuePos["Lkata"] = (D3DXVECTOR3(0.8f, 0.5f, 1.0f) - m_MotionModel["Lkata"]->GetPosition()) / 30;

				m_MotionFlame = 30;

				break;

			case 2:
				m_MotionDelyFlag = true;
				break;
			default:
				break;

			}
		}

		if (m_MotionDelyFlag)
		{
			if (m_FlameCnt > 20)
			{
				m_MotionEnd = true;
				m_FlameCnt = 0;
			}
		}
	}

	if (PlayMotion != "")
	{
		m_FlameCnt++;
		m_FlameCnt2++;
	}
}
