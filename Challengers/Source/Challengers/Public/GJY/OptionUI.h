// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionUI.generated.h"

/**
 * 
 */
UCLASS()
class CHALLENGERS_API UOptionUI : public UUserWidget
{
	GENERATED_BODY()
	


protected:
	virtual void NativeConstruct() override;



public:


	UPROPERTY(EditDefaultsOnly, Category = "Opt", meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher_Notices;

	UPROPERTY(EditDefaultsOnly, Category = "Opt", meta = (BindWidget))
	class UButton* TitleButton;

	UPROPERTY(EditDefaultsOnly, Category = "Opt", meta = (BindWidget))
	class UButton* GameQuitButton;


	UPROPERTY(EditDefaultsOnly, Category = "Opt", meta = (BindWidget))
	class USlider* VolumeSlider;


	 float DefaultVolumeSize = 1.0f;
	 float SetVolumeSize = 0;

	class ABGMActor* VolumeActor;



	UPROPERTY(EditDefaultsOnly, Category = "Opt", meta = (BindWidget))
	class UButton* OKbutton;

	UPROPERTY(EditDefaultsOnly, Category = "Opt", meta = (BindWidget))
	class UButton* NoButton;

	UPROPERTY(EditDefaultsOnly, Category = "Opt", meta = (BindWidget))
	class UButton* TitleYes;

	UPROPERTY(EditDefaultsOnly, Category = "Opt", meta = (BindWidget))
	class UButton* TitleNo;


	UPROPERTY(EditDefaultsOnly, Category = "Opt", meta = (BindWidget))
	class UButton* QuitYes;

	UPROPERTY(EditDefaultsOnly, Category = "Opt", meta = (BindWidget))
	class UButton* QuitNo;



	UFUNCTION()
	void ClickTitleButton();

	UFUNCTION()
	void GoToTitleMap();
	UFUNCTION()
	void ClickNoGameTitleMap();

	UFUNCTION()
	void ClickGameQuitButton();



	UFUNCTION()
	void VolumeSave();
	
	UFUNCTION()
	void VolumeCancel();




	UFUNCTION()
	void FinalQuit();

	UFUNCTION()
	void NoQuit();

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_close;

	UFUNCTION()
	void CloseOptionUI();



};
