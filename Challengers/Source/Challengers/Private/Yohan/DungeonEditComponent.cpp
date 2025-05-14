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

	// ���� ������ UI�� ����
	if (dungeonEditUI_BP)
	{
		dungeonEditUI = CreateWidget<UDungeonEditWidget>(GetWorld(), dungeonEditUI_BP);
		dungeonEditUI->AddToViewport();

		dungeonEditUI->text_costOver->SetVisibility(ESlateVisibility::Hidden);
	}
	
	// �÷��̾� ã�ƿ���
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
		// ��ġ�� �� ���� ���̶�� �������� ������
		if (!bIsObjectFixed && (!IsEnemyOnNavMesh(enemyLocation) || gm->curEnemyCost + SelectedEnemy->enemySpec.totalCost >= gm->totalEnemyCost))
		{
			SelectedEnemy->GetMesh()->SetOverlayMaterial(redMI);
			// ������ ���ʹ��� �������� ����
			SelectedEnemy->SetActorEnableCollision(false);
		}		
		// ��ġ�� �� �ִ� ���� �ִٸ�, �������� �ʷϻ�
		else if (!bIsObjectFixed && IsEnemyOnNavMesh(enemyLocation))
		{
			SelectedEnemy->GetMesh()->SetOverlayMaterial(greenMI);
			// ������ ���ʹ��� �������� �Ҵ�
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
		// ���� ������ ������ �̵��� �� �ε�UI ����

		// �ε�â ��Ÿ ���� ���Ⱑ �ƴ϶� UI���� �ʿ� ���� ȣ���ϵ��� ����
		loadingUI = CreateWidget<ULoadingWidget>(GetWorld(), loadingUI_BP);
		loadingUI->AddToViewport(1);
		loadingUI->HideAll();
	
	}

	bool bOutSuccess;

	// ���� ��ġ�ϴ� ���͸� �ҷ��´�
	// GetActorOfClass�� �̿��ؼ� ĳ������ �Ѵ�
	AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ALevelPlace::StaticClass());
	if (FoundActor)
	{
		auto LevelPlaceActor = Cast<ALevelPlace>(FoundActor);
		if (LevelPlaceActor)
		{
			// ���� ��ġ�ϴ� ������ ��ġ���� �����´�
			levLocation = LevelPlaceActor->GetActorLocation();
		}
	}
	
	// ���ϴ� ������ ���� ������ ���� �ʰ�, ���ϴ� ��ġ�� �ҷ��´�.
	ULevelStreamingDynamic* StreamingLevel = ULevelStreamingDynamic::LoadLevelInstance(GetWorld(), MapName.ToString(), levLocation, FRotator::ZeroRotator, bOutSuccess);
   
	// ������ �ҷ��Դٸ�..
	if (StreamingLevel)
    {		
		// �÷��̾ ���� ����� ��ġ ��Ų��
		levLocation.Z += 2500;
		dc->SetActorLocation(levLocation);				

		// ���� ������ UI ĵ���� ���̰� �ϱ�
		loadingUI->FadeOutStart(4);
		FTimerHandle timer;
		GetWorld()->GetTimerManager().SetTimer(timer, [&] {
			ShowArea();
			// �ε��� �����ٸ� �ε� UI �����
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

// �ҷ��� �� ����
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
	// ���ʹ� ���� �Ǵ��� ����
	bIsObjectFixed = false;

	if (pc)
	{
		// ���콺 Ŀ�� ���̴� �� = ���ʹ� ����
		pc->bShowMouseCursor = true;
				
		// �����Ϸ��� ���ʹ̰� �ִٸ�
		if (SelectedEnemy_BP && SelectedEnemy == nullptr)
		{			
			FHitResult HitResult;
			FVector SpawnLocation = HitResult.Location;
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			// ���콺 Ŀ�� ��ġ�� ���ʹ� ����
			SelectedEnemy = GetWorld()->SpawnActor<ABaseEnemy>(SelectedEnemy_BP, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
			
			// ������ ���ʹ̰� �ִٸ�
			if (SelectedEnemy)
			{
				// ������ ���ʹ̿� ���̺�� ������ �־��ֱ�
				SelectedEnemy->LoadData(_body, _weapon1, _weapon2, _gear, _AIData);		
				
				// ������ ���ʹ��� �������� ����
				SelectedEnemy->SetActorEnableCollision(false);				
			}
			
		}
		
		// ��ǲ ��带 UI & Game���� ���༭ �Ѵ� �����̰� ����
		//pc->SetInputMode(FInputModeGameAndUI());
	}
}

void UDungeonEditComponent::UpdateObjectPosition()
{
	FHitResult HitResult;
	// ���콺 Ŀ���� �浹 ����� ������
	if (GetMouseCursorHitResult(HitResult))
	{
		// ������ ���ʹ��� ��ġ�� ���콺�� �����ϱ�
		FVector TargetLocation = HitResult.Location;
		if (SelectedEnemy)
		{
			TargetLocation.Z += SelectedEnemy->GetSimpleCollisionHalfHeight(); // ������Ʈ�� �ٴ� ���� �ֵ��� ���� ����
			SelectedEnemy->SetActorLocation(TargetLocation);
		}
		
		// ���ʹ� ��ġ�Ǳ� �� ��ġ�� ����
		enemyLocation = SelectedEnemy->GetActorLocation();
	}
}

bool UDungeonEditComponent::GetMouseCursorHitResult(FHitResult& HitResult)
{
	if (pc)
	{
		// ECC_WorldStatic ä�η� �浹 üũ, üũ�� ���� ���ٸ�
		bool bHit = pc->GetHitResultUnderCursor(ECC_WorldStatic, false, HitResult);
		if (!bHit)
		{
			// ECC_Visibility ä�η� ��õ�
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
	// ���� ���� NavMesh�� �����´�
	UNavigationSystemV1* navSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	// NavMesh�� ���ٸ� False
	if (!navSys)
	{
		return false;
	}
	// NavMesh�� ��ġ�� �޾ƿ�
	FNavLocation navLocation;
	// ProjectPointToNavigation �Լ��� ����ؼ� Location�� NavMesh �ȿ� �ִ��� ���� ��ȯ
	bool bisOnNavMesh = navSys->ProjectPointToNavigation(Location, navLocation);

	return bisOnNavMesh;
}

void UDungeonEditComponent::SetEnemyLocation()
{
	if (!SelectedEnemy)
	{
		return;
	}

	// ���콺 Ŭ���� ���� ��, bIsObjectFixed�� False �̰�, bisOnNavMesh�� True �̰�, ����cost�� totalCost���� �۴ٸ�
	if (!bIsObjectFixed && IsEnemyOnNavMesh(enemyLocation) && gm->curEnemyCost + SelectedEnemy->enemySpec.totalCost <= gm->totalEnemyCost)
	{
		

		// bIsObjectFixed �� True�� �ٲ㼭 ��ġ ����
		bIsObjectFixed = true;

		// ������ ���ʹ��� �ڽ�Ʈ�� �޾ƿ´�		
		// ������ ���ʹ��� �ڽ�Ʈ�� ���Ӹ�忡 �����ؼ�, totalCost�� ���Ѵ�
		gm->curEnemyCost = gm->curEnemyCost + SelectedEnemy->enemySpec.totalCost;

		pc->bShowMouseCursor = true;
		
		// ���ʹ� ���͸��� ������� ������
		SelectedEnemy->GetMesh()->SetOverlayMaterial(nullptr);

		// SelectedEnemy �Ҵ� ����
		SelectedEnemy = nullptr;
	}
	// ���� �ڽ�Ʈ�� totalCost���� ũ�ٸ�
	else if (gm->curEnemyCost >= gm->totalEnemyCost)
	{
		// ���ʹ� ��ġ �ȵǰ� �ؾ� ��
		bIsObjectFixed = false;
		// �ڽ�Ʈ�� �ʰ� �Ǿ��ٴ� ���� ���
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

			// UI�� �����ϵ��� ����
			AActor* OwnerActor = GetOwner();
			Params.AddIgnoredActor(OwnerActor); // �θ� ���͸� ����

			// ECC_WorldStatic ä�η� ���� Ʈ���̽�
			bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_WorldStatic, Params);
			if (!bHit)
			{
				// ECC_Visibility ä�η� ��õ�
				bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);
			}

			// �浹�� ���� enemy���
			if (bHit && HitResult.GetActor()->ActorHasTag(FName("Enemy")) && SelectedEnemy == nullptr)
			{
				// enemy ��Ʈ�� ���� ����
				if (controllUI_BP)
				{
					controllUI = CreateWidget<UDE_EnemyControlWidget>(GetWorld(), controllUI_BP);
					controllUI->AddToViewport();

					// ���콺 Ŀ�� ��ġ�� ����
					FVector2D MousePosition;
					if (pc->GetMousePosition(MousePosition.X, MousePosition.Y))
					{
						controllUI->SetPositionInViewport(MousePosition, true);

						bisControlUI = true;
					}
				}
				// �浹 ������ ���͸� SelectedEnemy�� �����
				_selectedEnemy = Cast<ABaseEnemy>(HitResult.GetActor());

				SelectedEnemy = _selectedEnemy;

				// ��Ʈ�� ������ �����Ǿ� ���� ���� ���� ������ ������ Ŭ�� �ȵǰ� ����
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

			// ��Ʈ�� ���� �����, ���������� UI �ٽ� Ȱ��ȭ
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

	// ���ʹ̸� ������ �� �ִ� ���·� �����
	bIsObjectFixed = false;

	// ������ ���ʹ��� �������� ����
	SelectedEnemy->SetActorEnableCollision(false); 
	
	// �̹� ��ġ�� ������ üũ
	bIsMoved = true;

	// �̹� ��ġ�Ǿ��ٸ�, �ڽ�Ʈ�� 0���� �����Ѵ�
	if (bIsMoved)
	{
		SelectedEnemy->enemySpec.totalCost = 0;
	}
}


void UDungeonEditComponent::SetEnemyDelete()
{	
	controllUI->SetVisibility(ESlateVisibility::Hidden);

	// ������ ��, ���� �ڽ�Ʈ���� ������ ���ʹ��� �ڽ�Ʈ�� ����
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
		// ECC_WorldStatic ä�η� �浹 üũ, üũ�� ���� ���ٸ�
		bool bHit = pc->GetHitResultUnderCursor(ECC_WorldStatic, false, hitResult);
		if (!bHit)
		{
			// ECC_Visibility ä�η� ��õ�
			bHit = pc->GetHitResultUnderCursor(ECC_Visibility, false, hitResult);
		}
		// �浹�� ���� enemy���
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


