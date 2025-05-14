#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/ListView.h>
#include "PlayerCustomizer.generated.h"

UCLASS()
class CHALLENGERS_API UPlayerCustomizer : public UUserWidget
{
	GENERATED_BODY()


public:
	UPROPERTY()
	FString NickName = " ";

	bool bClick = false;

	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UWidgetSwitcher* CharCumaSwitcher;

	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UWidgetSwitcher* ColorSwitcherUI;

	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UImage* Image_10;

	//UPROPERTY(meta = (BindWidget))
	//TObjectPtr<UListView> HairColorListView;
	//UPROPERTY(meta = (BindWidget))
	//TObjectPtr<UListView> ClothesListView; 


	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* HairLeftButton;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* HairRightButton;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* ClothesLeftButton;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* ClothesRightButton;

	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* GlovesLeftButton;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* GlovesRightButton;

	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* BoyButton;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* GirlButton;

	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* HairColorChangeButton;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* ClothesColorChangeButton;

	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* StartButton;

	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UEditableText* InputNickName;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UTextBlock* TextBlock_PlayerName;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* Button_Yes;
	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UButton* Button_No;

	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UUniformGridPanel* hairGridPanel;

	UPROPERTY(EditDefaultsOnly, Category = "Custom", meta = (BindWidget))
	class UUniformGridPanel* ClothesGridPanel;

	UPROPERTY()
	UDataTable* HairColorDataTable;
	UPROPERTY()
	UDataTable* ClothesColorDataTable;



	UPROPERTY(EditDefaultsOnly)
	class ACreatorTestCharacter* CC;

	UPROPERTY(EditDefaultsOnly)
	class UOurGameInstance* OG;


protected:

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:

	const FVector Start = FVector(-190, 10 ,60);
	const FVector End = FVector(-210, 10, 75);
	FTimerHandle alpha;
	float Speed = 2.0f;

	bool bCameraMoving1 = false;
	bool bCameraMoving2 = false;

	bool bIsZoom = false;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UFrontHairColorList> hairColor_bp;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UClothesColorList> clothesColor_bp;

	//머리카락 변경버튼 함수
	UFUNCTION()
	void HairUPBtn();
	UFUNCTION()
	void HairDownBtn();
 
	//얼굴 변경버튼 함수
	UFUNCTION()
	void ClothesUpBtn();
	UFUNCTION()
	void ClothesDownBtn();

	UFUNCTION()
	void GlovesUpBtn();
	UFUNCTION()
	void GlovesDownBtn();

	UFUNCTION()
	void SelectBoy();
	UFUNCTION()
	void SelectGirl();

	UFUNCTION()
	void GameStartBtn();

	UFUNCTION()
	void CharacterCreate();
	UFUNCTION()
	void CharacterCancel();

	UFUNCTION()
	void ClothesChangeColor();
	UFUNCTION()
	void HairChangeColor();

	UFUNCTION()
	void HairColorSelect();
	UFUNCTION()
	void ClothesColorSelect();




	UFUNCTION()
	void MovingCamera();
	UFUNCTION()
	void ReturnCamera();

	bool bCanReturnCamera = false;



};
