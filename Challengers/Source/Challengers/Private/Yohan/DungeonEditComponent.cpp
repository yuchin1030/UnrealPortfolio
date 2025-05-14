// Fill out your copyright notice in the Description page of Project Settings.


#include "Yohan/DungeonEditComponent.h"
#include "Yohan/DungeonEditWidget.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "OurGameInstance.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Engine/LevelStreamingDynamic.h>
#include "ChallengersCharacter.h"
#include "Yohan/LevelPlace.h"
#include "OurGameModeBase.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/SpectatorPawn.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Engine/DirectionalLight.h>
#include "Engine.h"
#include "Yohan/DungeonEditCharacter.h"
#include "MainPlayerController.h"
#include "Yohan/DungeonEditCharacterController.h"
#include <../../../../../../../Source/Runtime/NavigationSystem/Public/NavigationSystem.h>
#include "Yohan/SaveDungeonData.h"
#include "Yohan/DungeonEditGameModeBase.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/TextBlock.h>
#include "Yohan/DE_EnemyControlWidget.h"
#include <../../../../../../../Source/Runtime/NavigationSystem/Public/NavMesh/RecastNavMesh.h>
#include "LoadingWidget.h"
#include "Components/Image.h"



UDungeonEditComponent::UDungeonEditComponent()
{
	
	PrimaryComponentTick.bCanEverTick = true;


}



void UDungeonEditComponent::BeginPlay()
{
	Super::BeginPlay();

	// 던전 에디터 UI를 띄운다
	if (dungeonEditUI_BP)
	{
		dungeonEditUI = CreateWidget<UDungeonEditWidget>(GetWorld(), dungeonEditUI_BP);
		dungeonEditUI->AddToViewport();

		dungeonEditUI->text_costOver->SetVisibility(ESlateVisibility::Hidden);
	}
	
	// 플레이어 찾아오기
	for (TActorIterator<ADungeonEditCharacter> It(GetWorld()); It; ++It)
	{
		dc = *It;
	}

	for (TActorIterator<ADungeonEditCharacterController> It(GetWorld()); It; ++It)
	{
		pc = *It;
	}
	
	gm = Cast<ADungeonEditGameModeBase>(GetWorld()->GetAuthGameMode());

	
}


void UDungeonEditComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (SelectedEnemy && !bIsObjectFixed)
	{
		UpdateObjectPosition();
	}
	
	if (SelectedEnemy != nullptr)
	{		
		// 배치할 수 없는 곳이라면 오버레이 빨간색
		if (!bIsObjectFixed && (!IsEnemyOnNavMesh(enemyLocation) || gm->curEnemyCost + SelectedEnemy->enemySpec.totalCost >= gm->totalEnemyCost))
		{
			SelectedEnemy->GetMesh()->SetOverlayMaterial(redMI);
			// 스폰된 에너미의 피직스를 끈다
			SelectedEnemy->SetActorEnableCollision(false);
		}		
		// 배치할 수 있는 곳에 있다면, 오버레이 초록색
		else if (!bIsObjectFixed && IsEnemyOnNavMesh(enemyLocation))
		{
			SelectedEnemy->GetMesh()->SetOverlayMaterial(greenMI);
			// 스폰된 에너미의 피직스를 켠다
			SelectedEnemy->SetActorEnableCollision(true);
		}

		else if (bIsObjectFixed && bisControlUI && SelectedEnemy)
		{
			SelectedEnemy->GetMesh()->SetOverlayMaterial(yellowMI);
		}
		else
		{
			if (SelectedEnemy)
			{
				SelectedEnemy->GetMesh()->SetOverlayMaterial(nullptr);
			}

		}

	}
		ActiveOverlay();
	
	
}

