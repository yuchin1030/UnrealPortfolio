// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GearStruct.generated.h"

USTRUCT(BlueprintType)
struct FgearSpec : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsBuffType = false;//true로 자기강화형, false로 발사형
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float useCooldown = 0.0f;//공격 재사용 대기시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float activeTime = 0.0f;//발동 후 지속 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABaseGear> shape = nullptr;//기어 자체의 블루프린트
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AActor> shootActor = nullptr;//발사형 발동시 발사되는 발사체
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraSystem* gearActiveEffect = nullptr;//발동이펙트
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMaterialInstance* overlayMat = nullptr;//지속시간동안 보이는 오버레이
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 weight = 0;//무기 무게
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 cost = 0;//무기의 가격
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString name = "";//소체의 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = "true"))
	FString discription = "";//소체의 설명
};

class CHALLENGERS_API GearStruct
{
public:
	GearStruct();
	~GearStruct();
};
