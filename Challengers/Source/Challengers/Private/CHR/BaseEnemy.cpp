// Fill out your copyright notice in the Description page of Project Settings.


#include "CHR/BaseEnemy.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GamePlayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "EngineUtils.h"
#include "OurGameInstance.h"
#include "CHR/EnemyBodyStruct.h"
#include "CHR/WeaponStruct.h"
#include "CHR/BaseWeapon.h"
#include "CHR/LongWeapon.h"
#include "CHR/BaseGear.h"
#include "CHR/CEnemyAnimInst.h"
#include "CHR/LEnemyAnimInst.h"
#include "ChallengersCharacter.h"
#include "NavigationSystem.h"
#include "Net/UnrealNetwork.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h>
#include "CHR/BaseBullet.h"
#include <OurGameModeBase.h>
#include "CHR/BaseAreaAtk.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -88.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	bReplicates = true;
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	//게임 인스턴스, AI컨트롤러(서버만 가능해서 수정예정), 네비매쉬 캐싱
	gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());
	AC = Cast<AEnemyAIController>(GetController());
	NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);

	//테스트용 이름. 일단 디폴트 값으로 에너미를 만든다.
	enemySpec.name = TEXT("TestEnemy");
	MakeBody();
	MakeWeapon2(weapon2RowName);
	MakeWeapon1(weapon1RowName);
	MakeGear(gearRowName);
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//타겟과 거리는 항상 체크
	if (playerREF) {
		targetDist = FVector::Dist(GetActorLocation(), playerREF->GetActorLocation());
		//UE_LOG(LogTemp, Warning, TEXT("X: %f, Y: %f, Z: %f"), playerREF->GetActorLocation().X, playerREF->GetActorLocation().Y, playerREF->GetActorLocation().Z);
		//UE_LOG(LogTemp, Warning, TEXT("Dist : %f"), targetDist);
	}

	forwardSpeed = FVector::DotProduct(GetVelocity().GetSafeNormal(), GetActorForwardVector());
	rightSpeed = FVector::DotProduct(GetVelocity().GetSafeNormal(), GetActorRightVector());

	if (currentHP <= 0 && AIState != EAttackState::DIED)
	{
		AIState = EAttackState::DIED;
	}

	switch (AIState)
	{
	case EAttackState::IDLE :
		//애니메이션 변경여부 체크
		//AnimCheak();
	break;
	case EAttackState::READY:
		//행동 선택 대기 상태 1틱으로 지나감?
		//애니메이션 변경여부 체크
		//AnimCheak();
	break;
	case EAttackState::MOVE :
	case EAttackState::MOVRTORUN:
		SetOwner(GetWorld()->GetFirstPlayerController());
		ServerRPC_MoveToBattleDist();
	break;
	case EAttackState::MOVETOATK :
		SetOwner(GetWorld()->GetFirstPlayerController());
		ServerRPC_MoveToAtkDist();
	break;
	case EAttackState::ATTACK :
		SetOwner(GetWorld()->GetFirstPlayerController());
		ServerRPC_Attack();
	break;
	case EAttackState::USINGGEAR :
		UseGear();
	break;
	case EAttackState::WEAPONCHANGE:
		if (bWillChangeWeapon)
		{
			SwapWeapon();
		}
	break;
	case EAttackState::DIED :
		Died(true);
	break;
	default:
	break;
	}
}

//게임 인스턴스의 데이터 테이블에서 bodyRowName값을 불러온 뒤 enemySpec에 입력
void ABaseEnemy::MakeBody()
{
	if(gi){
		FbodySpec* bodyData = gi->DT_BodyData->FindRow<FbodySpec>(bodyRowName, "");
		enemySpec.totalHP = bodyData->HP;
		enemySpec.bIsBossType = bodyData->bIsBossType;
		enemySpec.totalDEF = bodyData->DEF;
		enemySpec.speed = bodyData->speed;
		GetCharacterMovement()->MaxWalkSpeed = 600 * enemySpec.speed;
		GetCharacterMovement()->MaxAcceleration = 2048 * enemySpec.speed;
		enemySpec.weightLimit = bodyData->weightLimit;
		enemySpec.currentWeight = 0;
		enemySpec.totalCost = bodyData->cost;
		GetMesh()->SetSkeletalMesh(bodyData->shape);
		GetMesh()->SetAnimClass(bodyData->anim);
		GetCapsuleComponent()->SetCapsuleRadius(bodyData->size);

		currentHP = enemySpec.totalHP;
	}
}

