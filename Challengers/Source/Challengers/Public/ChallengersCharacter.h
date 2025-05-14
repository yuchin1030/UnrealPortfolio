#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "BJK/BuffDebuffManager.h"
#include "ChallengersCharacter.generated.h"

UENUM (BlueprintType)
enum class EWeaponType : uint8
{
	SWORD,
	WAND,
	GUN,
};


class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AChallengersCharacter : public ACharacter
{
	GENERATED_BODY()


	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Attack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_ChangeWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Skill1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Skill2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Skill3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_BowSkill3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Interact;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_ShowCursor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_SkillMenu;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Dash;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Heal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_RightMouse;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Chat;
	
	// F1키를 누르면 튜토리얼 UI 창이 나온다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_Tutorial;

	// F1키를 누르면 튜토리얼 UI 창이 나온다.
	UFUNCTION()
	void OpenTutorial_UI();

	UPROPERTY(EditDefaultsOnly)
	class UNiagaraComponent* TeleportVFX;

	UPROPERTY(EditDefaultsOnly)
	class UNiagaraComponent* DashVFX;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	class USkeletalMeshComponent* Part1;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	class USkeletalMeshComponent* Part2;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	class USkeletalMeshComponent* Part3;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	class USkeletalMeshComponent* Part4;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	class USkeletalMeshComponent* Part5;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	class USkeletalMeshComponent* Part6;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	class USkeletalMeshComponent* Part7;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	class USkeletalMeshComponent* Part8;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	class USkeletalMeshComponent* Part9;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	class USkeletalMeshComponent* Part10;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	class USkeletalMeshComponent* Part11;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	class USkeletalMeshComponent* Part12;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	class USkeletalMeshComponent* Part13;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	class USkeletalMeshComponent* Part14;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	class USkeletalMeshComponent* Part15;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	class USkeletalMeshComponent* Part16;

	UPROPERTY(EditDefaultsOnly, Category = "Custom")
	class USkeletalMeshComponent* Part17;

public:
	
	

	AChallengersCharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MySettings, ReplicatedUsing = OnRepWeaponInitVisible)
	TArray<UChildActorComponent*> currentWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MySettings)
	class UChildActorComponent* swordComp;

	UPROPERTY()
	class ASword* sword;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MySettings)
	class UChildActorComponent* wandComp;

	UPROPERTY()
	class AWand* wand;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MySettings)
	class UChildActorComponent* gunComp;

	UPROPERTY()
	class ABow* gun;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MySettings)
	class USkillSystemComponent* skillSystemComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MySettings, Replicated)
	int32 currentWeaponNum = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MySettings)
	int32 prevWeaponNum = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MySettings, Replicated)
	int32 swordBasicAttackCnt = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MySettings, Replicated)
	int32 wandBasicAttackCnt = 0;

	UPROPERTY()
	int32 currentSkillNum = 0;

	class UAnimMontage* basicMontageToPlay;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	TArray<UAnimMontage*> swordBasicAttackMontages;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UAnimMontage* SwordSkill1Montage;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UAnimMontage* SwordSkill1_Combo_Montage;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UAnimMontage* SwordSkill2Montage;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UAnimMontage* SwordSkill2_Combo_Montage;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UAnimMontage* SwordSkill3Montage;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UAnimMontage* SwordSkill3_Combo_Montage;
	
	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	TArray<UAnimMontage*> wandBasicAttackMontages;

	/*UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UAnimMontage* WandBasicMontage;*/

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UAnimMontage* WandSkill1Montage;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UAnimMontage* WandSkill1_Complete_Montage;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UAnimMontage* WandSkill2_Start_Montage;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UAnimMontage* WandSkill2_Loop_Montage;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UAnimMontage* WandSkill2_End_Montage;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UAnimMontage* WandSkill1_Combo_Montage;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UAnimMontage* WandSkill2_Combo_Montage;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UAnimMontage* WandSkill3_Start_Montage;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UAnimMontage* WandSkill3_Loop_Montage;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UAnimMontage* WandSkill3_End_Montage;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UAnimMontage* BowBasicMontage;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UAnimMontage* BowSkill1_Start_Montage;
	
	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UAnimMontage* BowSkill1_Loop_Montage;
		
	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UAnimMontage* BowSkill1_End_Montage;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UAnimMontage* BowSkill2_Start_Montage;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UAnimMontage* BowSkill2_Loop_Montage;
		
	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UAnimMontage* BowSkill2_End_Montage;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UAnimMontage* BowSkill3_Start_Montage;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UAnimMontage* BowSkill3_Loop_Montage;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UAnimMontage* BowSkill3_End_Montage;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UAnimMontage* Die_montage;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UAnimMontage* DashMontage;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UAnimMontage* TeleportMontage;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UMainPlayerWidget* mainUI;

	UPROPERTY()
	class AGun* gunBasicActor;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	TSubclassOf<class AGun> gunBasicActor_bp;

	UPROPERTY()
	class AWandBasic* wandBasicActor;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	TSubclassOf<class AWandBasic> wandBasicActor_bp;

	UPROPERTY()
	class AWandSkill1Actor_Combo* wandSkill1_Combo_var;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	TSubclassOf<class AWandSkill1Actor_Combo> wandSkill1_Combo_bp;

	UPROPERTY()
	class AWandSkill1Actor_Completed* wandSkill1_Complete_var;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	TSubclassOf<class AWandSkill1Actor_Completed> wandSkill1_Complete_bp;

	UPROPERTY()
	class AWandSkill1SpawnActor* wandSkill1Actor;

	UPROPERTY(EditDefaultsOnly, Category = "MySettings")
	TSubclassOf<class AWandSkill1SpawnActor> wandSkill1Actor_bp;
	/*UPROPERTY()
	class AWandSkill2Actor* wandSkill2Actor_var;*/

	/*UPROPERTY(EditDefaultsOnly, Category = MySettings)
	TSubclassOf<class AWandSkill2Actor> wandSkill2_bp;*/

	UPROPERTY()
	class AWandSkill2Actor_Combo* wandSkill2_Combo_var;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	TSubclassOf<class AWandSkill2Actor_Combo> wandSkill2_Combo_bp;

	UPROPERTY()
	class AWandSkill3Actor* wandSkill3Actor_var;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	TSubclassOf<class AWandSkill3Actor> wandSkill3_bp;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	TSubclassOf<class ABowSkill1Actor> arrow_bp;

	UPROPERTY()
	class ABowSkill2Actor* bowSkill2Actor;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	TSubclassOf<class ABowSkill2Actor> bowSkill2Actor_bp;

	UPROPERTY()
	class ABowSkill3Actor* bowSkill3Actor;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	TSubclassOf<class ABowSkill3Actor> bowSkill3Actor_bp;

	UPROPERTY()
	class ABowSkill3DecalActor* bowSkill3DecalActor;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	TSubclassOf<class ABowSkill3DecalActor> bowSkill3DecalActor_bp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MySettings, Replicated)
	float arrow2Gage = 0;

	UPROPERTY()
	UDataTable* DT_SkillStruct;

	UPROPERTY(VisibleAnywhere, Replicated)
	FVector finalAimLoc;

	bool bShowCursor = true;
	bool bBasicPlaying;

	UPROPERTY(Replicated)
	bool bDashing;

	// 딜레이 시간이 모두 지나면 대시가 되도록
	bool bDashDelay;

	// 대시 딜레이
	UPROPERTY()
	float DashDelay=0.3f;

	// 검스킬1 움직임 관련 불 변수
	UPROPERTY(Replicated)
	bool bSword1CanMove;

	bool bRightMouse;

	// WandSkill3 시작했는지 여부
	UPROPERTY(Replicated)
	bool bIsWandSkill3Started;
	bool bWandSkill3Pressing;

	bool bWandComboPlaying;

	UPROPERTY(Replicated)
	bool bSkillUsing;

	// bSkillUsing 과 따로 관리하는 이유: bSkillUsing으로 다른스킬사용불가를 제어해주면 검1번스킬 쓸때 못 움직임
	UPROPERTY(Replicated)
	bool bSwordSkill1Using;

	bool bSingleMap;

	UPROPERTY(Replicated)
	bool bSpawnWand3;

	UPROPERTY(Replicated)
	bool bBowSkill2;

	UPROPERTY(Replicated)
	bool bComboUsing;

	// 쿨타임 불 변수들
	UPROPERTY(Replicated)
	bool bSword1;

	UPROPERTY(Replicated)
	bool bSword2;

	UPROPERTY(Replicated)
	bool bSword3;

	UPROPERTY(Replicated)
	bool bWand1;

	UPROPERTY(Replicated)
	bool bWand2;

	UPROPERTY(Replicated)
	bool bWand3;

	UPROPERTY(Replicated)
	bool bBow1;
	
	UPROPERTY(Replicated)
	bool bBow2;

	UPROPERTY(Replicated)
	bool bBow3;

	// 스킬별 쿨타임 시간
	float sword1Time = 0;
	float sword2Time = 0;
	float sword3Time = 0;
	float wand1Time = 0;
	float wand2Time = 0;
	float wand3Time = 0;
	float bow1Time = 0;
	float bow2Time = 0;
	float bow3Time = 0;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MySettings)
	bool bCanSwordBasicAttack = true;

	bool bCanWandBasicAttack = true;

	FTimerHandle attackDelayHdl;

	
	UPROPERTY()
	int32 cnt = 0;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UClass* ABP_Sword_Single;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UClass* ABP_Sword_Multi;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UClass* ABP_Wand;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class UClass* ABP_Bow;

	UFUNCTION()
	void InvisibleDash();

	UFUNCTION()
	void SetAnimBlueprint(UClass* abp);

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	int32 arrow1PoolSize = 10;

	UPROPERTY(EditAnywhere, Category = MySettings)
	TArray<class ABowSkill1Actor*> arrow1Pool;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	int32 potionCnt = 5;

	UFUNCTION()
	void SetArrow1Pool(class ABowSkill1Actor* arrow1);

	UFUNCTION(Server, Reliable)
	void ServerRPC_SetArrow1Pool(class ABowSkill1Actor* _arrow1);

	UFUNCTION(Server, Reliable)
	void ServerRPC_CoolTime(int32 _index, float _coolTime);

	UFUNCTION(Client, Reliable)
	void ClientRPC_CoolTime(int32 index_, float coolTime_);


	////////////////// 사운드 ////////////////////
	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class USoundBase* swordAttackSound1;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class USoundBase* swordAttackSound2;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class USoundBase* swordAttackSound3;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class USoundBase* bowBasicSound;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class USoundBase* bowSkill1Sound;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class USoundBase* bowSkill2Sound;

	// 무기 변경하면 들리는 소리
	UFUNCTION()
	void ChangeWeaponSound();

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class USoundBase* ChangeWeapon_Sword;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class USoundBase* ChangeWeapon_Wand;

	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	class USoundBase* ChangeWeapon_Bow;

	//UPROPERTY()
	//UDataTable* DT_PresetSample;
	
	//UFUNCTION()
	//void OnRep_bBowSkill2();

	UFUNCTION(Server, Reliable)
	void ServerRPC_SetbBowSkill2();

	UFUNCTION()
	void CheckSkillName();
	
	UFUNCTION(Server, Reliable)
	void ServerRPC_InitWeaponVisibility();

	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_InitWeaponVisibility();

	UFUNCTION(Server, Reliable)
	void ServerRPC_Attack(FVector _wandBasicLoc, FRotator _controlRot, FRotator _newConRot, AChallengersCharacter* _CC);

	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_Attack(UAnimMontage* _montage);

	UFUNCTION()
	void Skill1();

	UFUNCTION(Server, Reliable)
	void ServerRPC_Skill1(FVector _curPlayerForward, FVector _curLoc, AChallengersCharacter* _cc);
	
	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_Skill1(int32 _currentWeaponNum);

	UFUNCTION()
	void Skill1_Completed();

	UFUNCTION(Server, Reliable)
	void ServerRPC_Skill1_Completed(int32 _currentWeaponNum, AChallengersCharacter* _this);

	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_Skill1_Completed(int32 currentWeaponNum_);

	UFUNCTION()
	void Skill2();

	UFUNCTION(Server, Reliable)
	void ServerRPC_Skill2(AChallengersCharacter* _cc);
	
	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_Skill2(int32 _currentWeaponNum);

	UFUNCTION()
	void Skill2_Completed();

	UFUNCTION(Server, Reliable)
	void ServerRPC_Skill2_Completed(FVector _spawnLoc, FRotator _spawnRot, class AChallengersCharacter* _this);

	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_Skill2_Completed();

	UFUNCTION()
	void Skill3();

	UFUNCTION(Server, Reliable)
	void ServerRPC_Skill3(class AChallengersCharacter* _player);

	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_Skill3(int32 _currentWeaponNum);

	UFUNCTION()
	void Skill3_Completed();

	UFUNCTION(Server, Reliable)
	void ServerRPC_Skill3_Completed(int32 _currentWeaponNum, AChallengersCharacter* _player);

	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_Skill3_Completed(int32 currentWeaponNum_);

	UFUNCTION()
	void Skill1_Triggered();

	UFUNCTION(Server, Reliable)
	void ServerRPC_BowSkill1_Triggered(AChallengersCharacter* _this);

	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_BowSkill1_Triggered();

	UFUNCTION(Server, Reliable)
	void ServerRPC_WandSkill2_Triggered();

	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_WandSkill2_Triggered();

	UFUNCTION()
	void Skill2_Triggered();

	UFUNCTION(Server, Reliable)
	void ServerRPC_BowSkill2_Triggered();

	
	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_BowSkill2_Triggered();

	UFUNCTION()
	void Skill3_Triggered();

	UFUNCTION(Server, Reliable)
	void ServerRPC_BowSkill3_Triggered(FVector _finalAimLoc);	//

	
	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_BowSkill3_Triggered();

	UFUNCTION()
	void ShowMouseCursor();

	UFUNCTION()
	void ShowSkillMenu();

	UFUNCTION()
	void Dash();
	
	UFUNCTION()
	void Dash_Triggered();

	UFUNCTION(Server, Reliable)
	void ServerRPC_Dash_Triggered();
	
	UFUNCTION()
	void Dash_Completed();

	UFUNCTION()
	void Teleport();

	UFUNCTION(Server, Reliable)
	void ServerRPC_Dash();
	
	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_Dash();

	UFUNCTION(Server, Reliable)
	void ServerRPC_Dash_Completed();

	UFUNCTION()
	void Heal();
	
	UFUNCTION()
	void ComboAttack();

	UFUNCTION(Server, Reliable)
	void ServerRPC_ComboAttack(FVector _spawnLoc, int32 _inputKey, AChallengersCharacter* _player);
	
	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_ComboAttack(int32 _skillNum);

	UPROPERTY()
	int32 skillNum = 1;

	UFUNCTION(BlueprintCallable)
	void WandSkill3_Ready();

	UFUNCTION(Server, Reliable)
	void ServerRPC_WandSkill3_Ready(FVector _start, FVector _end, AChallengersCharacter* _playerChar, FRotator _newRot);

	UPROPERTY()
	FRotator newRot;

	//UFUNCTION(Client, Reliable)
	//void ClientRPC_WandSkill3_Ready(bool bSpawnWand3_);

	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_WandSkill3_Ready();

	UFUNCTION(BlueprintCallable)
	void SpawnArrowBasic();

	UFUNCTION(Server, Reliable)
	void ServerRPC_SpawnArrowBasic(FVector _spawnLoc, FRotator _spawnRot, class AChallengersCharacter* _this);

	UFUNCTION(BlueprintCallable)
	void SpawnWand3();

	UFUNCTION(Server, Reliable)
	void ServerRPC_SpawnWand3();

	UFUNCTION(BlueprintCallable)
	void SpawnArrow1();

	UFUNCTION(Server, Reliable)
	void ServerRPC_SpawnArrow1(FVector _spawnLoc, FRotator _spawnRot);

	UFUNCTION(Server, Reliable)
	void ServerRPC_DecreaseMP(int32 _UsedMP);

	UFUNCTION(Client, Reliable)
	void ClientRPC_DecreaseMP(int32 _MP);

	UFUNCTION(Server, Reliable)
	void ServerRPC_IncreaseMP(int32 _UsedMP);

	UFUNCTION(Client, Reliable)
	void ClientRPC_IncreaseMP(int32 _MP);

	UFUNCTION(BlueprintCallable)
	void PlayMyMontage(UAnimMontage* montage);

	UFUNCTION()
	void OnSwordBsMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
	void OnWandBsMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(Server, Reliable)
	void ServerRPC_DecreaseHP(float _Damage);

	UFUNCTION(Client, Reliable)
	void ClientRPC_DecreaseHP(int32 _HP);

	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_DecreaseHP();

	UFUNCTION(Server, Reliable)
	void ServerRPC_ChangeWeapon(int32 _prevWeaponNum, int32 _currentWeaponNum, AChallengersCharacter* player);
	
	UFUNCTION(Client, Reliable)
	void ClientRPC_ChangeWeapon(int32 currentWeaponNum_);

	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_ChangeWeapon(int32 _prevWeaponNum_, int32 _currentWeaponNum_);

	// 무기 교체를 막는 버프를 적용시키기 위해 만든 변수
	bool BlockChange;

	class AMainPlayerController* pc;



	//virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// 커스텀 NPC에게 UI창을 최대 1개만 띄우게 하기위해 사용되는 변수
	bool bShowSelectCustomNPC = true;
	// 전투출정 NPC에게 UI창을 최대 1개만 띄우게 하기위해 사용되는 변수
	bool bShowBattleNPC = true;
	// 무기강화 NPC에게 UI창을 최대 1개만 띄우게 하기위해 사용되는 변수
	bool bShowWeaponUpgradeNPC = true;
	// K키를 눌렀을 때 UI창을 최대 1개만 띄우게 하기위해 사용되는 변수
	bool bShowSkillSet = true;
	// F1키를 눌렀을 때 UI창을 최대 1개만 띄우게 하기위해 사용되는 변수
	bool bShowTutorial = true;

	// 테스트룸에서 UI창을 최대 1개만 띄우게 하기위해 사용되는 변수
	bool bShowAISetting = true;
	bool bShowEnemySetting = true;
	bool bShowSaveWidget = true;
	bool bShowLoadWidget = true;

	// 무기 활성화 시 K키를 막기 위해 만듦 
	bool InputKeyButton_K;

	void CanWalk();


protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			
	// 공격
	void Attack(const FInputActionValue& Value);

	// 무기 바꾸기
	void ChangeWeapon(const FInputActionValue& Value);

	void Interact(const FInputActionValue& Value);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	virtual void Tick(float DeltaTime) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	UPROPERTY(EditDefaultsOnly, Category = MySettings)
	TSubclassOf<AActor> startLoc_BP;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ACreatorTestCharacter* CT;

UPROPERTY()
class UOurGameInstance* OG;


UPROPERTY()
UDataTable* BodyDataTable;

UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRap_SetNickName)
FString playerName = "Nickname";

// 데미지 계수(비율)
UPROPERTY()
float damageRatio = 1;

// 플레이어 돈
UPROPERTY()
int32 playerGold = 100000000;

UPROPERTY(BlueprintReadWrite, Category = MySettings)
int32 HP = 1000;

UPROPERTY(BlueprintReadWrite, Replicated)
int32 MP = 1000;

UPROPERTY(VisibleAnywhere, Replicated)
TArray<int32> skillPointsArr;

UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MySettings)
int32 playerLevel = 1;

UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MySettings)
int32 maxPlayerLevel = 40;

UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MySettings)
int32 playerCurrentExp = 950;

UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MySettings)
int32 playerMaxExp = 1000;

UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MySettings)
int32 enemyCost = 2000;

UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MySettings)
int32 plusCost = 100;

// 무기 레벨 및 공격력
UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MySettings)
TArray<int32> weaponLevel;

UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MySettings)
TArray<int32> currentWeaponStat;

UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MySettings)
TArray<int32> nextWeaponStat;

UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MySettings)
TArray<int32> upgWeaponNeedGold;

UPROPERTY()
UDataTable* HairColorDataTable;

UPROPERTY()
UDataTable* ClothesDataTable;

UPROPERTY()
UDataTable* SkinDataTable;

UPROPERTY(ReplicatedUsing = Onrep_LoadPlayers)
bool bBoy;

UPROPERTY(ReplicatedUsing = Onrep_LoadPlayers)
TArray<FName> FinalMeshArr;

UPROPERTY(ReplicatedUsing = Onrep_LoadPlayers)
int ClothesColorNum;

UPROPERTY(ReplicatedUsing = Onrep_LoadPlayers)
int HairColorNum;

UPROPERTY(ReplicatedUsing = Onrep_LoadPlayers)
bool bGlove;



UFUNCTION()
void Onrep_LoadPlayers();

UFUNCTION()
void LoadPlayer();

UFUNCTION(Server, Reliable)
void ServerRPC_LoadPlayer(bool _bBoy, const TArray<FName>& _FinalMeshArr, const FString& _playerName, int _ClothesColorNum, int _HairColorNum, bool _bGlove, class AChallengersCharacter* _player);

