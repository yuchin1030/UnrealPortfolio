// Fill out your copyright notice in the Description page of Project Settings.


#include "Yuchin/SkillPresetSaveData.h"

USkillPresetSaveData::USkillPresetSaveData()
{
	skillDataList.playerName = "Nickname";
	skillDataList.skillPointArr.Init(0, 9);	// 배열 사이즈 9 모든 값 0으로 초기화
	skillDataList.canUseSkillPoint = 30;
}
