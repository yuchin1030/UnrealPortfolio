// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CHR/BaseEnemy.h"
#include "TREnemyList.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API UTREnemyList : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* enemyNameText;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* enemyCostText;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* enemyTypeText;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* button_enemySelect;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* button_Remove;
		
	FName _bodyRowName;
	
	FName _weapon1RowName;
	
	FName _weapon2RowName;
	
	FName _gearRowName;

	FString _name;

	bool _bIsBossType;
	
	struct FAIStat _AIData;
		
	UPROPERTY()
	class ADungeonEditCharacter* dc;

	int32 enemyIndex;

	UFUNCTION()
	void EnemySelect();

	UFUNCTION()
	void RemoveEnemy(FString __name);

	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* SelectAnim;

	UFUNCTION()
	void OnHovered();

	UFUNCTION()
	void OnUnHovered();


	///////////////////////////////////////////////////////////////////////////////
	UFUNCTION()
	void ClickRemove();
};
