// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoadingWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API ULoadingWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image_Single;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image_Multi;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image_Steam;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image_Dissel;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image_Cyber;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image_Test;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image_Char;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UBorder* FadeBorder;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* FadeOut;

	UFUNCTION()
	void HideAll();

	UFUNCTION()
	void FadeOutStart(float waitTime);


};
