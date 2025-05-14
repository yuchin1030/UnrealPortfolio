// Copyright Epic Games, Inc. All Rights Reserved.

#include "ChallengersCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/StaticMeshComponent.h"
#include "TestPreset.h"
#include "Engine/DataTable.h"
#include "Kismet/DataTableFunctionLibrary.h"
#include "Sword.h"
#include "MainPlayerController.h"
#include "SelectCustomWidget.h"
#include "Wand.h"
#include "Gun.h"
#include "SkillSystemComponent.h"
#include "BJK/BattleNPCWidget.h"
#include "Animation/AnimMontage.h"
#include "BJK/MainPlayerWidget.h"
#include "BJK/UpgradeWeaponNPCWidget.h"
#include "Yuchin/WandSkill2Actor.h"
#include "Yuchin/WandSkill3Actor.h"
#include "Yuchin/Arrow.h"
#include "Yuchin/Arrow2.h"
#include "Kismet/KismetMathLibrary.h"
#include "SkillStruct.h"
#include "GJY/CustomModeBase.h"
#include "OurGameInstance.h"
#include "GJY/SkeletalMeshStructure.h"
#include "Yohan/DungeonEditComponent.h"
#include "Kismet/GameplayStatics.h"
#include "WandSkill1Actor_Completed.h"
#include "Yuchin/WandSkill1Actor_Combo.h"
#include "Yuchin/WandSkill2Actor_Combo.h"
#include "Yuchin/WandBasic.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Yuchin/PlayerAnimInstance.h"
#include "Yuchin/BowSkill2Actor.h"
#include "Components/DecalComponent.h"
#include "Yuchin/BowSkill3DecalActor.h"
#include "Yuchin/BowSkill3Actor.h"
#include "Net/UnrealNetwork.h"
#include "BJK/SkillSettingWidget.h"
#include "Animation/AnimBlueprint.h"
#include "CHR/CreateRoomWidget.h"
#include "BJK/BuffDebuffManager.h"
#include <../../../../../../../Source/Runtime/CoreUObject/Public/Templates/SubclassOf.h>
#include "Yuchin/BowSkill1Actor.h"
#include "Yohan/OurGameStateBase.h"
#include "Yuchin/WandSkill1SpawnActor.h"
#include "Kismet/GameplayStatics.h"
#include "GJY/MaterialStruct.h" 
#include "GJY/OptionUI.h"
#include "CHR/TestRoomGameMode.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/EditableText.h>
#include <../../../../../../../Source/Runtime/Slate/Public/Framework/Application/SlateApplication.h>
#include <../../../../../../../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraComponent.h>
#include "GJY/CharacterName.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/WidgetComponent.h>
#include "Bow.h"
#include <../../../../../../../Source/Runtime/Engine/Public/EngineUtils.h>

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AChallengersCharacter



AChallengersCharacter::AChallengersCharacter()
{
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	TeleportVFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("TeleportVFX"));
	TeleportVFX->SetupAttachment(GetMesh());
	TeleportVFX->SetRelativeLocation(FVector(0, 0, 110));
	TeleportVFX->SetRelativeScale3D(FVector(2.5));
	TeleportVFX->SetVisibility(false);

	DashVFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("DashVFX"));
	DashVFX->SetupAttachment(GetMesh());
	DashVFX->SetRelativeLocation(FVector(0, -40, 40.184996));
	DashVFX->SetRelativeLocation(FVector(0, 0, -90));
	TeleportVFX->SetRelativeScale3D(FVector(0.6));
	DashVFX->SetVisibility(false);

	Part1 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Part1"));
	Part1->SetupAttachment(GetMesh());

	Part2 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Part2"));
	Part2->SetupAttachment(GetMesh());

	Part3 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Part3"));
	Part3->SetupAttachment(GetMesh());

	Part4 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Part4"));
	Part4->SetupAttachment(GetMesh());

	Part5 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Part5"));
	Part5->SetupAttachment(GetMesh());

	Part6 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Part6"));
	Part6->SetupAttachment(GetMesh());

	Part7 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Part7"));
	Part7->SetupAttachment(GetMesh());

	Part8 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Part8"));
	Part8->SetupAttachment(GetMesh());

	Part9 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Part9"));
	Part9->SetupAttachment(GetMesh());

	Part10 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Part10"));
	Part10->SetupAttachment(GetMesh());

	Part11 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Part11"));
	Part11->SetupAttachment(GetMesh());

	Part12 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Part12"));
	Part12->SetupAttachment(GetMesh());

	Part13 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Part13"));
	Part13->SetupAttachment(GetMesh());

	Part14 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Part14"));
	Part14->SetupAttachment(GetMesh());

	Part15 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Part15"));
	Part15->SetupAttachment(GetMesh());

	Part16 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Part16"));
	Part16->SetupAttachment(GetMesh());

	Part17 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Part17"));
	Part17->SetupAttachment(GetMesh());

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	swordComp = CreateDefaultSubobject<UChildActorComponent>(TEXT("swordComp"));
	swordComp->SetupAttachment(GetMesh());

	wandComp = CreateDefaultSubobject<UChildActorComponent>(TEXT("wandComp"));
	wandComp->SetupAttachment(GetMesh(), TEXT("wand"));

	gunComp = CreateDefaultSubobject<UChildActorComponent>(TEXT("gunComp"));
	gunComp->SetupAttachment(GetMesh(), TEXT("gun"));

	skillSystemComp = CreateDefaultSubobject<USkillSystemComponent>(TEXT("skillSystemComp"));

//==================================================================================================================
	
 	NameComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("NickName"));
 	NameComp -> SetupAttachment(RootComponent);
 	NameComp->SetRelativeLocation(FVector(0,0,100));
}

void AChallengersCharacter::BeginPlay()
{
	Super::BeginPlay();

	pc = Cast<AMainPlayerController>(Controller);

	OG = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());

	sword = Cast<ASword>(swordComp->GetChildActor());
	wand = Cast<AWand>(wandComp->GetChildActor());
	gun = Cast<ABow>(gunComp->GetChildActor());
 
	/*weaponLevel.Init(1, 3);
	currentWeaponStat.Init(30, 3);
	nextWeaponStat.Init(round(30 + pow(sqrt(2), weaponLevel[0])), 3);
	upgWeaponNeedGold.Init(100, 3);*/


	
	/////////////////////////// �ؿ� //////////////////////////
	//nextWeaponStat.Init(round(30 + pow(sqrt(2), weaponLevel[0])), 3);
	
	if (IsLocallyControlled())
	{
		LoadPlayer();

	}

	
	/////////////////////////////////////////////////////////////////////
	

	

	UE_LOG(LogTemp, Warning, TEXT("GetCurrentLevel : %s"), *UGameplayStatics::GetCurrentLevelName(GetWorld()));

	// �̱۸�, ��Ƽ���϶� sword Idle �ִϸ��̼� �ٸ�
	if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == "SingleMap")
	{

		if (ABP_Sword_Single)
		{
			SetAnimBlueprint(ABP_Sword_Single);
			swordComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "WeaponBack");
			bSingleMap = true;
			InputKeyButton_K=false;
		}
	}
	else
	{

		if (ABP_Sword_Multi)
		{
			SetAnimBlueprint(ABP_Sword_Multi);
			swordComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "sword");
			InputKeyButton_K =true;
		}
	}
	
	DT_SkillStruct = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/Yuchin/Skills/DT_SkillsInfo.DT_SkillsInfo'"));

	ServerRPC_InitWeaponVisibility();

	//skillSystemComp->LoadPreset();

	if (pc) {
		pc->CreateMainPlayerWidget();
	}

	// ȭ�� ��ų1 Object Pooling
	for (int32 i = 0; i < arrow1PoolSize; i++)
	{
		FActorSpawnParameters params;

		ABowSkill1Actor* arrow1 = GetWorld()->SpawnActor<ABowSkill1Actor>(arrow_bp, FVector(0,0, -70000), FRotator(0), params);

		arrow1->ArrowActivate(false);

		arrow1Pool.Add(arrow1);

		arrow1->PlayerInit(this);
	}

	// ���� �⺻ ���� ����ȭ
	FActorSpawnParameters params;
	/*wandBasicActor = GetWorld()->SpawnActor<AWandBasic>(wandBasicActor_bp, FVector(0), FRotator(0), params);
	wandBasicActor->WandBasicActivate(false);*/

	// ���� 3 ����ȭ
	wandSkill3Actor_var = GetWorld()->SpawnActor<AWandSkill3Actor>(wandSkill3_bp, FVector(0), FRotator::ZeroRotator, params);
	wandSkill3Actor_var->WandSkill3Activate(false);

	auto* controller = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());

	if (controller)
	{
		if (controller->IsLocalController())
		{
			if (controller->mainplayerWidget)
			{
				controller->mainplayerWidget->EXP_Update(this);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerExp No Controller!!!!!!!!!!"));
	}



	// ����ġ ���� �� ������ �׽�Ʈ
// 	AOurGameStateBase* gs = Cast<AOurGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
// 	gs->_bDungeonFinished = true;
 	//SetPlayerExpAndLevel();
}

void AChallengersCharacter::Tick(float DeltaTime)
{
	if (bDashDelay)
	{
		DashDelay -= DeltaTime;
		if (DashDelay <= 0)
		{
			bDashDelay = false;
			DashDelay = 0.3;
		}
	}
	
	// �� ��ų1 ��Ÿ��
	if (bSword1)
	{
		sword1Time += DeltaTime;

		ServerRPC_CoolTime(0, sword1Time);

		if (sword1Time >= OG->DT_SkillInfo->FindRow<FSkillsInfo>(FName("Sword1"), "")->CoolTime)
		{
			bSword1 = false;
			
			sword1Time = 0;
		}
	}

	
	// �� ��ų2 ��Ÿ��
	if (bSword2)
	{
		sword2Time += DeltaTime;

		ServerRPC_CoolTime(1, sword2Time);

		if (sword2Time >= OG->DT_SkillInfo->FindRow<FSkillsInfo>(FName("Sword2"), "")->CoolTime)
		{
			bSword2 = false;
			
			sword2Time = 0;
		}
	}

	// �� ��ų3 ��Ÿ��
	if (bSword3)
	{
		sword3Time += DeltaTime;

		ServerRPC_CoolTime(2, sword3Time);

		if (sword3Time >= OG->DT_SkillInfo->FindRow<FSkillsInfo>(FName("Sword3"), "")->CoolTime)
		{
			bSword3 = false;

			sword3Time = 0;
		}
	}

	// ���� ��ų1 ��Ÿ��
	if (bWand1)
	{
		wand1Time += DeltaTime;

		ServerRPC_CoolTime(3, wand1Time);

		if (wand1Time >= OG->DT_SkillInfo->FindRow<FSkillsInfo>(FName("Magic1"), "")->CoolTime)
		{
			bWand1 = false;

			wand1Time = 0;
		}
	}

	// ���� ��ų2 ��Ÿ��
	if (bWand2)
	{
		wand2Time += DeltaTime;

		ServerRPC_CoolTime(4, wand2Time);

		if (wand2Time >= OG->DT_SkillInfo->FindRow<FSkillsInfo>(FName("Magic2"), "")->CoolTime)
		{
			bWand2 = false;

			wand2Time = 0;
		}
	}

	// ���� ��ų3 ��Ÿ��
	if (bWand3)
	{
		wand3Time += DeltaTime;

		ServerRPC_CoolTime(5, wand3Time);

		if (wand3Time >= OG->DT_SkillInfo->FindRow<FSkillsInfo>(FName("Magic3"), "")->CoolTime)
		{
			bWand3 = false;

			wand3Time = 0;
		}
	}

	// �� ��ų1 ��Ÿ��
	if (bBow1)
	{
		bow1Time += DeltaTime;

		ServerRPC_CoolTime(6, bow1Time);

		if (bow1Time >= OG->DT_SkillInfo->FindRow<FSkillsInfo>(FName("Gun1"), "")->CoolTime)
		{
			bBow1 = false;

			bow1Time = 0;
		}
	}

	// �� ��ų2 ��Ÿ��
	if (bBow2)
	{
		bow2Time += DeltaTime;
	
		ServerRPC_CoolTime(7, bow2Time);

		if (bow2Time >= OG->DT_SkillInfo->FindRow<FSkillsInfo>(FName("Gun2"), "")->CoolTime)
		{
			bBow2 = false;

			bow2Time = 0;
		}
	}

	// �� ��ų3 ��Ÿ��
	if (bBow3)
	{
		bow3Time += DeltaTime;

		ServerRPC_CoolTime(8, bow3Time);

		if (bow3Time >= OG->DT_SkillInfo->FindRow<FSkillsInfo>(FName("Gun3"), "")->CoolTime)
		{
			bBow3 = false;

			bow3Time = 0;
		}
	}
	//UE_LOG(LogTemp, Warning, TEXT("bow3Time : %f"), bow3Time);

	if (bBowSkill2)
	{
		UE_LOG(LogTemp, Warning, TEXT("bBowSkill2 : %d"), bBowSkill2);
		
		if (arrow2Gage >= 0 && arrow2Gage < 100)
		{
			arrow2Gage++;
		}
		
		UE_LOG(LogTemp, Warning, TEXT("%f"), arrow2Gage);
	}
	//OnRep_bBowSkill2();


}

void AChallengersCharacter::ServerRPC_CoolTime_Implementation(int32 _index, float _coolTime)
{
	ClientRPC_CoolTime(_index, _coolTime);
}

void AChallengersCharacter::ClientRPC_CoolTime_Implementation(int32 index_, float coolTime_)
{
	if (pc && pc->IsLocalController())
	{
		pc->mainplayerWidget->CoolTime_Skill(index_, coolTime_);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CoolTime :: No PC"));
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AChallengersCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<AMainPlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AChallengersCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AChallengersCharacter::Look);

		EnhancedInputComponent->BindAction(IA_Attack, ETriggerEvent::Started, this, &AChallengersCharacter::Attack);

		EnhancedInputComponent->BindAction(IA_ChangeWeapon, ETriggerEvent::Started, this, &AChallengersCharacter::ChangeWeapon);

		EnhancedInputComponent->BindAction(IA_Interact, ETriggerEvent::Started, this, &AChallengersCharacter::Interact);

		EnhancedInputComponent->BindAction(IA_ShowCursor, ETriggerEvent::Started, this, &AChallengersCharacter::ShowMouseCursor);

		EnhancedInputComponent->BindAction(IA_SkillMenu, ETriggerEvent::Started, this, &AChallengersCharacter::ShowSkillMenu);

		EnhancedInputComponent->BindAction(IA_OptionMenu, ETriggerEvent::Started, this, &AChallengersCharacter::ShowOptionMenu);


		EnhancedInputComponent->BindAction(IA_Skill1, ETriggerEvent::Started, this, &AChallengersCharacter::Skill1);
		EnhancedInputComponent->BindAction(IA_Skill1, ETriggerEvent::Triggered, this, &AChallengersCharacter::Skill1_Triggered);
		EnhancedInputComponent->BindAction(IA_Skill1, ETriggerEvent::Completed, this, &AChallengersCharacter::Skill1_Completed);

		EnhancedInputComponent->BindAction(IA_Skill2, ETriggerEvent::Started, this, &AChallengersCharacter::Skill2);
		EnhancedInputComponent->BindAction(IA_Skill2, ETriggerEvent::Triggered, this, &AChallengersCharacter::Skill2_Triggered);
		EnhancedInputComponent->BindAction(IA_Skill2, ETriggerEvent::Completed, this, &AChallengersCharacter::Skill2_Completed);

		EnhancedInputComponent->BindAction(IA_Skill3, ETriggerEvent::Started, this, &AChallengersCharacter::Skill3);
		EnhancedInputComponent->BindAction(IA_Skill3, ETriggerEvent::Triggered, this, &AChallengersCharacter::Skill3_Triggered);
		EnhancedInputComponent->BindAction(IA_Skill3, ETriggerEvent::Completed, this, &AChallengersCharacter::Skill3_Completed);


		EnhancedInputComponent->BindAction(IA_Dash, ETriggerEvent::Started, this, &AChallengersCharacter::Dash);
		EnhancedInputComponent->BindAction(IA_Dash, ETriggerEvent::Triggered, this, &AChallengersCharacter::Dash_Triggered);
		EnhancedInputComponent->BindAction(IA_Dash, ETriggerEvent::Completed, this, &AChallengersCharacter::Dash_Completed);

		EnhancedInputComponent->BindAction(IA_Heal, ETriggerEvent::Started, this, &AChallengersCharacter::Heal);

		EnhancedInputComponent->BindAction(IA_RightMouse, ETriggerEvent::Started, this, &AChallengersCharacter::ComboAttack);

		// ä��
		EnhancedInputComponent->BindAction(IA_Chat, ETriggerEvent::Started, this, &AChallengersCharacter::Chat);


		// F1Ű�� ������ Ʃ�丮�� UI â�� ���´�.
		EnhancedInputComponent->BindAction(IA_Tutorial, ETriggerEvent::Started, this, &AChallengersCharacter::OpenTutorial_UI);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

// F1Ű�� ������ Ʃ�丮�� UI â�� ���´�.
void AChallengersCharacter::OpenTutorial_UI()
{
	if (bShowTutorial)
	{
		pc->CreateTutorialWidget();
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
		bShowTutorial = false;
	}
}

void AChallengersCharacter::ServerRPC_SetbBowSkill2_Implementation()
{
	bBowSkill2 = !bBowSkill2;
}

//void AChallengersCharacter::OnRep_bBowSkill2()
//{
//	if (bBowSkill2)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("bBowSkill2 : %d"), bBowSkill2);
//
//		if (arrow2Gage >= 0 && arrow2Gage < 100)
//		{
//			arrow2Gage++;
//		}
//
//		UE_LOG(LogTemp, Warning, TEXT("%f"), arrow2Gage);
//	}
//}


void AChallengersCharacter::InvisibleDash()
{
	DashVFX->SetVisibility(false);
}

void AChallengersCharacter::SetAnimBlueprint(UClass* abp)
{
	GetMesh()->SetAnimClass(abp);
	Part1->SetAnimClass(abp);
	Part2->SetAnimClass(abp);
	Part3->SetAnimClass(abp);
	Part4->SetAnimClass(abp);
	Part5->SetAnimClass(abp);
	Part6->SetAnimClass(abp);
	Part7->SetAnimClass(abp);
	Part8->SetAnimClass(abp);
	Part9->SetAnimClass(abp);
	Part10->SetAnimClass(abp);
	Part11->SetAnimClass(abp);
	Part12->SetAnimClass(abp);
	Part13->SetAnimClass(abp);
	Part14->SetAnimClass(abp);
	Part15->SetAnimClass(abp);
	Part16->SetAnimClass(abp);
	Part17->SetAnimClass(abp);
}

void AChallengersCharacter::SetArrow1Pool(ABowSkill1Actor* arrow1)
{
	ServerRPC_SetArrow1Pool(arrow1);
}

void AChallengersCharacter::ServerRPC_SetArrow1Pool_Implementation(class ABowSkill1Actor* _arrow1)
{
	arrow1Pool.Add(_arrow1);
}

// ���� �����ϸ� �鸮�� �Ҹ�
void AChallengersCharacter::ChangeWeaponSound()
{
	if (currentWeaponNum == 0)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), ChangeWeapon_Sword);
	}
	else if (currentWeaponNum == 1)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), ChangeWeapon_Wand);
	}
	else if (currentWeaponNum == 2)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), ChangeWeapon_Bow);
	}
}

