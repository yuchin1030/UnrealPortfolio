// Copyright Epic Games, Inc. All Rights Reserved.

#include "CassTeraCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "TestEnemyy.h"
#include "GameTimerWidget.h"
#include "MainUI.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/StaticMeshComponent.h"
#include "../../../../../../../Program Files/Epic Games/UE_5.3/Engine/Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"
#include <Grenade.h>
#include <Kismet/KismetMathLibrary.h>
#include "CassTeraPlayerController.h"
#include "PersonPlayerController.h"
#include "HidePlayer.h"
#include "StartLocation.h"
#include "EngineUtils.h"
#include "CassteraGameState.h"
#include "ResultWidget.h"
#include "ChatWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ACassTeraCharacter

ACassTeraCharacter::ACassTeraCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	characterMovement = GetCharacterMovement();

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

	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	//GetMesh()->SetupAttachment(FollowCamera);

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
	gun = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunComp"));
	gun->SetupAttachment(GetMesh());
	gun->SetRelativeLocation(FVector(6.974221, 17.777489, 3.074630));
	gun->SetRelativeRotation(FRotator(-1.104704, 63.238364, 1.899696));
}


void ACassTeraCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	gs = Cast<ACassteraGameState>(UGameplayStatics::GetGameState(GetWorld()));

	UGameplayStatics::PlaySound2D(GetWorld(), GameStartSound);
	// ��Ʈ�ѷ������� OnPossess ���� create �ϴϱ� mainUI �� ��ſ���.. ����? -> ����Բ� ���庼����
	// PossessedBy �� addmainui �־ �ȵƾ���... 
 	if (IsLocallyControlled())
 	{
		ServerRPC_AddMainUI();

		// Ÿ�̹� ���� ������ �̹� ServerRPC_DisableOutLiner �� ȣ�� �ǰ� HidePlayer �� �ε�Ǵ� ���� �߻�
		// ==> HidePlayer���� üũ �Ұ�. 
		// ���� �ε� �ð��� �˳��� �༭ HidePlayer �� ã�� �� �ְ� ��.
		FTimerHandle checkhandler;
		GetWorldTimerManager().SetTimer(checkhandler, [&]() {

			ServerRPC_DisableOutLiner();
		}, 5.0f, false);
 	}
	if(HasAuthority())
	{
		ClientRPC_DisableOutLiner();
	}
	//ServerRPC_AddTimerUI();
	auto pc = Cast<APlayerController>(Controller);
	if (pc)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer()))
		{
			// clearMappingContext�� ���� ������ �����Ǿ� �ִ� ĳ������ imc���� ���󰡴µ�..
			// RemoveMappingContext(���� ���� imc) �� ���� ���ϴ� �� �ϳ��� ������..
			// Ȥ�� ���� ������ �ִ� imc�� �������� �� ������, �����ϰ� ���� �̸��� ���� ģ���� �ִٸ� �����, ���� imc �߰��Ѵ�.
			Subsystem->RemoveMappingContext(DefaultMappingContext);
			Subsystem->AddMappingContext(DefaultMappingContext, 0);

		}
	}

	if (pc && pc->IsLocalController())
	{
		UE_LOG(LogTemp, Warning, TEXT("1111111111111111111111"));
			// �繰 ��������(10��) �� ������
			ServerRPC_ChangeMovement();
	}
	

	// ���� ���� ��ġ ����
	TArray<AActor*> actorArray;
	// TsubClass ������ BP_startLocation�� �迭�� ��´�
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), BP_startLocation, actorArray);

	// �迭�� ũ�Ⱑ 0 �̻��̶��, BP_startLocation�� �ִٴ� ���� �ȴ�
	if (actorArray.Num() > 0)
	{		
		// ���忡 �ϳ��� ��ġ�Ǿ� �����Ƿ�, �迭�� 0�� �ε����� ��ġ�� �޾ƿͼ�, �÷��̾ �����Ѵ�
		SetActorLocation(actorArray[0]->GetActorLocation());

		// ����, ���� ���� ��ġ�Ǿ� �ִٸ�, tag�� �̿��ؼ� ã�� �� �ִ�.
	}

}

void ACassTeraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

}

void ACassTeraCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}



//////////////////////////////////////////////////////////////////////////
// Input

void ACassTeraCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACassTeraCharacter::Move);
		//EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ACassTeraCharacter::MoveFin);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACassTeraCharacter::Look);

		// Fire
		EnhancedInputComponent->BindAction(ia_fire, ETriggerEvent::Started, this, &ACassTeraCharacter::Fire);
		EnhancedInputComponent->BindAction(ia_fire, ETriggerEvent::Completed, this, &ACassTeraCharacter::FireFin);

		// Throw
		EnhancedInputComponent->BindAction(ia_throw, ETriggerEvent::Started, this, &ACassTeraCharacter::Throw);
		EnhancedInputComponent->BindAction(ia_throw, ETriggerEvent::Completed, this, &ACassTeraCharacter::ThrowFinish);

		// ä��
		EnhancedInputComponent->BindAction(ia_chat, ETriggerEvent::Started, this, &ACassTeraCharacter::OnIAChat);
		EnhancedInputComponent->BindAction(ia_chatEnter, ETriggerEvent::Started, this, &ACassTeraCharacter::OnIAChatEnter);

	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ACassTeraCharacter::Move(const FInputActionValue& Value)
{
	//bMoving = true;

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

void ACassTeraCharacter::MoveFin(const FInputActionValue& Value)
{
	//bMoving = false;
}

void ACassTeraCharacter::Look(const FInputActionValue& Value)
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

void ACassTeraCharacter::AddMainUI()
{
	// ���� �����ϴ� ���ΰ��� UI�� �����ϰ�ʹ�.
	//MyController = Cast<ACassTeraPlayerController>(Controller);
	auto* pc = Cast<APersonPlayerController>(Controller);

	//	gameTimerwidget = Cast<UGameTimerWidget>(CreateWidget(GetWorld(), WBP_gameTimerWidget));
	/*if (pc && pc->mainUI)
	{
		mainUI = pc->mainUI;
		mainUI->AddToViewport();
		UE_LOG(LogTemp, Error, TEXT("main ui viewport"));

	}*/

	if (IsLocallyControlled())
	{
		mainUI = Cast<UMainUI>(CreateWidget(GetWorld(), WBP_mainUI));
		mainUI->AddToViewport();
		UE_LOG(LogTemp, Error, TEXT("Create MainUI"));
	}

	// ä�� �߰�
	if (nullptr == pc->chatUI)
	{
		pc->chatUI = Cast<UChatWidget>(CreateWidget(GetWorld(), Chat_BP));
		pc->chatUI->AddToViewport();
	}
	chatUI = pc->chatUI;
}

void ACassTeraCharacter::Fire(const FInputActionValue& Value)
{
	// ��Ÿ�� ����ź ���� �Ŀ� �� �� ������(bThrowing�� true ���·� ��), 
	// --> ����ź 0�� �����̸鼭 bThrowing�� true �� bThrowing = false �� ������ �������
	if (grenadeCount <= 0 && bThrowing)
	{
		bThrowing = false;
	}

	if (bThrowing || bFiring || false == bGameStart)
		return;

	bFiring = true;

	ServerRPC_Fire();
}

void ACassTeraCharacter::FireFin(const FInputActionValue& Value)
{
	bFiring = false;
}

// ����� ����
void ACassTeraCharacter::ServerRPC_Fire_Implementation()
{
	// �� ��鼭 ����ź ���ÿ� ���� ���ϰ� �ϴ� ����

	FHitResult HitInfo;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	FVector start = FollowCamera->GetComponentLocation();
	FVector end = start + FollowCamera->GetComponentRotation().Vector() * 1000.0f;

	bool bFire = GetWorld()->LineTraceSingleByChannel(HitInfo, start, end, ECC_Visibility, params);

	MultiRPC_Fire(HitInfo, bFire);
	//PlayAnimMontage(FireMontage);

	if (bFire)
	{
		//DrawDebugLine(GetWorld(), start, end, FColor::Red, 0, 2);
		//DrawDebugSphere(GetWorld(), HitInfo.Location, 10, 10, FColor::Green, 0, 2);
		UE_LOG(LogTemp, Warning, TEXT("FIRE"));

		// enemy �� ������
		if (HitInfo.GetActor()->IsA<AHidePlayer>())
		{
			enemyPlayer = Cast<AHidePlayer>(HitInfo.GetActor());

			// ���ʹ� ������ -1
			enemyPlayer->ServerRPC_Damaged();
			UE_LOG(LogTemp, Warning, TEXT("ENEMY"));


			// ������
			if (enemyPlayer->currentHP == 0)
			{
// 				enemyPlayer->ServerRPC_Die();
				ServerRPC_KillUI();
			}
		}
		else
		{

			// enemy �ƴϸ� �����̹���
			ServerRPC_WorngShot();
			
			// ���� Ŭ���ؼ� �ð� ���� ���� ������ ����
			if (gs->bDecreasing)
				return;
			
			// enemy �ƴϸ� �ð� ����
			gs->ServerRPC_DecreaseTime();

			/*for (TActorIterator<AHidePlayer> it(GetWorld()); it; ++it)
			{
				enemyPlayer = *it;
				enemyPlayer->ServerRPC_WrongShot();
			}*/
				//NotEnemyResult();	
		}
	}
}

void ACassTeraCharacter::MultiRPC_Fire_Implementation(FHitResult HitInfo, bool bFire)
{

	PlayAnimMontage(FireMontage);
	if (gunShot)
	{

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), gunShot,GetActorLocation());
	}

}


