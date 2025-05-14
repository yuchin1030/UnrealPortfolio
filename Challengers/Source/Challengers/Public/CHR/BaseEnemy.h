// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CHR/EnemyAIController.h"
#include "BaseEnemy.generated.h"

UENUM(BlueprintType)
enum class EPhaseState : uint8 {
	PHASE1,
	PHASE2,
	PHASE3,
};

USTRUCT(BlueprintType)
struct FAIStat
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float battleDist = 0.0f;//전투거리 100~1800
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float randomArea = 0.0f;//이동, 공격시 랜덤값 비율. 0 ~ 0.5
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float moveRate = 0.0f;//이동빈도. 1회 이동 후 대기하는 시간. 0 ~ 5초
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float playerFindDist = 0.0f;//인식범위. 1000 ~ 2000
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float targetChangeRate = 0.0f;//타겟 변경 비율. 타겟 변경 탐색 쿨타임. 1 ~ 10초
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float phase2Rate = 0.0f;//2페이즈 체력 비율. 0.2~0.8
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float phase3Rate = 0.0f;//3페이즈 체력 비율. 0.1~0.6
};

USTRUCT(BlueprintType)
struct Fspec
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString name = "";//몬스터의 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsBossType = false;//에너미 타입. true면 보스타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 totalHP = 0;//총 HP. 모든 파트의 HP의 합
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 totalAttackPoint = 0;//무기 1,2의 공격력 합
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 totalDEF = 0;//무기 1,2의 방어력 합
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float speed = 0.0f;//이동 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 weightLimit = 0;//장비 중량 한계.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 currentWeight = 0;//현재 장비 중량. 한계값을 넘으면 넘은 비율만큼 속도를 줄이자?
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 totalCost = 0;//모든 장비의 가격
};

