// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PersonPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CASSTERA_API APersonPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// ������
	APersonPlayerController(const FObjectInitializer & ObjectInitializer);

	FORCEINLINE UClass * GetPlayerPawnClass() {return MyPawnClass;}

	UPROPERTY()
	class UGameTimerWidget* gameTimerwidget;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UGameTimerWidget> WBP_gameTimerWidget;

	UPROPERTY()
	class UMainUI* mainUI;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UMainUI> WBP_MainUI;

	// ä��
	UPROPERTY()
	class UChatWidget* chatUI;

// 	UFUNCTION(Server, Reliable)
// 	void ServerRPC_CreateTimerUI();
// 
// 	
// 	UFUNCTION(NetMulticast, Reliable)
// 	void MultiRPC_CreateTimerUI();
	

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* aPawn) override;
	
	virtual void Tick(float DeltaTime) override;



	UPROPERTY()
	class ACassteraGameState* gs;
	
	// �ùٸ� �� Ŭ���� Ŭ���̾�Ʈ �� ��ȯ
	UFUNCTION(Server, Reliable)
	void ServerRPC_DefinePawnClass();

	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_DefinePawnClass();

	// �� ��Ʈ�ѷ��� ���� ������ �� Ŭ���� ����
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRPC_SetPawn(TSubclassOf<APawn> InPawnClass);

	// ����Ϸ��� ���� �� Ŭ����
	UPROPERTY(Replicated)
	TSubclassOf<APawn> MyPawnClass;

	// ����� ù ��° �� ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category ="MySettings")
	TSubclassOf<APawn> SeakPlayerPawn;

	// ����� �� ��° �� ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category ="MySettings")
	TSubclassOf<APawn> HidePlayerPawn;

	// �������� �� ����
	UPROPERTY()
	int32 rate = 50;


public:
	//���� �÷��̾� �������� �ٲٱ�
	UFUNCTION(Server, Reliable)
	void ServerRPC_ChangeToSpectator(AHidePlayer* hidePlayer, bool isOldPawnDestroy = false);
	UFUNCTION(Client, Reliable)
	void ClientRPC_ChangeToSpectator(AHidePlayer* hidePlayer);

	//���� �÷��̾� �������->���� ������ �ٲٱ�(����)
	UFUNCTION(Server, Reliable)
	void ServerRPC_ChangeToPlayer();

	//�ٲٱ� �����Լ�
	UFUNCTION()
	void ChangeToPlayer();

	UPROPERTY()
	class AHidePlayerCamera* spectator;
	UPROPERTY()
	class ACassTeraCharacter* seekPlayer;
	UPROPERTY()
	class AHidePlayer* origin;

	UPROPERTY()
	class APersonPlayerGameModeBase* gm; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HidePlayer")
	TSubclassOf<class AHidePlayerCamera> watcingCam_bp;
	UPROPERTY()
	class AHidePlayerCamera* watchingCam;

	UPROPERTY()
	int32 _hidePlayerCount;

//	UPROPERTY()
//	class APawn* origin;

	UPROPERTY()
	bool bHidePlayerDie;

};
