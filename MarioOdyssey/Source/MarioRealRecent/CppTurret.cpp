// Fill out your copyright notice in the Description page of Project Settings.


#include "CppTurret.h"
#include "Kismet/KismetMathLibrary.h"
#include "CharacterInterface.h"
#include "TurretAnimInterface.h"
#include "MarioRealRecentCharacter.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/ArrowComponent.h>
#include "Koopa_ball.h"
#include <Koopa_Violethat.h>
#include <Koopa_WhiteHat.h>
#include "Koopa_FirstVioletHat.h"
#include "Koopa_SecondVioletHat.h"
#include <../../../../../../../Source/Runtime/Engine/Public/EngineUtils.h>

#define OUT


// Sets default values
ACppTurret::ACppTurret()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	TurretMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(Root);

	//Beam = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Beam"));
	//Beam->SetupAttachment(TurretMesh, TEXT("BeamSocket"));

	Beam1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Beam1"));
	Beam1->SetupAttachment(TurretMesh, TEXT("BeamSocket1"));


	Target1 = CreateDefaultSubobject<USceneComponent>(TEXT("Target1"));
	Target1->SetupAttachment(Root);

	Target2 = CreateDefaultSubobject<USceneComponent>(TEXT("Target2"));
	Target2->SetupAttachment(Root);

	FollowTarget = CreateDefaultSubobject<USceneComponent>(TEXT("FollowTarget"));
	FollowTarget->SetupAttachment(Root);


	spawnArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Component"));
	spawnArrow->SetupAttachment(Beam1);

	spawnArrowV1 = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Component1"));
	spawnArrowV1->SetupAttachment(Beam1);

	spawnArrowV2 = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Component2"));
	spawnArrowV2->SetupAttachment(Beam1);

	spawnArrowV3 = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Component3"));
	spawnArrowV3->SetupAttachment(Beam1);

	spawnArrowV4 = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Component4"));
	spawnArrowV4->SetupAttachment(Beam1);

	spawnArrowW = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Component5"));
	spawnArrowW->SetupAttachment(Beam1);

}

// Called when the game starts or when spawned
void ACppTurret::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(ChangeTargetTimerhandle, this, &ACppTurret::ChangeBeamTarget, ChangeTargetDelay, true, 1.f);
	GetWorldTimerManager().SetTimer(TraceTimerhandle, this, &ACppTurret::TraceBeam, .1f, true, .1f);

	//TurretMesh->PlayAnimation(Anims[0], false);
}

// Called every frame
void ACppTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	UpdateLookAtTarget(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("%f"), anyTime);
	currentTime += DeltaTime;
	anyTime += DeltaTime ;
	if (anyTime >15.0f && anyTime<=27.0f) {
		if (!bFireBall) {
			UpdateLookAtTarget(DeltaTime);
			if (currentTime > BalldelayTime) {
				//쿠파 폭탄 날리기

				GetWorld()->SpawnActor<AKoopa_ball>(enemy_bp, spawnArrow->GetComponentLocation(), spawnArrow->GetComponentRotation());


				currentTime = 0;
			}
		}
		else {
			UpdateLookAtTarget(DeltaTime);
			if (currentTime > BalldelayTime) {
				//쿠파 폭탄 날리기

				GetWorld()->SpawnActor<AKoopa_ball>(enemyFire_bp, spawnArrow->GetComponentLocation(), spawnArrow->GetComponentRotation());


				currentTime = 0;
			}
		}
	}

	else if (anyTime > 53 && anyTime < 83) {
		if (bIsWearingHat) {
			anyTime=0;
			TimeLineTime++;
	}
	else{
		UpdateLookAtTarget(DeltaTime);
		if (currentTime > delayTime) {
			bFireBall = true;
			GetWorld()->SpawnActor<AKoopa_FirstVioletHat>(violet_bp1, spawnArrowV1->GetComponentLocation(), spawnArrowV1->GetRelativeRotation());
			GetWorld()->SpawnActor<AKoopa_Violethat>(violet_bp, spawnArrowV2->GetComponentLocation(), spawnArrowV2->GetRelativeRotation() );
			GetWorld()->SpawnActor<AKoopa_WhiteHat>(white_bp, spawnArrowW->GetComponentLocation(), spawnArrowW->GetRelativeRotation());
			GetWorld()->SpawnActor<AKoopa_Violethat>(violet_bp, spawnArrowV3->GetComponentLocation(), spawnArrowV3->GetRelativeRotation());
			GetWorld()->SpawnActor<AKoopa_SecondVioletHat>(violet_bp2, spawnArrowV4->GetComponentLocation(), spawnArrowV4->GetRelativeRotation());
			currentTime = 0;
			

			UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f"), spawnArrowV2->GetRelativeRotation().Roll, spawnArrowV2->GetRelativeRotation().Pitch, spawnArrowV2->GetRelativeRotation().Yaw)
		}
		}
	}
	else if (anyTime > 83)
	{
		anyTime = 0;
		TimeLineTime++;
	}
}
//TraceBeam();