//확정을 누르면 변경해야함
void ABaseEnemy::ChangeBody(FName newBody)
{
	SetOwner(GetWorld()->GetFirstPlayerController());
	ServerRPC_ChangeBody(newBody);
}

void ABaseEnemy::ServerRPC_ChangeBody_Implementation(FName newBody)
{
	if (gi) {
		FbodySpec* oldData = gi->DT_BodyData->FindRow<FbodySpec>(bodyRowName, "");
		FbodySpec* newData = gi->DT_BodyData->FindRow<FbodySpec>(newBody, "");
		enemySpec.totalHP = newData->HP;
		currentHP = enemySpec.totalHP;
		enemySpec.bIsBossType = newData->bIsBossType;
		enemySpec.totalDEF += newData->DEF - oldData->DEF;
		enemySpec.speed = newData->speed;
		orignSpeed = newData->speed;
		GetCharacterMovement()->MaxWalkSpeed = 600 * enemySpec.speed;
		GetCharacterMovement()->MaxAcceleration = 2048 * enemySpec.speed;
		enemySpec.weightLimit = newData->weightLimit;
		enemySpec.totalCost += newData->cost - oldData->cost;
		GetMesh()->SetSkeletalMesh(newData->shape);
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->SetAnimInstanceClass(newData->anim);
		GetCapsuleComponent()->SetCapsuleRadius(newData->size);
		bodyRowName = newBody;
		OnRep_ChangeBody();
	}
}

void ABaseEnemy::OnRep_ChangeBody()
{
	if (gi == nullptr) {
		gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());
	}

	if (gi) {
		FbodySpec* newData = gi->DT_BodyData->FindRow<FbodySpec>(bodyRowName, "");
		GetMesh()->SetSkeletalMesh(newData->shape);
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->SetAnimInstanceClass(newData->anim);
		UE_LOG(LogTemp, Warning, TEXT("OnRep_ChangeBody"));
	}
}

void ABaseEnemy::MakeWeapon1(FName newWeapon)
{
	SetOwner(GetWorld()->GetFirstPlayerController());
	ServerRPC_MakeWeapon1(newWeapon);
}

void ABaseEnemy::ServerRPC_MakeWeapon1_Implementation(FName newWeapon)
{
	weapon1RowName = newWeapon;

	if (weapon1RowName == FName("W1_0"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Weapon1 is empty"));
		weapon1 = nullptr;
		return;
	}
	else if (gi)
	{
		FweaponSpec* weaponData = gi->DT_Weapon1Data->FindRow<FweaponSpec>(weapon1RowName, "");
		if (weaponData)
		{
			weapon1 = GetWorld()->SpawnActor<ABaseWeapon>(weaponData->shape);
			if (weapon1)
			{
				weapon1->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("hand_rSocket"));
				weapon1->dataInit(weapon1RowName, true, this);
				enemySpec.currentWeight += weapon1->weaponStat.weight;
				enemySpec.totalCost += weapon1->weaponStat.cost;
				weapon1AnimInst = weaponData->anim;
				UE_LOG(LogTemp, Warning, TEXT("ServerRPC_MakeWeapon1 Name : %s"), *weapon1AnimInst->GetName());
				OnRep_MakeWeapon1();
				GetMesh()->SetAnimInstanceClass(weapon1AnimInst);
			}
		}
	}
}

void ABaseEnemy::OnRep_MakeWeapon1()
{
	UE_LOG(LogTemp, Warning, TEXT("OnRep_MakeWeapon1 Name : %s"), *weapon1AnimInst->GetName());
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetAnimInstanceClass(weapon1AnimInst);
}

void ABaseEnemy::ChangeWeapon1(FName newWeapon)
{
	if (weapon1)
	{
		enemySpec.totalCost -= weapon1->weaponStat.cost;
		enemySpec.currentWeight -= weapon1->weaponStat.weight;
		weapon1->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		if (weapon1->ActorHasTag(FName("LongWeapon"))) {
			Cast<ALongWeapon>(weapon1)->ClearBullet();
		}
		else {
			weapon1->ClearBleed();
		}
		weapon1 = nullptr;
	}
	
	MakeWeapon1(newWeapon);
}