void UDungeonEditComponent::OpenMap(FName MapName)
{
	if (loadingUI_BP)
	{
		// 던전 에디터 맵으로 이동할 때 로딩UI 띄우기

		// 로딩창 베타 때는 여기가 아니라 UI에서 맵에 따라 호출하도록 변경
		loadingUI = CreateWidget<ULoadingWidget>(GetWorld(), loadingUI_BP);
		loadingUI->AddToViewport(1);
		loadingUI->HideAll();
	
	}

	bool bOutSuccess;

	// 레벨 배치하는 액터를 불러온다
	// GetActorOfClass를 이용해서 캐스팅을 한다
	AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ALevelPlace::StaticClass());
	if (FoundActor)
	{
		auto LevelPlaceActor = Cast<ALevelPlace>(FoundActor);
		if (LevelPlaceActor)
		{
			// 레벨 배치하는 액터의 위치값을 가져온다
			levLocation = LevelPlaceActor->GetActorLocation();
		}
	}
	
	// 원하는 레벨을 현재 레벨을 닫지 않고, 원하는 위치에 불러온다.
	ULevelStreamingDynamic* StreamingLevel = ULevelStreamingDynamic::LoadLevelInstance(GetWorld(), MapName.ToString(), levLocation, FRotator::ZeroRotator, bOutSuccess);
   
	// 레벨이 불려왔다면..
	if (StreamingLevel)
    {		
		// 플레이어를 맵의 상공에 위치 시킨다
		levLocation.Z += 2500;
		dc->SetActorLocation(levLocation);				

		// 던전 에디터 UI 캔버스 보이게 하기
		loadingUI->FadeOutStart(4);
		FTimerHandle timer;
		GetWorld()->GetTimerManager().SetTimer(timer, [&] {
			ShowArea();
			// 로딩이 끝났다면 로딩 UI 지우기
			loadingUI->RemoveFromParent();
			if (loadingEndDelegate.IsBound()) {
				loadingEndDelegate.Execute();
			}
			}, 5, false);

		FInputModeGameAndUI inputMode;
		inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockOnCapture);
		pc->SetInputMode(inputMode);
	}
   
}

// 불러온 맵 끄기
void UDungeonEditComponent::CloseMap(FName MapName)
{
	ULevelStreaming* StreamingLevel = UGameplayStatics::GetStreamingLevel(this, MapName);
	if (StreamingLevel)
	{
		StreamingLevel->SetShouldBeLoaded(false);
		StreamingLevel->SetShouldBeVisible(false);
		StreamingLevel->bShouldBlockOnLoad = false;
		StreamingLevel->SetIsRequestingUnloadAndRemoval(true);
		
		HideArea();
	}
}



