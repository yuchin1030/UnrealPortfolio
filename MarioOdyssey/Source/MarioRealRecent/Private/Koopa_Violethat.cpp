// Fill out your copyright notice in the Description page of Project Settings.


#include "Koopa_Violethat.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/BoxComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h>
#include "../MarioRealRecentCharacter.h"
#include "EngineUtils.h"

// Sets default values
AKoopa_Violethat::AKoopa_Violethat()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(50));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	meshComp->SetupAttachment(boxComp);
	meshComp->SetRelativeLocation(FVector(0, 0, -50));
}

// Called when the game starts or when spawned
void AKoopa_Violethat::BeginPlay()
{
	Super::BeginPlay();
	moveDirection = GetActorForwardVector();
	SetLifeSpan(10.0f);
}

// Called every frame
void AKoopa_Violethat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	VioDel=VioDel+DeltaTime;
	if(VioDel>4){
		if (VioDel > 5 && VioDel < 5.5f) {
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

