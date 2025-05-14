
#include "BJK/TitleWidget.h"
#include "Components/Button.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/TextBlock.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Image.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "OurGameInstance.h"



void UTitleWidget::NativeConstruct()
{
	APlayerController* pc = Cast<APlayerController >(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	pc->bShowMouseCursor = true;

	Button_LoadGame->OnClicked.AddDynamic(this, &UTitleWidget::OnClickButton_LoadGame);
	Button_LoadGame->OnHovered.AddDynamic(this, &UTitleWidget::OnHoveredButton_LoadGame);
	Button_LoadGame->OnUnhovered.AddDynamic(this,&UTitleWidget::UTitleWidget::OnUnHoveredButton_LoadGame);

	Button_NewGame->OnClicked.AddDynamic(this, &UTitleWidget::OnClickButton_NewGame);
	Button_NewGame->OnHovered.AddDynamic(this, &UTitleWidget::OnHoveredButton_NewGame);
	Button_NewGame->OnUnhovered.AddDynamic(this, &UTitleWidget::UTitleWidget::OnUnHoveredButton_NewGame);

	Button_Quit->OnClicked.AddDynamic(this, &UTitleWidget::OnClickButton_Quit);
	Button_Quit->OnHovered.AddDynamic(this, &UTitleWidget::OnHoveredButton_Quit);
	Button_Quit->OnUnhovered.AddDynamic(this, &UTitleWidget::UTitleWidget::OnUnHoveredButton_Quit);


	UUserWidget::PlayAnimation(LogoAnim, 0, 1, EUMGSequencePlayMode::Forward, 1);

}



// 계속하기 버튼
void UTitleWidget::OnClickButton_LoadGame()
{
	APlayerController* pc = Cast<APlayerController >(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	pc->bShowMouseCursor = false;

	Cast<UOurGameInstance>(GetWorld()->GetGameInstance())->bSLoading = true;
}

void UTitleWidget::OnHoveredButton_LoadGame()
{
	Image_Line1->SetVisibility(ESlateVisibility::Visible);
	UUserWidget::PlayAnimation(OneAnim, 0, 1, EUMGSequencePlayMode::Forward, 1);
}

void UTitleWidget::OnUnHoveredButton_LoadGame()
{
	UUserWidget::PlayAnimation(OneAnim, 0, 1, EUMGSequencePlayMode::Reverse, 1);
	Image_Line1->SetVisibility(ESlateVisibility::Visible);
}

// 새로 시작하기 버튼
void UTitleWidget::OnClickButton_NewGame()
{
	
}

void UTitleWidget::OnHoveredButton_NewGame()
{
	Image_Line2->SetVisibility(ESlateVisibility::Visible);
	UUserWidget::PlayAnimation(TwoAnim, 0, 1, EUMGSequencePlayMode::Forward, 1);
}

void UTitleWidget::OnUnHoveredButton_NewGame()
{
	UUserWidget::PlayAnimation(TwoAnim, 0, 1, EUMGSequencePlayMode::Reverse, 1);
	Image_Line2->SetVisibility(ESlateVisibility::Hidden);
}

// 종료 버튼
void UTitleWidget::OnClickButton_Quit()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}

void UTitleWidget::OnHoveredButton_Quit()
{
	Image_Line3->SetVisibility(ESlateVisibility::Visible);
	UUserWidget::PlayAnimation(ThreeAnim, 0, 1, EUMGSequencePlayMode::Forward, 1);
}

void UTitleWidget::OnUnHoveredButton_Quit()
{
	UUserWidget::PlayAnimation(ThreeAnim, 0, 1, EUMGSequencePlayMode::Reverse, 1);
	Image_Line3->SetVisibility(ESlateVisibility::Hidden);
}
