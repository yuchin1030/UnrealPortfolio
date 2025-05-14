#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleWidget.generated.h"



UCLASS()
class CHALLENGERS_API UTitleWidget : public UUserWidget
{
	GENERATED_BODY()


	virtual void NativeConstruct() override;


	// ����ϱ� ��ư
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_LoadGame;

	UFUNCTION()
	void OnClickButton_LoadGame();

	UFUNCTION()
	void OnHoveredButton_LoadGame();

	UFUNCTION()
	void OnUnHoveredButton_LoadGame();


	// ���� �����ϱ� ��ư
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_NewGame;

	UFUNCTION()
	void OnClickButton_NewGame();

	UFUNCTION()
	void OnHoveredButton_NewGame();

	UFUNCTION()
	void OnUnHoveredButton_NewGame();



	// ���� ��ư
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Button_Quit;

	UFUNCTION()
	void OnClickButton_Quit();

	UFUNCTION()
	void OnHoveredButton_Quit();

	UFUNCTION()
	void OnUnHoveredButton_Quit();



	// ����ϱ� ����
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image_Line1;
	
	
	// �����ϱ� ����
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image_Line2;


	// ���� ����
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