void ABaseEnemy::MakeWeapon2(FName newWeapon)
{
	SetOwner(GetWorld()->GetFirstPlayerController());
	ServerRPC_MakeWeapon2(newWeapon);
}

void ABaseEnemy::ServerRPC_MakeWeapon2_Implementation(FName newWeapon)
{
	weapon2RowName = newWeapon;

	if (weapon2RowName == FName("W2_0"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Weapon2 is empty"));
		weapon2 = nullptr;
		return;
	}
	else if (gi)
	{
		FweaponSpec* weaponData = gi->DT_Weapon2Data->FindRow<FweaponSpec>(weapon2RowName, "");
		if (weaponData)
		{
			weapon2 = GetWorld()->SpawnActor<ABaseWeapon>(weaponData->shape);
			if (weapon2)
			{
				if (weaponData->attackRange == 150.0f) {
					weapon2->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("backHolderSocket"));
				}
				else {
					weapon2->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("staffHolderSocket"));
				}
				weapon2->dataInit(weapon2RowName, false, this);
				enemySpec.currentWeight += weapon2->weaponStat.weight;
				enemySpec.totalCost += weapon2->weaponStat.cost;
				weapon2AnimInst = weaponData->anim;
				OnRep_MakeWeapon2();
				GetMesh()->SetAnimInstanceClass(weapon2AnimInst);
				UE_LOG(LogTemp, Warning, TEXT("ServerRPC_MakeWeapon2 Name : %s"), *weapon2AnimInst->GetName());
			}
		}
	}
}

void ABaseEnemy::OnRep_MakeWeapon2()
{
	UE_LOG(LogTemp, Warning, TEXT("OnRep_MakeWeapon2 Name : %s"), *weapon2AnimInst->GetName());
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetAnimInstanceClass(weapon2AnimInst);
}

void ABaseEnemy::ChangeWeapon2(FName newWeapon)
{
	if (weapon2 != nullptr)
	{
		enemySpec.totalCost -= weapon2->weaponStat.cost;
		enemySpec.currentWeight -= weapon2->weaponStat.weight;
		weapon2->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		if (weapon2->ActorHasTag(FName("LongWeapon"))) {
			Cast<ALongWeapon>(weapon2)->ClearBullet();
		}
		else {
			weapon2->ClearBleed();
		}
		weapon2 = nullptr;
	}
	
	MakeWeapon2(newWeapon);
}

//특수능력 장비를 생성한다.
void ABaseEnemy::MakeGear(FName newGear)
{
	gearRowName = newGear;

	if (gearRowName == FName("0"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Gear is empty"));
		gear = nullptr;
		return;
	}
	else if (gi)
	{
		FgearSpec* gearData = gi->DT_GearData->FindRow<FgearSpec>(gearRowName, "");
		gear = GetWorld()->SpawnActor<ABaseGear>(gearData->shape);
		gear->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("root"));
		gear->DataInit(gearRowName, false, this);
		enemySpec.currentWeight += gear->gearStat.weight;
		enemySpec.totalCost += gear->gearStat.cost;
	}
}

void ABaseEnemy::ChangeGear(FName newGear)
{
	if (gear != nullptr)
	{
		enemySpec.totalCost -= gear->gearStat.cost;
		enemySpec.currentWeight -= gear->gearStat.weight;
		UE_LOG(LogTemp, Warning, TEXT("gear weight : %d"), gear->gearStat.weight);
		gear->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		gear->Destroy();
		gear = nullptr;
	}
	
	MakeGear(newGear);
}

void ABaseEnemy::CheakWeightLimit()
{
	if (enemySpec.currentWeight > enemySpec.weightLimit) {
		//(초과치 - 한계치)/한계치 -> 초과비울
		//1 - 초과비율 을 곱해서 비례해서 느리게 한다.
		enemySpec.speed = orignSpeed * FMath::Clamp(1 - ((enemySpec.currentWeight - enemySpec.weightLimit) / (float)enemySpec.weightLimit), 0.0f, 1.0f);
	}
	else {
		enemySpec.speed = orignSpeed;
	}
	GetCharacterMovement()->MaxWalkSpeed = 600 * enemySpec.speed;
	GetCharacterMovement()->MaxAcceleration = 2048 * enemySpec.speed;
	UE_LOG(LogTemp, Warning, TEXT("currentspeed : %f -> %f"), enemySpec.speed, 600 * enemySpec.speed);
}