//}
//타겟 쫓아가게 만들기
void ACppTurret::UpdateLookAtTarget(float DeltaTime)
{
	if (ChangeNumber < 100) {

		if (LookAtRotation.Equals(TargetRotation, 1.f)) {
			return;
		}

		//시작과 끝의 로테이션 값을 찾는다.
		LookAtRotation += RotationDelta * RotationRateMultiplier * DeltaTime;

		//인터페이스에 update look at rotation을 추가해서 블루프린트로 다뤘다(자세한 것은ABP_Turret1에)
		if (TurretMesh->GetAnimInstance()->Implements<UTurretAnimInterface>()) {
			ITurretAnimInterface::Execute_UpdateLookAtRotation(TurretMesh->GetAnimInstance(), LookAtRotation);
		}
	}
	//여기까지 만들어둔 followtarget의 로테이션 값을 구해 그 방향으로 빔을 쏘는 코드이다.
}

void ACppTurret::ChangeBeamTarget()
{
	TimerCount++;

	//	if (ChangeNumber < 10) {
			//if (TimerCount % 2 == 0) {
	for (TActorIterator<AMarioRealRecentCharacter> player(GetWorld()); player; ++player)
	{
		// 자신이 플레이어를 바라보는 방향을 moveDirection으로 설정한다.
		moveDirection = (player->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		FollowTarget->SetWorldLocation(player->GetActorLocation());

	}
	ChangeNumber++;

	//	}
// 		else {
// 			FollowTarget->SetWorldLocation(Target2->GetComponentLocation());
// 			ChangeNumber++;
// 		}
//	}
	//else {
	//	Beam1->SetHiddenInGame(false);
	//}

	//여기까지 일정 시간이 지나면 타겟을 변경시키는 코드이다.
	FVector Start = TurretMesh->GetSocketLocation("BeamSocket1");
	FVector End = FollowTarget->GetComponentLocation();
	TargetRotation = UKismetMathLibrary::FindLookAtRotation(Start, End);

	RotationDelta = TargetRotation - LookAtRotation;
	RotationDelta.Normalize();
	//여기까지 목이 돌아갈때 부드럽게 돌아가도록

}
// 라인트레이스로 캐릭터와의 충돌 감지
void ACppTurret::TraceBeam()
{

	FHitResult HitResult;
	FVector Start = TurretMesh->GetSocketLocation("BeamSocket");
	FVector End = Start + Beam1->GetRightVector() * -3000;

	FCollisionObjectQueryParams objQueryParams;
	objQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
	objQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	//충돌 체크에서 제외할 액터 또는 컴포넌트
	FCollisionQueryParams queryParams;
	queryParams.AddIgnoredActor(this);
	bool bResult = GetWorld()->LineTraceSingleByObjectType(HitResult, Start, End, objQueryParams, queryParams);

	if (bResult)
	{
		DrawDebugLine(GetWorld(), Start, HitResult.ImpactPoint, FColor(0, 255, 0), false, 2.0f, 0, 1);
		CheckEnemy(HitResult.GetActor());
		//UE_LOG(LogTemp, Warning, TEXT("%s"),*HitResult.GetActor()->GetActorNameOrLabel());
	}
	else {

	}
	// 	FCollisionQueryParams CollQueryParams;
	// 	CollQueryParams.AddIgnoredActor(this);
	// 
	// 	bool bHit=GetWorld()->LineTraceSingleByChannel(OUT HitResult, Start, End, ECollisionChannel::ECC_Camera, CollQueryParams);
	// 
	// 	if (bHit) {
	// 		CheckEnemy(HitResult.GetActor());
	// 	}
	// 	else{
	// 		UE_LOG(LogTemp, Warning, TEXT("else"));
	// 	}
}

void ACppTurret::CheckEnemy(AActor* HitActor)
{
	if (HitActor->Implements<UCharacterInterface>()) {

		bool bEnemy = ICharacterInterface::Execute_IsEnemy(HitActor);

		if (bEnemy) {
			Enemy = HitActor;
			//	UE_LOG(LogTemp,Warning,TEXT("qqqqqqqqqqqqqqqqqqqqqq"));
		}
		else {

		}
	}
}

void ACppTurret::FollowEnemy(float DeltaTime)
{
	FVector Start = TurretMesh->GetSocketLocation("BeamSocket");
	FVector End = Enemy->GetActorLocation();

	FRotator RotationToEnemy = UKismetMathLibrary::FindLookAtRotation(Start, End);

	LookAtRotation = FMath::RInterpTo(LookAtRotation, RotationToEnemy, DeltaTime, 10);

	if (TurretMesh->GetAnimInstance()->Implements<UTurretAnimInterface>()) {
		ITurretAnimInterface::Execute_UpdateLookAtRotation(TurretMesh->GetAnimInstance(), LookAtRotation);
	}
}

//여기부턴 모자를 날리는 기술
void ACppTurret::Shoot()
{

}