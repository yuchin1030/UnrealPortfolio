// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DE_EnemyControlWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API UDE_EnemyControlWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* button_move;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* button_delete;

	UPROPERTY()
	class ADungeonEditCharacter* dc;

	UFUNCTION()
	void Move();

	UFUNCTION()
	void Delete();
};
