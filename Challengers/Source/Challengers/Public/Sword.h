// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sword.generated.h"

UCLASS()
class CHALLENGERS_API ASword : public AActor
{
	GENERATED_BODY()
	
public:	
	ASword();

	

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class UOurGameInstance* gi;

	UPROPERTY(EditDefaultsOnly, Category="MySettings")
	class UStaticMeshComponent* swordMeshComp;

	UPROPERTY(EditDefaultsOnly, Category="MySettings")
	class UArrowComponent* traceStart;

	UPROPERTY(EditDefaultsOnly, Category="MySettings")
	class UArrowComponent* traceEnd;

	UPROPERTY(EditDefaultsOnly, Category = "MySettings")
	class UBoxComponent* HitBox;

	UPROPERTY(EditDefaultsOnly, Category="MySettings")
	class ABaseEnemy* enemy;

	UPROPERTY()
	FTimerHandle traceHdl;

	UPROPERTY()
	int32 currentSkillNum;

	UPROPERTY()
	int32 swordBasicAttackCnt = 0;

	UPROPERTY()
	float basicAttackDamagePercent = 0;

	// 스킬계수
	UPROPERTY()
	TArray<float> skillDamagePercents;

	// 무기 공격력
	UPROPERTY(Replicated)
	int32 weaponAttackPower = 30;

	UPROPERTY()
	TArray<AActor*> enemies;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	TArray<USoundBase*> swordHitSound;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class USoundBase* sword1HitSound;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class USoundBase* sword2HitSound;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class USoundBase* sword3HitSound;

	UPROPERTY(EditAnywhere, Category = MySettings)
	class UNiagaraSystem* hitVFX;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageType> damageType;

	UFUNCTION()
	void SwordBasicAttack();

	UFUNCTION()
	void SwordSkill1();

	UFUNCTION()
	void SwordSkill2();

	UFUNCTION()
	void SwordSkill3();

	UFUNCTION()
	void StartSwordTrace(int32 _currentSkillNum);

	UFUNCTION()
	void LoopSwordTrace();

	UFUNCTION()
	void StopSwordTrace();

	UFUNCTION()
	void WeaponHit(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(Server, Reliable)
	void ServerRPC_ApplyDamage(ABaseEnemy* _enemyREF);

	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_ApplyDamage(FVector hitLoc);

	UFUNCTION()
	void CheckBasicAttackCnt(int32 _swordBasicAttackCnt);


	UPROPERTY(EditDefaultsOnly ,Category = "Niagara")
	class UNiagaraComponent* WeaponEffect;

	UFUNCTION()
	void UpgradeSwordEffect(int32 weaponLevel);

	class AChallengersCharacter* CC;


	UPROPERTY(ReplicatedUsing = OnRap_ShowEffect)
	FVector EffectSwordScale = FVector(0, 0, 0);

	UFUNCTION(Server,Reliable)
	void ServerRPC_ShowEffect(int32 NewUpgradeValue);

	UFUNCTION()
	void OnRap_ShowEffect();
	

};
