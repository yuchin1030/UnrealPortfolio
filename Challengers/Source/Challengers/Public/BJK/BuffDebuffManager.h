#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BJK/BuffDebuff.h"
#include "BuffDebuffManager.generated.h"


UCLASS()
class CHALLENGERS_API ABuffDebuffManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ABuffDebuffManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	const UDataTable* DT_BuffDeBuff = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/BJK/BluePrints/DT_BuffDeBuff.DT_BuffDeBuff'"));

	class AMainPlayerController* PlayerController;

	UPROPERTY()
	class UOurGameInstance* gi;

	void BuffDebuffStruct();

	UFUNCTION(Server, Reliable)
	void ServerRPC_BuffDebuffStruct();

	UFUNCTION(Server, Reliable)
	void ServerRPC_HiddenBuff();

	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_HiddenBuff();


	// 5초 뒤 무기 변경 불가능하게 하기 위해 생성
	float BlockChange =3.0f;
	bool block = false;

	// 5초 뒤 버프이름 안보이게 하기
	float ShowTime = 5.0f;
	bool HiddenBuffName = false;


	float SwordDamage=0.0f;
	float WandDamage=0.0f;
	float BowDamage=0.0f;


	FAllBuffDebuff BDStruct;

	UPROPERTY(ReplicatedUsing = OnRep_BDApply)
	int32 RandomIndex=0;

	UFUNCTION()
	void OnRep_BDApply();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BuffDebuff")
    UDataTable* BuffDebuffTable;

};
