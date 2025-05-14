// Fill out your copyright notice in the Description page of Project Settings.


#include "Yuchin/PlayerInfoSaveData.h"

UPlayerInfoSaveData::UPlayerInfoSaveData()
{
	playerInfoDataList.playerName = "Nickname";
	playerInfoDataList.playerLevel = 1;
	playerInfoDataList.playerGold = 100000000;
	playerInfoDataList.playerCurrentExp = 0;
	playerInfoDataList.playerMaxExp = 1000;
	playerInfoDataList.playerEnemyCost = 2000;
	playerInfoDataList.weaponLevel.Init(1, 3);
	playerInfoDataList.currentWeaponStat.Init(30, 3);
	playerInfoDataList.nextWeaponStat.Init(31, 3);
	playerInfoDataList.upgWeaponNeedGold.Init(100, 3);
}