//페이즈1->2로 변경 시 장비 변경
void ABaseEnemy::SwapWeapon()
{
	UE_LOG(LogTemp, Warning, TEXT("SwapWeapon"));
	ServerRPC_SwapWeapon();
}

void ABaseEnemy::ServerRPC_SwapWeapon_Implementation()
{
	if (bWillChangeWeapon && (GetMesh()->GetAnimInstance()->Montage_IsPlaying(MonChangeWeaponClose) || GetMesh()->GetAnimInstance()->Montage_IsPlaying(MonChangeWeaponLong))) {

		UE_LOG(LogTemp, Warning, TEXT("Change"));
		bWillChangeWeapon = false;
		return;
	}

	if (weapon2)
	{
		AC->StopMovement();
		weapon2AnimInst = weapon2->weaponStat.anim;
		OnRep_MakeWeapon2();
		GetMesh()->SetAnimInstanceClass(weapon2AnimInst);
		if (weapon2->weaponStat.attackRange == 150.0f)
		{
			bIsMontageSelect = true;
		}
		else
		{
			bIsMontageSelect = false;
		}
		OnRep_SwapWeapon();
	}
}

void ABaseEnemy::OnRep_SwapWeapon()
{
	if (bIsMontageSelect) {
		GetMesh()->GetAnimInstance()->Montage_Play(MonChangeWeaponClose);
		UE_LOG(LogTemp, Warning, TEXT("1to2"));
	}
	else {
		GetMesh()->GetAnimInstance()->Montage_Play(MonChangeWeaponLong);
		UE_LOG(LogTemp, Warning, TEXT("1to2"));
	}
}

//
void ABaseEnemy::LoadData(FName _bodyRowName, FName _weapon1RowName, FName _weapon2RowName, FName _gearRowName, FAIStat _AIData)
{
	UE_LOG(LogTemp, Warning, TEXT("loadData : %s, %s, %s, %s, %f"), *_bodyRowName.ToString(), *_weapon1RowName.ToString(), *_weapon2RowName.ToString(), *_gearRowName.ToString(), _AIData.battleDist);
	
	temp1 = _weapon1RowName;
	temp2 = _weapon2RowName;

	ChangeBody(_bodyRowName);
	if (_gearRowName != FName("0"))
	{
		ChangeGear(_gearRowName);
	}

	if (_weapon2RowName != FName("W2_0"))
	{
		FTimerHandle weaponTimer2;
		GetWorld()->GetTimerManager().SetTimer(weaponTimer2, FTimerDelegate::CreateLambda([&]() {
				ChangeWeapon2(temp2);
		}), 0.1f, false);
	}

	if (_weapon1RowName != FName("W1_0"))
	{
		FTimerHandle weaponTimer1;
		GetWorld()->GetTimerManager().SetTimer(weaponTimer1, FTimerDelegate::CreateLambda([&]() {
			ChangeWeapon1(temp1);
		}), 0.2f, false);
	}

	FTimerHandle WeightTimer;
	GetWorld()->GetTimerManager().SetTimer(WeightTimer, FTimerDelegate::CreateLambda([&]() {
		CheakWeightLimit();
		}), 0.3f, false);

	AIData = _AIData;

}

void ABaseEnemy::FindPlayer()
{
	//인식범위 최대값이 2000이므로
	targetDist = AIData.playerFindDist;
	//찾기 전 초기화
	playerREF = nullptr;

	for (TActorIterator<AChallengersCharacter> iter(GetWorld()); iter; ++iter) {
		AChallengersCharacter* tempPlayer = *iter;

		//이미 죽었거나 중간에 장애물이 있으면 무시한다.
		if (tempPlayer->HP <= 0 || !CheakBlock(tempPlayer))
		{
			continue;
		}

		float tempDist = FVector::Dist(GetActorLocation(), tempPlayer->GetActorLocation());
		if (tempDist < targetDist) {
			playerREF = *iter;
			targetDist = tempDist;
		}
	}

	if (playerREF == nullptr)
	{
		if (HasAuthority())
		{
			AC->SetFocus(nullptr);
		}
		AIState = EAttackState::IDLE;
	}
	else
	{
		if (HasAuthority())
		{
			AC->SetFocus(playerREF);
		}
	}//로코모션 적용용 함수.
}

