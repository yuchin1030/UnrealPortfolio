#include "SelectCustomWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/CanvasPanel.h>
#include "MainPlayerController.h"
#include "ChallengersCharacter.h"
#include "CustomNPC.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "OurGameInstance.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Sound/SoundBase.h>

void USelectCustomWidget::NativeConstruct()
{
	Button_MonsterSetting->OnHovered.AddDynamic(this, &USelectCustomWidget::OnHoverMonsterSetting);
	Button_MonsterSetting->OnUnhovered.AddDynamic(this, &USelectCustomWidget::OnUnHoveredMonsterSetting);

	Button_DungeonSetting->OnHovered.AddDynamic(this, &USelectCustomWidget::OnHoverDungeonSetting);
	Button_DungeonSetting->OnUnhovered.AddDynamic(this, &USelectCustomWidget::OnUnHoveredDungeonSetting);


	Button_Close->OnClicked.AddDynamic(this, &USelectCustomWidget::OnClickClose);

	CustomNPCSound();
}

void USelectCustomWidget::CustomNPCSound()
{
	if (NPCSoundPlay)
	{
		UGameplayStatics::PlaySound2D(this, NPCSoundPlay);
	}
}

void USelectCustomWidget::OnHoverMonsterSetting()
{
	UUserWidget::PlayAnimation(SelectMonsterSetAnim, 0, 1, EUMGSequencePlayMode::Forward,3);

}

void USelectCustomWidget::OnHoverDungeonSetting()
{
	UUserWidget::PlayAnimation(SelectDungeonSetAnim, 0, 1, EUMGSequencePlayMode::Forward,3);

}

void USelectCustomWidget::OnUnHoveredMonsterSetting()
{
	UUserWidget::PlayAnimation(SelectMonsterSetAnim, 0, 1, EUMGSequencePlayMode::Reverse, 3);

}

void USelectCustomWidget::OnUnHoveredDungeonSetting()
{
	UUserWidget::PlayAnimation(SelectDungeonSetAnim, 0, 1, EUMGSequencePlayMode::Reverse, 3);

}

// Ã¢ ´Ý±â
void USelectCustomWidget::OnClickClose()
{
	AChallengersCharacter* player = Cast<AChallengersCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	APlayerController* PlayerController = Cast<APlayerController >(UGameplayStatics::GetPlayerController(GetWorld(), 0));


	PlayerController->SetShowMouseCursor(false);
	PlayerController->SetInputMode(FInputModeGameOnly());
	SetVisibility(ESlateVisibility::Hidden);
	bClosed =true;
	if (player != nullptr)
	{
		player->CanWalk();
	}
	player->bShowSelectCustomNPC = false;
}
