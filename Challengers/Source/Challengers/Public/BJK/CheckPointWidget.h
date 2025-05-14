// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CheckPointWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API UCheckPointWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;


	class AOurGameModeBase* OGM = nullptr;
	class ACustomModeBase* CGM = nullptr;
	class ADungeonEditGameModeBase* DGM = nullptr;
	class UOurGameInstance* GI = nullptr;
	class AOurGameStateBase* OGS = nullptr;

	bool Test;

	UPROPERTY()
	class UCheckPointWidget* ShowMapNameWidget;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image_A;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image_B;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image_C;


	// 마을로 돌아 올 시에 나오는 문구 애니메이션
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* CheckAnim;

	// 몬스터 커스터 마이징에 입장 시에 나오는 문구 애니메이션
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* TestRoomAnim;

	// 멀티방에 입장 시에 나오는 문구 애니메이션
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* MultiANim;


	UFUNCTION()
	void ShowMapname();
};
