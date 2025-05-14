// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CHR/EnemySaveData.h"
#include "TestRoomLoadWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API UTestRoomLoadWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	void NativeConstruct() override;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* button_bossEnemy;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* button_normalEnemy;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* button_Return;
	UPROPERTY(EditDefaultsOnly, Category = "UI", meta = (BindWidget))
	class UButton* RemoveYes;
	UPROPERTY(EditDefaultsOnly, Category = "UI", meta = (BindWidget))
	class UButton* RemoveNo;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* image_enemyBack;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* image_bossBack;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* image_enemyBack_off;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* image_bossBack_off;
	UPROPERTY(meta = (BindWidget))
	class UImage* DeleteMonster;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UScrollBox* enemyScroll;

	UPROPERTY(EditDefaultsOnly, Category = "UI", meta = (BindWidget))
	class UCanvasPanel* CanvasPannel_RemoveQuestion;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UTREnemyList> EnemyListUI_BP;

	UPROPERTY()
	TArray<FEnemySaveDataStruct> loadDataList;

	UPROPERTY()
	FString name;

	class UTREnemyList* listTemp;

	class ATestRoomGameMode* TRGM;

	class AMainPlayerController* pc;

	class ACameraActor* settingCamera;

	void MoveToEnemy();

	UFUNCTION()
	void ShowNormalEnemyList();

	UFUNCTION()
	void ShowBossEnemyList();

	UFUNCTION()
	void CloseWidget();

	UFUNCTION()
	void WantRemove();

	UFUNCTION()
	void NoWantRemove();
};