bool ABaseEnemy::CheakBlock(AChallengersCharacter* tempPlayer)
{
	//체크 시작점과 끝점을 설정
	FVector startLoc = GetActorLocation();
	FVector endLoc = tempPlayer->GetActorLocation();
	float dist = FVector::Dist(startLoc, endLoc);

	FHitResult hitInfo;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	//플레이어의 캡슐 크기보다 큰 동안(실질 true)
	while (dist > 42.0f)
	{
		//찾아낸 플레이어를 향해 라인트레이스를 쏘고, 히트된 대상이 플레이어가 아니면 무시한다
		bool bResult = GetWorld()->LineTraceSingleByChannel(hitInfo, startLoc, endLoc, ECC_GameTraceChannel2, params);
		
		if (bResult)
		{
			//플레이어면 true
			if (hitInfo.GetActor() == tempPlayer)
			{
				return true;
			}
			//플레이어가 아니고 에너미도 아니면 false
			else if (!hitInfo.GetActor()->ActorHasTag(FName("Enemy")))
			{
				return false;
			}
			//에너미이면
			else{
				//시작점을 에너미 위치로 재설정
				startLoc = hitInfo.ImpactPoint;
				//맞은 에너미는 제외하기
				params.AddIgnoredActor(hitInfo.GetActor());
				//맞은 위치부터 거리 재계산
				dist = FVector::Dist(startLoc, endLoc);
			}
		}
	}
	//이건 보험
	return false;
}
/*
void ABaseEnemy::AnimCheak()
{
	if (GetMesh()->GetAnimInstance()->GetName().Contains("Manny") || GetMesh()->GetAnimInstance()->GetName().Contains("Quinn")) {
		if (HasAuthority()) {
			UE_LOG(LogTemp, Warning, TEXT("ServerAnimCheak"));
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("ClientAnimCheak"));
		}
		SetOwner(GetWorld()->GetFirstPlayerController());
		ServerRPC_AnimCheak();
	}
}

void ABaseEnemy::ServerRPC_AnimCheak_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("ServerRPC_AnimCheak Start If"));
	weapon1AnimInst = nullptr;
	weapon2AnimInst = nullptr;
	if (enemyPhase == EPhaseState::PHASE1) {
		UE_LOG(LogTemp, Warning, TEXT("enemyPhase == EPhaseState::PHASE1"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("enemyPhase != EPhaseState::PHASE1"));
	}

	if (weapon1) {
		UE_LOG(LogTemp, Warning, TEXT("weapon1"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("weapon1 = Null"));
	}



	if (weapon1 && (enemyPhase == EPhaseState::PHASE1 || (enemyPhase != EPhaseState::PHASE1 && weapon2 == nullptr))) {
		weapon1AnimInst = weapon1->weaponStat.anim;
		UE_LOG(LogTemp, Warning, TEXT("ServerRPC_AnimCheak : Name1 : %s"), *GetMesh()->GetAnimInstance()->GetName());
		OnRep_MakeWeapon1();
		GetMesh()->SetAnimInstanceClass(weapon1AnimInst);
	}
	else if (weapon2) {
		weapon2AnimInst = weapon2->weaponStat.anim;
		UE_LOG(LogTemp, Warning, TEXT("ServerRPC_AnimCheak : Name2 : %s"), *GetMesh()->GetAnimInstance()->GetName());
		OnRep_MakeWeapon2();
		GetMesh()->SetAnimInstanceClass(weapon2AnimInst);
	}
}
*/
void ABaseEnemy::ServerRPC_MoveToBattleDist_Implementation()
{
	if (playerREF == nullptr)
	{
		AIState = EAttackState::IDLE;
		return;
	}

	if (!bIsMoving)
	{
		//UE_LOG(LogTemp, Warning, TEXT("MoveToBattleDist()"));
		movePlace = GetActorLocation() - playerREF->GetActorLocation();
		movePlace.Normalize();
		movePlace *= AIData.battleDist;

		if (NavSys)
		{
			NavSys->K2_GetRandomReachablePointInRadius(GetWorld(), movePlace, movePlace, AIData.battleDist * (1.0f + FMath::RandRange(-AIData.randomArea, AIData.randomArea)));
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("No Nav!"));
			NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
			return;
		}

		movePlace += playerREF->GetActorLocation();

		movePlace.Z = GetActorLocation().Z;

		//UE_LOG(LogTemp, Warning, TEXT("Move - X: %f, Y: %f, Z: %f"), movePlace.X, movePlace.Y, movePlace.Z);
		OnRep_MoveEnemy();
		bIsMoving = true;
		GetWorld()->GetTimerManager().SetTimer(moveResetTimer, FTimerDelegate::CreateLambda([&](){
			bIsMoving = false;
			AIState = EAttackState::READY;
		}), 1.0f + AIData.moveRate, false);
	}
	else{
		moveDist = FVector::Dist(GetActorLocation(), movePlace);
		if (moveDist < GetCapsuleComponent()->GetScaledCapsuleRadius() * 2.0f) {
			if (GetWorld()->GetTimerManager().IsTimerActive(moveResetTimer)) {
				GetWorld()->GetTimerManager().ClearTimer(moveResetTimer);
			}
			bIsMoving = false;
			AIState = EAttackState::READY;
		}
	}
}