void AChallengersCharacter::CheckSkillName()
{

}

void AChallengersCharacter::ServerRPC_InitWeaponVisibility_Implementation()
{
	currentWeapon[0] = swordComp;
	currentWeapon[1] = wandComp;
	currentWeapon[2] = gunComp;

	OnRepWeaponInitVisible();

	//MultiRPC_InitWeaponVisibility();
}

void AChallengersCharacter::MultiRPC_InitWeaponVisibility_Implementation()
{
	currentWeapon[0]->SetVisibility(true);
	currentWeapon[1]->SetVisibility(false);
	currentWeapon[2]->SetVisibility(false);
}

void AChallengersCharacter::Skill1()
{
	if (bSkillUsing || bSwordSkill1Using || bSingleMap || MP <= 0)
	{
		return;
	}

	switch (currentWeaponNum)
	{
	case 0:
		if (skillPointsArr[0] > 0)
		{
			GetCharacterMovement()->bUseControllerDesiredRotation = true;
			GetCharacterMovement()->bOrientRotationToMovement = false;

			ServerRPC_Skill1(FVector::ZeroVector, FVector::ZeroVector, this);
		}
		break;
	case 1:
		if (skillPointsArr[3] > 0 && false == bWand3)
		{
			GetCharacterMovement()->bUseControllerDesiredRotation = true;
			GetCharacterMovement()->bOrientRotationToMovement = false;

			ServerRPC_Skill3(this);
		}
		break;
	case 2:
		if (skillPointsArr[6] > 0 && false == bBow1)
		{
			GetCharacterMovement()->bUseControllerDesiredRotation = true;
			GetCharacterMovement()->bOrientRotationToMovement = false;

			ServerRPC_Skill1(FVector::ZeroVector, FVector::ZeroVector, this);
		}
		break;
	}

}

void AChallengersCharacter::ServerRPC_Skill1_Implementation(FVector _curPlayerForward, FVector _curLoc, AChallengersCharacter* _cc)
{
	UE_LOG(LogTemp, Warning, TEXT("Skill1 : %d"), bSkillUsing);

	FActorSpawnParameters params;

	switch (currentWeaponNum)
	{
	case 0:
		if (false == bSword1)
		{
			_cc->GetCharacterMovement()->bUseControllerDesiredRotation = true;
			_cc->GetCharacterMovement()->bOrientRotationToMovement = false;

			// �ٸ� ��ų ��� �Ұ�
			bSwordSkill1Using = true;

			bSword1 = true;

			currentSkillNum = 1;
			ServerRPC_DecreaseMP(DT_SkillStruct->FindRow<FSkillsInfo>(FName("Sword1"), "")->UsedMP);

			MultiRPC_Skill1(currentWeaponNum);

			sword->SwordSkill1();
		}
		break;
	case 1:
		if (false == bWand3)
		{
			_cc->GetCharacterMovement()->bUseControllerDesiredRotation = true;
			_cc->GetCharacterMovement()->bOrientRotationToMovement = false;

			if (wandSkill1Actor_bp != nullptr)
			{
				wandSkill1Actor = GetWorld()->SpawnActor<AWandSkill1SpawnActor>(wandSkill1Actor_bp, _curLoc + _curPlayerForward * 800.0f, FRotator(0), params);
			}

			if (wandSkill1Actor)
			{
				ServerRPC_SetSkillPointsDmgPercent(3);

				wandSkill1Actor->ServerRPC_WandSkill1Hit();
			}
		}
	
		break;
	case 2:
		if (false == bBow1 && currentBowSkillNum == -1)
		{
			bSkillUsing = true;
			currentBowSkillNum = 1;

			_cc->GetCharacterMovement()->bUseControllerDesiredRotation = true;
			_cc->GetCharacterMovement()->bOrientRotationToMovement = false;

			MultiRPC_Skill1(currentWeaponNum);

		}
		break;
	}
}

void AChallengersCharacter::Skill1_Triggered()
{
	if (MP <= 0)
	{
		return;
	}

	switch (currentWeaponNum)
	{
	case 0:
		break;
	case 1:
		UE_LOG(LogTemp, Warning, TEXT("bWand3 : %d"), bWand3);
		if (skillPointsArr[3] > 0 && false == bWand3)
		{
			UE_LOG(LogTemp, Warning, TEXT("Skill1_Triggered"));
			//UE_LOG(LogTemp, Warning, TEXT("bWand3 : %d"), bWand3);

			WandSkill3_Ready();
		}
		break;
	case 2:
		if (skillPointsArr[6] > 0 && currentBowSkillNum == 1 && false == bWand1)
		{
			// ������ �ð� ��� ó�� �� �� ĳ���� ȸ���ϰ�, �� ������ �����ż� ��� ��
			FTimerHandle delay;
			GetWorldTimerManager().SetTimer(delay, [&] {
				GetCharacterMovement()->bUseControllerDesiredRotation = false;
				GetCharacterMovement()->bOrientRotationToMovement = true;

				ServerRPC_BowSkill1_Triggered(this);
			}, 0.3f, false);

		}
		break;
	}
	

	
}

void AChallengersCharacter::ServerRPC_BowSkill1_Triggered_Implementation(AChallengersCharacter* _this)
{
	if (skillSystemComp->GunSkillArr[0] == true && false == bBow1)
	{
		// Start -> Loop Anim
		if (!GetMesh()->GetAnimInstance()->Montage_IsPlaying(BowSkill1_Start_Montage) && !GetMesh()->GetAnimInstance()->Montage_IsPlaying(BowSkill1_Loop_Montage))
		{
			MultiRPC_BowSkill1_Triggered();
		}

		_this->GetCharacterMovement()->bUseControllerDesiredRotation = false;
		_this->GetCharacterMovement()->bOrientRotationToMovement = true;

		ServerRPC_DecreaseMP(DT_SkillStruct->FindRow<FSkillsInfo>(FName("Gun1"), "")->UsedMP);

		//gun->GunSkill1();
	}
	
}

void AChallengersCharacter::MultiRPC_Skill1_Implementation(int32 _currentWeaponNum)
{
	switch (_currentWeaponNum)
	{
	case 0 :
		PlayMyMontage(SwordSkill1Montage);
		break;
	case 1 :
		PlayMyMontage(WandSkill1Montage);
		break;
	case 2 :
		PlayMyMontage(BowSkill1_Start_Montage);
		break;
	}
}


void AChallengersCharacter::MultiRPC_BowSkill1_Triggered_Implementation()
{
	PlayMyMontage(BowSkill1_Loop_Montage);
}

void AChallengersCharacter::Skill1_Completed()
{

	switch (currentWeaponNum)
	{
	case 0:
		if (skillPointsArr[0] > 0 && MP > 0)
		{
			FTimerHandle delay;
			GetWorldTimerManager().SetTimer(delay, [&] {
				GetCharacterMovement()->bUseControllerDesiredRotation = false;
				GetCharacterMovement()->bOrientRotationToMovement = true;

			}, 0.3f, false);

			ServerRPC_Skill1_Completed(currentWeaponNum, this);
		}
		break;
	case 1:
		if (skillPointsArr[3] > 0 && false == bWand3)
		{
			FTimerHandle delay;
			GetWorldTimerManager().SetTimer(delay, [&] {
				GetCharacterMovement()->bUseControllerDesiredRotation = false;
				GetCharacterMovement()->bOrientRotationToMovement = true;

			}, 0.3f, false);

			ServerRPC_Skill3_Completed(currentWeaponNum, this);

			UE_LOG(LogTemp, Warning, TEXT("Skill1_Completed"));

		}
		break;
	case 2:
		if (skillPointsArr[6] > 0 && currentBowSkillNum == 1)
		{
			FTimerHandle delay;
			GetWorldTimerManager().SetTimer(delay, [&] {
				GetCharacterMovement()->bUseControllerDesiredRotation = false;
				GetCharacterMovement()->bOrientRotationToMovement = true;

			}, 0.3f, false);

			ServerRPC_Skill1_Completed(currentWeaponNum, this);
		}
		break;
	}


	

}

void AChallengersCharacter::ServerRPC_Skill1_Completed_Implementation(int32 _currentWeaponNum, AChallengersCharacter* _this)
{
	_this->GetCharacterMovement()->bUseControllerDesiredRotation = false;
	_this->GetCharacterMovement()->bOrientRotationToMovement = true;

	if (skillSystemComp->GunSkillArr[0] == true && false == bBow1)
	{
		bBow1 = true;
		
		MultiRPC_Skill1_Completed(_currentWeaponNum);		
	}
}

void AChallengersCharacter::MultiRPC_Skill1_Completed_Implementation(int32 currentWeaponNum_)
{
	switch (currentWeaponNum_)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		PlayMyMontage(BowSkill1_End_Montage);
		break;
	}

}

void AChallengersCharacter::Skill2()
{
	if (bSkillUsing || bSwordSkill1Using || bSingleMap || MP <= 0)
		return;			

	switch (currentWeaponNum)
	{
	case 0:
		if (skillPointsArr[1] > 0 && false == bSword2)
		{			
			FRotator rot = FollowCamera->GetForwardVector().Rotation();
			rot.Pitch = 0;
			rot.Roll = 0;
			SetActorRotation(rot);
			ServerRPC_Skill2(this);			
		}
		break;
	case 1:
		if (skillPointsArr[4] > 0 && false == bWand2)
		{
			GetCharacterMovement()->bUseControllerDesiredRotation = true;
			GetCharacterMovement()->bOrientRotationToMovement = false;

			ServerRPC_Skill2(this);
		}
		break;
	case 2:
		if (skillPointsArr[7] > 0 && false == bBow2)
		{
			GetCharacterMovement()->bUseControllerDesiredRotation = true;
			GetCharacterMovement()->bOrientRotationToMovement = false;

			ServerRPC_Skill2(this);
		}
		break;
	}
	
}

