// Fill out your copyright notice in the Description page of Project Settings.


#include "CHR/CEnemyAnimInst.h"
#include "CHR/BaseEnemy.h"

void UCEnemyAnimInst::AnimNotify_Enemy_ActiveBox()
{
	if (enemyREF) {
		enemyREF->Anim_CloseAtkStart();
	}
}

void UCEnemyAnimInst::AnimNotify_Enemy_DeactiveBox()
{
	if (enemyREF) {
		enemyREF->Anim_CloseAtkEnd();
	}
}
