#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SelectCCWidget.generated.h"

/**
 * 
 */
UCLASS()
class USelectCCWidget : public UUserWidget
{
	GENERATED_BODY()

	public:

	virtual void NativeConstruct() override;

	// Panel 연결
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UCanvasPanel* CanvasPanel_CC_Select;


	// 예 버튼
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Yes;

	UFUNCTION()
	void OnClickYes();


	
	// 아니오 버튼
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_No;

	UFUNCTION()
	void OnClickNo();




	// 플레이어 닉네임 표시
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
 	class UTextBlock* TextBlock_PlayerName;

};