void AChallengersCharacter::ServerRPC_Skill2_Implementation(AChallengersCharacter* _cc)
{
	FActorSpawnParameters params;


	switch (currentWeaponNum)
	{
	case 0:
		{
			bSkillUsing = true;
			bSword2 = true;

			currentSkillNum = 2;

			_cc->GetCharacterMovement()->bUseControllerDesiredRotation = true;
			_cc->GetCharacterMovement()->bOrientRotationToMovement = false;

			ServerRPC_DecreaseMP(DT_SkillStruct->FindRow<FSkillsInfo>(FName("Sword2"), "")->UsedMP);

			MultiRPC_Skill2(currentWeaponNum);

			//sword->SwordSkill2();
		}
		break;
	case 1:
		{
			bSkillUsing = true;
			bWand2 = true;

			_cc->GetCharacterMovement()->bUseControllerDesiredRotation = true;
			_cc->GetCharacterMovement()->bOrientRotationToMovement = false;

			ServerRPC_DecreaseMP(DT_SkillStruct->FindRow<FSkillsInfo>(FName("Magic2"), "")->UsedMP);

			skillNum = 2;

			// 2�޺� -> 2����ų�� �̵�
			MultiRPC_ComboAttack(skillNum);

			wandSkill2_Combo_var = GetWorld()->SpawnActor<AWandSkill2Actor_Combo>(wandSkill2_Combo_bp, GetActorLocation(), FRotator(0), params);

		}
		break;
	case 2:
		if (currentBowSkillNum == -1)
		{
			bSkillUsing = true;
			currentBowSkillNum = 2;

			_cc->GetCharacterMovement()->bUseControllerDesiredRotation = true;
			_cc->GetCharacterMovement()->bOrientRotationToMovement = false;

			ServerRPC_DecreaseMP(DT_SkillStruct->FindRow<FSkillsInfo>(FName("Gun2"), "")->UsedMP);

			MultiRPC_Skill2(currentWeaponNum);

			//gun->GunSkill2();
		}
		break;
	default:
		break;
	}
}

void AChallengersCharacter::MultiRPC_Skill2_Implementation(int32 _currentWeaponNum)
{
	switch (_currentWeaponNum)
	{
	case 0:
		PlayMyMontage(SwordSkill2Montage);
		break;
	case 1:
		PlayMyMontage(WandSkill2_Start_Montage);
		break;
	case 2:
		PlayMyMontage(BowSkill2_Start_Montage);
		break;
	}
}

void AChallengersCharacter::Skill2_Triggered()
{
	if (currentWeaponNum == 1)
	{
		//ServerRPC_WandSkill2_Triggered();
	}
	else if (currentWeaponNum == 2 && skillPointsArr[7] > 0 &&currentBowSkillNum == 2 && false == bBow2)
	{
		ServerRPC_BowSkill2_Triggered();
	}
}

void AChallengersCharacter::ServerRPC_WandSkill2_Triggered_Implementation()
{
	if (skillSystemComp->WandSkillArr[1] == true && false == bWand2)
	{
		if (!GetMesh()->GetAnimInstance()->Montage_IsPlaying(WandSkill2_Start_Montage) && !GetMesh()->GetAnimInstance()->Montage_IsPlaying(WandSkill2_Loop_Montage))
		{
			MultiRPC_WandSkill2_Triggered();
			ServerRPC_DecreaseMP(DT_SkillStruct->FindRow<FSkillsInfo>(FName("Magic2"), "")->UsedMP);
		}
	}
}

void AChallengersCharacter::MultiRPC_WandSkill2_Triggered_Implementation()
{
	PlayMyMontage(WandSkill2_Loop_Montage);
}

void AChallengersCharacter::ServerRPC_BowSkill2_Triggered_Implementation()
{
	if (skillSystemComp->GunSkillArr[1] == true && false == bBow2)
	{
		

		if (!GetMesh()->GetAnimInstance()->Montage_IsPlaying(BowSkill2_Start_Montage) && !GetMesh()->GetAnimInstance()->Montage_IsPlaying(BowSkill2_Loop_Montage))
		{
			MultiRPC_BowSkill2_Triggered();

			bBowSkill2 = true;
		}

		ServerRPC_DecreaseMP(DT_SkillStruct->FindRow<FSkillsInfo>(FName("Gun2"), "")->UsedMP);

	}

	
}

void AChallengersCharacter::MultiRPC_BowSkill2_Triggered_Implementation()
{		
	PlayMyMontage(BowSkill2_Loop_Montage);
}

void AChallengersCharacter::Skill2_Completed()
{
	switch (currentWeaponNum)
	{
	case 0:
		if (skillPointsArr[1] > 0)
		{
			FTimerHandle delay;
			GetWorldTimerManager().SetTimer(delay, [&] {
				GetCharacterMovement()->bUseControllerDesiredRotation = false;
				GetCharacterMovement()->bOrientRotationToMovement = true;

				ServerRPC_Skill2_Completed(FVector(0), FRotator(0), this);
			}, 0.3f, false);

		}
		break;
	case 1:
		if (skillPointsArr[4] > 0)
		{
			FTimerHandle delay;
			GetWorldTimerManager().SetTimer(delay, [&] {
				GetCharacterMovement()->bUseControllerDesiredRotation = false;
				GetCharacterMovement()->bOrientRotationToMovement = true;

				ServerRPC_Skill2_Completed(FVector(0), FRotator(0), this);
			}, 0.3f, false);

		}
		break;
	case 2:
		if (skillPointsArr[7] > 0 && currentBowSkillNum == 2)
		{
			FVector spawnLoc = GetActorLocation() + GetActorForwardVector() * 400.0f;
			FRotator spawnRot = GetActorRotation();

			FTimerHandle delay;
			GetWorldTimerManager().SetTimer(delay, [&] {
				GetCharacterMovement()->bUseControllerDesiredRotation = false;
				GetCharacterMovement()->bOrientRotationToMovement = true;

				UE_LOG(LogTemp, Error, TEXT("%f"), arrow2Gage);
			}, 0.3f, false);

			ServerRPC_Skill2_Completed(spawnLoc, spawnRot, this);

		}
		break;
	}
	// AM_WandSkill3_3
	//bSkillUsing = false;
}

void AChallengersCharacter::ServerRPC_Skill2_Completed_Implementation(FVector _spawnLoc, FRotator _spawnRot, AChallengersCharacter* _this)
{
	switch (currentWeaponNum)
	{
	case 0:
		_this->GetCharacterMovement()->bUseControllerDesiredRotation = false;
		_this->GetCharacterMovement()->bOrientRotationToMovement = true;
		break;
	case 1:
		_this->GetCharacterMovement()->bUseControllerDesiredRotation = false;
		_this->GetCharacterMovement()->bOrientRotationToMovement = true;
		break;
	case 2:
		if (skillSystemComp->GunSkillArr[1] == true && false == bBow2)
		{
			bBow2 = true;

			ServerRPC_SetbBowSkill2();

			FActorSpawnParameters params;			


			bowSkill2Actor = GetWorld()->SpawnActor<ABowSkill2Actor>(bowSkill2Actor_bp, _spawnLoc, _spawnRot, params);

			if (bowSkill2Actor != nullptr)
			{
				
				//bowSkill2Actor->fx->SetWorldRotation(newBowRot);
				
				// ��ų����Ʈ�� ���� ������ Ÿ�ݷ�
				bowSkill2Actor->damagePercent = 1 + 0.1 * (_this->skillPointsArr[7]);

				// bow �� ������ �� �����ϱ� �����ɶ� ��ȭ�� ���ݷ� ���� bowSkill2Actor �� �Ѱ���
				bowSkill2Actor->weaponAttackPower = (_this->currentWeaponStat[2]);

				// ��¡������ ���� ������ Ÿ�ݷ�
				bowSkill2Actor->SetDamageGage(arrow2Gage);

			}

			arrow2Gage = 0;

			MultiRPC_Skill2_Completed();

			_this->GetCharacterMovement()->bUseControllerDesiredRotation = false;
			_this->GetCharacterMovement()->bOrientRotationToMovement = true;

			UE_LOG(LogTemp, Error, TEXT("%f"), arrow2Gage);

		}
		break;
	}

	
}

void AChallengersCharacter::MultiRPC_Skill2_Completed_Implementation()
{
	switch (currentWeaponNum)
	{
	case 0:
		break;
	case 1:
		//PlayMyMontage(WandSkill2_End_Montage);
		break;
	case 2:
		PlayMyMontage(BowSkill2_End_Montage);
		UGameplayStatics::PlaySound2D(GetWorld(), bowSkill2Sound);
		
		
		break;
	}
}

void AChallengersCharacter::Skill3()
{
	if (bSkillUsing || bSwordSkill1Using || bSingleMap || MP <= 0)
		return;

	switch (currentWeaponNum)
	{
	case 0:
		if (skillPointsArr[2] > 0 && false == bSword3)
		{
			bSkillUsing = true;

			bSword3 = true;

			FRotator rot = FollowCamera->GetForwardVector().Rotation();
			rot.Pitch = 0;
			rot.Roll = 0;
			SetActorRotation(rot);
			ServerRPC_Skill3(this);
		}
		break;
	case 1:
	{
		if (skillPointsArr[5] > 0 && false == bWand1)
		{
			// ��ų1 -> ��ų3
			bSkillUsing = true;

			bWand1 = true;

			FRotator rot = FollowCamera->GetForwardVector().Rotation();
			rot.Pitch = 0;
			rot.Roll = 0;
			SetActorRotation(rot);

			ServerRPC_DecreaseMP(DT_SkillStruct->FindRow<FSkillsInfo>(FName("Magic3"), "")->UsedMP);

			FVector curPlayerForward = GetActorForwardVector();
			FVector curPlayerLoc = GetActorLocation();

			ServerRPC_Skill1(curPlayerForward, curPlayerLoc, this);

			MultiRPC_Skill1(currentWeaponNum);
		}
	}
		break;
	case 2:
		UE_LOG(LogTemp, Warning, TEXT("skillPointsArr[8] : %d"), skillPointsArr[8]);

		if (skillPointsArr[8] > 0 && false == bBow3)
		{
			GetCharacterMovement()->bUseControllerDesiredRotation = true;
			GetCharacterMovement()->bOrientRotationToMovement = false;

			FVector bowSkill3SpawnLoc = GetActorLocation() + GetActorForwardVector() * 200.0f;
			FRotator bowSkill3SpawnRot = GetActorRotation();

			FActorSpawnParameters params;
			params.Owner = this;

			bowSkill3DecalActor = GetWorld()->SpawnActor<ABowSkill3DecalActor>(bowSkill3DecalActor_bp, bowSkill3SpawnLoc, bowSkill3SpawnRot, params);

			ServerRPC_Skill3(this);
		}
		break;
	
	}

}

void AChallengersCharacter::ServerRPC_Skill3_Implementation(AChallengersCharacter* _player)
{
	

	switch (currentWeaponNum)
	{
	case 0:
		{
			_player->GetCharacterMovement()->bUseControllerDesiredRotation = true;
			_player->GetCharacterMovement()->bOrientRotationToMovement = false;

			currentSkillNum = 3;

			ServerRPC_DecreaseMP(DT_SkillStruct->FindRow<FSkillsInfo>(FName("Sword3"), "")->UsedMP);

			MultiRPC_Skill3(currentWeaponNum);

			sword->SwordSkill3();
		}
		break;
	case 1:
		{
			bSkillUsing = true;

			if (!bIsWandSkill3Started)
			{
				bIsWandSkill3Started = true;
			}

			// ��ų3 -> ��ų1
			_player->GetCharacterMovement()->bUseControllerDesiredRotation = true;
			_player->GetCharacterMovement()->bOrientRotationToMovement = false;
			

			MultiRPC_Skill3(currentWeaponNum);
		}
	
		break;
	case 2:
		{
			bSkillUsing = true;
		
			currentBowSkillNum = 3;
			_player->GetCharacterMovement()->bUseControllerDesiredRotation = true;
			_player->GetCharacterMovement()->bOrientRotationToMovement = false;

			ServerRPC_DecreaseMP(DT_SkillStruct->FindRow<FSkillsInfo>(FName("Gun3"), "")->UsedMP);

			MultiRPC_Skill3(currentWeaponNum);
			
			//gun->GunSkill3();
		}

		break;
	default:
		break;
	}
}

void AChallengersCharacter::MultiRPC_Skill3_Implementation(int32 _currentWeaponNum)
{
	switch (_currentWeaponNum)
	{
	case 0:
		PlayMyMontage(SwordSkill3Montage);
		break;
	case 1:
		PlayMyMontage(WandSkill3_Start_Montage);
		break;
	case 2:
		PlayMyMontage(BowSkill3_Start_Montage);
		break;
	}
}

void AChallengersCharacter::Skill3_Triggered()
{
	if (bSingleMap || MP <= 0)
		return;

	switch (currentWeaponNum)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		if (skillPointsArr[8] > 0 && false == bBow3)
		{
			FVector start = FollowCamera->GetComponentLocation();
			FVector end = start + FollowCamera->GetComponentRotation().Vector() * 2500.0f;

			// �ڱ��ڽ����׸� ���̴°Ÿ� ���� ���� rpc �ȳ����� ��
			FHitResult hitInfo;
			FCollisionQueryParams params;
			params.AddIgnoredActor(this);

			bool bHit = GetWorld()->LineTraceSingleByChannel(hitInfo, start, end, ECollisionChannel::ECC_Visibility, params);

			// �밢�� �Ʒ��� ���� �¾�����
			if (bHit)
			{
				TArray<FVector> aimPoints;
				aimPoints.Add(hitInfo.ImpactPoint);

				finalAimLoc = aimPoints.Last(aimPoints.Num() - 1);

				//DrawDebugSphere(GetWorld(), finalAimLoc, 150, 16, FColor::Red, false, 0.02f, 0, 2);

				if (bowSkill3DecalActor)
				{
					bowSkill3DecalActor->SetActorLocation(finalAimLoc);
				}
			}
			// �����϶�
			else {
				FHitResult hitInfoGround;

				FVector endBottom = end;
				endBottom.Z = -100000000;

				bool bHitGround = GetWorld()->LineTraceSingleByChannel(hitInfoGround, end, endBottom, ECollisionChannel::ECC_Visibility, params);

				TArray<FVector> aimPoints;
				aimPoints.Add(hitInfoGround.ImpactPoint);

				finalAimLoc = aimPoints.Last(aimPoints.Num() - 1);

				//DrawDebugSphere(GetWorld(), finalAimLoc, 150, 16, FColor::Red, false, 0.02f, 0, 2);
				if (bowSkill3DecalActor)
				{
					bowSkill3DecalActor->SetActorLocation(finalAimLoc);
				}

			}



			ServerRPC_BowSkill3_Triggered(finalAimLoc);
		}
		
		break;
			
	}


	
}

void AChallengersCharacter::ServerRPC_BowSkill3_Triggered_Implementation(FVector _finalAimLoc)	// FVector _finalAimLoc
{
	switch (currentWeaponNum)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		if (skillSystemComp->GunSkillArr[2] == true && false == bBow3 && currentBowSkillNum == 3)
		{
			finalAimLoc = _finalAimLoc;

			if (!GetMesh()->GetAnimInstance()->Montage_IsPlaying(BowSkill3_Start_Montage) && !GetMesh()->GetAnimInstance()->Montage_IsPlaying(BowSkill3_Loop_Montage))
			{
				MultiRPC_BowSkill3_Triggered();
			}
		}
		break;
	}
}

void AChallengersCharacter::MultiRPC_BowSkill3_Triggered_Implementation()
{
	PlayMyMontage(BowSkill3_Loop_Montage);
}

