#include "BJK/BattleNPCWidget.h"
#include "Components/Button.h"
#include "MainPlayerController.h"
#include "ChallengersCharacter.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>

void UBattleNPCWidget::NativeConstruct()
{
	Button_Close->OnClicked.AddDynamic(this, &UBattleNPCWidget::OnClickClose);
	Button_Reset->OnClicked.AddDynamic(this, &UBattleNPCWidget::OnClickReset);
	Button_CreateRoom->OnClicked.AddDynamic(this, &UBattleNPCWidget::OnClickCreateRoom);
}

// 창 닫기
void UBattleNPCWidget::OnClickClose()
{
	AChallengersCharacter* player = Cast<AChallengersCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	APlayerController* PlayerController = Cast<APlayerController >(UGameplayStatics::GetPlayerController(GetWorld(), 0));


	PlayerController->SetShowMouseCursor(false);
	PlayerController->SetInputMode(FInputModeGameOnly());
	SetVisibility(ESlateVisibility::Hidden);
	bClosed = true;
	if (player != nullptr)
	{
		player->CanWalk();
	}

	player->bShowBattleNPC=false;
}

// 새로고침
void UBattleNPCWidget::OnClickReset()
{
	
}

// 방 생성하기 버튼
void UBattleNPCWidget::OnClickCreateRoom()
{
	
}
