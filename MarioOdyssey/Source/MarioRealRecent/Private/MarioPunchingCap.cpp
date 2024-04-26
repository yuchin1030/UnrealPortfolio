// Fill out your copyright notice in the Description page of Project Settings.


#include "MarioPunchingCap.h"
#include <Components/SceneComponent.h>
#include <Components/BoxComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <Components/InterpToMovementComponent.h>


AMarioPunchingCap::AMarioPunchingCap()
{
	PrimaryActorTick.bCanEverTick = true;

	/*cupaHatCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("capCollision"));
	cupaHatCollision->SetRelativeScale3D(FVector(2.5f));
	SetRootComponent(cupaHatCollision);

	cupaHat = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("cupaHat"));
	cupaHat->SetRelativeScale3D(FVector(0.12f));
	cupaHat->SetRelativeLocation(FVector(0,0,-16));
	cupaHat->SetupAttachment(cupaHatCollision);

	interpMovement = CreateDefaultSubobject<UInterpToMovementComponent>(TEXT("interpMovement"));
	interpMovement->Duration = 1.0f;
	interpMovement->AddControlPointPosition(FVector(0, 0, 0));
	interpMovement->AddControlPointPosition(FVector(300, 0, 300));
	interpMovement->AddControlPointPosition(FVector(300, 0, 0));*/

}

void AMarioPunchingCap::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("beginplay"));
	

}

void AMarioPunchingCap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//CurveTimeline.TickTimeline(DeltaTime);
}

//void AMarioPunchingCap::CupaHatRotate()
//{
//	interpMovement->Activate(true);
//
//	// Ŀ�� �÷�Ʈ�� �Ҵ�Ǿ� �ִ��� Ȯ���Ͽ� Ŀ�갡 ǥ���ǵ��� �Ѵ�.
//	if (CurveFloat)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("yes"));
//
//		// Ÿ�Ӷ��� ��ü�� �븮�ڿ� ���� ������ Ÿ�Ӷ��� ���� �Լ� �Ҵ�
//		FOnTimelineFloat TimelineProgress;
//		// Ÿ�Ӷ��� ���� �Լ��� ����Ͽ� ���ε��� ���� Ŭ������ ����
//		TimelineProgress.BindUFunction(this, FName("TimelineProgress"));		// �츮�� ���ε��� �Լ�
//		CurveTimeline.AddInterpFloat(CurveFloat, TimelineProgress);
//		CurveTimeline.SetLooping(false);
//
//		StartRot = EndRot - GetActorRotation();
//		EndRot.Add(offset, 0, 0);
//
//		CurveTimeline.Play();
//	}
//	
//}
//
//void AMarioPunchingCap::TimelineProgress(float Value)
//{
//	FRotator NewRotation = FMath::Lerp(StartRot, EndRot, Value);
//	SetActorRotation(NewRotation);
//}
