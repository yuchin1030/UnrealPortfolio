// Fill out your copyright notice in the Description page of Project Settings.


#include "MarioThrowingCap.h"
#include <Components/SkeletalMeshComponent.h>
#include <Components/SphereComponent.h>
#include <GameFramework/RotatingMovementComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Components/SceneComponent.h>
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
//#include "MarioRealRecentCharacter.h"

// Sets default values
AMarioThrowingCap::AMarioThrowingCap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*defaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(defaultSceneRoot);

	cap = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("marioCap"));
	cap->SetupAttachment(defaultSceneRoot);

	throwCapColl = CreateDefaultSubobject<USphereComponent>(TEXT("capCollision"));
	throwCapColl->SetupAttachment(cap);
	throwCapColl->SetRelativeLocation(FVector(0, 0, 20));
	throwCapColl->SetRelativeScale3D(FVector(2));

	rotMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Rotate Movement"));
	proMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));

	rotMovement->RotationRate = FRotator(0, 700, 0);
	proMovement->InitialSpeed = 2500;
	proMovement->MaxSpeed = 3000;
	proMovement->ProjectileGravityScale = 0.1f;*/


}

// Called when the game starts or when spawned
void AMarioThrowingCap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMarioThrowingCap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

/*void AMarioThrowingCap::ReturnToPlayer()
{

	//UGameplayStatics::GetPlayerCharacter


	//UKismetSystemLibrary::MoveComponentTo(defaultSceneRoot);
}

AMarioRealRecentCharacter* AMarioThrowingCap::FindPlayer_BP()
{
	// 1. 플레이어의 월드 상의 위치를 찾는다.
	// 1-1. 현재 월드데이터에서 AMarioRealRecentCharacter 클래스로 된 모든 액터들을 찾는다.
	TArray<AActor*> players;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMarioRealRecentCharacter::StaticClass(), players);
}*/



