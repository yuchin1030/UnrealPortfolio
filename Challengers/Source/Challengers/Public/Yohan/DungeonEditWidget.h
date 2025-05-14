// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CHR/EnemySaveData.h"
#include "SaveDungeonData.h"
#include "DungeonEditWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API UDungeonEditWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	virtual void NativeConstruct();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* button_SteamPunk;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* button_DisselPunk;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* button_CyberPunk;
	
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UCanvasPanel* levelCanvas;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UCanvasPanel* enemyListCanvas;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* button_normalEnemy;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* button_bossEnemy;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UScrollBox* enemyScroll;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* button_SpawnCancel;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* button_EditCancel;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* button_saveDugeon;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* button_loadDugeon_test;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* button_DunName;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* button_closeSelect;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UEditableTextBox* editableText_DunName;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UCanvasPanel* dunNameCanvas;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* text_costOver;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* text_totalCost;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* text_curCost;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* image_dunBack;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* image_enemyBack;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* image_bossBack;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* image_dunBack_off;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* image_enemyBack_off;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* image_bossBack_off;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* button_closeDunSave;

	UPROPERTY()
	class ADungeonEditGameModeBase* gm;

	UPROPERTY()
	FString dunName;

	UPROPERTY()
	FString dunType;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UEnemyListWidget> EnemyListUI_BP;

	UPROPERTY()
	TArray<FEnemySaveDataStruct> loadDataList;

	UPROPERTY()
	TArray<FDunInfo> loadDunList;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UDungeonListWidget> dunListUI_BP;

	UPROPERTY()
	class ADungeonEditCharacter* dc;

	UPROPERTY()
	class APlayerController* pc;

	UPROPERTY()
	FString name;

	UFUNCTION()
	void OpenSteamPunkMap();

	UFUNCTION()
	void OpenDisselPunkMap();

	UFUNCTION()
	void OpenCyberPunkMap();

	UFUNCTION()
	void OpenLevelSelect();

	UFUNCTION()
	void CloseAllEditor();

	UFUNCTION()
	void ShowNormalEnemyList();

	UFUNCTION()
	void ShowBossEnemyList();

	UFUNCTION()
	void SelectCancel();

	UFUNCTION()
	void ReturnToTown();

	UFUNCTION()
	void SaveDungeon();

	UFUNCTION()
	void LoadDungeonList();

	UFUNCTION()
	void SaveDungeonName();

	UFUNCTION()
	void RemoveSaveDungeonName();
	///////////////////////////////////////////
	UFUNCTION()
	void WantHome();
	UFUNCTION()
	void NoWantHome();

	UFUNCTION()
	void WantRemove();
	UFUNCTION()
	void NoWantRemove();

	UPROPERTY(EditDefaultsOnly, Category = "UI", meta = (BindWidget))
	class UCanvasPanel* CanvasPannel_ReturnHome;

	UPROPERTY(EditDefaultsOnly, Category = "UI" , meta =(BindWidget))
	class UButton* Button_Yes;

	UPROPERTY(EditDefaultsOnly, Category = "UI" , meta =(BindWidget))
	class UButton* Button_No;

	UPROPERTY(EditDefaultsOnly, Category = "UI", meta = (BindWidget))
	class UCanvasPanel* CanvasPannel_RemoveQuestion;

	UPROPERTY(EditDefaultsOnly, Category = "UI", meta = (BindWidget))
	class UButton* RemoveYes;

	UPROPERTY(EditDefaultsOnly, Category = "UI", meta = (BindWidget))
	class UButton* RemoveNo;

	class UDungeonListWidget* dunListTemp;

	class UEnemyListWidget* listTemp;

	int32 index = 0;

	UPROPERTY(EditDefaultsOnly, Category = "UI", meta = (BindWidget))
	class UImage* System_Save;

	UPROPERTY(meta = (BindWidgetAnim),Transient)
	class UWidgetAnimation* Anim;

	UPROPERTY(meta =(BindWidget))
	class UImage* DeleteMonster;

	UPROPERTY(meta =(BindWidget))
	class UImage* DeleteDungeon;


	UFUNCTION()
	void ChildInit1();

	UFUNCTION()
	void ChildInit2();
};