UPROPERTY(ReplicatedUsing = Onrep_LoadPlayers)
class AChallengersCharacter* _player_;

UFUNCTION()
void OnRepWeaponInitVisible();

UFUNCTION()
void SetPlayerExpAndLevel();

UFUNCTION(Server, Reliable)
void ServerRPC_SetPlayerExpAndLevel();

UFUNCTION()
void SetEnemyCost();

UFUNCTION(Server, Reliable)
void ServerRPC_SetEnemyCost();

UFUNCTION()
void SetTotalSkillPoints();

UFUNCTION(Server, Reliable)
void ServerRPC_SetTotalSkillPoints();

UFUNCTION()
void UpgradeWeapon();

UFUNCTION()
void ServerRPC_UpgradeWeapon();

int32 canUseSkillPoint = 30;

UFUNCTION()
void LoadSkillPoints();

UFUNCTION(Server, Reliable)
void ServerRPC_LoadSkillPoints(const TArray<int32>& _skillPointsArr, int32 _canUseSkillPoint);

UFUNCTION(Client, Reliable)
void ClientRPC_LoadSkillPoints(const TArray<int32>& skillPointsArr_, int32 canUseSkillPoint_);

UFUNCTION()
void LoadPlayerInfo();

UFUNCTION(Server, Reliable) 
void ServerRPC_LoadPlayerInfo(const FString& _playerName, int32 _playerLevel, int32 _playerGold, int32 _playerCurrentExp, int32 _playerMaxExp, int32 _enemyCost, const TArray<int32>& _weaponLevel, const TArray<int32>& _currentWeaponStat, const TArray<int32>& _nextWeaponStat, const TArray<int32>& _upgWeaponNeedGold);

UFUNCTION(Server, Reliable) 

void ServerRPC_SetSkillPointsDmgPercent(int32 index);

//환록 추가
UPROPERTY(Replicated)
int32 currentBowSkillNum = -1;

UFUNCTION()
void Anim_AtkEnd();
 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
UInputAction* IA_OptionMenu;

UFUNCTION()
void ShowOptionMenu();

bool bOption = false;



//=============================================================
//채팅
	bool bchatEnabled = false;

	UFUNCTION(Server, Reliable)
	void ServerRPC_SendMsg(const FString& msg);
	
	UFUNCTION(NetMulticast, Reliable)
	void MultiRPC_SendMsg(const FString& msg);

	UFUNCTION()
	void Chat();

//=============================================닉네임
	UPROPERTY(EditDefaultsOnly, Category = "NickName")
	class UWidgetComponent* NameComp;

	UPROPERTY()
	class UCharacterName* NameUI;

	UFUNCTION(Server, Reliable)
	void ServerRPC_SetNickName();

	UFUNCTION()
	void OnRap_SetNickName();

	UFUNCTION(Server, Reliable)
	void ServerRPC_ShowEffect();
};