void ABaseEnemy::ServerRPC_MoveToAtkDist_Implementation()
{
	if (playerREF == nullptr)
	{
		AIState = EAttackState::IDLE;
		return;
	}

	if (!bIsMoving)
	{
		//UE_LOG(LogTemp, Warning, TEXT("MoveToAtkDist()"));
		float atkRange = 0.0f;
		switch (enemyPhase)
		{
		case EPhaseState::PHASE1:
			if (weapon1) {
				atkRange = weapon1->weaponStat.attackRange;
			}
			break;
		case EPhaseState::PHASE2:
		case EPhaseState::PHASE3:
			if (weapon2) {
				atkRange = weapon2->weaponStat.attackRange;
			}
			else if (weapon1){
				atkRange = weapon1->weaponStat.attackRange;
			}
			break;
		default:
			break;
		}
		movePlace = GetActorLocation() - playerREF->GetActorLocation();
		movePlace.Normalize();
		movePlace *= (atkRange * 0.4f);
		movePlace += playerREF->GetActorLocation();
		movePlace.Z = GetActorLocation().Z;

		//UE_LOG(LogTemp, Warning, TEXT("Atk - X: %f, Y: %f, Z: %f"), movePlace.X, movePlace.Y, movePlace.Z);

		OnRep_MoveEnemy();
		bIsMoving = true;

		GetWorld()->GetTimerManager().SetTimer(moveResetTimer, FTimerDelegate::CreateLambda([&]() {
			bIsMoving = false;
			AIState = EAttackState::READY;
		}), 1.0f + AIData.moveRate, false);
	}
	else {
		moveDist = FVector::Dist(GetActorLocation(), movePlace);
		if (moveDist < GetCapsuleComponent()->GetScaledCapsuleRadius() * 2.0f) {
			if(GetWorld()->GetTimerManager().IsTimerActive(moveResetTimer)){
				GetWorld()->GetTimerManager().ClearTimer(moveResetTimer);
			}
			bIsMoving = false;
			AIState = EAttackState::READY;
		}
	}
}

void ABaseEnemy::OnRep_MoveEnemy()
{
	if (AC) {
		AC->MoveToLocation(movePlace);
	}
}

void ABaseEnemy::ServerRPC_Attack_Implementation()
{
	if (!bIsAttacked) {
		if (atkAnimSelect == -1 && ((enemyPhase == EPhaseState::PHASE1 && weapon1) || (enemyPhase != EPhaseState::PHASE1 && weapon2 == nullptr && weapon1))) {
			atkAnimSelect = weapon1->weaponStat.attackSelector[(int32)FMath::RandRange(0, weapon1->atkMoveNum)];
		}
		else if (atkAnimSelect == -1 && weapon2) {
			atkAnimSelect = weapon2->weaponStat.attackSelector[(int32)FMath::RandRange(0, weapon2->atkMoveNum)];
		}
		bIsAttacked = true;
	}
}

