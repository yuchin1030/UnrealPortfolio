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
	bool bIsHoldTwoHand = false;//weapon1/2 ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 damage = 0;//���� ���ݷ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DEF = 0;//���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float attackRange = 0.0f;//���� �����Ÿ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float attackCooldown = 0.0f;//���� ���� ���ð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABaseWeapon> shape = nullptr;//��ü�� ���. ���� �������Ʈ ��ü
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UAnimInstance> anim = nullptr;//���� �ִϸ��̼�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> attackSelector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 weight = 0;//���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 cost = 0;//������ ����
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
