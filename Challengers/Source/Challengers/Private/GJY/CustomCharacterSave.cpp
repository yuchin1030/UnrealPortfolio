// Fill out your copyright notice in the Description page of Project Settings.


#include "GJY/CustomCharacterSave.h"

UCustomCharacterSave::UCustomCharacterSave()
{
	bIsMan=true;
	_FinalMeshArr.Init(FName(""),18);

	_FinalMeshArr[17] = FName("1");
	_FinalMeshArr[0] = FName("0");
	_FinalMeshArr[1] = FName("8");
	_FinalMeshArr[2] = FName("7");
	_FinalMeshArr[3] = FName("2");
	_FinalMeshArr[4] = FName("4");
	_FinalMeshArr[5] = FName("10");
	_FinalMeshArr[6] = FName("18");
	_FinalMeshArr[7] = FName("19");
	_FinalMeshArr[8] = FName("12");
	_FinalMeshArr[9] = FName("9");
	_FinalMeshArr[10] = FName("17");
	_FinalMeshArr[11] = FName("20");
	_FinalMeshArr[12] = FName("11");
	_FinalMeshArr[13] = FName("13");
	_FinalMeshArr[14] = FName("14");
	_FinalMeshArr[15] = FName("15");
	_FinalMeshArr[16] = FName("16");

	playerName = "Nickname";

	_ClothesColorNum = 0;
	_HairColorNum = 0;

	bGlove = false;
}
