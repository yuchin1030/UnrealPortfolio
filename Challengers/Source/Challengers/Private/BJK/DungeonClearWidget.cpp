#include "BJK/DungeonClearWidget.h"
#include "Components/Button.h"
#include "ChallengersCharacter.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "OurGameInstance.h"
#include "OurGameModeBase.h"
#include "Yohan/EnemyCountInDungeonWidget.h"
#include "MainPlayerController.h"
#include "Yohan/OurGameStateBase.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/TextBlock.h>
#include "BJK/MainPlayerWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <../../../../../../../Source/Runtime/Engine/Public/Net/UnrealNetwork.h>

void UDungeonClearWidget::NativeConstruct()
{
	OG = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());
	auto gs = Cast<AOurGameStateBase>(GetWorld()->GetGameState());

	// ������ ��� �ޱ�
	Button_GetItem->OnClicked.AddDynamic(this, &UDungeonClearWidget::OnClickGetItem);

	UUserWidget::PlayAnimation(AnimArrow, 0, 0, EUMGSequencePlayMode::Forward,1);

	auto pc = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
	if (pc)
	{
		pc->bShowMouseCursor = true;
	}

	Cost = gs->ClearWidget_Cost;


	TextBlock_GetGold->SetText(FText::AsNumber(Cost));
	TextBlock_getEXP->SetText(FText::AsNumber(Cost /3));

	OnRep_CostIn();
}

void UDungeonClearWidget::OnClickGetItem()
{
	// �÷��̾�� ȹ���� ���� ����ġ �߰�

	auto gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());
	auto gm = Cast<AOurGameModeBase>(GetWorld()->GetAuthGameMode());
	auto pc = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
	auto gs = Cast<AOurGameStateBase>(GetWorld()->GetGameState());

	pc->mainplayerWidget->CurrentCoin += ClearGold;
	pc->mainplayerWidget->TextBlock_Coin->SetText(FText::AsNumber(pc->mainplayerWidget->CurrentCoin));

	AChallengersCharacter* player = Cast<AChallengersCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	APlayerController* PlayerController = Cast<APlayerController >(UGameplayStatics::GetPlayerController(GetWorld(), 0));


	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->SetShowMouseCursor(false);
	//SetVisibility(ESlateVisibility::Hidden);
	player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

	if (pc)
	{
		pc->bShowMouseCursor = false;
	}


	if (gi)
	{
		if (gs)
		{
			// ������ ������, ���ʹ� ī��Ʈ UI�� ����
			gs->enemyCountUI -> RemoveFromParent();
		}
		// ���� Ŭ���� �ϰ� ���� ���� �̵�.
		gi->MoveToDungeon();
	}

	
}

void UDungeonClearWidget::OnRep_CostIn()
{
	TextBlock_GetGold->SetText(FText::AsNumber(Cost));
	TextBlock_getEXP->SetText(FText::AsNumber(Cost / 3));
}

void UDungeonClearWidget::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UDungeonClearWidget, Cost);

}