void AChallengersCharacter::Skill3_Completed()
{
	if (bSingleMap || MP <= 0)
		return;

	switch (currentWeaponNum)
	{
	case 0:
		if (skillPointsArr[2] > 0)
		{
			GetCharacterMovement()->bUseControllerDesiredRotation = false;
			GetCharacterMovement()->bOrientRotationToMovement = true;

			ServerRPC_Skill3_Completed(currentWeaponNum, this);
		}
		break;
	case 1:
		if (skillPointsArr[5] > 0 && false == bWand1)
		{
			GetCharacterMovement()->bUseControllerDesiredRotation = false;
			GetCharacterMovement()->bOrientRotationToMovement = true;

			ServerRPC_Skill1_Completed(currentWeaponNum, this);
		}
		break;
	case 2:
		if (skillPointsArr[8] > 0 && false == bBow3)
		{
			GetCharacterMovement()->bUseControllerDesiredRotation = false;
			GetCharacterMovement()->bOrientRotationToMovement = true;

			if (bowSkill3DecalActor)
				bowSkill3DecalActor->DestroyDecal();

			ServerRPC_Skill3_Completed(currentWeaponNum, this);

			//bowSkill3DecalActor->GetDecal()->SetVisibility(false);
			

			//gun->GunSkill3();
		
		}
		break;
	}

	

	// bSkillUsing = false;
}

void AChallengersCharacter::ServerRPC_Skill3_Completed_Implementation(int32 _currentWeaponNum, AChallengersCharacter* _player)
{
	UE_LOG(LogTemp, Warning, TEXT("skillSystemComp : %d"), skillSystemComp->WandSkillArr[2]);

	switch (_currentWeaponNum)
	{
	case 0:
		{
			_player->GetCharacterMovement()->bUseControllerDesiredRotation = false;
			_player->GetCharacterMovement()->bOrientRotationToMovement = true;
		}
		break;
	case 1:
		{
			bWand3 = true;
			bSpawnWand3 = false;
			bIsWandSkill3Started = false;

			// �޺� ������ �ƿ� ��ų loop �ִϸ��̼� ��
			bWandComboPlaying = false;

			MultiRPC_Skill3_Completed(_currentWeaponNum);

			_player->GetCharacterMovement()->bUseControllerDesiredRotation = false;
			_player->GetCharacterMovement()->bOrientRotationToMovement = true;

			if (wandSkill3Actor_var)
			{
				//wandSkill3Actor_var->Destroy();
				wandSkill3Actor_var->WandSkill3Activate(false);
				cnt = 0;
			}
		}
		break;
	case 2:
		if (currentBowSkillNum == 3)
		{
			bBow3 = true;

			MultiRPC_Skill3_Completed(_currentWeaponNum);

			_player->GetCharacterMovement()->bUseControllerDesiredRotation = false;
			_player->GetCharacterMovement()->bOrientRotationToMovement = true;

			FActorSpawnParameters params;
			bowSkill3Actor = GetWorld()->SpawnActor<ABowSkill3Actor>(bowSkill3Actor_bp, finalAimLoc, FRotator(0), params);

			if (bowSkill3Actor)
			{
				// ��ų����Ʈ�� ���� ������ Ÿ�ݷ�
				bowSkill3Actor->damagePercent = 1 + 0.1 * skillPointsArr[8];

				// bow �� ������ �� �����ϱ� �����ɶ� ��ȭ�� ���ݷ� ���� bowSkill3Actor �� �Ѱ���
				bowSkill3Actor->weaponAttackPower = currentWeaponStat[2];

				bowSkill3Actor->BowSkill3();
			}
		}
		break;
	}
	
}

void AChallengersCharacter::MultiRPC_Skill3_Completed_Implementation(int32 currentWeaponNum_)
{
	switch (currentWeaponNum_)
	{
	case 0:
		break;
	case 1:
		PlayMyMontage(WandSkill3_End_Montage);
		break;
	case 2:
		if (skillSystemComp->GunSkillArr[2] == true)
		{
			PlayMyMontage(BowSkill3_End_Montage);
		}
		break;
	}
}

void AChallengersCharacter::ShowMouseCursor()
{
	bShowCursor = !bShowCursor;

	pc->SetShowMouseCursor(bShowCursor);
}

void AChallengersCharacter::ShowSkillMenu()
{
	LoadSkillPoints();

	if (!InputKeyButton_K)
	{
		if (bShowSkillSet)
		{
			pc->CreateSkillSetWidget();
			pc->skillsetWidget->Sword1 = skillPointsArr[0];
			pc->skillsetWidget->Sword2 = skillPointsArr[1];
			pc->skillsetWidget->Sword3 = skillPointsArr[2];
			pc->skillsetWidget->Wand1 = skillPointsArr[3];
			pc->skillsetWidget->Wand2 = skillPointsArr[4];
			pc->skillsetWidget->Wand3 = skillPointsArr[5];
			pc->skillsetWidget->Bow1 = skillPointsArr[6];
			pc->skillsetWidget->Bow2 = skillPointsArr[7];
			pc->skillsetWidget->Bow3 = skillPointsArr[8];
			pc->skillsetWidget->CurrentSkillPoint = canUseSkillPoint;
			pc->skillsetWidget->SetSkillLevel();
			
			bShowSkillSet = false;
		}

		UE_LOG(LogTemp, Warning, TEXT("ShowSkillMenu"));
	}
	
}

void AChallengersCharacter::ShowOptionMenu()
{
	if (bOption == false)
	{
		pc->CreateOptionWidget();
		bOption = true;
		pc->SetInputMode(FInputModeGameAndUI());
		pc->SetShowMouseCursor(true);

		GetCharacterMovement()->Deactivate();

	}
	else
	{
		pc->OptionWidget->SetVisibility(ESlateVisibility::Hidden);
		bOption = false;
		pc->SetInputMode(FInputModeGameOnly());
		pc->SetShowMouseCursor(false);
		GetCharacterMovement()->Activate();
	}
}

void AChallengersCharacter::ServerRPC_SendMsg_Implementation(const FString& msg)
{
	MultiRPC_SendMsg(msg);
}

void AChallengersCharacter::MultiRPC_SendMsg_Implementation(const FString& msg)
{
	// ���� UI�� Addmsgȣ��
	auto pCon = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
	pCon->mainplayerWidget->AddMsg(msg);
}

void AChallengersCharacter::Chat()
{
	// ä�� Ȱ��ȭ

	//bchatEnabled = !bchatEnabled;

	if (pc->mainplayerWidget->Editable_chat->GetText().IsEmpty() == false)
	{
		pc->mainplayerWidget->OnMySendMsg();
		
	}
	
	if (bchatEnabled == false)
	{
		if (pc->mainplayerWidget->Editable_chat->GetText().IsEmpty())
		{
			pc->mainplayerWidget->ActiveEditableChat();
			FInputModeGameAndUI InputChatMode;
			pc->SetIgnoreLookInput(true);

			pc->SetInputMode(InputChatMode);
			//bchatEnabled = true;
			return;
		}
	}	
}

void AChallengersCharacter::ServerRPC_SetNickName_Implementation()
{
	OnRap_SetNickName();
}

void AChallengersCharacter::OnRap_SetNickName()
{
	for (TActorIterator<AChallengersCharacter> it(GetWorld()); it; ++it)
	{
		if (it->NameComp) {
			UCharacterName* nameWidget = Cast<UCharacterName>(it->NameComp->GetWidget());
			if (nameWidget) {
				nameWidget->ShowNickName(it->playerName);
			}
		}
	}
}

void AChallengersCharacter::ServerRPC_ShowEffect_Implementation()
{
	if (sword)
	{
		sword->UpgradeSwordEffect(weaponLevel[0]);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NoSword"));
	}
	if (wand)
	{
		wand->UpgradeWandEffect(weaponLevel[1]);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NoWand"));
	}
	if (gun)
	{
		gun->UpgradeBowEffect(weaponLevel[2]);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NoBow"));
	}
}

void AChallengersCharacter::Move(const FInputActionValue& Value)
{
	if (bSkillUsing || bSword1CanMove || bComboUsing)
	{
		return;
	}

	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AChallengersCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}

	
}

// �⺻ ����
void AChallengersCharacter::Attack(const FInputActionValue& Value)
{
	if (bSkillUsing || bSwordSkill1Using || bSingleMap)
		return;
		
	pc->mainplayerWidget->MP_Update(MP);

	UE_LOG(LogTemp, Warning, TEXT("MP : %d"), MP);
	
	if (pc)
	{
		if (pc->IsLocalController())
		{
			FVector wandBasicLoc = GetActorLocation() + GetActorForwardVector() * 100;
			FRotator controlRot = pc->GetControlRotation();
			FRotator newConRot = FRotator(0, controlRot.Yaw, 0);
			// Ŭ�� �ڱ� �ڽ����׵� ȸ���� ����� ����
			SetActorRotation(newConRot);

			ServerRPC_Attack(wandBasicLoc, controlRot, newConRot, this);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("pc is localController"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No pc!!!!!!!!"));
	}
}

void AChallengersCharacter::ServerRPC_Attack_Implementation(FVector _wandBasicLoc, FRotator _controlRot, FRotator _newConRot, AChallengersCharacter* _CC)
{
	currentSkillNum = 0;

	ServerRPC_IncreaseMP(1000);

	// Sword : ����
	if (currentWeaponNum == 0 && true == bCanSwordBasicAttack)
	{
		// �ٸ� ��ų ���Ұ�
		bSwordSkill1Using = true;

		// true �� �� ������
		bSword1CanMove = true;

		if (swordBasicAttackMontages.IsValidIndex(swordBasicAttackCnt))
		{
			UAnimMontage* montage = swordBasicAttackMontages[swordBasicAttackCnt];

			// ���� PlayMontage �� OnCompleted, OnInterrupted
			FOnMontageEnded MontageEndedDelegate;
			MontageEndedDelegate.BindUObject(this, &AChallengersCharacter::OnSwordBsMontageEnded);

			MultiRPC_Attack(montage);
			GetMesh()->GetAnimInstance()->Montage_SetEndDelegate(MontageEndedDelegate, montage);

			// ���� ���� �ִϸ��̼� �ε��� ����
			swordBasicAttackCnt = (swordBasicAttackCnt + 1) % swordBasicAttackMontages.Num();

			// ���� ���� ���� ����
			bCanSwordBasicAttack = false;

			// ���� �ð� �Ŀ� �ٽ� ���� �����ϵ��� ����
			GetWorld()->GetTimerManager().SetTimer(attackDelayHdl, [&] {
				bCanSwordBasicAttack = true;
				swordBasicAttackCnt = 0;
			}, 2.5f, false);

			sword->CheckBasicAttackCnt(swordBasicAttackCnt);
			UE_LOG(LogTemp, Warning, TEXT("%d"), swordBasicAttackCnt);
		}
	}
	// ������
	else if (currentWeaponNum == 1 && true == bCanWandBasicAttack)
	{
		bSkillUsing = true;

		_CC->SetActorRotation(_newConRot);

		// GetCharacterMovement()->MaxWalkSpeed = 180.0f;

		//wandBasicActor->SetActorLocation(_wandBasicLoc);
		//wandBasicActor->SetActorRotation(_controlRot);
		//FVector basicLoc = GetActorLocation() + GetActorForwardVector() * 500.0f;
		//wand->ServerRPC_WandBasicAttack(basicLoc, this);

		FActorSpawnParameters params;
		wandBasicActor = GetWorld()->SpawnActor<AWandBasic>(wandBasicActor_bp, _wandBasicLoc, GetActorRotation(), params);
		//wandBasicActor->WandBasicActivate(true);


		UAnimMontage* montage = wandBasicAttackMontages[wandBasicAttackCnt];

		UE_LOG(LogTemp, Warning, TEXT("%d"), wandBasicAttackCnt);

		// ���� PlayMontage �� OnCompleted, OnInterrupted
		FOnMontageEnded MontageEndedDelegate;
		MontageEndedDelegate.BindUObject(this, &AChallengersCharacter::OnWandBsMontageEnded);

		MultiRPC_Attack(montage);
		GetMesh()->GetAnimInstance()->Montage_SetEndDelegate(MontageEndedDelegate, montage);

		// ���� ���� �ִϸ��̼� �ε��� ����
		wandBasicAttackCnt = (wandBasicAttackCnt + 1) % wandBasicAttackMontages.Num();

		// ���� ���� ���� ����
		bCanWandBasicAttack = false;

		// ���� �ð� �Ŀ� �ٽ� ���� �����ϵ��� ����
		GetWorld()->GetTimerManager().SetTimer(attackDelayHdl, [&] {
			bCanWandBasicAttack = true;
			wandBasicAttackCnt = 0;
			}, 2.5f, false);
	}
	// Ȱ
	else if (currentWeaponNum == 2)
	{
		bSkillUsing = true;

		// ���� ���忡���� ȸ���� ����� ����
		_CC->SetActorRotation(_newConRot);

		GetCharacterMovement()->MaxWalkSpeed = 180.0f;

		MultiRPC_Attack(BowBasicMontage);
	}
}

void AChallengersCharacter::MultiRPC_Attack_Implementation(UAnimMontage* _montage)
{
	PlayMyMontage(_montage);

	if (currentWeaponNum == 0)
	{
		if (swordBasicAttackCnt == 0 || swordBasicAttackCnt == 2)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), swordAttackSound1);
		}
		else if (swordBasicAttackCnt == 1 || swordBasicAttackCnt == 3)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), swordAttackSound2);
		}
		else if (swordBasicAttackCnt == 4)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), swordAttackSound3);
		}
	}
	
}

void AChallengersCharacter::ChangeWeapon(const FInputActionValue& Value)
{
	pc->mainplayerWidget->ChangeAnim();
	if (bSkillUsing || bSwordSkill1Using)
		return;

	if (!BlockChange)
	{
		prevWeaponNum = currentWeaponNum;

		if (currentWeaponNum == 2)
		{
			currentWeaponNum = 0;
		}
		else
		{
			currentWeaponNum++;
		}
		ChangeWeaponSound();
		UE_LOG(LogTemp, Warning, TEXT("currentWeaponNum : %d"), currentWeaponNum);
		ServerRPC_ChangeWeapon(prevWeaponNum, currentWeaponNum, this);
	}
	
}

void AChallengersCharacter::ServerRPC_ChangeWeapon_Implementation(int32 _prevWeaponNum, int32 _currentWeaponNum, AChallengersCharacter* player)
{
	player->prevWeaponNum = _prevWeaponNum;
	player->currentWeaponNum = _currentWeaponNum;

	ClientRPC_ChangeWeapon(_currentWeaponNum);
	MultiRPC_ChangeWeapon(_prevWeaponNum, _currentWeaponNum);
}

void AChallengersCharacter::ClientRPC_ChangeWeapon_Implementation(int32 currentWeaponNum_)
{
	// �������� ���� ��ȣ ����(���� ��ü �� UI�� ���� ����)
	pc->mainplayerWidget->weaponNum = currentWeaponNum_;
	pc->mainplayerWidget->ChangeSwitcher();

	pc->mainplayerWidget->AnimSword(currentWeaponNum_);
	pc->mainplayerWidget->AnimWand(currentWeaponNum_);
	pc->mainplayerWidget->AnimBow(currentWeaponNum_);
}

