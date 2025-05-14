// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SelectCustomWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API USelectCustomWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	class AMainPlayerController* pc;
	class AChallengersCharacter* Player;
	class ACustomNPC* customNPC;

	bool bClosed;

	// NPC 목소리
	UFUNCTION()
    void CustomNPCSound();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    USoundBase* NPCSoundPlay;


	// 몬스터 버튼 위에 올릴시 애니메이션 실행
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim),Transient)
	class UWidgetAnimation* SelectMonsterSetAnim;

	// 던전 버튼 위에 올릴시 애니메이션 실행
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim),Transient)
	class UWidgetAnimation* SelectDungeonSetAnim;


	// Panel 연결
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UCanvasPanel* SelectCustomPanel;
	
	// 뒷배경 이미지 연결
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* BackGround;


	// 일반 몬스터 세팅하러 가는 버튼
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_MonsterSetting;


	// 던전 세팅하러 가는 버튼
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_DungeonSetting;

	// 창 닫기
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Close;

	UFUNCTION()
	void OnHoverMonsterSetting();

	UFUNCTION()
	void OnHoverDungeonSetting();

	UFUNCTION()
	void OnUnHoveredMonsterSetting();

	UFUNCTION()
	void OnUnHoveredDungeonSetting();


	UFUNCTION()
	void OnClickClose();

};
