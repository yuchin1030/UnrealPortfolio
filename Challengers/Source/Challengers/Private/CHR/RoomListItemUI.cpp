// Fill out your copyright notice in the Description page of Project Settings.


#include "CHR/RoomListItemUI.h"
#include "CHR/CreateRoomWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "OurGameInstance.h"


void URoomListItemUI::NativeConstruct()
{
	Btn_Join->OnClicked.AddDynamic(this, &URoomListItemUI::OnMyClickJoinRoom);
}

void URoomListItemUI::OnMyClickJoinRoom()
{
	UCreateRoomWidget* CRW = Cast<UCreateRoomWidget>(GetParent()->GetOuter()->GetOuter());
	if (CRW)
	{
		CRW->PlayFadeOut(true);
	}

	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
	
	FTimerHandle fadeTimer;
	GetWorld()->GetTimerManager().SetTimer(fadeTimer, ([&]() {
		auto gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());
		if (gi)
		{
			gi->JoinMySession(index);

			// 로딩 화면
			gi->bdunloadStart = true;
			gi->bisMulti = true;
			UE_LOG(LogTemp, Error, TEXT("%s"), gi->bdunloadStart ? TEXT("True") : TEXT("False"));
		}
	}), 1.0f, false);
}

void URoomListItemUI::Setup(const FSessionInfo& info)
{
	index = info.index;
	Text_RoomName->SetText(FText::FromString(info.roomName));
	int32 currentNum = info.currentPlayerCount;
}