void AChallengersCharacter::MultiRPC_ChangeWeapon_Implementation(int32 _prevWeaponNum_, int32 _currentWeaponNum_)
{
	switch (_currentWeaponNum_)
	{
	case 0:
		if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == "SingleMap")
		{
			if (ABP_Sword_Single)
			{
				SetAnimBlueprint(ABP_Sword_Single);
			}
		}
		else
		{
			if (ABP_Sword_Multi)
			{
				SetAnimBlueprint(ABP_Sword_Multi);
			}
		}
		break;
	case 1:
		if (ABP_Wand)
		{
			SetAnimBlueprint(ABP_Wand);
		}
		break;
	case 2:
		if (ABP_Bow)
		{
			SetAnimBlueprint(ABP_Bow);
		}
		break;
	default:
		break;
	}

	currentWeapon[_prevWeaponNum_]->SetVisibility(false);
	currentWeapon[_currentWeaponNum_]->SetVisibility(true);
}

void AChallengersCharacter::Interact(const FInputActionValue& Value)
{
	
	if (pc != nullptr)
	{
		if (!bShowSelectCustomNPC)
		{
			pc->CreateSelectCustomWidget();
			bShowSelectCustomNPC = true;
			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
			UE_LOG(LogTemp, Warning, TEXT("Interact"));
		}
		
		if (!bShowBattleNPC)
		{
			pc->CreateBattleWidget();
			bShowBattleNPC = true;
			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
			UE_LOG(LogTemp, Warning, TEXT("Interact12"));
		}

		if (!bShowWeaponUpgradeNPC)
		{
			pc->CreateUpgradeWeaponWidget();
			bShowWeaponUpgradeNPC = true;
			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
			UE_LOG(LogTemp, Warning, TEXT("Interact"));
		}
		
		if (!bShowAISetting)
		{
			bShowAISetting = true;
			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
			pc->SetInputMode(FInputModeUIOnly());
			pc->bShowMouseCursor = true;
			
			ATestRoomGameMode* TRGM = Cast<ATestRoomGameMode>(GetWorld()->GetAuthGameMode());
			if (TRGM)
			{
				TRGM->ShowAIUI();
			}
		}

		if (!bShowEnemySetting)
		{
			bShowEnemySetting = true;
			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
			pc->SetInputMode(FInputModeUIOnly());
			pc->bShowMouseCursor = true;
			if (pc->mainplayerWidget)
			{
				pc->mainplayerWidget->SetVisibility(ESlateVisibility::Hidden);
			}
			NameComp->SetVisibility(false);

			ATestRoomGameMode* TRGM = Cast<ATestRoomGameMode>(GetWorld()->GetAuthGameMode());
			if (TRGM)
			{
				TRGM->ShowSettingUI();
			}
		}

		if (!bShowSaveWidget)
		{
			bShowSaveWidget = true;
			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
			pc->SetInputMode(FInputModeUIOnly());
			pc->bShowMouseCursor = true;
			if (pc->mainplayerWidget)
			{
				pc->mainplayerWidget->SetVisibility(ESlateVisibility::Hidden);
			}

			ATestRoomGameMode* TRGM = Cast<ATestRoomGameMode>(GetWorld()->GetAuthGameMode());
			if (TRGM)
			{
				TRGM->ShowSaveUI();
			}
		}

		if (!bShowLoadWidget)
		{
			bShowLoadWidget = true;
			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
			pc->SetInputMode(FInputModeUIOnly());
			pc->bShowMouseCursor = true;
			if (pc->mainplayerWidget)
			{
				pc->mainplayerWidget->SetVisibility(ESlateVisibility::Hidden);
			}
			NameComp->SetVisibility(false);

			ATestRoomGameMode* TRGM = Cast<ATestRoomGameMode>(GetWorld()->GetAuthGameMode());
			if (TRGM)
			{
				TRGM->ShowLoadUI();
			}
		}
	}
}

void AChallengersCharacter::CanWalk()
{
	//SCWidget->bClosed;
	if (pc != nullptr)
	{
		if (pc->selectCustomWidget != nullptr)
		{
			if (pc->selectCustomWidget->bClosed)
			{
				GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
			}
		}
		if (pc->battleWidget != nullptr)
		{
 			if (pc->battleWidget->bClosed)
 			{
 				GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
 			}
		}
		if (pc->upgradeWeaponWidget != nullptr)
		{
			if (pc->upgradeWeaponWidget->bClosed)
			{
				GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
			}
		}
	}

}

void AChallengersCharacter::Dash()
{
	if (bSkillUsing || MP <= 0)
		return;

	bSkillUsing = false;
	bSwordSkill1Using = false;
	bSword1CanMove = false;
	bCanSwordBasicAttack = true;
	
	if (!bDashDelay)
	{
		ServerRPC_Dash();
		bDashDelay = true;
	}
	
}

void AChallengersCharacter::Dash_Triggered()
{
	if (currentWeaponNum == 0)
	{
		DashVFX->SetVisibility(true);
		ServerRPC_Dash_Triggered();
	}
}

void AChallengersCharacter::ServerRPC_Dash_Triggered_Implementation()
{
	ServerRPC_DecreaseMP(DT_SkillStruct->FindRow<FSkillsInfo>(FName("Dash"), "")->UsedMP / 5);	// 1
}

void AChallengersCharacter::Dash_Completed()
{

	if (currentWeaponNum == 0)
	{
		DashVFX->SetVisibility(false);
		ServerRPC_Dash_Completed();
	}
}

void AChallengersCharacter::Teleport()
{
	TeleportVFX->SetVisibility(true);
	GetMesh()->SetVisibility(false);
	Part1->SetVisibility(false);
	Part2->SetVisibility(false);
	Part3->SetVisibility(false);
	Part4->SetVisibility(false);
	Part5->SetVisibility(false);
	Part6->SetVisibility(false);
	Part7->SetVisibility(false);
	Part8->SetVisibility(false);
	Part9->SetVisibility(false);
	Part10->SetVisibility(false);
	Part11->SetVisibility(false);
	Part12->SetVisibility(false);
	Part13->SetVisibility(false);
	Part14->SetVisibility(false);
	Part15->SetVisibility(false);
	Part16->SetVisibility(false);
	Part17->SetVisibility(false);
	wandComp->SetVisibility(false);

	FTimerHandle showTimer;
	GetWorldTimerManager().SetTimer(showTimer, [&] {
		TeleportVFX->SetVisibility(false);
		GetMesh()->SetVisibility(true);
		Part1->SetVisibility(true);
		Part2->SetVisibility(true);
		Part3->SetVisibility(true);
		Part4->SetVisibility(true);
		Part5->SetVisibility(true);
		Part6->SetVisibility(true);
		Part7->SetVisibility(true);
		Part8->SetVisibility(true);
		Part9->SetVisibility(true);
		Part10->SetVisibility(true);
		Part11->SetVisibility(true);
		Part12->SetVisibility(true);
		Part13->SetVisibility(true);
		Part14->SetVisibility(true);
		Part15->SetVisibility(true);
		Part16->SetVisibility(true);
		Part17->SetVisibility(true);
		wandComp->SetVisibility(true);
		
	}, 0.2f, false);

	//FTimerHandle invisibleTimer;
	//GetWorldTimerManager().SetTimer(invisibleTimer, [&] {
	//	DashVFX->SetVisibility(false);

	//}, 0.5f, false);
}

void AChallengersCharacter::ServerRPC_Dash_Implementation()
{
	if (MP <= 0)
		return;

	if (currentWeaponNum == 0)
	{
		GetCharacterMovement()->MaxWalkSpeed = 1200;
	}
	else if (currentWeaponNum == 1 || currentWeaponNum == 2)
	{
		if (false == bDashing)
		{
			bDashing = true;

			ServerRPC_DecreaseMP(DT_SkillStruct->FindRow<FSkillsInfo>(FName("Dash"), "")->UsedMP);

			MultiRPC_Dash();

			FVector dashDir = GetActorForwardVector();
			float dashDistance = 3500; // ����� �Ÿ� (������ cm)

			FVector dashVec = dashDir * dashDistance;

			//FVector dashVec = FVector(GetVelocity().X * 10, GetVelocity().Y * 10, 0);
			LaunchCharacter(dashVec, false, false);


			bDashing = false;
		}
	}
	
}

void AChallengersCharacter::MultiRPC_Dash_Implementation()
{
	if (currentWeaponNum == 0)
	{

	}
	else if (currentWeaponNum == 1)
	{
		PlayMyMontage(TeleportMontage);
		Teleport();
	}
	else
	{
		DashVFX->SetVisibility(true);
		PlayMyMontage(DashMontage);
	}
}

void AChallengersCharacter::ServerRPC_Dash_Completed_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = 500;
}

void AChallengersCharacter::Heal()
{
	if (bSingleMap || potionCnt > 0)
	{
		potionCnt--;
		
		HP = UKismetMathLibrary::Clamp(HP + 100, 0, 1000);
		UE_LOG(LogTemp, Warning, TEXT("Player HP : %d"), HP);
	}
}

void AChallengersCharacter::ComboAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("bSkillUsing : %d"), bSkillUsing);

	if (bComboUsing || bSwordSkill1Using || bSingleMap || MP <= 0)
		return;

	FVector spawnLoc = GetActorLocation() + GetActorForwardVector() * 500;

	int32 inputKey = 0;

	if (pc->IsInputKeyDown(EKeys::One))
	{
		inputKey = 1;
	} 
	else if (pc->IsInputKeyDown(EKeys::Two))
	{
		inputKey = 2;
	}
	else if (pc->IsInputKeyDown(EKeys::Three))
	{
		inputKey = 3;

		// �����ָ� ������ ��� �߻���
		bWandSkill3Pressing = false;

		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
	}
	else
	{
		return;
	}

	ServerRPC_ComboAttack(spawnLoc, inputKey, this);

	
}

void AChallengersCharacter::ServerRPC_ComboAttack_Implementation(FVector _spawnLoc, int32 _inputKey, AChallengersCharacter* _player)
{
	bComboUsing = true;

	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// ��
	if (currentWeaponNum == 0)
	{
		// ��ų 1 + ��Ŭ�� �� �޺���ų
		if (_inputKey == 1)
		{
			//skillNum = 1;

			//// �ٸ� ��ų ��� �Ұ�
			//bSwordSkill1Using = true;

			//ServerRPC_DecreaseMP(DT_SkillStruct->FindRow<FSkillsInfo>(FName("Sword1"), "")->UsedMP * 2);

			//MultiRPC_ComboAttack(skillNum);
		}
		// ��ų 2 + ��Ŭ�� �� �޺���ų
		else if (_inputKey == 2 && skillPointsArr[1] > 0)
		{
			skillNum = 2;

			ServerRPC_DecreaseMP(DT_SkillStruct->FindRow<FSkillsInfo>(FName("Sword2"), "")->UsedMP * 2);

			MultiRPC_ComboAttack(skillNum);
		}
		// ��ų 3 + ��Ŭ�� �� �޺���ų
		else if (_inputKey == 3 && skillPointsArr[2] > 0)
		{
			skillNum = 3;

			ServerRPC_DecreaseMP(DT_SkillStruct->FindRow<FSkillsInfo>(FName("Sword3"), "")->UsedMP * 2);

			MultiRPC_ComboAttack(skillNum);
		}
	}
	// ������
	else if (currentWeaponNum == 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("currentWeaponNum : %d"), currentWeaponNum);

		// ��ų 1 + ��Ŭ�� �� �޺���ų
		if (_inputKey == 1 && skillPointsArr[3] > 0)
		{
			skillNum = 3;

			if (wandSkill3Actor_var)
			{
				wandSkill3Actor_var->WandSkill3Activate(false);
			}

			ServerRPC_DecreaseMP(DT_SkillStruct->FindRow<FSkillsInfo>(FName("Magic3"), "")->UsedMP);

			MultiRPC_ComboAttack(skillNum);

			_player->GetCharacterMovement()->bUseControllerDesiredRotation = false;
			_player->GetCharacterMovement()->bOrientRotationToMovement = true;

			wandSkill1_Complete_var = GetWorld()->SpawnActor<AWandSkill1Actor_Completed>(wandSkill1_Complete_bp, GetActorLocation(), FRotator(0), params);

			// AOE ������
			wandSkill1_Complete_var->WandSkill1();
			
		}
		// ��ų 2 + ��Ŭ�� �� �޺���ų
		else if (_inputKey == 2 && skillPointsArr[4] > 0)
		{
			skillNum = 1;

			ServerRPC_DecreaseMP(DT_SkillStruct->FindRow<FSkillsInfo>(FName("Magic2"), "")->UsedMP);

			// 1�޺� -> 2�޺�
			MultiRPC_ComboAttack(skillNum);

			wandSkill1_Combo_var = GetWorld()->SpawnActor<AWandSkill1Actor_Combo>(wandSkill1_Combo_bp, _spawnLoc, FRotator(0), params);

			//MultiRPC_ComboAttack(_currentWeaponNum, _wandCurrentSkillNum);

			if (wandSkill1_Combo_var != nullptr)
			{
				wandSkill1_Combo_var->WandSkill1_Combo();
			}
			//wandSkill2_Combo_var->WandSkill2_Combo();
		}
		// ��ų 3 + ��Ŭ�� �� �޺���ų	(���� ��ų 1 ������ ���������� ���� �̸� �ٲٱ� �����Ƽ� 3������ �ű�)
		else if (_inputKey == 3 && skillPointsArr[5] > 0)
		{
			skillNum = 1;

			ServerRPC_DecreaseMP(DT_SkillStruct->FindRow<FSkillsInfo>(FName("Magic1"), "")->UsedMP);


			// 2����ų -> 1�޺�
			MultiRPC_Skill2(currentWeaponNum);

			FVector curLoc = GetActorLocation();

			// �̰� ������ ����
			wand->ServerRPC_WandSkill2(curLoc, this);

			
		}
	}
	
	
	//ClientRPC_ComboAttack(currentWeaponNum, wandCurrentSkillNum);
}

void AChallengersCharacter::MultiRPC_ComboAttack_Implementation(int32 _skillNum)
{
	//UE_LOG(LogTemp, Warning, TEXT("_wandCurrentSkillNum : %d"), _wandCurrentSkillNum);
	if (currentWeaponNum == 0)
	{
		switch (_skillNum)
		{
		case 1:
			PlayMyMontage(SwordSkill1_Combo_Montage);
			break;
		case 2:
			PlayMyMontage(SwordSkill2_Combo_Montage);
			break;
		case 3:
			PlayMyMontage(SwordSkill3_Combo_Montage);
			break;
		default:
			break;
		}
	}
	else if (currentWeaponNum == 1)
	{

		switch (_skillNum)
		{
		case 1:
			PlayMyMontage(WandSkill1_Combo_Montage);
			UE_LOG(LogTemp, Warning, TEXT("11111111111111"));
			break;
		case 2:
			PlayMyMontage(WandSkill2_Combo_Montage);
			UE_LOG(LogTemp, Warning, TEXT("2222222222222"));
			break;
		case 3:
			PlayMyMontage(WandSkill1_Complete_Montage);
			UE_LOG(LogTemp, Warning, TEXT("333333333333"));
			break;
		default:
			break;
		}
	}
	else if (currentWeaponNum == 2)
	{

	}
	
}

