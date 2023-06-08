#include "PotionG.h"
#include "Scene.h"
#include "manager.h"
#include "Player.h"

void PotionG::UseAction()
{
	Scene* scene = Manager::GetScene();
	GameObject* pPlayer = scene->GetGameObject("Player", scene->PLAY_LAYER);

	int PlayerRedHp = pPlayer->GetComponent<Player>()->GetRedHp();

	//赤ゲージよりも回復量が多かったら
	if (PlayerRedHp < m_HealValue)
	{
		//赤ゲージを消し、緑ゲージを伸ばす
		pPlayer->GetComponent<Player>()->SetRedHp(0);

		//回復量が上限値を超えた場合
		if (pPlayer->GetComponent<Player>()->GetMaxHP() - pPlayer->GetComponent<Player>()->getHp() < m_HealValue)
		{
			pPlayer->GetComponent<Player>()->MaxHP();

		}
		else
		{
			pPlayer->GetComponent<Player>()->HealHP(m_HealValue);

		}

	}
	else //赤ゲージのほうが多かったら
	{
		//回復領分赤ゲージを緑ゲージに
		pPlayer->GetComponent<Player>()->SetRedHp(PlayerRedHp - m_HealValue);
		pPlayer->GetComponent<Player>()->HealHP(m_HealValue);

	}
}
