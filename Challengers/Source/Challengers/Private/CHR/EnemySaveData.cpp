// Fill out your copyright notice in the Description page of Project Settings.


#include "CHR/EnemySaveData.h"

UEnemySaveData::UEnemySaveData()
{
	for(int i = 0; i < enemyDataList.Num(); i++){
		enemyDataList[i].name = "";
	}
}
