// Fill out your copyright notice in the Description page of Project Settings.


#include "Yuchin/SkillPresetSaveData.h"

USkillPresetSaveData::USkillPresetSaveData()
{
	skillDataList.playerName = "Nickname";
	skillDataList.skillPointArr.Init(0, 9);	// �迭 ������ 9 ��� �� 0���� �ʱ�ȭ
	skillDataList.canUseSkillPoint = 30;
}
