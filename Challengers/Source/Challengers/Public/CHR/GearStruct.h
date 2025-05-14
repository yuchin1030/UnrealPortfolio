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
	bool bIsBuffType = false;//true�� �ڱⰭȭ��, false�� �߻���
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float useCooldown = 0.0f;//���� ���� ���ð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float activeTime = 0.0f;//�ߵ� �� ���� �ð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABaseGear> shape = nullptr;//��� ��ü�� �������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AActor> shootActor = nullptr;//�߻��� �ߵ��� �߻�Ǵ� �߻�ü
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraSystem* gearActiveEffect = nullptr;//�ߵ�����Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMaterialInstance* overlayMat = nullptr;//���ӽð����� ���̴� ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 weight = 0;//���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 cost = 0;//������ ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString name = "";//��ü�� �̸�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = "true"))
	FString discription = "";//��ü�� ����
};

class CHALLENGERS_API GearStruct
{
public:
	GearStruct();
	~GearStruct();
};
