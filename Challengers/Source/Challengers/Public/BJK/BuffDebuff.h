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

	// 이동속도 증가율
	UPROPERTY(EditAnywhere, Category = "BuffDebuff")
	float PlayerSpeed;

	// 체력 증가율
	UPROPERTY(EditAnywhere, Category = "BuffDebuff")
	float PlayerHelth;


	// 전체(기본공격력, 스킬)데미지 증가율
	UPROPERTY(EditAnywhere, Category = "BuffDebuff")
	float AllDamage;





	// 칼 스킬 데미지
	UPROPERTY(EditAnywhere, Category = "BuffDebuff")
	float SwordSkillDamage;

	// 지팡이 스킬 데미지
	UPROPERTY(EditAnywhere, Category = "BuffDebuff")
	float WandSkillDamage;

	// 활 스킬 데미지
	UPROPERTY(EditAnywhere, Category = "BuffDebuff")
	float BowSkillDamage;


	// 골드 획득량
	UPROPERTY(EditAnywhere, Category = "BuffDebuff")
	float GetGold;


	// 경험치 획득량
	UPROPERTY(EditAnywhere, Category = "BuffDebuff")
	float GetEXP;

};