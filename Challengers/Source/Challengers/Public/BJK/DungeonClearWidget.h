
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

	// Panel ¿¬°á
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UCanvasPanel* CanvasPanel_DungeonClear;


	// º¸»ó¹Þ±â ¹öÆ°
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_GetItem;

	UFUNCTION()
	void OnClickGetItem();


	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim),Transient)
	class UWidgetAnimation* AnimArrow;



	// È¹µæ °ñµå·®
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_GetGold;

	int32 ClearGold;

	// È¹µæ °æÇèÄ¡
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_getEXP;

	int32 ClearEXP;

	UPROPERTY(ReplicatedUsing = OnRep_CostIn)
	int32 Cost=0;

	UFUNCTION()
	void OnRep_CostIn();
};