void UDungeonEditComponent::OnMouseClick(FName _body, FName _weapon1, FName _weapon2, FName _gear, FAIStat _AIData)
{
	if (SelectedEnemy)
	{
		SelectedEnemy->Died(false);
		SelectedEnemy = nullptr;
	}
	// 에너미 고정 되는지 여부
	bIsObjectFixed = false;

	if (pc)
	{
		// 마우스 커서 보이는 것 = 에너미 고정
		pc->bShowMouseCursor = true;
				
		// 스폰하려는 에너미가 있다면
		if (SelectedEnemy_BP && SelectedEnemy == nullptr)
		{			
			FHitResult HitResult;
			FVector SpawnLocation = HitResult.Location;
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			// 마우스 커서 위치에 에너미 스폰
			SelectedEnemy = GetWorld()->SpawnActor<ABaseEnemy>(SelectedEnemy_BP, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
			
			// 스폰한 에너미가 있다면
			if (SelectedEnemy)
			{
				// 스폰된 에너미에 세이브된 데이터 넣어주기
				SelectedEnemy->LoadData(_body, _weapon1, _weapon2, _gear, _AIData);		
				
				// 스폰된 에너미의 피직스를 끈다
				SelectedEnemy->SetActorEnableCollision(false);				
			}
			
		}
		
		// 인풋 모드를 UI & Game으로 해줘서 둘다 움직이게 가능
		//pc->SetInputMode(FInputModeGameAndUI());
	}
}

void UDungeonEditComponent::UpdateObjectPosition()
{
	FHitResult HitResult;
	// 마우스 커서의 충돌 결과를 가져옴
	if (GetMouseCursorHitResult(HitResult))
	{
		// 스폰된 에너미의 위치를 마우스에 고정하기
		FVector TargetLocation = HitResult.Location;
		if (SelectedEnemy)
		{
			TargetLocation.Z += SelectedEnemy->GetSimpleCollisionHalfHeight(); // 오브젝트가 바닥 위에 있도록 높이 조정
			SelectedEnemy->SetActorLocation(TargetLocation);
		}
		
		// 에너미 배치되기 전 위치를 저장
		enemyLocation = SelectedEnemy->GetActorLocation();
	}
}

bool UDungeonEditComponent::GetMouseCursorHitResult(FHitResult& HitResult)
{
	if (pc)
	{
		// ECC_WorldStatic 채널로 충돌 체크, 체크된 것이 없다면
		bool bHit = pc->GetHitResultUnderCursor(ECC_WorldStatic, false, HitResult);
		if (!bHit)
		{
			// ECC_Visibility 채널로 재시도
			bHit = pc->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
		}

		if (bHit && HitResult.GetActor()->ActorHasTag(FName("Enemy")))
		{
			return false;
		}
		
		return bHit;
	}
		return false;
	
}

bool UDungeonEditComponent::IsEnemyOnNavMesh(FVector Location)
{
	// 현재 맵의 NavMesh를 가져온다
	UNavigationSystemV1* navSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	// NavMesh가 없다면 False
	if (!navSys)
	{
		return false;
	}
	// NavMesh의 위치를 받아옴
	FNavLocation navLocation;
	// ProjectPointToNavigation 함수를 사용해서 Location이 NavMesh 안에 있는지 여부 반환
	bool bisOnNavMesh = navSys->ProjectPointToNavigation(Location, navLocation);

	return bisOnNavMesh;
}

void UDungeonEditComponent::SetEnemyLocation()
{
	if (!SelectedEnemy)
	{
		return;
	}

	// 마우스 클릭을 했을 때, bIsObjectFixed가 False 이고, bisOnNavMesh가 True 이고, 현재cost가 totalCost보다 작다면
	if (!bIsObjectFixed && IsEnemyOnNavMesh(enemyLocation) && gm->curEnemyCost + SelectedEnemy->enemySpec.totalCost <= gm->totalEnemyCost)
	{
		

		// bIsObjectFixed 를 True로 바꿔서 위치 고정
		bIsObjectFixed = true;

		// 스폰된 에너미의 코스트를 받아온다		
		// 스폰된 에너미의 코스트를 게임모드에 저장해서, totalCost와 비교한다
		gm->curEnemyCost = gm->curEnemyCost + SelectedEnemy->enemySpec.totalCost;

		pc->bShowMouseCursor = true;
		
		// 에너미 매터리얼 원래대로 돌리기
		SelectedEnemy->GetMesh()->SetOverlayMaterial(nullptr);

		// SelectedEnemy 할당 해제
		SelectedEnemy = nullptr;
	}
	// 현재 코스트가 totalCost보다 크다면
	else if (gm->curEnemyCost >= gm->totalEnemyCost)
	{
		// 에너미 배치 안되게 해야 함
		bIsObjectFixed = false;
		// 코스트가 초과 되었다는 문구 출력
		dungeonEditUI->text_costOver->SetVisibility(ESlateVisibility::Visible);

		FTimerHandle costOver;
		GetWorld()->GetTimerManager().SetTimer(costOver, [&]{
			dungeonEditUI->text_costOver->SetVisibility(ESlateVisibility::Hidden);
		}, 1, false);
	}
	
}

void UDungeonEditComponent::ShowControlWidget()
{
	FHitResult HitResult;
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		FVector WorldLocation, WorldDirection;
		if (PC->DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
		{
			FVector Start = WorldLocation;
			FVector End = WorldLocation + (WorldDirection * 10000.0f);

			FCollisionQueryParams Params;
			Params.bTraceComplex = true;

			// UI를 무시하도록 설정
			AActor* OwnerActor = GetOwner();
			Params.AddIgnoredActor(OwnerActor); // 부모 액터를 무시

			// ECC_WorldStatic 채널로 라인 트레이스
			bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_WorldStatic, Params);
			if (!bHit)
			{
				// ECC_Visibility 채널로 재시도
				bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);
			}

			// 충돌한 것이 enemy라면
			if (bHit && HitResult.GetActor()->ActorHasTag(FName("Enemy")) && SelectedEnemy == nullptr)
			{
				// enemy 컨트롤 위젯 생성
				if (controllUI_BP)
				{
					controllUI = CreateWidget<UDE_EnemyControlWidget>(GetWorld(), controllUI_BP);
					controllUI->AddToViewport();

					// 마우스 커서 위치에 생성
					FVector2D MousePosition;
					if (pc->GetMousePosition(MousePosition.X, MousePosition.Y))
					{
						controllUI->SetPositionInViewport(MousePosition, true);

						bisControlUI = true;
					}
				}
				// 충돌 감지된 액터를 SelectedEnemy로 만든다
				_selectedEnemy = Cast<ABaseEnemy>(HitResult.GetActor());

				SelectedEnemy = _selectedEnemy;

				// 컨트롤 위젯이 생성되어 있을 때는 던전 에디터 위젯이 클릭 안되게 막음
				dungeonEditUI->SetVisibility(ESlateVisibility::HitTestInvisible);
			}
		}
	}
	
}

