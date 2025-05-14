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

	// Panel ����
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UCanvasPanel* CanvasPanel_CC_Select;


	// �� ��ư
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Yes;

	UFUNCTION()
	void OnClickYes();


	
	// �ƴϿ� ��ư
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_No;

	UFUNCTION()
	void OnClickNo();




	// �÷��̾� �г��� ǥ��
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
 	class UTextBlock* TextBlock_PlayerName;

};
