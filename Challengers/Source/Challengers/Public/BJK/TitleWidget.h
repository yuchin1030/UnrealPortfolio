#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleWidget.generated.h"



UCLASS()
class CHALLENGERS_API UTitleWidget : public UUserWidget
{
	GENERATED_BODY()


	virtual void NativeConstruct() override;


	// 계속하기 버튼
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_LoadGame;

	UFUNCTION()
	void OnClickButton_LoadGame();

	UFUNCTION()
	void OnHoveredButton_LoadGame();

	UFUNCTION()
	void OnUnHoveredButton_LoadGame();


	// 새로 시작하기 버튼
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_NewGame;

	UFUNCTION()
	void OnClickButton_NewGame();

	UFUNCTION()
	void OnHoveredButton_NewGame();

	UFUNCTION()
	void OnUnHoveredButton_NewGame();



	// 종료 버튼
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Quit;

	UFUNCTION()
	void OnClickButton_Quit();

	UFUNCTION()
	void OnHoveredButton_Quit();

	UFUNCTION()
	void OnUnHoveredButton_Quit();



	// 계속하기 라인
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image_Line1;
	
	
	// 새로하기 라인
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image_Line2;


	// 종료 라인
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image_Line3;

	
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* BackAnim;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* OneAnim;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* TwoAnim;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* ThreeAnim;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* LogoAnim;
	
};
