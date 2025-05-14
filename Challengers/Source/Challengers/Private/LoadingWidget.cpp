// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadingWidget.h"
#include "Components/Image.h"
#include "Components/Border.h"

void ULoadingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//UUserWidget::PlayAnimation(LoadingIcon, 0, 10);	
}

void ULoadingWidget::HideAll()
{
	Image_Single->SetVisibility(ESlateVisibility::Hidden);
	Image_Multi->SetVisibility(ESlateVisibility::Hidden);
	Image_Steam->SetVisibility(ESlateVisibility::Hidden);
	Image_Dissel->SetVisibility(ESlateVisibility::Hidden);
	Image_Cyber->SetVisibility(ESlateVisibility::Hidden);
	Image_Char->SetVisibility(ESlateVisibility::Hidden);
}

void ULoadingWidget::FadeOutStart(float waitTime)
{
	if (waitTime == 0)
	{
		PlayAnimation(FadeOut);
	}
	else {
		FTimerHandle fadeOutTimer;
		GetWorld()->GetTimerManager().SetTimer(fadeOutTimer, FTimerDelegate::CreateLambda([&]() {
			PlayAnimation(FadeOut);
			}), waitTime, false);
	}
}
