// Fill out your copyright notice in the Description page of Project Settings.


#include "GJY/OptionUI.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/Slider.h>
#include "CHR/BGMActor.h"
#include "EngineUtils.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/AudioComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "ChallengersCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UOptionUI::NativeConstruct()
{
	WidgetSwitcher_Notices->SetVisibility(ESlateVisibility::Hidden);	

	OKbutton->OnClicked.AddDynamic(this, &UOptionUI::VolumeSave);
	NoButton->OnClicked.AddDynamic(this, &UOptionUI::VolumeCancel);
	TitleButton->OnClicked.AddDynamic(this, &UOptionUI::ClickTitleButton);
	TitleYes->OnClicked.AddDynamic(this, &UOptionUI::GoToTitleMap);
	TitleNo->OnClicked.AddDynamic(this, &UOptionUI::ClickNoGameTitleMap);
	GameQuitButton->OnClicked.AddDynamic(this, &UOptionUI::ClickGameQuitButton);
	QuitYes->OnClicked.AddDynamic(this, &UOptionUI::FinalQuit);
	QuitNo->OnClicked.AddDynamic(this, &UOptionUI::NoQuit);
	Button_close->OnClicked.AddDynamic(this, &UOptionUI::CloseOptionUI);

	for (TActorIterator<ABGMActor> it(GetWorld()); it; ++it)
	{
		VolumeActor = *it;
	}
}

void UOptionUI::VolumeSave()
{
	
	SetVolumeSize = VolumeSlider->GetValue();

	VolumeActor->audioComp->SetVolumeMultiplier(SetVolumeSize); 
	DefaultVolumeSize = SetVolumeSize;

	UE_LOG(LogTemp, Warning, TEXT("Defaults:%f"), DefaultVolumeSize);
	UE_LOG(LogTemp, Warning, TEXT("SetVol:%f"), SetVolumeSize);

}

void UOptionUI::VolumeCancel()
{
	VolumeActor->audioComp->SetVolumeMultiplier(DefaultVolumeSize);

	UE_LOG(LogTemp, Warning, TEXT("Defaults:%f"), DefaultVolumeSize);
	UE_LOG(LogTemp, Warning, TEXT("SetVol:%f"), SetVolumeSize);
	VolumeSlider->SetValue(DefaultVolumeSize);
}



void UOptionUI::ClickTitleButton()
{
	WidgetSwitcher_Notices->SetVisibility(ESlateVisibility::Visible);
	WidgetSwitcher_Notices->SetActiveWidgetIndex(0);
}

void UOptionUI::GoToTitleMap()
{
	UGameplayStatics::OpenLevel(GetWorld(),"TitleMaps");
}

void UOptionUI::ClickNoGameTitleMap()
{
	WidgetSwitcher_Notices->SetVisibility(ESlateVisibility::Hidden);
}



void UOptionUI::ClickGameQuitButton()
{
	WidgetSwitcher_Notices->SetVisibility(ESlateVisibility::Visible);
	WidgetSwitcher_Notices->SetActiveWidgetIndex(1);
}

void UOptionUI::FinalQuit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(),GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}

void UOptionUI::NoQuit()
{
	WidgetSwitcher_Notices->SetVisibility(ESlateVisibility::Hidden);
}

void UOptionUI::CloseOptionUI()
{
	APlayerController* pc = Cast<APlayerController >(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	class AChallengersCharacter* cc = Cast<AChallengersCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	SetVisibility(ESlateVisibility::Hidden);
	cc->bOption = false;
	pc->SetInputMode(FInputModeGameOnly());
	pc->SetShowMouseCursor(false);
	cc->GetCharacterMovement()->Activate();

}

