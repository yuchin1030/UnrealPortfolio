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
	float battleDist = 0.0f;//�����Ÿ� 100~1800
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float randomArea = 0.0f;//�̵�, ���ݽ� ������ ����. 0 ~ 0.5
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float moveRate = 0.0f;//�̵���. 1ȸ �̵� �� ����ϴ� �ð�. 0 ~ 5��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float playerFindDist = 0.0f;//�νĹ���. 1000 ~ 2000
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float targetChangeRate = 0.0f;//Ÿ�� ���� ����. Ÿ�� ���� Ž�� ��Ÿ��. 1 ~ 10��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float phase2Rate = 0.0f;//2������ ü�� ����. 0.2~0.8
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float phase3Rate = 0.0f;//3������ ü�� ����. 0.1~0.6
};

USTRUCT(BlueprintType)
struct Fspec
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString name = "";//������ �̸�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsBossType = false;//���ʹ� Ÿ��. true�� ����Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 totalHP = 0;//�� HP. ��� ��Ʈ�� HP�� ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 totalAttackPoint = 0;//���� 1,2�� ���ݷ� ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 totalDEF = 0;//���� 1,2�� ���� ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float speed = 0.0f;//�̵� �ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 weightLimit = 0;//��� �߷� �Ѱ�.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 currentWeight = 0;//���� ��� �߷�. �Ѱ谪�� ������ ���� ������ŭ �ӵ��� ������?
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 totalCost = 0;//��� ����� ����
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
	class UCEnemyAnimInst* cAnimInst;//���� �ִ� �ν��Ͻ�

	UPROPERTY()
	class ULEnemyAnimInst* lAnimInst;//���Ÿ� �ִ� �ν��Ͻ�

	UPROPERTY(ReplicatedUsing = OnRep_PhaseCheck)
	int32 currentHP;//���� HP.

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, ReplicatedUsing=OnRep_ChangeBody)
	FName bodyRowName = FName("NB1");//��ü�� RowName

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName weapon1RowName = FName("W1_0");//���1�� RowName

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName weapon2RowName = FName("W2_0");//���2�� RowName

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Replicated)
	FName gearRowName = FName("0");//Ư���ɷ��� RowName
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, ReplicatedUsing = OnRep_MakeWeapon1)
	TSubclassOf<class UAnimInstance> weapon1AnimInst;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, ReplicatedUsing = OnRep_MakeWeapon2)
	TSubclassOf<class UAnimInstance> weapon2AnimInst;

	float orignSpeed = 1.0f;

	FName temp1;
	FName temp2;

	UPROPERTY()
	class ABaseWeapon* weapon1;//������� ���1

	UPROPERTY()
	class ABaseWeapon* weapon2;//������� ���2
	
	UPROPERTY()
	class ABaseGear* gear;//������� Ư���ɷ�

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	struct FAIStat AIData;//AI������ ����ü

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	struct Fspec enemySpec;//��� ��� �ɷ�ġ�� ������ ���� �ɷ�ġ

	EPhaseState enemyPhase = EPhaseState::PHASE1;//ü�¿� ���� ���� ������. �������� �۵�

	UPROPERTY(VisibleAnywhere, Replicated)
	EAttackState AIState = EAttackState::IDLE;//FSM���� ����ϴ� ���� �ൿ����

	UPROPERTY(VisibleAnywhere, Replicated)
	class AChallengersCharacter* playerREF;//Ÿ���õ� �÷��̾�

	float targetDist;//Ÿ�ٰ��� �Ÿ�

	UPROPERTY(Replicated)
	float moveDist;//�̵��� �̵��� ��ġ���� �Ÿ�

	float forwardSpeed;
	float rightSpeed;

	UPROPERTY(ReplicatedUsing = OnRep_MoveEnemy)
	FVector movePlace;//���� �̵��� ��ǥ

	UPROPERTY(Replicated)
	int32 atkAnimSelect = -1;//���� �ִϸ��̼� ���ÿ� ����

	bool bIsMoving = false;//���� �̵������� üũ

	bool bWillChangeWeapon = false;//�̹� �ൿ ���� �� ��� ���� �������� üũ

	UPROPERTY(Replicated)
	bool bIsAttacked = false;//���� �ൿ�� ���ۉ���� üũ

	bool bIsAlreadyDied = false;

	FTimerHandle moveResetTimer;

	UPROPERTY(BlueprintReadWrite, Replicated)
	int32 deathAnimSelect = -1;

	UPROPERTY(ReplicatedUsing = OnRep_SwapWeapon)
	bool bIsMontageSelect;//���� �̵��� ��ǥ

	UPROPERTY(EditDefaultsOnly)
	class UAnimMontage* MonChangeWeaponClose;//���� ���� ��� ���� ��Ÿ��

	UPROPERTY(EditDefaultsOnly)
	class UAnimMontage* MonChangeWeaponLong;//���Ÿ� ���� ��� ���� ��Ÿ��

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAnimMontage* MonGearActive;//Ư���ɷ� �ߵ� ��Ÿ��

	UFUNCTION(BlueprintCallable)
	void MakeBody();//bodyRowName�� �̿��Ͽ� ��ü�� ����

	UFUNCTION(BlueprintCallable)
	void ChangeBody(FName newBody);//��ü�� �ִ� ��Ȳ���� �ٸ� ��ü�� ����.

	UFUNCTION(Server, Reliable)
	void ServerRPC_ChangeBody(FName newBody);

	UFUNCTION()
	void OnRep_ChangeBody();

	UFUNCTION(BlueprintCallable)
	void MakeWeapon1(FName newWeapon);//weapon1RowName�� �̿��Ͽ� ���1 ����

	UFUNCTION(Server, Reliable)
	void ServerRPC_MakeWeapon1(FName newWeapon);

	UFUNCTION()
	void OnRep_MakeWeapon1();

	UFUNCTION(BlueprintCallable)
	void ChangeWeapon1(FName newWeapon);//���1�� �ִ� ��Ȳ���� �ٸ� ���1�� ����.

	UFUNCTION(BlueprintCallable)
	void MakeWeapon2(FName newWeapon);//weapon2RowName�� �̿��Ͽ� ���2 ����

	UFUNCTION(Server, Reliable)
	void ServerRPC_MakeWeapon2(FName newWeapon);

	UFUNCTION()
	void OnRep_MakeWeapon2();

	UFUNCTION(BlueprintCallable)
	void ChangeWeapon2(FName newWeapon);//���2�� �ִ� ��Ȳ���� �ٸ� ���2�� ����.

	UFUNCTION(BlueprintCallable)
	void MakeGear(FName newGear);//gearRowName�� �̿��Ͽ� Ư���ɷ� ����

	UFUNCTION(BlueprintCallable)
	void ChangeGear(FName newGear);//Ư���ɷ��� �ִ� ��Ȳ���� �ٸ� Ư���ɷ����� ����.

	void CheakWeightLimit();

	UFUNCTION(BlueprintCallable)
	void SwapWeapon();//������ 1���� 2�� �Ѿ �� ��� ���� �Լ�

	UFUNCTION(Server, Reliable)
	void ServerRPC_SwapWeapon();

	UFUNCTION()
	void OnRep_SwapWeapon();

	UFUNCTION(BlueprintCallable)
	void LoadData(FName _bodyRowName, FName _weapon1RowName, FName _weapon2RowName, FName _gearRowName, FAIStat _AIData);//Change �ø�� ����ִ�.

	UFUNCTION()
	void FindPlayer();//���� �ð����� �÷��̾ ��� ã�� ���� ����� �÷��̾ Ÿ������ ��´�.

	bool CheakBlock(AChallengersCharacter* tempPlayer);

	//void AnimCheak();

	//UFUNCTION(Server, Reliable)
	//void ServerRPC_AnimCheak();

	UFUNCTION(Server, Reliable)
	void ServerRPC_MoveToBattleDist();//���� �� �̵���ġ ���

	UFUNCTION(Server, Reliable)
	void ServerRPC_MoveToAtkDist();//���� �� �̵���ġ ���

	UFUNCTION()
	void OnRep_MoveEnemy();//�̵���ġ ��� �� ���� �̵�

	FORCEINLINE void ChangeATKState(){ AIState = EAttackState::ATTACK; };

	UFUNCTION(Server, Reliable)
	void ServerRPC_Attack();//���� ���·� �Ѿ���� ���� �ִϸ��̼��� �����Ѵ�.

	void UseGear();//Ư���ɷ� ���

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;//�⺻ �ǰ��Լ�

	UFUNCTION(Server, Reliable)
	void ServerRPC_dmgCal(float damage, AActor* DamageCauser);//ü�� ���Ҹ� ����ϰ� ��� ���ʹ̿� �Ѹ���.

	void Died(bool bDiedInBattle);//ü�� 0 = ����

	UFUNCTION(Server, Reliable)
	void ServerRPC_Died(bool bDiedInBattle);

	UFUNCTION()
	void OnRep_PhaseCheck();//ü�� ���ҿ� ���� ������ ��ȭ�� �ǽ�

	//�ִϸ��̼� ��Ƽ���̵�//

	void Anim_detach_Weapon();//��� ���� �� ���1 �����

	void Anim_attach_Weapon();//��� ���� �� ���1, ���2 ���� Ȧ��/�տ� ���̱�

	void Anim_CloseAtkStart();//����� ������ ���� ON

	void Anim_CloseAtkEnd();//����� ������ ���� OFF

	void Anim_AttackEnd();//���� �ִϸ��̼� ����. ���°� READY�� ����ȴ�.

	void Anim_FireMagic();//���Ÿ� ����� ����

	void Anim_ActiveGear();//Ư���ɷ� �ߵ� ����
};