void AChallengersCharacter::WandSkill3_Ready()
{
	FVector start = GetActorLocation();
	FVector end = start + GetActorForwardVector() * 1000;
	AChallengersCharacter* playerChar = this;

	FRotator playerViewRot = pc->GetControlRotation();

	// ����Ʈ�� �÷��̾� ���� �������� ��� ȸ���ϰԲ�
	newRot = UKismetMathLibrary::MakeRotFromZX(GetActorUpVector(), playerViewRot.Vector());

	ServerRPC_WandSkill3_Ready(start, end, playerChar, newRot);
}

void AChallengersCharacter::ServerRPC_WandSkill3_Ready_Implementation(FVector _start, FVector _end, AChallengersCharacter* _playerChar, FRotator _newRot)
{
	// ó���� �޺��� �� ���� ������ false false,
	// �޺� ���� �޺� �ִ� ������������ true, true
	// �޺� �ִ� ������ false, true
	// �ᱹ 3�� Ű�� ���� �ٽ� false false
	if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(WandSkill1_Complete_Montage) || bWandComboPlaying)
	{
		bWandComboPlaying = true;
		return;
	}

	if (!GetMesh()->GetAnimInstance()->Montage_IsPlaying(WandSkill3_Start_Montage) && !GetMesh()->GetAnimInstance()->Montage_IsPlaying(WandSkill3_Loop_Montage))
	{
		MultiRPC_WandSkill3_Ready();
	}

	UE_LOG(LogTemp, Warning, TEXT("bSpawnWand3 : %d"), bSpawnWand3);
	UE_LOG(LogTemp, Warning, TEXT("bSpawnWand3 cnt: %d"), cnt);
	
	// AM_WandSkill3_2 �� SpawnWand3 notify ������ �����ؾ� �տ��� ������ ��ó�� ����
	if (cnt == 0 && bSpawnWand3)
	{
		cnt++;


		if (wandSkill3Actor_var)
		{
			wandSkill3Actor_var->SetActorTransform(Part10->GetSocketTransform("LeftWeapon"));
			wandSkill3Actor_var->WandSkill3Activate(true);

		}
	}
		
	if (wandSkill3Actor_var != nullptr)
	{
		ServerRPC_SetSkillPointsDmgPercent(5);
		wandSkill3Actor_var->SetActorLocation(Part10->GetSocketLocation("LeftWeapon"));
		wandSkill3Actor_var->SetActorRotation(_newRot);
		wandSkill3Actor_var->WandSkill3(_start, _end, _playerChar);
	}

	
}

//void AChallengersCharacter::ClientRPC_WandSkill3_Ready_Implementation(bool bSpawnWand3_)
//{
//	// �÷��̾ ���� ����
//	//FRotator playerViewRot = GetWorld()->GetFirstPlayerController()->GetControlRotation();
//	if (pc)
//	{
//		
//
//		MultiRPC_WandSkill3_Ready(WandSkill3_Loop_Montage, bSpawnWand3_, newRot);
//	}
//}

void AChallengersCharacter::MultiRPC_WandSkill3_Ready_Implementation()
{
	PlayMyMontage(WandSkill3_Loop_Montage);
}

void AChallengersCharacter::SpawnArrowBasic()
{
	FVector spawnLoc = GetActorLocation() + GetActorForwardVector() * 50.0f;
	FRotator spawnRot = GetActorRotation();

	ServerRPC_SpawnArrowBasic(spawnLoc, spawnRot, this);
}

void AChallengersCharacter::ServerRPC_SpawnArrowBasic_Implementation(FVector _spawnLoc, FRotator _spawnRot, AChallengersCharacter* _this)
{
	FActorSpawnParameters params;
	gunBasicActor = GetWorld()->SpawnActor<AGun>(gunBasicActor_bp, _spawnLoc, _spawnRot, params);

	if (gunBasicActor)
	{
		gunBasicActor->weaponAttackPower = _this->currentWeaponStat[2];
	}
}

void AChallengersCharacter::SpawnWand3()
{
	ServerRPC_SpawnWand3();
}

void AChallengersCharacter::ServerRPC_SpawnWand3_Implementation()
{
	//UE_LOG(LogTemp, Warning, TEXT("cnt : %d"), cnt);
	ServerRPC_DecreaseMP(DT_SkillStruct->FindRow<FSkillsInfo>(FName("Magic1"), "")->UsedMP);

	if (cnt == 0 && bSpawnWand3 == false)
	{
		bSpawnWand3 = true;
		UE_LOG(LogTemp, Warning, TEXT("cnt++ : %d"), cnt);
	}
}

void AChallengersCharacter::SpawnArrow1()
{
	/*FActorSpawnParameters params;

	GetWorld()->SpawnActor<AArrow>(arrow_bp, GetActorLocation() + GetActorForwardVector() * 200.0f, GetActorRotation(), params)*/

	ServerRPC_DecreaseMP(DT_SkillStruct->FindRow<FSkillsInfo>(FName("Gun1"), "")->UsedMP);


	if (arrow1Pool.Num() > 0)
	{

		FVector spawnLoc = GetActorLocation() + GetActorForwardVector() * 200.0f;
		FRotator spawnRot = GetActorRotation();

		UE_LOG(LogTemp, Warning, TEXT("_spawnLoc : %f %f %f"), spawnLoc.X, spawnLoc.Y, spawnLoc.Z);

		SetOwner(GetWorld()->GetFirstPlayerController());

		ServerRPC_SpawnArrow1(spawnLoc, spawnRot);

	}

	
}

void AChallengersCharacter::ServerRPC_SpawnArrow1_Implementation(FVector _spawnLoc, FRotator _spawnRot)
{
	if (arrow1Pool.Num() > 0)
	{
		ABowSkill1Actor* arrow1 = arrow1Pool[0];

		// ��ų����Ʈ�� ���� ������ Ÿ�ݷ�
		arrow1->damagePercent = 1 + 0.1 * skillPointsArr[6];

		// bow �� ������ �� �����ϱ� �����ɶ� ��ȭ�� ���ݷ� ���� bowSkill1Actor �� �Ѱ���
		arrow1->weaponAttackPower = currentWeaponStat[2];

		arrow1->ArrowActivate(true);
		arrow1->SetActorLocation(_spawnLoc);
		arrow1->SetActorRotation(_spawnRot);

		UE_LOG(LogTemp, Warning, TEXT("ServerRPC _spawnLoc : %f %f %f"), _spawnLoc.X, _spawnLoc.Y, _spawnLoc.Z);

		arrow1Pool.RemoveAt(0);
		UE_LOG(LogTemp, Warning, TEXT("remove arrow1"));
	}
}

float AChallengersCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float temp = UKismetMathLibrary::Clamp(HP - Damage, 0, 1000);
	ServerRPC_DecreaseHP(Damage);

	if (HP <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Died"), HP);

		if (pc)
		{
			pc->DisableInput(pc);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("DecreaseHP : NO PC!!!!!!!"));
		}

	}

	return temp;
}

void AChallengersCharacter::ServerRPC_DecreaseHP_Implementation(float _Damage)
{

	if (HP > 0)
	{
		HP = UKismetMathLibrary::Clamp(HP - _Damage, 0, 1000);
		UE_LOG(LogTemp, Warning, TEXT("Player HP : %d"), HP);

		ClientRPC_DecreaseHP(HP);
	}
	
	
}

void AChallengersCharacter::ClientRPC_DecreaseHP_Implementation(int32 _HP)
{
	// �� Ŭ���̾�Ʈ�鿡�� HP �� ������Ʈ
	if (pc && pc->IsLocalController())
	{
		pc->mainplayerWidget->HP_Update(_HP);
	}
}

void AChallengersCharacter::MultiRPC_DecreaseHP_Implementation()
{
	// �״� �ִϸ��̼�
	PlayMyMontage(Die_montage);
}

void AChallengersCharacter::ServerRPC_DecreaseMP_Implementation(int32 _UsedMP)
{
	MP = UKismetMathLibrary::Clamp(MP - _UsedMP, 0, 1000);
	UE_LOG(LogTemp, Warning, TEXT("%d"), MP);
	
	ClientRPC_DecreaseMP(MP);
}


void AChallengersCharacter::ClientRPC_DecreaseMP_Implementation(int32 _MP)
{
	// �� Ŭ���̾�Ʈ�鿡�� MP �� ������Ʈ
	if (pc && pc->IsLocalController())
	{
		pc->mainplayerWidget->MP_Update(_MP);

	}

}

void AChallengersCharacter::ServerRPC_IncreaseMP_Implementation(int32 _IncreasedMP)
{
	MP = FMath::Clamp(MP + _IncreasedMP, 0, 1000);	// �⺻ ���� �� ������ MP ������Ŵ(��Ÿ ���� ������ bSkillUsing == false �϶���)
	
	ClientRPC_IncreaseMP(_IncreasedMP);
}

void AChallengersCharacter::ClientRPC_IncreaseMP_Implementation(int32 _MP)
{
	// �� Ŭ���̾�Ʈ�鿡�� MP �� ������Ʈ
	if (pc && pc->IsLocalController())
	{
		pc->mainplayerWidget->MP_Update(_MP);
	}
}

void AChallengersCharacter::PlayMyMontage(UAnimMontage* montage)
{
	GetMesh()->GetAnimInstance()->Montage_Play(montage);
	Part1->SetLeaderPoseComponent(GetMesh());
	Part2->SetLeaderPoseComponent(GetMesh());
	Part3->SetLeaderPoseComponent(GetMesh());
	Part4->SetLeaderPoseComponent(GetMesh());
	Part5->SetLeaderPoseComponent(GetMesh());
	Part6->SetLeaderPoseComponent(GetMesh());
	Part7->SetLeaderPoseComponent(GetMesh());
	Part8->SetLeaderPoseComponent(GetMesh());
	Part9->SetLeaderPoseComponent(GetMesh());
	Part10->SetLeaderPoseComponent(GetMesh());
	Part11->SetLeaderPoseComponent(GetMesh());
	Part12->SetLeaderPoseComponent(GetMesh());
	Part13->SetLeaderPoseComponent(GetMesh());
	Part14->SetLeaderPoseComponent(GetMesh());
	Part15->SetLeaderPoseComponent(GetMesh());
	Part16->SetLeaderPoseComponent(GetMesh());
	Part17->SetLeaderPoseComponent(GetMesh());

}

void AChallengersCharacter::OnSwordBsMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (!bInterrupted)
	{
		bCanSwordBasicAttack = true;
	}
}

void AChallengersCharacter::OnWandBsMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (!bInterrupted)
	{
		bCanWandBasicAttack = true;
	}
}


void AChallengersCharacter::LoadPlayer()
{
	if (OG != nullptr)
	{
		OG->LoadChacraterCustom();
		bBoy = OG->LoadbIsMan;
		FinalMeshArr = OG->LoadFinalMeshArr;
		playerName = OG->LoadPlayerName;
		ClothesColorNum = OG->LoadClothesColorNumber;
		HairColorNum = OG->LoadHairColorNumber;
		bGlove = OG->LoadbGlove;
	}
	UE_LOG(LogTemp, Warning, TEXT("LoadChacraterCustom :: bBoy: %d"), bBoy);

	//for (int32 i = 0; i < FinalMeshArr.Num(); i++)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("FinalMeshArr : %s"), FinalMeshArr[i]);
	//}
	UE_LOG(LogTemp, Warning, TEXT("ClothesColorNum : %d"), ClothesColorNum);
	UE_LOG(LogTemp, Warning, TEXT("HairColorNum : %d"), HairColorNum);

	UE_LOG(LogTemp, Warning, TEXT("bGlove : %d"), bGlove);




	/*if (bBoy == true)
	{
		SelectBoy(bBoy, FinalMeshArr, ClothesColorNum, HairColorNum, bGlove, this);
	}
	else
	{
		SelectGirl(bBoy, FinalMeshArr, ClothesColorNum, HairColorNum, bGlove, this);
	}*/

	SetOwner(GetWorld()->GetFirstPlayerController());

	ServerRPC_LoadPlayer(bBoy, FinalMeshArr, playerName, ClothesColorNum, HairColorNum, bGlove, this);


	/*if (!HasAuthority())
	{
		SetOwner(GetWorld()->GetFirstPlayerController());

		ServerRPC_LoadPlayer(bBoy, FinalMeshArr, ClothesColorNum, HairColorNum, bGlove, this);
	}*/
	LoadPlayerInfo();
	//ServerRPC_LoadPlayerInfo();
	LoadSkillPoints();
	//ServerRPC_LoadSkillPoints();

	SetOwner(GetWorld()->GetFirstPlayerController());
	ServerRPC_SetNickName();

	// ���� ����Ʈ ǥ�� ����
	if(IsLocallyControlled())
	{
		ServerRPC_ShowEffect();
	}
	
}

