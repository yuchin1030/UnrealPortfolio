// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterName.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API UCharacterName : public UUserWidget
{
	GENERATED_BODY()


private:
	
	virtual void NativeConstruct() override;


 public:

	UPROPERTY(EditDefaultsOnly, Category = "NickName" , meta = (BindWidget))
	class UTextBlock* Text_Name;

	UFUNCTION()
	void ShowNickName(FString NickName);


	class AChallengersCharacter* CC;
	
	



};
