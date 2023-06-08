#include "MaxPotion.h"
#include "Scene.h"
#include "manager.h"
#include "Player.h"

void MaxPotion::UseAction()
{
	Scene* scene = Manager::GetScene();
	GameObject* pPlayer = scene->GetGameObject("Player", scene->PLAY_LAYER);

	pPlayer->GetComponent<Player>()->SetRedHp(0);
	pPlayer->GetComponent<Player>()->MaxHP();

}
