#include "SuperChargeState.h"
#include "manager.h"
#include "Scene.h"
#include "Enemy.h"
#include "Motion.h"
#include "NomalState.h"
#include "Particle.h"

void SuperChargeState::Action()
{
	pEnemy->GetComponent<Motion>()->SetShaderCnt(2);
	pEnemy->GetComponent<Particle>()->SetUse(true);

	m_AngerCnt++;
	if (m_AngerCnt > 6000 || pEnemy->GetComponent<Enemy>()->GetFearFlag())
	{
		pEnemy->GetComponent<Enemy>()->ResetChargeCnt();
		pEnemy->GetComponent<Enemy>()->NextSituation(new NomalState(pEnemy));

	}
}

int SuperChargeState::GetStatus()
{
	return 3;
}
