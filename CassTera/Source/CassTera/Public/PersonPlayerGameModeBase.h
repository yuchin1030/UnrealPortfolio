// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PersonPlayerGameModeBase.generated.h"

/**
 * 
 */
UCLASS(minimalapi)
class APersonPlayerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	APersonPlayerGameModeBase();
	//virtual UClass* GetDefaultPawnClassForController_Implementation(class AController* InController) override;

	virtual void BeginPlay() override;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void Tick( float DeltaSeconds ) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	

	// ����� ù ��° �� ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category ="MySettings")
	TSubclassOf<APawn> SeakPlayerPawn;

	// ����� �� ��° �� ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category ="MySettings")
	TSubclassOf<APawn> HidePlayerPawn;

	// ���� ���� ����
	UPROPERTY()
	int32 playerRate = 50;

	// �ִ� ���� ����
	int32 maxSeaker = 1;

	// ���� ���� ����
	int32 curSeaker = 0;

	// ���� �޽� ��ġ
	UPROPERTY(EditDefaultsOnly, Category = "MySettings")
	TSubclassOf<class AObjects> Objects_BP;
	UPROPERTY(Replicated)
	class AObjects* Objects;


	UPROPERTY()
	TArray<class AHidePlayer*> hidePlayers;

	UPROPERTY()
	class AHidePlayer* hidePlayer;


	UPROPERTY()
	class ACassteraGameState* gs;

	UPROPERTY()
	class UResultWidget* resultWidget;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UResultWidget> wbp_resultWidget;


	UFUNCTION()
	void DecreaseHidePlayerCount();

	bool bBurningSound;
};

