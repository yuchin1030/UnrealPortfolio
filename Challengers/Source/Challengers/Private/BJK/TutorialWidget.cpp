#include "BJK/TutorialWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/PlayerController.h>
#include "GameFramework/CharacterMovementComponent.h"
#include "ChallengersCharacter.h"

void UTutorialWidget::NativeConstruct()
{
	player = Cast<AChallengersCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	Button_Close->OnClicked.AddDynamic(this, &UTutorialWidget::OnClickClose);

	Button_Key->OnClicked.AddDynamic(this, &UTutorialWidget::OnClickKey);
	Button_Mon->OnClicked.AddDynamic(this, &UTutorialWidget::OnClickMon);
	Button_Dun->OnClicked.AddDynamic(this, &UTutorialWidget::OnClickDun);

}



void UTutorialWidget::OnClickClose()
{
	APlayerController* PlayerController = Cast<APlayerController >(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->SetShowMouseCursor(false);
	SetVisibility(ESlateVisibility::Hidden);
	player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	player->bShowTutorial = true;
}

void UTutorialWidget::OnClickKey()
{
	WidgetSwitcher_Tutorial->SetActiveWidgetIndex(0);
}

void UTutorialWidget::OnClickMon()
{
	WidgetSwitcher_Tutorial->SetActiveWidgetIndex(1);

}

void UTutorialWidget::OnClickDun()
{
	WidgetSwitcher_Tutorial->SetActiveWidgetIndex(2);

}
