// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/DungeonEditCharacter.h"
#include "Yohan/DungeonEditComponent.h"
#include "MainPlayerController.h"
#include <../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h>
#include <../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>


ADungeonEditCharacter::ADungeonEditCharacter()
{
	// ���� ������ ������Ʈ �߰�
	dungeonEditComponent = CreateDefaultSubobject<UDungeonEditComponent>(TEXT("DungeonEditComponent"));
}

