// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoadWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API ULoadWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:

	virtual void NativeConstruct() override;




	// 캐릭터 삭제 버튼
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Destroy;

	UFUNCTION()
	void OnClickDestroy();



	// 나가기 버튼
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Quit;

	UFUNCTION()
	void OnClickQuit();



	// 계속하기 버튼
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Load;

	UFUNCTION()
	void OnClickLoad();

};
