// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Yohan/SaveDungeonData.h"
#include "CreateRoomWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API UCreateRoomWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	// NPC 목소리
	UFUNCTION()
    void BattleNPCSound();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    USoundBase* NPCSoundPlay;


	bool bClosed;
	UPROPERTY(EditDefaultsOnly, Meta=(BindWidget))
	class UButton* Btn_X;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Btn_Refresh;

	UPROPERTY(EditDefaultsOnly, Meta=(BindWidget))
	class UBorder* CreateMenu;

	UPROPERTY(EditDefaultsOnly, Meta=(BindWidget))
	class UButton* Btn_ShowCreate;

	UPROPERTY(EditDefaultsOnly, Meta=(BindWidget))
	class UButton* Btn_Create;

	UPROPERTY(EditDefaultsOnly, Meta=(BindWidget))
	class UButton* Btn_CreateX;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UScrollBox* RoomList;

	UPROPERTY(EditDefaultsOnly, Meta=(BindWidget))
	class UEditableText* editText_RoomName;

	UPROPERTY(EditDefaultsOnly, Meta=(BindWidget))
	class UScrollBox* scroll_DunList;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim),Transient)
	class UWidgetAnimation* FadeOut;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Failed;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class URoomListItemUI> roomItemUIFactory;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UCreateRoomDungeonListWidget> dunListUI_BP;

	UPROPERTY()
	TArray<FDunInfo> loadDunList;

	UPROPERTY()
	class UOurGameInstance* gi;

	virtual void NativeConstruct() override;

	// 버튼 Allfalse
	UFUNCTION()
	void Allfalse();

	UFUNCTION()
	void OnMyClickCreateRoom();

	UFUNCTION()
	void OnMyClickX();

	UFUNCTION()
	void RefreshRoomList();

	UFUNCTION()
	void OnClickFindRoom();

	UFUNCTION()
	void ShowCreateUI();

	UFUNCTION()
	void HideCreateUI();

	UFUNCTION()
	void AddRoomInfoUI(const struct FSessionInfo& info);

	UFUNCTION(BlueprintCallable)
	void PlayFadeOut(bool bIsSucceed);
};