void ACassTeraCharacter::ServerRPC_IMC_Implementation()
{
	MultiRPC_IMC();
}

void ACassTeraCharacter::MultiRPC_IMC_Implementation()
{
	if (IsLocallyControlled())
	{
		/*if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				Subsystem->ClearAllMappings();
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}*/
		auto pc = Cast<APlayerController>(Controller);
		if (pc)
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer()))
			{
				Subsystem->RemoveMappingContext(DefaultMappingContext);
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
}

void ACassTeraCharacter::ShowKillUI()
{

	// ų �̹���, �ؽ�Ʈ UI ����
	if (mainUI)
		mainUI->ShowKillContent();
}

void ACassTeraCharacter::NotEnemyResult()
{

	if (gs->timerWidget != nullptr)
	{
		
		if (mainUI)
		{
			mainUI->img_RedCH->SetVisibility(ESlateVisibility::Visible);

			FTimerHandle visibleHandler;
			GetWorld()->GetTimerManager().SetTimer(visibleHandler, [&]() {

				mainUI->img_RedCH->SetVisibility(ESlateVisibility::Hidden);

				GetWorld()->GetTimerManager().ClearTimer(visibleHandler);
				
				//bDecreasing = false;
			}, 0.5f, false);
		}
		

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Fail222222"));
	}
}

void ACassTeraCharacter::ClientRPC_WorngShot_Implementation()
{
	NotEnemyResult();
}

void ACassTeraCharacter::ServerRPC_WorngShot_Implementation()
{
	ClientRPC_WorngShot();
}

void ACassTeraCharacter::ClientRPC_KillUI_Implementation()
{
	ShowKillUI();
}

void ACassTeraCharacter::ServerRPC_KillUI_Implementation()
{
	ClientRPC_KillUI();
}

//void ACassTeraCharacter::ClientRPC_AddTimerUI_Implementation()
//{
//	if(IsLocallyControlled())
//	{
//	auto* pc = Cast<APersonPlayerController>(Controller);
//
//		//	gameTimerwidget = Cast<UGameTimerWidget>(CreateWidget(GetWorld(), WBP_gameTimerWidget));
//		if (pc->gameTimerwidget)
//		{
//			gameTimerwidget = pc->gameTimerwidget;
//			if (IsLocallyControlled())
//			{
//				gameTimerwidget->AddToViewport();
//				//ServerRPC_SetTimer();
//			}
//		}
//	}
//}
//
//void ACassTeraCharacter::ServerRPC_AddTimerUI_Implementation()
//{
//	ClientRPC_AddTimerUI();
//}

void ACassTeraCharacter::Throw(const FInputActionValue& Value)
{
	if (bFiring || bThrowing || false == bGameStart)
		return;

	ServerRPC_Throw();
}

