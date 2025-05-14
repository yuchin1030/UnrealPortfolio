// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponStruct.generated.h"

USTRUCT(BlueprintType)
struct FweaponSpec : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsHoldTwoHand = false;//weapon1/2 판정
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 damage = 0;//무기 공격력
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DEF = 0;//무기 방어력
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float attackRange = 0.0f;//공격 사정거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float attackCooldown = 0.0f;//공격 재사용 대기시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABaseWeapon> shape = nullptr;//소체의 모습. 무기 블루프린트 자체
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UAnimInstance> anim = nullptr;//무장 애니메이션
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> attackSelector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 weight = 0;//무기 무게
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 cost = 0;//무기의 가격
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString name = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = "true"))
	FString description = "";
};

class CHALLENGERS_API WeaponStruct
{
public:
	WeaponStruct();
	~WeaponStruct();
};
