// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JoinBattle_ReadyWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API UJoinBattle_ReadyWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;



	// �����غ� ��ư
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Ready;

	UFUNCTION()
	void OnClickReady();
	

	// ������ ��ư
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Quit;

	UFUNCTION()
	void OnClickQuit();

};
