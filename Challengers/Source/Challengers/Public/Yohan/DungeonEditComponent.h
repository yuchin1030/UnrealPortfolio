// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Engine/DirectionalLight.h>
#include "DungeonEditComponent.generated.h"

DECLARE_DELEGATE(FLoadingEnd);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CHALLENGERS_API UDungeonEditComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UDungeonEditComponent();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	FLoadingEnd loadingEndDelegate;

	UPROPERTY()
	FVector levLocation;

	UPROPERTY()
	ASpectatorPawn* newPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TPS")
    TSubclassOf<class ABaseEnemy> SelectedEnemy_BP;

	UPROPERTY(BlueprintReadWrite)
	class ABaseEnemy* SelectedEnemy;

	UPROPERTY(BlueprintReadWrite)
	class ABaseEnemy* _selectedEnemy;

	// 던전 에디터 UI 생성
	UPROPERTY(EditDefaultsOnly, Category  = "UI")
	TSubclassOf<class UDungeonEditWidget> dungeonEditUI_BP;

	class UDungeonEditWidget* dungeonEditUI;

	UPROPERTY()
	class ADungeonEditCharacter* dc;

	UPROPERTY()
	class ADungeonEditCharacterController* pc;

	UPROPERTY(BlueprintReadWrite)
	bool bIsObjectFixed = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bIsMoved = false;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UDE_EnemyControlWidget> controllUI_BP;

	UPROPERTY(BlueprintReadWrite)
	class UDE_EnemyControlWidget* controllUI;

	UPROPERTY()
	FVector enemyLocation;

	UPROPERTY()
	class ADungeonEditGameModeBase* gm;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInstance* greenMI;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInstance* redMI;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInstance* yellowMI;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> disAbleArea_BP;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> enAbleArea_BP;

	UPROPERTY(BlueprintReadWrite)
	bool bisControlUI;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ULoadingWidget> loadingUI_BP;

	UPROPERTY()
	class ULoadingWidget* loadingUI;

	UPROPERTY()
	class ABaseEnemy* _enemy;

	UFUNCTION(BlueprintCallable)
	void OpenMap(FName MapName);

	UFUNCTION(BlueprintCallable)
	void CloseMap(FName MapName);

// 	UFUNCTION(BlueprintCallable)
//     void SpawnSelectedObject();

	UFUNCTION()
	void OnMouseClick(FName _body, FName _weapon1, FName _weapon2, FName _gear, FAIStat _AIData);

	UFUNCTION(BlueprintCallable)
	void UpdateObjectPosition();

	UFUNCTION(BlueprintCallable)
	bool GetMouseCursorHitResult(FHitResult& HitResult);

	UFUNCTION(BlueprintCallable)
	bool IsEnemyOnNavMesh(FVector Location);

	UFUNCTION(BlueprintCallable)
	void SetEnemyLocation();
			
	UFUNCTION(BlueprintCallable)
	void SetEnemyMove();

	UFUNCTION(BlueprintCallable)
	void ShowControlWidget();

	UFUNCTION(BlueprintCallable)
	void HideControlWidget();

	UFUNCTION()
	void SetEnemyDelete();

	UFUNCTION()
	void ShowArea();

	UFUNCTION()
	void HideArea();

	UFUNCTION()
	void ActiveOverlay();
	
private:
};
