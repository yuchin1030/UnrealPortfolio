#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuffDebuff.generated.h"

UCLASS()
class CHALLENGERS_API ABuffDebuff : public AActor
{
	GENERATED_BODY()
	
public:	
	ABuffDebuff();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


};

USTRUCT(BlueprintType)
struct FAllBuffDebuff : public FTableRowBase
{
	GENERATED_BODY()

public:

	FAllBuffDebuff()
		: PlayerSpeed(1.0f)
		, PlayerHelth(1.0f)
		, SwordSkillDamage(1.0f)

		, WandSkillDamage(1.0f)

		, BowSkillDamage(1.0f)
	{}

	// �̵��ӵ� ������
	UPROPERTY(EditAnywhere, Category = "BuffDebuff")
	float PlayerSpeed;

	// ü�� ������
	UPROPERTY(EditAnywhere, Category = "BuffDebuff")
	float PlayerHelth;


	// ��ü(�⺻���ݷ�, ��ų)������ ������
	UPROPERTY(EditAnywhere, Category = "BuffDebuff")
	float AllDamage;





	// Į ��ų ������
	UPROPERTY(EditAnywhere, Category = "BuffDebuff")
	float SwordSkillDamage;

	// ������ ��ų ������
	UPROPERTY(EditAnywhere, Category = "BuffDebuff")
	float WandSkillDamage;

	// Ȱ ��ų ������
	UPROPERTY(EditAnywhere, Category = "BuffDebuff")
	float BowSkillDamage;


	// ��� ȹ�淮
	UPROPERTY(EditAnywhere, Category = "BuffDebuff")
	float GetGold;


	// ����ġ ȹ�淮
	UPROPERTY(EditAnywhere, Category = "BuffDebuff")
	float GetEXP;

};