void ACassTeraCharacter::ThrowFinish(const FInputActionValue& Value)
{
	if (false == bGameStart)
		return;

	ServerRPC_ThrowFin();

}

void ACassTeraCharacter::ServerRPC_Throw_Implementation()
{
	bThrowing = true;

	grenadeCount--;

	if (grenadeCount >= 0)
	{
		//grenade = Cast<AGrenade>(grenade_bp);
		FActorSpawnParameters params;
		grenade = GetWorld()->SpawnActor<AGrenade>(grenade_bp, gun->GetSocketTransform("Weapon_L"), params);
		UE_LOG(LogTemp, Warning, TEXT("spawn grenade"));

		MultiRPC_Throw(bThrowing, grenadeCount);
	}
}

void ACassTeraCharacter::MultiRPC_Throw_Implementation(bool _bThrowing, int32 _grenadeCount)
{
	bThrowing = _bThrowing;
	grenadeCount = _grenadeCount;

	if (mainUI)
		mainUI->ShowGrenadeCount();

	gun->SetVisibility(false);
	
	/*FActorSpawnParameters params;
	grenade = GetWorld()->SpawnActor<AGrenade>(grenade_bp, gun->GetSocketTransform("Weapon_L"), params);*/
	//UE_LOG(LogTemp, Warning, TEXT("spawn grenade"));

	if (grenade)
	{
		grenade->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "Weapon_L");
		UE_LOG(LogTemp, Warning, TEXT("attach grenade"));
	}
}

void ACassTeraCharacter::ServerRPC_ThrowFin_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("ServerRPC_ThrowFin"));

	if (grenadeCount >= 0)
	{
		bThrowing = false;

		MultiRPC_ThrowFin(bThrowing);

		if (grenade)
		{
			grenade->ServerRPC_BeforeBomb();
		}
	}

}

void ACassTeraCharacter::MultiRPC_ThrowFin_Implementation(bool _bThrowing)
{
	bThrowing = _bThrowing;

	PlayAnimMontage(throwMontage);

	gun->SetVisibility(true);
	UE_LOG(LogTemp, Warning, TEXT("MultiRPC_ThrowFin"));PlayAnimMontage(throwMontage);

}

void ACassTeraCharacter::ServerRPC_Lose_Implementation()
{
	ClientRPC_Lost();

}

void ACassTeraCharacter::ClientRPC_Lost_Implementation()
{
	gs = Cast<ACassteraGameState>(GetWorld()->GetGameState());
	if (gs)
	{
		if (loseSound)
		{
		UGameplayStatics::PlaySound2D(GetWorld(), loseSound);

		}
		resultWidget = Cast<UResultWidget>(CreateWidget(GetWorld(), wbp_resultWidget));
		resultWidget = gs->resultWidget;
		resultWidget->AddToViewport();
		resultWidget->text_Win->SetVisibility(ESlateVisibility::Hidden);
		resultWidget->text_Lose->SetVisibility(ESlateVisibility::Visible);
		bWin = false;

		auto* PlayerController = Cast<APersonPlayerController>(Controller);
		if (PlayerController)
		{
			PlayerController->SetShowMouseCursor(true);
		}
// 		ServerRPC_CountDown();

//		gs->ServerRPC_ShowResult(bWin);
	}
}


void ACassTeraCharacter::ServerRPC_Win_Implementation()
{
	ClientRPC_Win();

}


void ACassTeraCharacter::ClientRPC_Win_Implementation()
{
	gs = Cast<ACassteraGameState>(GetWorld()->GetGameState());
	if (gs)
	{	
		if (winSound)
		{
		UGameplayStatics::PlaySound2D(GetWorld(), winSound);

		}
		resultWidget = Cast<UResultWidget>(CreateWidget(GetWorld(), wbp_resultWidget));
		resultWidget = gs->resultWidget;
		resultWidget->AddToViewport();
		resultWidget->text_Win->SetVisibility(ESlateVisibility::Visible);
		resultWidget->text_Lose->SetVisibility(ESlateVisibility::Hidden);
		bWin = true;
		auto* PlayerController = Cast<APersonPlayerController>(Controller);
		if (PlayerController)
		{
			PlayerController->SetShowMouseCursor(true);
		}
// 		ServerRPC_CountDown();

//		gs->ServerRPC_ShowResult(bWin);
	}
}



