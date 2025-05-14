// Fill out your copyright notice in the Description page of Project Settings.


#include "CHR/LEnemyAnimInst.h"
#include "CHR/BaseEnemy.h"

void ULEnemyAnimInst::AnimNotify_Enemy_FireMagic()
{
	if (enemyREF) {
		enemyREF->Anim_FireMagic();
	}
}
