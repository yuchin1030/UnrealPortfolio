#include "VRPlayer.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Camera/CameraComponent.h>
#include <../../../../../../../Source/Runtime/HeadMountedDisplay/Public/MotionControllerComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Engine/SkeletalMesh.h>
#include <../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>
#include <../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h>




AVRPlayer::AVRPlayer()
{
 
	PrimaryActorTick.bCanEverTick = true;

	// VRī�޶� ������Ʈ�� �����ϰ� ��Ʈ�� ���̰�ʹ�.
	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("VR Player Camera"));
	cameraComp->SetupAttachment(RootComponent);

	// ��� ��Ʈ�ѷ� �޼�, ������ �����ϰ� ��Ʈ�� ���̰�ʹ�.
	motionLeft = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("motionLeft"));
	motionLeft->SetTrackingMotionSource(TEXT("Left"));
	motionRight = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("motionRight"));
	motionRight->SetTrackingMotionSource(TEXT("Right"));

	motionLeft->SetupAttachment(RootComponent);
	motionRight->SetupAttachment(RootComponent);

	// �޼�, ������ ���̷�Ż �޽� ������Ʈ�� ���� ��� ��Ʈ�ѷ��� ���̰�ʹ�.
	meshLeft = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("meshLeft"));
	meshRight = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("meshRight"));

	meshLeft->SetupAttachment(motionLeft);
	meshRight->SetupAttachment(motionRight);



	



	// �޼�, ������ ���̷�Ż �޽� �ε��ؼ� �����ϰ�ʹ�.
	// �޼� 
	ConstructorHelpers::FObjectFinder<USkeletalMesh>TempMeshLeft(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_left.SKM_MannyXR_left'"));

	// �޼� �ε尡 ���� �ߴٸ� ���� �ϰ�ʹ�.
	if (meshLeft)
	{
		meshLeft->SetSkeletalMesh(TempMeshLeft.Object);
		meshLeft->SetWorldLocationAndRotation(FVector(-2.981260f, -3.5f, 4.561753f), FRotator(-25, -180, 90));
		//(X=-2.981260,Y=-3.500000,Z=4.561753)
		//(Pitch=-25.000000,Yaw=-179.999999,Roll=89.999998)

	}



	// ������ 
	ConstructorHelpers::FObjectFinder<USkeletalMesh>TempMeshRight(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_MannyXR_right.SKM_MannyXR_right'"));
	// ������ �ε尡 ���� �ߴٸ� ���� �ϰ�ʹ�.
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

	// �÷��̾� ��Ʈ�ѷ��� ��������ʹ�.
	auto* pc = Cast<APlayerController>(Controller);
	// UEnhancedInputLocalPlayerSubsystem�� �����ͼ�
	if (pc)
	{
		auto subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
		if (subsystem)
		{
			// AddMappingContext�� ȣ���ϰ�ʹ�.
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

// �÷��̾��� �����¿츦 �����̰� �ϴ� �Լ�
void AVRPlayer::OnIAMove(const FInputActionValue& value)
{
	FVector2D PlayerDir = value.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(),PlayerDir.Y);
	AddMovementInput(GetActorRightVector(),PlayerDir.X);

}

// �÷��̾��� �þ߿� ���� ȸ���ϴ� �Լ�
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