void ACassTeraCharacter::ServerRPC_AddMainUI_Implementation()
{
	ClientRPC_AddMainUI();
}

void ACassTeraCharacter::ClientRPC_AddMainUI_Implementation()
{
	AddMainUI();
}

//void ACassTeraCharacter::ServerRPC_SetTimer_Implementation()
//{
//	MultiRPC_SetTimer();
//}
//
//void ACassTeraCharacter::MultiRPC_SetTimer_Implementation()
//{
//	if (gameTimerwidget)
//	{
//		gameTimerwidget->SetTimer();
//	}
//}

void ACassTeraCharacter::ServerRPC_DisableOutLiner_Implementation()
{
	ClientRPC_DisableOutLiner();	
}

void ACassTeraCharacter::ClientRPC_DisableOutLiner_Implementation()
{
	if (IsLocallyControlled())
	{
		for (TActorIterator<AHidePlayer> it(GetWorld()); it; ++it)
		{
			hidePlayer = *it;

			if (hidePlayer)
			{
				hidePlayer->meshComp->SetOverlayMaterial(nullptr);

			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("cant find hideplayer"));
			}
		}
	}
}

void ACassTeraCharacter::ServerRPC_ChangeMovement_Implementation()
{
	// ���� ���� ��(bGameStart == false) ������ ����
	ClientRPC_ChangeMovement(bGameStart);

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	UE_LOG(LogTemp, Warning, TEXT("move none"));

	FTimerHandle changeMoveHandler;
	GetWorld()->GetTimerManager().SetTimer(changeMoveHandler, [&]() {
		
		if (this->IsValidLowLevel())
		{
			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

			bGameStart = true;
			UE_LOG(LogTemp, Warning, TEXT("move"));

			// ���� ���۵Ǹ�(bGameStart == true) ������ �����
			ClientRPC_ChangeMovement(bGameStart);
		}

	}, 10.0f, false);
	
	//ClientRPC_ChangeMovement(bGameStart, characterMovement);



}

void ACassTeraCharacter::ClientRPC_ChangeMovement_Implementation(bool _bGameStart)
{
	bGameStart = _bGameStart;

	ChangePersonPlayerMovement();
}

void ACassTeraCharacter::ChangePersonPlayerMovement()
{
	if (mainUI)
	{
		bGameStart ? mainUI->HideStartUI() : mainUI->ShowStartUI();
	}
}

// ä��
void ACassTeraCharacter::ServerRPC_SendMsg_Implementation(const FString& msg)
{
	MultiRPC_SendMsg(msg);
}

void ACassTeraCharacter::MultiRPC_SendMsg_Implementation(const FString& msg)
{
	// ���� �÷��̾� ��Ʈ�ѷ��� �����ͼ� chatUI�� addMsgȣ��
	auto* pc = Cast<APersonPlayerController>(GetWorld()->GetFirstPlayerController());
	if (pc)
	{
		pc->chatUI->AddMsg(msg);
	}
}

void ACassTeraCharacter::OnIAChatEnter(const FInputActionValue& value)
{
	auto* pc = Cast<APersonPlayerController>(GetWorld()->GetFirstPlayerController());
	//if(pc)
	//pc->chatUI->OnMyClickSendMsg();
}

// ä�� IA Ű ������ �� ����� ���
void ACassTeraCharacter::OnIAChat(const FInputActionValue& value)
{
	auto* pc = Cast<APersonPlayerController>(GetWorld()->GetFirstPlayerController());
	if (nullptr == pc)
	{
		return;
	}
	
	bChatEnabled = !bChatEnabled;
	
	if (bChatEnabled)
	{	
		pc->SetInputMode(FInputModeGameAndUI());
		pc->SetShowMouseCursor(true);
	}
	else
	{
		pc->chatUI->OnMyClickSendMsg();
		pc->SetInputMode(FInputModeGameOnly());
		pc->SetShowMouseCursor(false);
	}
}