void AChallengersCharacter::ServerRPC_LoadPlayer_Implementation(bool _bBoy, const TArray<FName>& _FinalMeshArr, const FString& _playerName, int _ClothesColorNum, int _HairColorNum, bool _bGlove, AChallengersCharacter* _player)
{
	bBoy = _bBoy;
	FinalMeshArr = _FinalMeshArr;
	playerName = _playerName;
	ClothesColorNum = _ClothesColorNum;
	HairColorNum = _HairColorNum;
	bGlove = _bGlove;
	_player_ = _player;
	
	UE_LOG(LogTemp, Warning, TEXT("ServerRPC : _player_ : %s"), *_player_->GetName());

	if (bBoy == true)
	{
		BodyDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/GJY/MBodyDataTable.MBodyDataTable'"));
		HairColorDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/GJY/HairColorDataTable.HairColorDataTable'"));
		ClothesDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/GJY/ClothesColorDataTable_M.ClothesColorDataTable_M'"));
		SkinDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/GJY/SkinDataTable.SkinDataTable'"));

		FName ClothesNum = FName(*FString::FromInt(ClothesColorNum));
		FName HairNum = FName(*FString::FromInt(HairColorNum));

		GetMesh()->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[17], "")->SkeletalBody);
		Part1->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[0], "")->SkeletalBody);
		Part2->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[1], "")->SkeletalBody);
		Part3->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[2], "")->SkeletalBody);
		Part4->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[3], "")->SkeletalBody);
		Part5->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[4], "")->SkeletalBody);
		Part6->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[5], "")->SkeletalBody);
		Part7->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[6], "")->SkeletalBody);
		Part8->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[7], "")->SkeletalBody);
		Part9->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[8], "")->SkeletalBody);
		Part10->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[9], "")->SkeletalBody);
		Part11->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[10], "")->SkeletalBody);
		Part12->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[11], "")->SkeletalBody);
		Part13->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[12], "")->SkeletalBody);
		Part14->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[13], "")->SkeletalBody);
		Part15->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[14], "")->SkeletalBody);
		Part16->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[15], "")->SkeletalBody);
		Part17->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[16], "")->SkeletalBody);

		Part4->SetMaterial(0, HairColorDataTable->FindRow<FMaterialType>(HairNum, "")->MaterialInst);
		Part5->SetMaterial(0, HairColorDataTable->FindRow<FMaterialType>(HairNum, "")->MaterialInst);

		Part2->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		Part3->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		Part6->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		Part7->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		Part8->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		Part9->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		Part11->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		Part12->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		Part13->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		Part14->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		Part15->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		Part16->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		Part17->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);

		if (bGlove == true)
		{
			Part8->SetMaterial(0, SkinDataTable->FindRow<FMaterialType>(FName("1"), "")->MaterialInst);
		}
	}
	else{
		if (bBoy == false)
		{
			BodyDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/GJY/FBodyDataTable.FBodyDataTable'"));
			HairColorDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/GJY/HairColorDataTable.HairColorDataTable'"));
			ClothesDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/GJY/ClothesColorDataTable_F.ClothesColorDataTable_F'"));
			SkinDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/GJY/SkinDataTable.SkinDataTable'"));
		}
		FName ClothesNum = FName(*FString::FromInt(ClothesColorNum));
		FName HairNum = FName(*FString::FromInt(HairColorNum));


		GetMesh()->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[17], "")->SkeletalBody);
		Part1->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[0], "")->SkeletalBody);
		Part2->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[1], "")->SkeletalBody);
		Part3->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[2], "")->SkeletalBody);
		Part4->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[3], "")->SkeletalBody);
		Part5->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[4], "")->SkeletalBody);
		Part6->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[5], "")->SkeletalBody);
		Part7->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[6], "")->SkeletalBody);
		Part8->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[7], "")->SkeletalBody);
		Part9->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[8], "")->SkeletalBody);
		Part10->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[9], "")->SkeletalBody);
		Part11->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[10], "")->SkeletalBody);
		Part12->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[11], "")->SkeletalBody);
		Part13->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[12], "")->SkeletalBody);
		Part14->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[13], "")->SkeletalBody);
		Part15->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[14], "")->SkeletalBody);
		Part16->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[15], "")->SkeletalBody);
		Part17->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[16], "")->SkeletalBody);

		Part4->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		Part5->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		Part6->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		Part7->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		Part8->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		Part9->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		Part10->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		Part11->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		Part12->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		Part13->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		Part14->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		Part17->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);

		Part2->SetMaterial(0, HairColorDataTable->FindRow<FMaterialType>(HairNum, "")->MaterialInst);
		Part3->SetMaterial(0, HairColorDataTable->FindRow<FMaterialType>(HairNum, "")->MaterialInst);

		if (bGlove == true)
		{
			Part9->SetMaterial(0, SkinDataTable->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
			Part10->SetMaterial(0, SkinDataTable->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
		}
	}

	

}

void AChallengersCharacter::Onrep_LoadPlayers()
{
	if (bBoy == true)
	{
		BodyDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/GJY/MBodyDataTable.MBodyDataTable'"));
		HairColorDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/GJY/HairColorDataTable.HairColorDataTable'"));
		ClothesDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/GJY/ClothesColorDataTable_M.ClothesColorDataTable_M'"));
		SkinDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/GJY/SkinDataTable.SkinDataTable'"));

		FName ClothesNum = FName(*FString::FromInt(ClothesColorNum));
		FName HairNum = FName(*FString::FromInt(HairColorNum));

		UE_LOG(LogTemp, Warning, TEXT("Onrep : _player_ : %s"), *_player_->GetName());


		_player_->GetMesh()->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[17], "")->SkeletalBody);
		_player_->Part1->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[0], "")->SkeletalBody);
		_player_->Part2->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[1], "")->SkeletalBody);
		_player_->Part3->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[2], "")->SkeletalBody);
		_player_->Part4->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[3], "")->SkeletalBody);
		_player_->Part5->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[4], "")->SkeletalBody);
		_player_->Part6->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[5], "")->SkeletalBody);
		_player_->Part7->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[6], "")->SkeletalBody);
		_player_->Part8->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[7], "")->SkeletalBody);
		_player_->Part9->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[8], "")->SkeletalBody);
		_player_->Part10->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[9], "")->SkeletalBody);
		_player_->Part11->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[10], "")->SkeletalBody);
		_player_->Part12->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[11], "")->SkeletalBody);
		_player_->Part13->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[12], "")->SkeletalBody);
		_player_->Part14->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[13], "")->SkeletalBody);
		_player_->Part15->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[14], "")->SkeletalBody);
		_player_->Part16->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[15], "")->SkeletalBody);
		_player_->Part17->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[16], "")->SkeletalBody);

		_player_->Part4->SetMaterial(0, HairColorDataTable->FindRow<FMaterialType>(HairNum, "")->MaterialInst);
		_player_->Part5->SetMaterial(0, HairColorDataTable->FindRow<FMaterialType>(HairNum, "")->MaterialInst);

		_player_->Part2->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		_player_->Part3->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		_player_->Part6->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		_player_->Part7->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		_player_->Part8->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		_player_->Part9->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		_player_->Part11->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		_player_->Part12->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		_player_->Part13->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		_player_->Part14->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		_player_->Part15->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		_player_->Part16->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		_player_->Part17->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);

		if (bGlove == true)
		{
			_player_->Part8->SetMaterial(0, SkinDataTable->FindRow<FMaterialType>(FName("1"), "")->MaterialInst);
		}
	}
	else {
		if (bBoy == false)
		{
			BodyDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/GJY/FBodyDataTable.FBodyDataTable'"));
			HairColorDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/GJY/HairColorDataTable.HairColorDataTable'"));
			ClothesDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/GJY/ClothesColorDataTable_F.ClothesColorDataTable_F'"));
			SkinDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/GJY/SkinDataTable.SkinDataTable'"));
		}
		FName ClothesNum = FName(*FString::FromInt(ClothesColorNum));
		FName HairNum = FName(*FString::FromInt(HairColorNum));


		_player_->GetMesh()->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[17], "")->SkeletalBody);
		_player_->Part1->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[0], "")->SkeletalBody);
		_player_->Part2->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[1], "")->SkeletalBody);
		_player_->Part3->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[2], "")->SkeletalBody);
		_player_->Part4->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[3], "")->SkeletalBody);
		_player_->Part5->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[4], "")->SkeletalBody);
		_player_->Part6->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[5], "")->SkeletalBody);
		_player_->Part7->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[6], "")->SkeletalBody);
		_player_->Part8->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[7], "")->SkeletalBody);
		_player_->Part9->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[8], "")->SkeletalBody);
		_player_->Part10->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[9], "")->SkeletalBody);
		_player_->Part11->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[10], "")->SkeletalBody);
		_player_->Part12->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[11], "")->SkeletalBody);
		_player_->Part13->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[12], "")->SkeletalBody);
		_player_->Part14->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[13], "")->SkeletalBody);
		_player_->Part15->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[14], "")->SkeletalBody);
		_player_->Part16->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[15], "")->SkeletalBody);
		_player_->Part17->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[16], "")->SkeletalBody);

		_player_->Part4->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		_player_->Part5->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		_player_->Part6->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		_player_->Part7->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		_player_->Part8->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		_player_->Part9->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		_player_->Part10->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		_player_->Part11->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		_player_->Part12->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		_player_->Part13->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		_player_->Part14->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);
		_player_->Part17->SetMaterial(0, ClothesDataTable->FindRow<FMaterialType>(ClothesNum, "")->MaterialInst);

		_player_->Part2->SetMaterial(0, HairColorDataTable->FindRow<FMaterialType>(HairNum, "")->MaterialInst);
		_player_->Part3->SetMaterial(0, HairColorDataTable->FindRow<FMaterialType>(HairNum, "")->MaterialInst);

		if (bGlove == true)
		{
			_player_->Part9->SetMaterial(0, SkinDataTable->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
			_player_->Part10->SetMaterial(0, SkinDataTable->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
		}
	}

}

void AChallengersCharacter::OnRepWeaponInitVisible()
{
	currentWeapon[0]->SetVisibility(true);
	currentWeapon[1]->SetVisibility(false);
	currentWeapon[2]->SetVisibility(false);
}

void AChallengersCharacter::SetPlayerExpAndLevel()
{
	if (IsLocallyControlled())
	{
		if (playerLevel < maxPlayerLevel)
		{
			AOurGameStateBase* gs = Cast<AOurGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));

			// ������ Ŭ�����ߴٸ�
			// ������ ���� enemyCost ��ŭ ����ġ ����
			playerCurrentExp += OG->createDunCost;
			//playerCurrentExp += 900;

			// ������ ���� enemyCost ��ŭ ��� ����
			playerGold += OG->createDunCost;
			//playerGold += 500;

			UE_LOG(LogTemp, Warning, TEXT("playerCurrentExp : %d"), playerCurrentExp);

			// ���� �� ����ġ ���� ������
			if (playerCurrentExp >= playerMaxExp)
			{
				// ������
				playerLevel++;
				// ����ġ ����
				playerCurrentExp %= playerMaxExp;
				// �������� �ִ� ����ġ�� ����
				playerMaxExp *= 1.5f;

				ServerRPC_SetEnemyCost();
				ServerRPC_SetTotalSkillPoints();
			}

			auto* controller = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());

			if (controller)
			{
				if (controller->IsLocalController())
				{
					if (controller->mainplayerWidget)
					{
						controller->mainplayerWidget->EXP_Update(this);
					}
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("PlayerExp No Controller!!!!!!!!!!"));
			}



			// ���� Ŭ���� ������ ����
			OG->SavePlayerInfoData(playerName, playerLevel, playerGold, playerCurrentExp, playerMaxExp, enemyCost, weaponLevel, currentWeaponStat, nextWeaponStat, upgWeaponNeedGold);

			UE_LOG(LogTemp, Warning, TEXT("SavePlayerInfoData::playerLevel : %d"), playerLevel);
			UE_LOG(LogTemp, Warning, TEXT("SavePlayerInfoData::playerGold : %d"), playerGold);
			UE_LOG(LogTemp, Warning, TEXT("SavePlayerInfoData::playerCurrentExp : %d"), playerCurrentExp);
			UE_LOG(LogTemp, Warning, TEXT("SavePlayerInfoData::playerMaxExp : %d"), playerMaxExp);
			UE_LOG(LogTemp, Warning, TEXT("SavePlayerInfoData::enemyCost : %d"), enemyCost);
		
		}
	}
	//ServerRPC_SetPlayerExpAndLevel();
}

void AChallengersCharacter::ServerRPC_SetPlayerExpAndLevel_Implementation()
{
	

		// �ε�
		//LoadPlayerInfo();


	
}

void AChallengersCharacter::SetEnemyCost()
{
	
	
}

void AChallengersCharacter::ServerRPC_SetEnemyCost_Implementation()
{
	// 1���� ���������� 100�� ��
	enemyCost += plusCost;

	// 10������ �߰��� 50 �� �� ( = 150)
	if (playerLevel % 10 == 0 && !(playerLevel == maxPlayerLevel))
	{
		enemyCost += plusCost / 2;
	}

	// 40����(����)�̸� 100 �� �� ( = 200)
	if (playerLevel == maxPlayerLevel)
	{
		enemyCost += plusCost;
	}

	UE_LOG(LogTemp, Warning, TEXT("enemyCost : %d"), enemyCost);
}

void AChallengersCharacter::SetTotalSkillPoints()
{
	
}

void AChallengersCharacter::ServerRPC_SetTotalSkillPoints_Implementation()
{
	if (playerLevel % 2 == 0)
	{
		// 2�������� 1����Ʈ�� ��
		canUseSkillPoint++;

		// 10�������� 2����Ʈ�� ��
		if (playerLevel == 10)
			canUseSkillPoint += 1;
		// 40����(����)�� ��� 3����Ʈ ��
		else if (playerLevel == 40)
			canUseSkillPoint += 2;
	}
}

void AChallengersCharacter::UpgradeWeapon()
{
	ServerRPC_UpgradeWeapon();
}

