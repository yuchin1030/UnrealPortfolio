
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DungeonClearWidget.generated.h"


UCLASS()
class CHALLENGERS_API UDungeonClearWidget : public UUserWidget
{
	GENERATED_BODY()
	
	public:

	virtual void NativeConstruct() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY()
	class UOurGameInstance* OG;

	// Panel ����
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UCanvasPanel* CanvasPanel_DungeonClear;


	// ����ޱ� ��ư
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_GetItem;

	UFUNCTION()
	void OnClickGetItem();


	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim),Transient)
	class UWidgetAnimation* AnimArrow;



	// ȹ�� ��差
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_GetGold;

	int32 ClearGold;

	// ȹ�� ����ġ
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_getEXP;

	int32 ClearEXP;

	UPROPERTY(ReplicatedUsing = OnRep_CostIn)
	int32 Cost=0;

	UFUNCTION()
	void OnRep_CostIn();
};