void ABaseEnemy::UseGear()
{
	if (!GetMesh()->GetAnimInstance()->Montage_IsPlaying(MonGearActive)) {
		//UE_LOG(LogTemp, Warning, TEXT("UseGear()"));
		GetMesh()->GetAnimInstance()->Montage_SetPlayRate(MonGearActive, 0.25);
		GetMesh()->GetAnimInstance()->Montage_Play(MonGearActive);
	}
}

float ABaseEnemy::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	ServerRPC_dmgCal(Damage, DamageCauser);
	
	return 0.0f;
}

void ABaseEnemy::ServerRPC_dmgCal_Implementation(float damage, AActor* DamageCauser)
{
	currentHP -= damage * (FMath::Clamp(100.0f - (float)enemySpec.totalDEF, 0.0f, 100.0f) / 100.0f);
	UE_LOG(LogTemp, Warning, TEXT("Enemy HP : %d"), currentHP);

	//죽었을 때 마지막 공격을 가한 플레이어를 바라본다.
	if (currentHP <= 0)
	{
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		AIState = EAttackState::DIED;
		GetCharacterMovement()->SetMovementMode(MOVE_None);
		auto gm = Cast<AOurGameModeBase>(GetWorld()->GetAuthGameMode());
		if (gm)
		{
			// 죽을 때 게임모드의 총 카운트를 -1 한다
			if (gm->enemyCurrent > 0)
			{
				gm->enemyCurrent -= 1;

				if (gm->enemyCurrent == 0)
				{
					gm->bDungeonFinished = true;
				}
			}

		}

		if (damage <= 100) {
			deathAnimSelect = FMath::RandRange(0, 1);
		}
		else {
			deathAnimSelect = FMath::RandRange(2, 3);
		}
	}

	OnRep_PhaseCheck();
}

void ABaseEnemy::Died(bool bDiedInBattle)
{
	ServerRPC_Died(bDiedInBattle);
}

void ABaseEnemy::ServerRPC_Died_Implementation(bool bDiedInBattle)
{
	if (bIsAlreadyDied)
	{
		return;
	}
	else
	{
		bIsAlreadyDied = true;
	}

	if (HasAuthority() && AC) {
		AC->SetFocus(nullptr);
	}

	if (bDiedInBattle) {
		if (weapon1) {
			//weapon1->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			//weapon1->weaponBody->SetSimulatePhysics(true);
			//weapon1->weaponBody->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
			FTimerHandle drop1Timer;
			GetWorld()->GetTimerManager().SetTimer(drop1Timer, FTimerDelegate::CreateLambda([&]() {
				if (weapon1->ActorHasTag(FName("LongWeapon"))) {
					Cast<ALongWeapon>(weapon1)->ClearBullet();
				}
				else{
					weapon1->ClearBleed();
				}
				}), 1.5f, false);
		}
		if (weapon2) {
			//weapon2->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			//weapon2->weaponBody->SetSimulatePhysics(true);
			//weapon2->weaponBody->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
			FTimerHandle drop2Timer;
			GetWorld()->GetTimerManager().SetTimer(drop2Timer, FTimerDelegate::CreateLambda([&]() {
				if (weapon2->ActorHasTag(FName("LongWeapon"))) {
					Cast<ALongWeapon>(weapon2)->ClearBullet();
				}
				else {
					weapon2->ClearBleed();
				}
				}), 1.5f, false);
		}
		if (gear) {
			gear->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			gear->Destroy();
		}

		FTimerHandle killTimer;
		GetWorld()->GetTimerManager().SetTimer(killTimer, FTimerDelegate::CreateLambda([&]() {
			Destroy();
			}), 3.0f, false);
	}
	else {
		if (weapon1) {
			weapon1->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			if (weapon1->ActorHasTag(FName("LongWeapon"))) {
				Cast<ALongWeapon>(weapon1)->ClearBullet();
			}
			else {
				weapon1->ClearBleed();
			}
		}
		if (weapon2) {
			weapon2->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			if (weapon2->ActorHasTag(FName("LongWeapon"))) {
				Cast<ALongWeapon>(weapon2)->ClearBullet();
			}
			else {
				weapon2->ClearBleed();
			}
		}
		if (gear) {
			gear->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			gear->Destroy();
		}

		FTimerHandle killTimer;
		GetWorld()->GetTimerManager().SetTimer(killTimer, FTimerDelegate::CreateLambda([&]() {
			Destroy();
			}), 0.1f, false);
	}
}