void AChallengersCharacter::ServerRPC_UpgradeWeapon()
{
	if (pc->IsLocalController())
	{
		// ���� â�� Į â�϶�
		if (pc->upgradeWeaponWidget->currentSwitcherIndex == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("UpgradeWeapon11111"));

			// ���� ���� 20���� �۰�, �÷��̾ �����ϰ� �ִ� ��尡 ��ȭ�� �ʿ��� ��庸�� ���ų� �������� ��ȭ ����
			if (weaponLevel[0] < 20 && playerGold >= upgWeaponNeedGold[0])
			{
				UE_LOG(LogTemp, Warning, TEXT("UpgradeWeapon22222"));

				// Į ������
				weaponLevel[0] = weaponLevel[0] + 1;

				// �÷��̾� ���� ��� ����
				playerGold -= upgWeaponNeedGold[0];

				// Į ��ȭ�� �ʿ��� ���� ���� ������ (��ġ �ٲٷ��� 1.5�� �ٲ��ָ� ��)
				upgWeaponNeedGold[0] = round(upgWeaponNeedGold[0] * 1.5f);

				// ���� ���ݷ� += 1.414 * n����(n��) ---- ���� default ���ݷ� : 30
				currentWeaponStat[0] = nextWeaponStat[0];

				// ���� ��ȭ�ϸ� ��ȭ�� ���ݷ� ���� sword �� �Ѱ���
				sword->weaponAttackPower = currentWeaponStat[0];
				UE_LOG(LogTemp, Warning, TEXT("sword->weaponAttackPower : %d"), sword->weaponAttackPower);

				// 32 = 30 + 1.414 * 2
				nextWeaponStat[0] = round(30 + pow(sqrt(2), weaponLevel[0]));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("S_No gold"));
			}
		}
		// ���� â�� ���� â�϶�
		else if (pc->upgradeWeaponWidget->currentSwitcherIndex == 1)
		{
			// ���� ���� 20���� ���� ���� ��ȭ ����
			if (weaponLevel[1] < 20 && playerGold >= upgWeaponNeedGold[1])
			{
				// ������ ������
				weaponLevel[1] = weaponLevel[1] + 1;

				// �÷��̾� ���� ��� ����
				playerGold -= upgWeaponNeedGold[1];

				// ������ ��ȭ�� �ʿ��� ���� ���� ������ (��ġ �ٲٷ��� 1.5�� �ٲ��ָ� ��)
				upgWeaponNeedGold[1] = round(upgWeaponNeedGold[1] * 1.5f);

				// ���� ���ݷ� += 1.414 * n����(n��) ---- ���� default ���ݷ� : 30
				currentWeaponStat[1] = nextWeaponStat[1];

				// 32 = 30 + 1.414 * 2
				nextWeaponStat[1] = round(30 + pow(sqrt(2), weaponLevel[1]));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("W_No gold"));
			}
		}
		// ���� â�� Ȱ â�϶�
		else if (pc->upgradeWeaponWidget->currentSwitcherIndex == 2)
		{
			// ���� ���� 20���� ���� ���� ��ȭ ����
			if (weaponLevel[2] < 20 && playerGold >= upgWeaponNeedGold[2])
			{
				// Ȱ ������
				weaponLevel[2] = weaponLevel[2] + 1;

				// �÷��̾� ���� ��� ����
				playerGold -= upgWeaponNeedGold[2];

				// Ȱ ��ȭ�� �ʿ��� ���� ���� ������ (��ġ �ٲٷ��� 1.5�� �ٲ��ָ� ��)
				upgWeaponNeedGold[2] = round(upgWeaponNeedGold[2] * 1.5f);

				// ���� ���ݷ� += 1.414 * n����(n��) ---- ���� default ���ݷ� : 30
				currentWeaponStat[2] = nextWeaponStat[2];

				// 32 = 30 + 1.414 * 2
				nextWeaponStat[2] = round(30 + pow(sqrt(2), weaponLevel[2]));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("B_No gold"));
			}
		}

		// ��ȭ��ư ������ ����
		OG->SavePlayerInfoData(playerName, playerLevel, playerGold, playerCurrentExp, playerMaxExp, enemyCost, weaponLevel, currentWeaponStat, nextWeaponStat, upgWeaponNeedGold);
		
		
		//��ȭ ����Ʈ ǥ�� �Լ� ȣ��.

		UE_LOG(LogTemp, Warning, TEXT("Save :: playerName : %s, playerGold : %d, weaponLevel[0] : %d, currentWeaponStat[0] : %d, nextWeaponStat[0] : %d, upgWeaponNeedGold : %d"), *playerName, playerGold, weaponLevel[0], currentWeaponStat[0], nextWeaponStat[0], upgWeaponNeedGold[0]);

		UE_LOG(LogTemp, Warning, TEXT("Save :: playerName : %s, playerGold : %d, weaponLevel[1] : %d, currentWeaponStat[1] : %d, nextWeaponStat[1] : %d, upgWeaponNeedGold : %d"), *playerName, playerGold, weaponLevel[1], currentWeaponStat[1], nextWeaponStat[1], upgWeaponNeedGold[1]);

		UE_LOG(LogTemp, Warning, TEXT("Save :: playerName : %s, playerGold : %d, weaponLevel[2] : %d, currentWeaponStat[2] : %d, nextWeaponStat[2] : %d, upgWeaponNeedGold : %d"), *playerName, playerGold, weaponLevel[2], currentWeaponStat[2], nextWeaponStat[2], upgWeaponNeedGold[2]);

		// �ε�
		ServerRPC_LoadPlayerInfo(playerName, playerLevel, playerGold, playerCurrentExp, playerMaxExp, enemyCost, weaponLevel, currentWeaponStat, nextWeaponStat, upgWeaponNeedGold);

		sword-> UpgradeSwordEffect(weaponLevel[0]);
		wand -> UpgradeWandEffect(weaponLevel[1]);
		gun->UpgradeBowEffect(weaponLevel[2]);
	}
	
}

void AChallengersCharacter::LoadSkillPoints()
{
	// ����� ��ų ������ �ε�
	OG->LoadSkillPresetData();

	// playerName = OG->loadedSkillDataList.playerName;
	skillPointsArr = OG->loadedSkillDataList.skillPointArr;
	canUseSkillPoint = OG->loadedSkillDataList.canUseSkillPoint;
	UE_LOG(LogTemp, Warning, TEXT("LoadSkillPoints :: playerName : %s, canUseSkillPoint : %d"), *playerName, canUseSkillPoint);

	ServerRPC_LoadSkillPoints(skillPointsArr, canUseSkillPoint);
}

void AChallengersCharacter::ServerRPC_LoadSkillPoints_Implementation(const TArray<int32>& _skillPointsArr, int32 _canUseSkillPoint)
{
	skillPointsArr = _skillPointsArr;
	canUseSkillPoint = _canUseSkillPoint;

	// SkillSystemComponent �迭�� �־��ֱ� (��ų�ý��� ������ �� SkillSystemComponent���� ����)
		// SkillPoint �� 0 �̻��ΰŸ� ����(��ų�� ����ٴ� �ǹ�)
	for (int32 i = 0; i < 9; i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("skillPointsArr : %d"), skillPointsArr[i]);
	}


	for (int32 i = 0; i <= 2; i++)
	{
		if (skillPointsArr[i] > 0)
		{
			skillSystemComp->SwordSkillArr[i] = true;

			// ��ų ����Ʈ�� �������� ������ Ÿ�� up
			// ��ų ����Ʈ 1�϶� 1.1, 2�϶� 1.2 ... 10(����)�϶� 2
			sword->skillDamagePercents[i] = 1 + 0.1 * skillPointsArr[i];
		}
	}

	for (int32 i = 3; i <= 5; i++)
	{
		if (skillPointsArr[i] > 0)
		{
			skillSystemComp->WandSkillArr[i - 3] = true;
		}
	}

	for (int32 i = 6; i <= 8; i++)
	{
		if (skillPointsArr[i] > 0)
			skillSystemComp->GunSkillArr[i - 6] = true;
	}
	//ClientRPC_LoadSkillPoints(skillPointsArr, canUseSkillPoint);

	UE_LOG(LogTemp, Warning, TEXT("ServerRPC_LoadSkillPoints :: playerName : %s, canUseSkillPoint : %d"), *playerName, canUseSkillPoint);
}

void AChallengersCharacter::ClientRPC_LoadSkillPoints_Implementation(const TArray<int32>& skillPointsArr_, int32 canUseSkillPoint_)
{
	
}

void AChallengersCharacter::LoadPlayerInfo()
{
	// ����� �÷��̾� ���� �ε�
	OG->LoadPlayerInfoData();

	playerName = OG->loadedPlayerInfoDataList.playerName;
	playerLevel = OG->loadedPlayerInfoDataList.playerLevel;
	playerGold = OG->loadedPlayerInfoDataList.playerGold;
	playerCurrentExp = OG->loadedPlayerInfoDataList.playerCurrentExp;
	playerMaxExp = OG->loadedPlayerInfoDataList.playerMaxExp;
	enemyCost = OG->loadedPlayerInfoDataList.playerEnemyCost;
	weaponLevel = OG->loadedPlayerInfoDataList.weaponLevel;
	currentWeaponStat = OG->loadedPlayerInfoDataList.currentWeaponStat;
	nextWeaponStat = OG->loadedPlayerInfoDataList.nextWeaponStat;
	upgWeaponNeedGold = OG->loadedPlayerInfoDataList.upgWeaponNeedGold;


	UE_LOG(LogTemp, Warning, TEXT("LoadPlayerInfo :: playerName : %s, playerGold : %d, weaponLevel[0] : %d, currentWeaponStat[0] : %d, nextWeaponStat[0] : %d, upgWeaponNeedGold : %d"), *playerName, playerGold, weaponLevel[0], currentWeaponStat[0], nextWeaponStat[0], upgWeaponNeedGold[0]);

	UE_LOG(LogTemp, Warning, TEXT("LoadPlayerInfo :: playerName : %s, playerGold : %d, weaponLevel[1] : %d, currentWeaponStat[1] : %d, nextWeaponStat[1] : %d, upgWeaponNeedGold : %d"), *playerName, playerGold, weaponLevel[1], currentWeaponStat[1], nextWeaponStat[1], upgWeaponNeedGold[1]);

	UE_LOG(LogTemp, Warning, TEXT("LoadPlayerInfo :: playerName : %s, playerGold : %d, weaponLevel[2] : %d, currentWeaponStat[2] : %d, nextWeaponStat[2] : %d, upgWeaponNeedGold : %d"), *playerName, playerGold, weaponLevel[2], currentWeaponStat[2], nextWeaponStat[2], upgWeaponNeedGold[2]);
	if (sword) {
		sword->weaponAttackPower = currentWeaponStat[0];
	}
	else {
		sword = Cast<ASword>(swordComp->GetChildActor());
		if (sword) {
			sword->weaponAttackPower = currentWeaponStat[0];
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("No Sword. WHY?"));
		}
	}

	ServerRPC_LoadPlayerInfo(playerName, playerLevel, playerGold, playerCurrentExp, playerMaxExp, enemyCost, weaponLevel, currentWeaponStat, nextWeaponStat, upgWeaponNeedGold);

	OnRap_SetNickName();
}

void AChallengersCharacter::ServerRPC_LoadPlayerInfo_Implementation(const FString& _playerName, int32 _playerLevel, int32 _playerGold, int32 _playerCurrentExp, int32 _playerMaxExp, int32 _enemyCost, const TArray<int32>& _weaponLevel, const TArray<int32>& _currentWeaponStat, const TArray<int32>& _nextWeaponStat, const TArray<int32>& _upgWeaponNeedGold)
{
	playerName = _playerName;
	playerLevel = _playerLevel;
	playerGold = _playerGold;
	playerCurrentExp = _playerCurrentExp;
	playerMaxExp = _playerMaxExp;
	enemyCost = _enemyCost;
	weaponLevel = _weaponLevel;
	currentWeaponStat = _currentWeaponStat;
	nextWeaponStat = _nextWeaponStat;
	upgWeaponNeedGold = _upgWeaponNeedGold;

	UE_LOG(LogTemp, Warning, TEXT("ServerRPC_LoadPlayerInfo :: playerName : %s, playerGold : %d, playerCurrentExp : %d, playerMaxExp : %d, enemyCost : %d, weaponLevel[0] : %d, currentWeaponStat[0] : %d, nextWeaponStat[0] : %d, upgWeaponNeedGold : %d"), *playerName, playerGold, playerCurrentExp, playerMaxExp, enemyCost, weaponLevel[0], currentWeaponStat[0], nextWeaponStat[0], upgWeaponNeedGold[0]);

	UE_LOG(LogTemp, Warning, TEXT("ServerRPC_LoadPlayerInfo :: playerName : %s, playerGold : %d, playerCurrentExp : %d, playerMaxExp : %d, enemyCost : %d, weaponLevel[1] : %d, currentWeaponStat[1] : %d, nextWeaponStat[1] : %d, upgWeaponNeedGold : %d"), *playerName, playerGold, playerCurrentExp, playerMaxExp, enemyCost, weaponLevel[1], currentWeaponStat[1], nextWeaponStat[1], upgWeaponNeedGold[1]);

	UE_LOG(LogTemp, Warning, TEXT("ServerRPC_LoadPlayerInfo :: playerName : %s, playerGold : %d, playerCurrentExp : %d, playerMaxExp : %d, enemyCost : %d, weaponLevel[2] : %d, currentWeaponStat[2] : %d, nextWeaponStat[2] : %d, upgWeaponNeedGold : %d"), *playerName, playerGold, playerCurrentExp, playerMaxExp, enemyCost, weaponLevel[2], currentWeaponStat[2], nextWeaponStat[2], upgWeaponNeedGold[2]);
}

void AChallengersCharacter::ServerRPC_SetSkillPointsDmgPercent_Implementation(int32 index)
{
	if (skillPointsArr[index] > 0)
	{
		if (index == 3)
		{
			wandSkill1Actor->damagePercent = 1 + 0.1 * skillPointsArr[index];

			// wand �� ������ �� �����ϱ� �����ɶ� ��ȭ�� ���ݷ� ���� wandskill1Actor �� �Ѱ���
			wandSkill1Actor->weaponAttackPower = currentWeaponStat[1];
		}
		else if (index == 4)
		{
			wand->skill2Actor->damagePercent = 1 + 0.1 * skillPointsArr[index];

			//  wand �� ������ �� �����ϱ� �����ɶ� ��ȭ�� ���ݷ� ���� wandskill2Actor �� �Ѱ���
			wand->skill2Actor->weaponAttackPower = currentWeaponStat[1];
		}
		else
		{
			wandSkill3Actor_var->damagePercent = 1 + 0.1 * skillPointsArr[index];

			//  wand �� ������ �� �����ϱ� �����ɶ� ��ȭ�� ���ݷ� ���� wandskill3Actor �� �Ѱ���
			wandSkill3Actor_var->weaponAttackPower = currentWeaponStat[1];
		}
	}
	
	
}

void AChallengersCharacter::Anim_AtkEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("Skill Anim End!"));
	bSkillUsing = false;
	bSwordSkill1Using = false;
	bComboUsing = false;

	if (bSword1CanMove)
	{
		bSword1CanMove = false;
	}
	
	if (currentWeaponNum == 2)
	{
		currentBowSkillNum = -1;
	}
}




void AChallengersCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AChallengersCharacter, currentWeaponNum);
	DOREPLIFETIME(AChallengersCharacter, currentBowSkillNum);
	DOREPLIFETIME(AChallengersCharacter, swordBasicAttackCnt);
	DOREPLIFETIME(AChallengersCharacter, finalAimLoc);
	DOREPLIFETIME(AChallengersCharacter, bDashing);
	DOREPLIFETIME(AChallengersCharacter, bSkillUsing);
	DOREPLIFETIME(AChallengersCharacter, bSwordSkill1Using);
	DOREPLIFETIME(AChallengersCharacter, bComboUsing);
	DOREPLIFETIME(AChallengersCharacter, bSword1CanMove);
	DOREPLIFETIME(AChallengersCharacter, bIsWandSkill3Started);
	DOREPLIFETIME(AChallengersCharacter, bSpawnWand3);
	DOREPLIFETIME(AChallengersCharacter, bBowSkill2);
	DOREPLIFETIME(AChallengersCharacter, bSword1);
	DOREPLIFETIME(AChallengersCharacter, bSword2);
	DOREPLIFETIME(AChallengersCharacter, bSword3);
	DOREPLIFETIME(AChallengersCharacter, bWand1);
	DOREPLIFETIME(AChallengersCharacter, bWand2);
	DOREPLIFETIME(AChallengersCharacter, bWand3);
	DOREPLIFETIME(AChallengersCharacter, bBow1);
	DOREPLIFETIME(AChallengersCharacter, bBow2);
	DOREPLIFETIME(AChallengersCharacter, bBow3);
	DOREPLIFETIME(AChallengersCharacter, currentWeapon);
	DOREPLIFETIME(AChallengersCharacter, arrow2Gage);

	DOREPLIFETIME(AChallengersCharacter, MP);

	DOREPLIFETIME(AChallengersCharacter, bBoy);
	DOREPLIFETIME(AChallengersCharacter, FinalMeshArr);
	DOREPLIFETIME(AChallengersCharacter, ClothesColorNum);
	DOREPLIFETIME(AChallengersCharacter, HairColorNum);
	DOREPLIFETIME(AChallengersCharacter, bGlove);
	DOREPLIFETIME(AChallengersCharacter, _player_);

	DOREPLIFETIME(AChallengersCharacter, skillPointsArr);
	
	DOREPLIFETIME(AChallengersCharacter, playerName);
}