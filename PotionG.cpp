#include "PotionG.h"
#include "Scene.h"
#include "manager.h"
#include "Player.h"

void PotionG::UseAction()
{
	Scene* scene = Manager::GetScene();
	GameObject* pPlayer = scene->GetGameObject("Player", scene->PLAY_LAYER);

	int PlayerRedHp = pPlayer->GetComponent<Player>()->GetRedHp();

	//�ԃQ�[�W�����񕜗ʂ�����������
	if (PlayerRedHp < m_HealValue)
	{
		//�ԃQ�[�W�������A�΃Q�[�W��L�΂�
		pPlayer->GetComponent<Player>()->SetRedHp(0);

		//�񕜗ʂ�����l�𒴂����ꍇ
		if (pPlayer->GetComponent<Player>()->GetMaxHP() - pPlayer->GetComponent<Player>()->getHp() < m_HealValue)
		{
			pPlayer->GetComponent<Player>()->MaxHP();

		}
		else
		{
			pPlayer->GetComponent<Player>()->HealHP(m_HealValue);

		}

	}
	else //�ԃQ�[�W�̂ق�������������
	{
		//�񕜗̕��ԃQ�[�W��΃Q�[�W��
		pPlayer->GetComponent<Player>()->SetRedHp(PlayerRedHp - m_HealValue);
		pPlayer->GetComponent<Player>()->HealHP(m_HealValue);

	}
}
