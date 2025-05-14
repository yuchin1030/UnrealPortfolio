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

	// NPC ��Ҹ�
	UFUNCTION()
    void CustomNPCSound();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    USoundBase* NPCSoundPlay;


	// ���� ��ư ���� �ø��� �ִϸ��̼� ����
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim),Transient)
	class UWidgetAnimation* SelectMonsterSetAnim;

	// ���� ��ư ���� �ø��� �ִϸ��̼� ����
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim),Transient)
	class UWidgetAnimation* SelectDungeonSetAnim;


	// Panel ����
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UCanvasPanel* SelectCustomPanel;
	
	// �޹�� �̹��� ����
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* BackGround;


	// �Ϲ� ���� �����Ϸ� ���� ��ư
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_MonsterSetting;


	// ���� �����Ϸ� ���� ��ư
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_DungeonSetting;

	// â �ݱ�
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
