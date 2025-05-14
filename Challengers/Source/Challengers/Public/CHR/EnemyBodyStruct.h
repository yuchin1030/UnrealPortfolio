// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBodyStruct.generated.h"

USTRUCT(BlueprintType)
struct FbodySpec : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HP = 0;//소체의 체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsBossType = false;//에너미 타입. true면 보스타입r
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DEF = 0;//기본 방어력
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float speed = 0.0f;//이동 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMesh* shape = nullptr;//소체의 모습
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UAnimInstance> anim = nullptr;//비무장 애니메이션
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float size = 0.0f;//몬스터의 크기. 캡슐의 반지름.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 weightLimit = 0;//장비 무게 제한
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 cost = 0;//소체의 가격
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString name = "";//소체의 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = "true"))
	FString discription = "";//소체의 설명
};

class EnemyBodyStruct
{
public:
	EnemyBodyStruct();
	~EnemyBodyStruct();
};
