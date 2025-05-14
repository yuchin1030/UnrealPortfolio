// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FrontHairColorList.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API UFrontHairColorList : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	class UColorStruct* CS;
	class ACreatorTestCharacter* CC;

	UPROPERTY(meta = (BindWidget))
	class UButton* SelectButton;

	UPROPERTY(meta = (BindWidget))
	class UImage* img_BtnColor;

	int number = 0;


	UFUNCTION()
	void ClickSelectButton();

};
