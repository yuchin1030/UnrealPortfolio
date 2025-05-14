#include "BJK/BuffDebuffManager.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "OurGameInstance.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h>
#include "SkillStruct.h"
#include "ChallengersCharacter.h"
#include "MainPlayerController.h"
#include "BJK/MainPlayerWidget.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/PlayerController.h>
#include <../../../../../../../Source/Runtime/Engine/Public/EngineUtils.h>
#include "Net/UnrealNetwork.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/TextBlock.h>
#include "Yohan/OurGameStateBase.h"
#include "Yohan/EnemyCountInDungeonWidget.h"

ABuffDebuffManager::ABuffDebuffManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABuffDebuffManager::BeginPlay()
{
	Super::BeginPlay();
	
    gi = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());
}

void ABuffDebuffManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (block)
    {
        AChallengersCharacter* player = Cast<AChallengersCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
        BlockChange -= DeltaTime;
         PlayerController->mainplayerWidget->TextBlock_BlockTime->SetText(FText::FromString(FString::FromInt(BlockChange)));

        if (BlockChange <= 0)
        {
            block = false;
            BlockChange =5.0f;
            player->BlockChange = true;
        }
    }   
    if (HiddenBuffName)
    {
        ShowTime -= DeltaTime;


        if (ShowTime <= 0)
        {
            ServerRPC_HiddenBuff();
        }
    }
  

}
    
void ABuffDebuffManager::ServerRPC_HiddenBuff_Implementation()
{

    MultiRPC_HiddenBuff();
}

void ABuffDebuffManager::MultiRPC_HiddenBuff_Implementation()
{
    PlayerController = Cast<AMainPlayerController >(UGameplayStatics::GetPlayerController(GetWorld(), 0));

    HiddenBuffName = false;
    if (PlayerController->mainplayerWidget) {
        PlayerController->mainplayerWidget->HiddenBuff();
    }
}

void ABuffDebuffManager::OnRep_BDApply()
{
    
    PlayerController = Cast<AMainPlayerController >(UGameplayStatics::GetPlayerController(GetWorld(), 0));

    AOurGameStateBase* gs = Cast<AOurGameStateBase>(GetWorld()->GetGameState());
    for (TActorIterator<AMainPlayerController> It(GetWorld()); It; ++It)
    {
        if (PlayerController)
        {
            if (PlayerController->mainplayerWidget) {
                PlayerController->mainplayerWidget->ShowBuff(RandomIndex);
            }
        }
        if (gs)
        {
            gs->enemyCountUI->ApplyBuff(RandomIndex);
        }
    }

    
   
}

void ABuffDebuffManager::BuffDebuffStruct()
{
    if(HasAuthority()){
	    SetOwner(GetWorld()->GetFirstPlayerController());
	    ServerRPC_BuffDebuffStruct();
    }
}

