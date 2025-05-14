#include "BJK/DungeonClearFailWidget.h"
#include "Components/Button.h"
#include "ChallengersCharacter.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "OurGameInstance.h"
#include "MainPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"


void UDungeonClearFailWidget::NativeConstruct()
{
	// ������ ��� �ޱ�
	Button_GetItem->OnClicked.AddDynamic(this, &UDungeonClearFailWidget::OnClickGetItem);

	UUserWidget::PlayAnimation(AnimArrow, 0, 0, EUMGSequencePlayMode::Forward, 1);
	
	auto pc = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());

	pc->SetInputMode(FInputModeUIOnly());
	pc->bShowMouseCursor = true;
}

void UDungeonClearFailWidget::OnClickGetItem()
{
	// �÷��̾�� ȹ���� ���� ����ġ �߰�

	auto gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());
	if (gi)
	{
		auto pc = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());

		pc->SetInputMode(FInputModeGameOnly());
		pc->bShowMouseCursor = false;

		// ���� Ŭ���� �ϰ� ���� ���� �̵�.
		gi->MoveToDungeon();
	}

	AChallengersCharacter* player = Cast<AChallengersCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	APlayerController* PlayerController = Cast<APlayerController >(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->SetShowMouseCursor(false);
	//SetVisibility(ESlateVisibility::Hidden);

	player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}


// ȹ�� ��差
// void UDungeonClearFailWidget::GetGoldPlayer()
// {
// 	
// }
// ȹ�� ����ġ
// void UDungeonClearFailWidget::GetEXPPlayer()
// {
// 	
// }
