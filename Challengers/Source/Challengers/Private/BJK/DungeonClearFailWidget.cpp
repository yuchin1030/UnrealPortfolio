#include "BJK/DungeonClearFailWidget.h"
#include "Components/Button.h"
#include "ChallengersCharacter.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "OurGameInstance.h"
#include "MainPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"


void UDungeonClearFailWidget::NativeConstruct()
{
	// 아이템 모두 받기
	Button_GetItem->OnClicked.AddDynamic(this, &UDungeonClearFailWidget::OnClickGetItem);

	UUserWidget::PlayAnimation(AnimArrow, 0, 0, EUMGSequencePlayMode::Forward, 1);
	
	auto pc = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());

	pc->SetInputMode(FInputModeUIOnly());
	pc->bShowMouseCursor = true;
}

void UDungeonClearFailWidget::OnClickGetItem()
{
	// 플레이어에게 획득한 돈과 경험치 추가

	auto gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());
	if (gi)
	{
		auto pc = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());

		pc->SetInputMode(FInputModeGameOnly());
		pc->bShowMouseCursor = false;

		// 게임 클리어 하고 나서 던전 이동.
		gi->MoveToDungeon();
	}

	AChallengersCharacter* player = Cast<AChallengersCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	APlayerController* PlayerController = Cast<APlayerController >(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->SetShowMouseCursor(false);
	//SetVisibility(ESlateVisibility::Hidden);

	player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}


// 획득 골드량
// void UDungeonClearFailWidget::GetGoldPlayer()
// {
// 	
// }
// 획득 경험치
// void UDungeonClearFailWidget::GetEXPPlayer()
// {
// 	
// }
