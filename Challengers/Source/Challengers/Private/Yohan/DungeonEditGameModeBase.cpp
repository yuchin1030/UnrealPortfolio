// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/DungeonEditGameModeBase.h"
#include "Yohan/DungeonEditCharacter.h"
#include "ChallengersCharacter.h"
#include "OurGameInstance.h"

ADungeonEditGameModeBase::ADungeonEditGameModeBase()
{	
	DefaultPawnClass = ADungeonEditCharacter::StaticClass();
}

void ADungeonEditGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// ��ġ�� �� �ִ� �ڽ�Ʈ�� �� = ĳ������ enemyCost
	auto gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());
	totalEnemyCost = gi->_enemyCost;

	
}

void ADungeonEditGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	curEnemyCost = FMath::Clamp(curEnemyCost, 0, totalEnemyCost);
}