void ABuffDebuffManager::ServerRPC_BuffDebuffStruct_Implementation()
{
    TArray<FName> RowNames = BuffDebuffTable->GetRowNames();
    //RandomIndex = FMath::RandRange(0, 4 - 1);
    RandomIndex = FMath::RandRange(0, RowNames.Num() - 1);

    UE_LOG(LogTemp, Warning, TEXT("%d"), RandomIndex);
    
    OnRep_BDApply();

    AChallengersCharacter* player;
    for (TActorIterator<AChallengersCharacter> It(GetWorld()); It; ++It)
    {
        player = *It;
        if (player)
        {
            
            // 이동속도 1.5배 증가
            if (RandomIndex == 0)
            {
                // 이동속도 
                UCharacterMovementComponent* MovementComponent = player->GetCharacterMovement();
                if (MovementComponent)
                {
                    float playerspeed = DT_BuffDeBuff->FindRow<FAllBuffDebuff>("SpeedUp", "")->PlayerSpeed;

                    MovementComponent->MaxWalkSpeed *= playerspeed;
                    UE_LOG(LogTemp, Warning, TEXT("SpeedUp : %f"), MovementComponent->MaxWalkSpeed);
                    HiddenBuffName = true;
                }
            }
            // 이동속도 20% 감소
            else if (RandomIndex == 1)
            {
                // 이동속도 
                UCharacterMovementComponent* MovementComponent = player->GetCharacterMovement();
                if (MovementComponent)
                {
                    float playerspeed = DT_BuffDeBuff->FindRow<FAllBuffDebuff>("SpeedDown", "")->PlayerSpeed;

                    MovementComponent->MaxWalkSpeed *= playerspeed;
                    HiddenBuffName = true;
                    UE_LOG(LogTemp, Warning, TEXT("SpeedDown : %f"), MovementComponent->MaxWalkSpeed);

                }
            }
            // 플레이어 체력 1.5배 증가
            else if (RandomIndex == 2)
            {
                // 플레이어 체력
                float playerHP = player->HP;
                float playerHelth = DT_BuffDeBuff->FindRow<FAllBuffDebuff>("HelthUp", "")->PlayerHelth;
                if (playerHP)
                {
                    playerHP *= playerHelth;
                    HiddenBuffName = true;
                    UE_LOG(LogTemp, Warning, TEXT("HelthUp : %f"), playerHP);
                }
            }
            // 플레이어 체력 20% 감소
            else if (RandomIndex == 3)
            {
                // 플레이어 체력
                float playerHP = player->HP;
                float playerHelth = DT_BuffDeBuff->FindRow<FAllBuffDebuff>("HelthDown", "")->PlayerHelth;
                if (playerHP)
                {
                    playerHP *= playerHelth;
                    HiddenBuffName = true;
                    UE_LOG(LogTemp, Warning, TEXT("HelthDown : %f"), playerHP);
                }
            }
            // 칼 모든 스킬데미지 1.3배 증가
            else if (RandomIndex == 4)
            {

                gi->buffSwordDamagePercent = DT_BuffDeBuff->FindRow<FAllBuffDebuff>("SwordDamage", "")->SwordSkillDamage;
                HiddenBuffName = true;
            }
            // 칼 모든 스킬데미지 10% 감소
            else if (RandomIndex == 5)
            {
                gi->buffSwordDamagePercent = DT_BuffDeBuff->FindRow<FAllBuffDebuff>("SwordDamage", "")->SwordSkillDamage;
                HiddenBuffName = true;
            }
            // 지팡이 모든 스킬데미지 1.3배 증가
            else if (RandomIndex == 6)
            {
                gi->buffWandDamagePercent = DT_BuffDeBuff->FindRow<FAllBuffDebuff>("WandDamage", "")->WandSkillDamage;
                HiddenBuffName = true;
            }
            // 지팡이 모든 스킬데미지 10% 감소
            else if (RandomIndex == 7)
            {
                gi->buffWandDamagePercent = DT_BuffDeBuff->FindRow<FAllBuffDebuff>("WandDamage", "")->WandSkillDamage;
                HiddenBuffName = true;
            }
            // 활 모든 스킬데미지 1.3배 증가
            else if (RandomIndex == 8)
            {
                gi->buffBowDamagePercent = DT_BuffDeBuff->FindRow<FAllBuffDebuff>("BowDamage", "")->BowSkillDamage;
                HiddenBuffName = true;
            }
            // 활 모든 스킬데미지 10% 감소
            else if (RandomIndex == 9)
            {
                gi->buffBowDamagePercent = DT_BuffDeBuff->FindRow<FAllBuffDebuff>("BowDamage", "")->BowSkillDamage;
                HiddenBuffName = true;
            }
            // 무기교체 금지
            else if (RandomIndex == 10)
            {
                block = true;
                HiddenBuffName = true;
                UE_LOG(LogTemp, Warning, TEXT("BlockChange"));
            }
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("RowNames.Num : %d"), RandomIndex);
}


void ABuffDebuffManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ABuffDebuffManager, RandomIndex);


}