void ABaseEnemy::OnRep_PhaseCheck()
{
	if (enemySpec.bIsBossType == true && enemyPhase == EPhaseState::PHASE1 && currentHP <= enemySpec.totalHP * AIData.phase2Rate) {
		//UE_LOG(LogTemp, Warning, TEXT("PHASE2"));
		enemyPhase = EPhaseState::PHASE2;
		if (weapon2)
		{
			bWillChangeWeapon = true;
		}
	}
	else if (enemySpec.bIsBossType == true && enemyPhase != EPhaseState::PHASE3 && currentHP <= enemySpec.totalHP * AIData.phase3Rate) {
		//UE_LOG(LogTemp, Warning, TEXT("PHASE3"));
		enemyPhase = EPhaseState::PHASE3;
	}
	else if (currentHP <= 0)
	{
		AIState = EAttackState::DIED;
	}
}

void ABaseEnemy::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// 에너미 체력 동기화
	DOREPLIFETIME(ABaseEnemy, currentHP);
	DOREPLIFETIME(ABaseEnemy, movePlace);
	DOREPLIFETIME(ABaseEnemy, atkAnimSelect);
	DOREPLIFETIME(ABaseEnemy, AIState);
	DOREPLIFETIME(ABaseEnemy, playerREF);
	DOREPLIFETIME(ABaseEnemy, moveDist);
	DOREPLIFETIME(ABaseEnemy, deathAnimSelect);
	DOREPLIFETIME(ABaseEnemy, bodyRowName);
	DOREPLIFETIME(ABaseEnemy, gearRowName);
	DOREPLIFETIME(ABaseEnemy, weapon1AnimInst);
	DOREPLIFETIME(ABaseEnemy, weapon2AnimInst);
	DOREPLIFETIME(ABaseEnemy, bIsAttacked);
	DOREPLIFETIME(ABaseEnemy, bIsMontageSelect);
}

void ABaseEnemy::Anim_detach_Weapon()
{
	if (weapon1)
	{
		weapon1->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		weapon1->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("Weapon1Hanger"));
	}
}

void ABaseEnemy::Anim_attach_Weapon()
{
	if (weapon2)
	{
		weapon2->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		weapon2->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("hand_rSocket"));
	}

	cAnimInst = nullptr;
	lAnimInst = nullptr;
}

void ABaseEnemy::Anim_CloseAtkStart()
{
	if ((enemyPhase == EPhaseState::PHASE1 && weapon1) || (enemyPhase != EPhaseState::PHASE1 && weapon2 == nullptr && weapon1)) {
		weapon1->ActiveDmgBox();
	}
	else if (weapon2){
		weapon2->ActiveDmgBox();
	}
}

void ABaseEnemy::Anim_CloseAtkEnd()
{
	if ((enemyPhase == EPhaseState::PHASE1 && weapon1) || (enemyPhase != EPhaseState::PHASE1 && weapon2 == nullptr && weapon1)) {
		weapon1->DeactiveDmgBox();
	}
	else if (weapon2){
		weapon2->DeactiveDmgBox();
	}
}

void ABaseEnemy::Anim_AttackEnd()
{
	AIState = EAttackState::READY;
	bIsAttacked = false;
	atkAnimSelect = -1;
}

void ABaseEnemy::Anim_FireMagic()
{
	FVector firePos = GetActorLocation() + GetActorForwardVector() * 150.0f;
	FVector targetPos = FVector::ZeroVector;
	if (playerREF)
	{
		targetPos = playerREF->GetActorLocation();
	}

	FRotator targetDir = (targetPos - firePos).Rotation();

	if ((enemyPhase == EPhaseState::PHASE1 && weapon1) || (enemyPhase != EPhaseState::PHASE1 && weapon2 == nullptr && weapon1)) {
		Cast<ALongWeapon>(weapon1)->FireMagic(firePos, targetDir, targetPos);
	}
	else if (weapon2) {
		Cast<ALongWeapon>(weapon2)->FireMagic(firePos, targetDir, targetPos);
	}
}

void ABaseEnemy::Anim_ActiveGear()
{
	if (gear)
	{
		gear->ActivateGear();
	}
}
