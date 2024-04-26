// Fill out your copyright notice in the Description page of Project Settings.


#include "Koopa_FirstVioletHat.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/BoxComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h>
#include "../MarioRealRecentCharacter.h"
#include "EngineUtils.h"

// Sets default values
AKoopa_FirstVioletHat::AKoopa_FirstVioletHat()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(boxComp);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	meshComp->SetupAttachment(boxComp);
}

// Called when the game starts or when spawned
void AKoopa_FirstVioletHat::BeginPlay()
{
	Super::BeginPlay();
	

	SetLifeSpan(10.0f);
}

// Called every frame
void AKoopa_FirstVioletHat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	VioDel = VioDel + DeltaTime;
	if (VioDel > 0) {
		if (VioDel > 1 && VioDel < 1.5f) {
			for (TActorIterator<AMarioRealRecentCharacter> player(GetWorld()); player; ++player)
			{
				// 자신이 플레이어를 바라보는 방향을 moveDirection으로 설정한다.
				moveDirection = (player->GetActorLocation() - GetActorLocation()).GetSafeNormal();

			}
			SetActorLocation(GetActorLocation() + moveDirection * moveSpeed * DeltaTime);
			SetActorRotation(GetActorRotation() + WhiteRot);
			moveDirection1 = GetActorForwardVector();
	}
	else
		{
			SetActorLocation(GetActorLocation() + moveDirection * moveSpeed * DeltaTime);
			SetActorRotation(GetActorRotation() + WhiteRot);
		}
}
	else {
		SetActorRotation(GetActorRotation() + WhiteRot);
	}
}

