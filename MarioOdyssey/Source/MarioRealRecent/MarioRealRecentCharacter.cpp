// Copyright Epic Games, Inc. All Rights Reserved.

#include "MarioRealRecentCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include <Components/ArrowComponent.h>
#include <MarioThrowingCap.h>


DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AMarioRealRecentCharacter

AMarioRealRecentCharacter::AMarioRealRecentCharacter()
{
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
	CameraBoom->SetRelativeLocation(FVector(0, 0, 180));

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)




	// ===================================================================================================================
	/*arrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow1"));
	arrowComp->SetupAttachment(GetMesh());
	arrowComp->SetRelativeLocation(FVector(0, 10, 90));
	arrowComp->SetRelativeRotation(FRotator(0, 90, 0));

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Cap Collision"));
	boxComp->SetupAttachment(GetMesh());
	boxComp->SetRelativeLocation(FVector(0, -10, 135));
	boxComp->SetRelativeRotation(FRotator(0, 0, -20));

	skmComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MarioCap"));
	skmComp->SetupAttachment(boxComp);
	skmComp->SetRelativeLocation(FVector(0, 0, -15));
	skmComp->SetRelativeScale3D(FVector(0.75));

	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));*/
}

void AMarioRealRecentCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Hello"));
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMarioRealRecentCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMarioRealRecentCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMarioRealRecentCharacter::Look);

		// 던지기
		//EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Started, this, &AMarioRealRecentCharacter::Throw);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AMarioRealRecentCharacter::Move(const FInputActionValue& Value)
{
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

void AMarioRealRecentCharacter::Look(const FInputActionValue& Value)
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

//void AMarioRealRecentCharacter::Throw(const FInputActionValue& Value)
//{
//	//if (Controller != nullptr)
//	if (isOnMario)
//	{
//		isOnMario = false;
//
//		// 충돌 옵션 (무조건 내가 설정한 위치에서 생성)
//		FActorSpawnParameters params;
//		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
//	
//		// 화살표의 world location 및 rotation 위치에 모자를 생성한다.
//		FVector spawnLoc = arrowComp->GetComponentLocation() + FVector(0,0,10);
//		FRotator spawnRot = arrowComp->GetComponentRotation();
//		FVector spawnScale = arrowComp->GetComponentScale();
//
//		// 마리오 던지는 모자 생성
//		AMarioThrowingCap* spawnedCap = GetWorld()->SpawnActor<AMarioThrowingCap>(throwCaps, spawnLoc, spawnRot, params);
//
//		skmComp->SetVisibility(false);
//
//		
//		// delay
//		// return to player
//
//		isOnMario = true;
//	}
//}