void UDungeonEditComponent::HideControlWidget()
{
	if (!bIsMoved)
	{
		if (controllUI && bisControlUI)
		{
			controllUI->RemoveFromParent();

			// 컨트롤 위젯 지우고, 던전에디터 UI 다시 활성화
			dungeonEditUI->SetVisibility(ESlateVisibility::Visible);

			if (SelectedEnemy)
			{
				SelectedEnemy->GetMesh()->SetOverlayMaterial(nullptr);

				SelectedEnemy = nullptr;
			}
			
			bisControlUI = false;
		}
	}	
}


void UDungeonEditComponent::SetEnemyMove()
{
	controllUI->SetVisibility(ESlateVisibility::Hidden);

	// 에너미를 움직일 수 있는 상태로 만든다
	bIsObjectFixed = false;

	// 스폰된 에너미의 피직스를 끈다
	SelectedEnemy->SetActorEnableCollision(false); 
	
	// 이미 배치된 것인지 체크
	bIsMoved = true;

	// 이미 배치되었다면, 코스트를 0으로 간주한다
	if (bIsMoved)
	{
		SelectedEnemy->enemySpec.totalCost = 0;
	}
}


void UDungeonEditComponent::SetEnemyDelete()
{	
	controllUI->SetVisibility(ESlateVisibility::Hidden);

	// 삭제될 때, 현재 코스트에서 삭제된 에너미의 코스트를 뺀다
	gm->curEnemyCost = gm->curEnemyCost - SelectedEnemy->enemySpec.totalCost;

	SelectedEnemy->Died(false);

	SelectedEnemy = nullptr;
	
}

void UDungeonEditComponent::ShowArea()
{
	if (!disAbleArea_BP || !enAbleArea_BP)
	{
		return;
	}

	TArray<AActor*> enAbleAreas;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), enAbleArea_BP, enAbleAreas);

	for (int j = 0; j < enAbleAreas.Num(); j++)
	{
		enAbleAreas[j]->SetActorHiddenInGame(false);
		enAbleAreas[j]->SetActorEnableCollision(false);
	}
}

void UDungeonEditComponent::HideArea()
{
	TArray<AActor*> disAbleAreas;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), disAbleArea_BP, disAbleAreas);

	for (int i = 0; i < disAbleAreas.Num(); i++)
	{
		disAbleAreas[i]->SetActorHiddenInGame(true);
		disAbleAreas[i]->SetActorEnableCollision(false);
	}

	TArray<AActor*> enAbleAreas;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), enAbleArea_BP, enAbleAreas);

	for (int j = 0; j < enAbleAreas.Num(); j++)
	{
		enAbleAreas[j]->SetActorHiddenInGame(true);
		enAbleAreas[j]->SetActorEnableCollision(false);
	}
}

void UDungeonEditComponent::ActiveOverlay()
{
	FHitResult hitResult;
	if (pc)
	{
		// ECC_WorldStatic 채널로 충돌 체크, 체크된 것이 없다면
		bool bHit = pc->GetHitResultUnderCursor(ECC_WorldStatic, false, hitResult);
		if (!bHit)
		{
			// ECC_Visibility 채널로 재시도
			bHit = pc->GetHitResultUnderCursor(ECC_Visibility, false, hitResult);
		}
		// 충돌한 것이 enemy라면
		if (bIsObjectFixed && bHit && hitResult.GetActor()->ActorHasTag(FName("Enemy")) && SelectedEnemy == nullptr )
		{	
			_enemy = Cast<ABaseEnemy>(hitResult.GetActor());
			_enemy->GetMesh()->SetOverlayMaterial(yellowMI); 			
		}
		else
		{
			if (_enemy)
			{
				_enemy->GetMesh()->SetOverlayMaterial(nullptr);
				_enemy = nullptr;
			}
			
		}
	}
}


