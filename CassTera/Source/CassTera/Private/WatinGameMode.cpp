// Fill out your copyright notice in the Description page of Project Settings.


#include "WatinGameMode.h"
#include "WaitingRoomTimerWidget.h"

AWatinGameMode::AWatinGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWatinGameMode::BeginPlay()
{
	Super::BeginPlay();

	//// Ÿ�̸� ui�� �����ϰ�
	//if (WaitingTimerUI_BP)
	//{
	//	WaitingTimerUI = Cast< UWaitingRoomTimerWidget>(CreateWidget(GetWorld(), WaitingTimerUI_BP));

	//	// ����Ʈ�� ������
	//	WaitingTimerUI->AddToViewport();
	//}
	
}

void AWatinGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// ���� ���� Ÿ�̸Ӹ� ������
	/*StartTimer -= DeltaSeconds;*/
}
