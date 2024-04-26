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
//	// 커브 플로트가 할당되어 있는지 확인하여 커브가 표현되도록 한다.
//	if (CurveFloat)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("yes"));
//
//		// 타임라인 자체에 대리자와 같은 종류의 타임라인 진행 함수 할당
//		FOnTimelineFloat TimelineProgress;
//		// 타임라인 진행 함수를 사용하여 바인딩을 통해 클래스에 참조
//		TimelineProgress.BindUFunction(this, FName("TimelineProgress"));		// 우리가 바인딩할 함수
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