UCLASS()
class ABaseEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class UOurGameInstance* gi;

	UPROPERTY()
	class AEnemyAIController* AC;

	class UNavigationSystemV1* NavSys;

	UPROPERTY()
	class UCEnemyAnimInst* cAnimInst;//근접 애님 인스턴스

	UPROPERTY()
	class ULEnemyAnimInst* lAnimInst;//원거리 애님 인스턴스

	UPROPERTY(ReplicatedUsing = OnRep_PhaseCheck)
	int32 currentHP;//현재 HP.

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, ReplicatedUsing=OnRep_ChangeBody)
	FName bodyRowName = FName("NB1");//몸체의 RowName

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName weapon1RowName = FName("W1_0");//장비1의 RowName

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName weapon2RowName = FName("W2_0");//장비2의 RowName

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Replicated)
	FName gearRowName = FName("0");//특수능력의 RowName
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, ReplicatedUsing = OnRep_MakeWeapon1)
	TSubclassOf<class UAnimInstance> weapon1AnimInst;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, ReplicatedUsing = OnRep_MakeWeapon2)
	TSubclassOf<class UAnimInstance> weapon2AnimInst;

	float orignSpeed = 1.0f;

	FName temp1;
	FName temp2;

	UPROPERTY()
	class ABaseWeapon* weapon1;//장비중인 장비1

	UPROPERTY()
	class ABaseWeapon* weapon2;//장비중인 장비2
	
	UPROPERTY()
	class ABaseGear* gear;//장비중인 특수능력

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	struct FAIStat AIData;//AI데이터 구조체

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	struct Fspec enemySpec;//모든 장비 능력치를 총합한 최종 능력치

	EPhaseState enemyPhase = EPhaseState::PHASE1;//체력에 따른 현재 페이즈. 보스형만 작동

	UPROPERTY(VisibleAnywhere, Replicated)
	EAttackState AIState = EAttackState::IDLE;//FSM에서 사용하는 현재 행동상태

	UPROPERTY(VisibleAnywhere, Replicated)
	class AChallengersCharacter* playerREF;//타겟팅된 플레이어

	float targetDist;//타겟과의 거리

	UPROPERTY(Replicated)
	float moveDist;//이동시 이동할 위치까지 거리

	float forwardSpeed;
	float rightSpeed;

	UPROPERTY(ReplicatedUsing = OnRep_MoveEnemy)
	FVector movePlace;//다음 이동할 좌표

	UPROPERTY(Replicated)
	int32 atkAnimSelect = -1;//공격 애니메이션 선택용 변수

	bool bIsMoving = false;//현재 이동중인지 체크

	bool bWillChangeWeapon = false;//이번 행동 종료 후 장비 변경 예정인지 체크

	UPROPERTY(Replicated)
	bool bIsAttacked = false;//공격 행동이 시작됬는지 체크

	bool bIsAlreadyDied = false;

	FTimerHandle moveResetTimer;

	UPROPERTY(BlueprintReadWrite, Replicated)
	int32 deathAnimSelect = -1;

	UPROPERTY(ReplicatedUsing = OnRep_SwapWeapon)
	bool bIsMontageSelect;//다음 이동할 좌표

	UPROPERTY(EditDefaultsOnly)
	class UAnimMontage* MonChangeWeaponClose;//근접 무기 장비 변경 몽타주

	UPROPERTY(EditDefaultsOnly)
	class UAnimMontage* MonChangeWeaponLong;//원거리 무기 장비 변경 몽타주

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAnimMontage* MonGearActive;//특수능력 발동 몽타주

	UFUNCTION(BlueprintCallable)
	void MakeBody();//bodyRowName을 이용하여 몸체를 생성

	UFUNCTION(BlueprintCallable)
	void ChangeBody(FName newBody);//몸체가 있는 상황에서 다른 몸체로 변경.

	UFUNCTION(Server, Reliable)
	void ServerRPC_ChangeBody(FName newBody);

	UFUNCTION()
	void OnRep_ChangeBody();

	UFUNCTION(BlueprintCallable)
	void MakeWeapon1(FName newWeapon);//weapon1RowName을 이용하여 장비1 생성

	UFUNCTION(Server, Reliable)
	void ServerRPC_MakeWeapon1(FName newWeapon);

	UFUNCTION()
	void OnRep_MakeWeapon1();

	UFUNCTION(BlueprintCallable)
	void ChangeWeapon1(FName newWeapon);//장비1이 있는 상황에서 다른 장비1로 변경.

	UFUNCTION(BlueprintCallable)
	void MakeWeapon2(FName newWeapon);//weapon2RowName을 이용하여 장비2 생성

	UFUNCTION(Server, Reliable)
	void ServerRPC_MakeWeapon2(FName newWeapon);

	UFUNCTION()
	void OnRep_MakeWeapon2();

	UFUNCTION(BlueprintCallable)
	void ChangeWeapon2(FName newWeapon);//장비2가 있는 상황에서 다른 장비2로 변경.

	UFUNCTION(BlueprintCallable)
	void MakeGear(FName newGear);//gearRowName을 이용하여 특수능력 생성

	UFUNCTION(BlueprintCallable)
	void ChangeGear(FName newGear);//특수능력이 있는 상황에서 다른 특수능력으로 변경.

	void CheakWeightLimit();

	UFUNCTION(BlueprintCallable)
	void SwapWeapon();//페이즈 1에서 2로 넘어갈 때 장비 변경 함수

	UFUNCTION(Server, Reliable)
	void ServerRPC_SwapWeapon();

	UFUNCTION()
	void OnRep_SwapWeapon();

	UFUNCTION(BlueprintCallable)
	void LoadData(FName _bodyRowName, FName _weapon1RowName, FName _weapon2RowName, FName _gearRowName, FAIStat _AIData);//Change 시리즈가 들어있다.

	UFUNCTION()
	void FindPlayer();//일정 시간마다 플레이어를 모두 찾고 가장 가까운 플레이어를 타겟으로 삼는다.

	bool CheakBlock(AChallengersCharacter* tempPlayer);

	//void AnimCheak();

	//UFUNCTION(Server, Reliable)
	//void ServerRPC_AnimCheak();

	UFUNCTION(Server, Reliable)
	void ServerRPC_MoveToBattleDist();//공격 전 이동위치 계산

	UFUNCTION(Server, Reliable)
	void ServerRPC_MoveToAtkDist();//공격 시 이동위치 계산

	UFUNCTION()
	void OnRep_MoveEnemy();//이동위치 계산 후 실제 이동

	FORCEINLINE void ChangeATKState(){ AIState = EAttackState::ATTACK; };

	UFUNCTION(Server, Reliable)
	void ServerRPC_Attack();//공격 상태로 넘어갔을때 공격 애니메이션을 결정한다.

	void UseGear();//특수능력 사용

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;//기본 피격함수

	UFUNCTION(Server, Reliable)
	void ServerRPC_dmgCal(float damage, AActor* DamageCauser);//체력 감소를 계산하고 모든 에너미에 뿌린다.

	void Died(bool bDiedInBattle);//체력 0 = 죽음

	UFUNCTION(Server, Reliable)
	void ServerRPC_Died(bool bDiedInBattle);

	UFUNCTION()
	void OnRep_PhaseCheck();//체력 감소에 따른 페이즈 변화를 실시

	//애니메이션 노티파이들//

	void Anim_detach_Weapon();//장비 변경 중 장비1 때어내기

	void Anim_attach_Weapon();//장비 변경 중 장비1, 장비2 각각 홀더/손에 붙이기

	void Anim_CloseAtkStart();//장비의 데미지 판정 ON

	void Anim_CloseAtkEnd();//장비의 데미지 판정 OFF

	void Anim_AttackEnd();//공격 애니메이션 종료. 상태가 READY로 변경된다.

	void Anim_FireMagic();//원거리 무기로 공격

	void Anim_ActiveGear();//특수능력 발동 시점
};
