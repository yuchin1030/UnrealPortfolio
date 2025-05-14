// Fill out your copyright notice in the Description page of Project Settings.


#include "CHR/CreateRoomWidget.h"
#include "OurGameInstance.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/ScrollBox.h"
#include "Components/Border.h"
#include "ChallengersCharacter.h"
#include "CHR/RoomListItemUI.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Yohan/DungeonListWidget.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/TextBlock.h>
#include "Yohan/CreateRoomDungeonListWidget.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Sound/SoundBase.h>

#define PLAYERNUM 4

void UCreateRoomWidget::BattleNPCSound()
{
	if (NPCSoundPlay)
	{
		UGameplayStatics::PlaySound2D(this, NPCSoundPlay);
	}
}

void UCreateRoomWidget::NativeConstruct()
{
	gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());
	
	gi->OnMySessionSearchCompleteDelegate.AddDynamic(this, &UCreateRoomWidget::AddRoomInfoUI);
	gi->createRoomDelegate.BindUFunction(this, FName("PlayFadeOut"));

	Btn_X->OnClicked.AddDynamic(this, &UCreateRoomWidget::OnMyClickX);
	Btn_Refresh->OnClicked.AddDynamic(this, &UCreateRoomWidget::OnClickFindRoom);
	Btn_ShowCreate->OnClicked.AddDynamic(this, &UCreateRoomWidget::ShowCreateUI);
	Btn_CreateX->OnClicked.AddDynamic(this, &UCreateRoomWidget::HideCreateUI);
	Btn_Create->OnClicked.AddDynamic(this, &UCreateRoomWidget::OnMyClickCreateRoom);

	if (gi) {
		gi->FindOtherSessions();
	}

	BattleNPCSound();
}

void UCreateRoomWidget::Allfalse()
{
	TArray<UWidget*> itemList = scroll_DunList->GetAllChildren();

	if (!itemList.IsEmpty())
	{
		for (UWidget* item : itemList)
		{
			UCreateRoomDungeonListWidget* castedItem = Cast<UCreateRoomDungeonListWidget>(item);
			if (castedItem->Show == true)
			{
				castedItem->Show = false;
				castedItem->OnUnHovered();
			}
			
		}
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Empty"));
}

void UCreateRoomWidget::OnMyClickCreateRoom()
{
	//APlayerController* playerController = Cast<APlayerController >(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (gi) {
		gi->CreateMySession(editText_RoomName->GetText().ToString());		
	}
}

void UCreateRoomWidget::OnMyClickX()
{
	AChallengersCharacter* player = Cast<AChallengersCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	APlayerController* playerController = Cast<APlayerController >(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	playerController->SetInputMode(FInputModeGameOnly());
	playerController->SetShowMouseCursor(false);
	SetVisibility(ESlateVisibility::Hidden);

	bClosed = true;
	player->CanWalk(); 
	player->bShowBattleNPC=false;
}

void UCreateRoomWidget::RefreshRoomList()
{
	if (gi) {
		gi->FindOtherSessions();
	}
}

void UCreateRoomWidget::OnClickFindRoom()
{
	RoomList->ClearChildren();
	if (gi) {
		gi->FindOtherSessions();
	}
}

void UCreateRoomWidget::ShowCreateUI()
{
	CreateMenu->SetVisibility(ESlateVisibility::Visible);
		
	if (gi)
	{
		loadDunList.Empty();
		// 생성되어 있는 던전 데이터 로드
		gi->LoadDungeonData();
		loadDunList = gi->loadedDunData;

		scroll_DunList->ClearChildren();

		for (int i = 0; i < loadDunList.Num(); i++)
		{
			// 던전 리스트 위젯을 생성
			UCreateRoomDungeonListWidget* dunListTemp = CreateWidget<UCreateRoomDungeonListWidget>(this, dunListUI_BP);

			if (dunListTemp)
			{
				// 던전 리스트 위젯 인덱스 부여
				dunListTemp->dunIndex = i;
				
				// 던전 이름 부여
				FText nameText = FText::FromString(loadDunList[i].dunName);
				dunListTemp->dungeonNameText->SetText(nameText);

				// 던전 타입 부여
				FText typeText = FText::FromString(loadDunList[i].dunType);
				dunListTemp->dungeonTypeText->SetText(typeText);
				
				// 던전 코스트 부여
				dunListTemp->dungeonCostText->SetText(FText::FromString(FString::FromInt(loadDunList[i].dunTotalCost)));

				// 던전 리스트 위젯 던전 정보 부여
				dunListTemp->_dunName = loadDunList[i].dunName;
				dunListTemp->_dunType = loadDunList[i].dunType;
				dunListTemp->_savedEnemys = loadDunList[i].savedEnemys;
				dunListTemp->_dunCost = loadDunList[i].dunTotalCost;

				scroll_DunList->AddChild(dunListTemp);
			}
		}
	}
}

void UCreateRoomWidget::HideCreateUI()
{
	CreateMenu->SetVisibility(ESlateVisibility::Hidden);
}

void UCreateRoomWidget::AddRoomInfoUI(const FSessionInfo& info)
{
	auto ui = CreateWidget<URoomListItemUI>(this, roomItemUIFactory);

	ui->Setup(info);

	RoomList->AddChild(ui);
}

void UCreateRoomWidget::PlayFadeOut(bool bIsSucceed)
{
	if (bIsSucceed) {
		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
		PlayAnimation(FadeOut);
	}
	else {
		PlayAnimation(Failed);
	}
}
