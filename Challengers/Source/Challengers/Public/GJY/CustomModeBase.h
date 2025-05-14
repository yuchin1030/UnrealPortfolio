#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CustomModeBase.generated.h"

DECLARE_DELEGATE(FLoadingEnd);

/**
 * 
 */
UCLASS()
class CHALLENGERS_API ACustomModeBase : public AGameModeBase
{
	GENERATED_BODY()
	

	UPROPERTY(EditAnywhere, Category = "Customs")
	TSubclassOf<class UPlayerCustomizer> CustomWidget;

	UPROPERTY(EditAnywhere, Category = "Custom")
	TSubclassOf<class UEnemyCustomizer> EnemyWidget;
	
	UPROPERTY(EditAnywhere, Category = "Custom")
	TSubclassOf<class UAISettingCustomizer> AIWidget;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class ULoadingWidget> loadingUI_BP;

	UPROPERTY()
	class ULoadingWidget* loadingUI;



public:
	ACustomModeBase();

	FLoadingEnd loadingEndDelegate;

	UPROPERTY()
	class UPlayerCustomizer* Custom_Inst;

	UPROPERTY()
	class UEnemyCustomizer* Enemy_Inst;

	UPROPERTY()
	class UAISettingCustomizer* AI_Inst;

	class ABaseEnemy* CustomEnemy;

	bool bIsRotate = false;

	bool bIsBack;

	FTimerHandle rotateTimer;

	UFUNCTION()
	void ShowCharacterCustomizer();
	UFUNCTION()
	void ShowEnemyCustomizer();
	UFUNCTION()
	void ShowAISettingUI();

	void RotateEnemy(class ABaseEnemy* RotateEnemy, bool _bIsBack);

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;




};
