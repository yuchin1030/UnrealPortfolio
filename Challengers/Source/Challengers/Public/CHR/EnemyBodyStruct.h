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
	int32 HP = 0;//��ü�� ü��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsBossType = false;//���ʹ� Ÿ��. true�� ����Ÿ��r
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DEF = 0;//�⺻ ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float speed = 0.0f;//�̵� �ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMesh* shape = nullptr;//��ü�� ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UAnimInstance> anim = nullptr;//���� �ִϸ��̼�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float size = 0.0f;//������ ũ��. ĸ���� ������.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 weightLimit = 0;//��� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 cost = 0;//��ü�� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString name = "";//��ü�� �̸�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = "true"))
	FString discription = "";//��ü�� ����
};

class EnemyBodyStruct
{
public:
	EnemyBodyStruct();
	~EnemyBodyStruct();
};
