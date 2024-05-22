#include "VRPlayer.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Camera/CameraComponent.h>
#include <../../../../../../../Source/Runtime/HeadMountedDisplay/Public/MotionControllerComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Engine/SkeletalMesh.h>
#include <../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>
#include <../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h>




AVRPlayer::AVRPlayer()
{
 
	PrimaryActorTick.bCanEverTick = true;

	// VR카메라 컴포넌트를 생성하고 루트에 붙이고싶다.
	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("VR Player Camera"));
	cameraComp->SetupAttachment(RootComponent);

	// 모션 컨트롤러 왼손, 오른손 생성하고 루트에 붙이고싶다.
	motionLeft = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("motionLeft"));
	motionLeft->SetTrackingMotionSource(TEXT("Left"));
	motionRight = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("motionRight"));
	motionRight->SetTrackingMotionSource(TEXT("Right"));

	motionLeft->SetupAttachment(RootComponent);
	motionRight->SetupAttachment(RootComponent);

	// 왼손, 오른손 스켈레탈 메시 컴포넌트를 만들어서 모션 컨트롤러에 붙이고싶다.
	meshLeft = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("meshLeft"));
	meshRight = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("meshRight"));

	meshLeft->SetupAttachment(motionLeft);
	meshRight->SetupAttachment(motionRight);



	



	// 왼손, 오른손 스켈레탈 메시 로드해서 적용하고싶다.
	// 왼손 
	ConstructorHelpers::FObjectFinder<USkeletalMesh>TempMeshLeft(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_left.SKM_MannyXR_left'"));

	// 왼손 로드가 성공 했다면 적용 하고싶다.
	if (meshLeft)
	{
		meshLeft->SetSkeletalMesh(TempMeshLeft.Object);
		meshLeft->SetWorldLocationAndRotation(FVector(-2.981260f, -3.5f, 4.561753f), FRotator(-25, -180, 90));
		//(X=-2.981260,Y=-3.500000,Z=4.561753)
		//(Pitch=-25.000000,Yaw=-179.999999,Roll=89.999998)

	}



	// 오른손 
	ConstructorHelpers::FObjectFinder<USkeletalMesh>TempMeshRight(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_right.SKM_MannyXR_right'"));
	// 오른손 로드가 성공 했다면 적용 하고싶다.
	if (TempMeshRight.Succeeded())
	{
		meshRight->SetSkeletalMesh(TempMeshRight.Object);
		meshRight->SetWorldLocationAndRotation(FVector(-2.981260f, 3.5f, 4.561753f), FRotator(25, 0, 90));
		//(X=-2.981260,Y=3.500000,Z=4.561753)
		//(Pitch=25.000000,Yaw=0.000000,Roll=89.999999)
	}



}


void AVRPlayer::BeginPlay()
{
	Super::BeginPlay();

	// 플레이어 컨트롤러를 가져오고싶다.
	auto* pc = Cast<APlayerController>(Controller);
	// UEnhancedInputLocalPlayerSubsystem를 가져와서
	if (pc)
	{
		auto subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
		if (subsystem)
		{
			// AddMappingContext를 호출하고싶다.
			subsystem->AddMappingContext(IMC_VRPlayer, 0);
		}
	}
	
}


void AVRPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

// Called to bind functionality to input
void AVRPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto* input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	if (input)
	{
		input->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AVRPlayer::OnIAMove);
		input->BindAction(IA_Turn, ETriggerEvent::Triggered, this, &AVRPlayer::OnIATurn);
		input->BindAction(IA_Grab_Left, ETriggerEvent::Started, this, &AVRPlayer::OnIAGrab_Left);
		input->BindAction(IA_Grab_Right, ETriggerEvent::Started, this, &AVRPlayer::OnIAGrab_Right);
	}
	
}

// 플레이어의 상하좌우를 움직이게 하는 함수
void AVRPlayer::OnIAMove(const FInputActionValue& value)
{
	FVector2D PlayerDir = value.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(),PlayerDir.Y);
	AddMovementInput(GetActorRightVector(),PlayerDir.X);

}

// 플레이어의 시야에 맞춰 회전하는 함수
void AVRPlayer::OnIATurn(const FInputActionValue& value)
{
	float v = value.Get<float>();
	AddControllerYawInput(v);
}

void AVRPlayer::OnIAGrab_Left(const FInputActionValue& value)
{
	UE_LOG(LogTemp,Warning,TEXT("aseeas"));
}

void AVRPlayer::OnIAGrab_Right(const FInputActionValue& value)
{

	UE_LOG(LogTemp, Warning, TEXT("ESAASEAS"));
}




