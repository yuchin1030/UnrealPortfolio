// Fill out your copyright notice in the Description page of Project Settings.


#include "WaitingRoomTimerWidget.h"
#include "WatinGameMode.h"
#include "Components/TextBlock.h"
#include "WaitingRoomGameState.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>

void UWaitingRoomTimerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateCanTick();

	gm = Cast<AWatinGameMode>(GetWorld()->GetAuthGameMode());
	gs = Cast<AWaitingRoomGameState>(UGameplayStatics::GetGameState(GetWorld()));
}

void UWaitingRoomTimerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


}

void UWaitingRoomTimerWidget::TimerSet()
{
	if (gs)
	{
		// ���� ������Ʈ�� ���� Ÿ�̸Ӹ� �޾ƿͼ�, �ʸ� �����Ѵ�
		FString secString = FString::FromInt((int)(gs->StartTimer) % 60);
		FText sec = FText::FromString(secString);
		Text_Seconds->SetText(sec);
	}
}
