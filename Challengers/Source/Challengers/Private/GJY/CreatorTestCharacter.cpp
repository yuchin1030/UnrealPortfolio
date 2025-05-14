#include "GJY/CreatorTestCharacter.h"
#include "GJY/PlayerCustomizer.h"
#include "Components/SkeletalMeshComponent.h"
#include "GJY/CustomModeBase.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "OurGameInstance.h"
#include "GJY/SkeletalMeshStructure.h"
#include "GJY/MaterialStruct.h"


ACreatorTestCharacter::ACreatorTestCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	MeshBoom->SetupAttachment(RootComponent);

	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	GetMesh()->SetupAttachment(MeshBoom);

	Part1 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Part1"));
	Part1->SetupAttachment(MeshBoom);
	Part1->SetRelativeLocation(FVector(0, 0, -90));
	Part1->SetRelativeRotation(FRotator(0, -90, 0));

	Part2 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Part2"));
	Part2->SetupAttachment(MeshBoom);
	Part2->SetRelativeLocation(FVector(0, 0, -90));
	Part2->SetRelativeRotation(FRotator(0, -90, 0));

	Part3 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Part3"));
	Part3->SetupAttachment(MeshBoom);
	Part3->SetRelativeLocation(FVector(0, 0, -90));
	Part3->SetRelativeRotation(FRotator(0, -90, 0));

	Part4 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Part4"));
	Part4->SetupAttachment(MeshBoom);
	Part4->SetRelativeLocation(FVector(0, 0, -90));
	Part4->SetRelativeRotation(FRotator(0, -90, 0));

	Part5 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Part5"));
	Part5->SetupAttachment(MeshBoom);
	Part5->SetRelativeLocation(FVector(0, 0, -90));
	Part5->SetRelativeRotation(FRotator(0, -90, 0));

	Part6 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Part6"));
	Part6->SetupAttachment(MeshBoom);
	Part6->SetRelativeLocation(FVector(0, 0, -90));
	Part6->SetRelativeRotation(FRotator(0, -90, 0));

	Part7 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Part7"));
	Part7->SetupAttachment(MeshBoom);
	Part7->SetRelativeLocation(FVector(0, 0, -90));
	Part7->SetRelativeRotation(FRotator(0, -90, 0));

	Part8 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Part8"));
	Part8->SetupAttachment(MeshBoom);
	Part8->SetRelativeLocation(FVector(0, 0, -90));
	Part8->SetRelativeRotation(FRotator(0, -90, 0));

	Part9 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Part9"));
	Part9->SetupAttachment(MeshBoom);
	Part9->SetRelativeLocation(FVector(0, 0, -90));
	Part9->SetRelativeRotation(FRotator(0, -90, 0));

	Part10 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Part10"));
	Part10->SetupAttachment(MeshBoom);
	Part10->SetRelativeLocation(FVector(0, 0, -90));
	Part10->SetRelativeRotation(FRotator(0, -90, 0));

	Part11 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Part11"));
	Part11->SetupAttachment(MeshBoom);
	Part11->SetRelativeLocation(FVector(0, 0, -90));
	Part11->SetRelativeRotation(FRotator(0, -90, 0));

	Part12 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Part12"));
	Part12->SetupAttachment(MeshBoom);
	Part12->SetRelativeLocation(FVector(0, 0, -90));
	Part12->SetRelativeRotation(FRotator(0, -90, 0));

	Part13 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Part13"));
	Part13->SetupAttachment(MeshBoom);
	Part13->SetRelativeLocation(FVector(0, 0, -90));
	Part13->SetRelativeRotation(FRotator(0, -90, 0));

	Part14 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Part14"));
	Part14->SetupAttachment(MeshBoom);
	Part14->SetRelativeLocation(FVector(0, 0, -90));
	Part14->SetRelativeRotation(FRotator(0, -90, 0));

	Part15 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Part15"));
	Part15->SetupAttachment(MeshBoom);
	Part15->SetRelativeLocation(FVector(0, 0, -90));
	Part15->SetRelativeRotation(FRotator(0, -90, 0));

	Part16 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Part16"));
	Part16->SetupAttachment(MeshBoom);
	Part16->SetRelativeLocation(FVector(0, 0, -90));
	Part16->SetRelativeRotation(FRotator(0, -90, 0));

	Part17 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Part17"));
	Part17->SetupAttachment(MeshBoom);
	Part17->SetRelativeLocation(FVector(0, 0, -90));
	Part17->SetRelativeRotation(FRotator(0, -90, 0));

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

}


void ACreatorTestCharacter::BeginPlay()
{
	Super::BeginPlay();

	FinalMeshArr.Init(FName(""), 18);
	FemaleMeshArr.Init(FName(""), 18);
	MaleMeshArr.Init(FName(""), 18);

	ACustomModeBase* CM = Cast<ACustomModeBase>(GetWorld()->GetAuthGameMode());
	Customs = CM->Custom_Inst;

	UOurGameInstance* OG = Cast<UOurGameInstance>(GetWorld()->GetGameInstance());

	SDT = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/GJY/SkinDataTable.SkinDataTable'"));

	if (OG != nullptr)
	{
		OG->LoadChacraterCustom();
		bBoy = OG->LoadbIsMan;
		FinalMeshArr = OG->LoadFinalMeshArr;
	}

	for (int32 i = 0; i < FinalMeshArr.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("%d : %s"), i, *FinalMeshArr[i].ToString());
	}

	if (bBoy == true)
	{
		SelectBoy();
	}
	else
	{
		SelectGirl();
	}
}


void ACreatorTestCharacter::ChangeHair()
{
	if (Customs != nullptr)
	{
		if (bBoy == true)
		{
			if (HairIndex == 0)
			{
				Part4->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("2"), "")->SkeletalBody);
				Part5->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("4"), "")->SkeletalBody);

				MaleMeshArr[3] = FName("2");
				MaleMeshArr[4] = FName("4");

			}
			else if (HairIndex == 1)
			{
				Part4->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("2"), "")->SkeletalBody);
				Part5->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("5"), "")->SkeletalBody);

				MaleMeshArr[3] = FName("2");
				MaleMeshArr[4] = FName("5");

			}
			else if (HairIndex == 2)
			{
				Part4->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("2"), "")->SkeletalBody);
				Part5->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("6"), "")->SkeletalBody);

				MaleMeshArr[3] = FName("2");
				MaleMeshArr[4] = FName("6");

			}
			else if (HairIndex == 3)
			{
				Part4->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("3"), "")->SkeletalBody);
				Part5->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("4"), "")->SkeletalBody);

				MaleMeshArr[3] = FName("3");
				MaleMeshArr[4] = FName("4");

			}
			else if (HairIndex == 4)
			{
				Part4->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("3"), "")->SkeletalBody);
				Part5->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("5"), "")->SkeletalBody);

				MaleMeshArr[3] = FName("3");
				MaleMeshArr[4] = FName("5");

			}
			else if (HairIndex == 5)
			{
				Part4->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("3"), "")->SkeletalBody);
				Part5->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("6"), "")->SkeletalBody);

				MaleMeshArr[3] = FName("3");
				MaleMeshArr[4] = FName("6");

			}

		}
		else
		{
			if (HairIndex == 0)
			{
				Part2->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("2"), "")->SkeletalBody);
				Part3->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("4"), "")->SkeletalBody);


				FemaleMeshArr[1] = FName("2");
				FemaleMeshArr[2] = FName("4");

			}
			else if (HairIndex == 1)
			{
				Part2->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("2"), "")->SkeletalBody);
				Part3->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("5"), "")->SkeletalBody);


				FemaleMeshArr[1] = FName("2");
				FemaleMeshArr[2] = FName("5");


			}
			else if (HairIndex == 2)
			{
				Part2->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("2"), "")->SkeletalBody);
				Part3->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("6"), "")->SkeletalBody);


				FemaleMeshArr[1] = FName("2");
				FemaleMeshArr[2] = FName("6");

			}
			else if (HairIndex == 3)
			{

				Part2->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("3"), "")->SkeletalBody);
				Part3->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("4"), "")->SkeletalBody);


				FemaleMeshArr[1] = FName("3");
				FemaleMeshArr[2] = FName("4");

			}
			else if (HairIndex == 4)
			{
				Part2->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("3"), "")->SkeletalBody);
				Part3->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("5"), "")->SkeletalBody);


				FemaleMeshArr[1] = FName("3");
				FemaleMeshArr[2] = FName("5");

			}
			else if (HairIndex == 5)
			{
				Part2->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("3"), "")->SkeletalBody);
				Part3->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("6"), "")->SkeletalBody);


				FemaleMeshArr[1] = FName("3");
				FemaleMeshArr[2] = FName("6");

			}
		}

	}
}

void ACreatorTestCharacter::ChangeClothes()
{
	if (bBoy)
	{
		if (ClothesIndex == 0)
		{
			Part15->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("14"), "")->SkeletalBody);
			MaleMeshArr[14] = FName("14");

		}
		else if (ClothesIndex == 1)
		{
			Part15->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("NoAssets"), "")->SkeletalBody);
			MaleMeshArr[14] = FName("NoAssets");
		}
	}
	else
	{
		if (ClothesIndex == 0)
		{
			GetMesh()->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("1"), "")->SkeletalBody);
			Part5->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("8"), "")->SkeletalBody);
			Part6->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("9"), "")->SkeletalBody);
			Part7->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("10"), "")->SkeletalBody);
			Part11->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("14"), "")->SkeletalBody);
			Part12->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("15"), "")->SkeletalBody);
			Part13->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("16"), "")->SkeletalBody);
			Part14->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("17"), "")->SkeletalBody);

			FemaleMeshArr[17] = FName("1");
			FemaleMeshArr[4] = FName("8");
			FemaleMeshArr[5] = FName("9");
			FemaleMeshArr[6] = FName("10");
			FemaleMeshArr[10] = FName("14");
			FemaleMeshArr[11] = FName("15");
			FemaleMeshArr[12] = FName("16");
			FemaleMeshArr[13] = FName("17");

		}
		else if (ClothesIndex == 1)
		{

			GetMesh()->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("1"), "")->SkeletalBody);
			Part5->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("NoAssets"), "")->SkeletalBody);
			Part6->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("NoAssets"), "")->SkeletalBody);
			Part7->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("21"), "")->SkeletalBody);
			Part11->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("NoAssets"), "")->SkeletalBody);
			Part12->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("NoAssets"), "")->SkeletalBody);
			Part13->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("16"), "")->SkeletalBody);
			Part14->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("NoAssets"), "")->SkeletalBody);


			FemaleMeshArr[17] = FName("1");
			FemaleMeshArr[4] = FName("NoAssets");
			FemaleMeshArr[5] = FName("NoAssets");
			FemaleMeshArr[6] = FName("21");
			FemaleMeshArr[10] = FName("NoAssets");
			FemaleMeshArr[11] = FName("NoAssets");
			FemaleMeshArr[12] = FName("16");
			FemaleMeshArr[13] = FName("NOAssets");

		}
	}

}

void ACreatorTestCharacter::ChangeGloves()
{
	if (bBoy == true)
	{
		if (GlovesIndex == 0)
		{

			Part7->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("18"), "")->SkeletalBody);
			Part8->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("19"), "")->SkeletalBody);
			Part12->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("20"), "")->SkeletalBody);

			MaleMeshArr[6] = FName("18");
			MaleMeshArr[7] = FName("19");
			MaleMeshArr[11] = FName("20");

			bGlove = false;

			if (bGlove == false)
			{
				Part8->SetMaterial(0, CDT->FindRow<FMaterialType>(FName(*FString::FromInt(GloveNum)), "")->MaterialInst);
			}

		}
		else if (GlovesIndex == 1)
		{

			Part7->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("NoAssets"), "")->SkeletalBody);
			Part8->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("21"), "")->SkeletalBody);
			Part12->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("NoAssets"), "")->SkeletalBody);

			MaleMeshArr[6] = FName("NoAssets");
			MaleMeshArr[7] = FName("21");
			MaleMeshArr[11] = FName("NoAssets");

			bGlove = true;

			if (bGlove == true)
			{
				Part8->SetMaterial(0, SDT->FindRow<FMaterialType>(FName("1"), "")->MaterialInst);
			}
		}
	}
	else
	{
		if (GlovesIndex == 0)
		{

			Part9->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("12"), "")->SkeletalBody);
			Part10->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("13"), "")->SkeletalBody);

			FemaleMeshArr[8] = FName("12");
			FemaleMeshArr[9] = FName("13");

			bGlove = false;
			if (bGlove == false)
			{
				Part9->SetMaterial(0, CDT->FindRow<FMaterialType>(FName(*FString::FromInt(GloveNum)), "")->MaterialInst);
				Part10->SetMaterial(0, CDT->FindRow<FMaterialType>(FName(*FString::FromInt(GloveNum)), "")->MaterialInst);
			}


		}
		else if (GlovesIndex == 1)
		{
			Part9->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("23"), "")->SkeletalBody);
			Part10->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("22"), "")->SkeletalBody);

			FemaleMeshArr[8] = FName("23");
			FemaleMeshArr[9] = FName("22");

			bGlove = true;

			if (bGlove == true)
			{
				Part9->SetMaterial(0, SDT->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
				Part10->SetMaterial(0, SDT->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
			}
		}
	}
}



void ACreatorTestCharacter::SelectBoy()
{

	if (bBoy == true)
	{
		BodyDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/GJY/MBodyDataTable.MBodyDataTable'"));
		ChangeAnim();
		CDT = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/GJY/ClothesColorDataTable_M.ClothesColorDataTable_M'"));
	}

	GetMesh()->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("1"), "")->SkeletalBody);
	Part1->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("0"), "")->SkeletalBody);
	Part2->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("8"), "")->SkeletalBody);
	Part3->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("7"), "")->SkeletalBody);
	Part4->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("2"), "")->SkeletalBody);
	Part5->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("4"), "")->SkeletalBody);
	Part6->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("10"), "")->SkeletalBody);
	Part7->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("18"), "")->SkeletalBody);
	Part8->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("19"), "")->SkeletalBody);
	Part9->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("12"), "")->SkeletalBody);
	Part10->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("9"), "")->SkeletalBody);
	Part11->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("17"), "")->SkeletalBody);
	Part12->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("20"), "")->SkeletalBody);
	Part13->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("11"), "")->SkeletalBody);
	Part14->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("13"), "")->SkeletalBody);
	Part15->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("14"), "")->SkeletalBody);
	Part16->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("15"), "")->SkeletalBody);
	Part17->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("16"), "")->SkeletalBody);

	MaleMeshArr[17] = FName("1");
	MaleMeshArr[0] = FName("0");
	MaleMeshArr[1] = FName("8");
	MaleMeshArr[2] = FName("7");
	MaleMeshArr[3] = FName("2");
	MaleMeshArr[4] = FName("4");
	MaleMeshArr[5] = FName("10");
	MaleMeshArr[6] = FName("18");
	MaleMeshArr[7] = FName("19");
	MaleMeshArr[8] = FName("12");
	MaleMeshArr[9] = FName("9");
	MaleMeshArr[10] = FName("17");
	MaleMeshArr[11] = FName("20");
	MaleMeshArr[12] = FName("11");
	MaleMeshArr[13] = FName("13");
	MaleMeshArr[14] = FName("14");
	MaleMeshArr[15] = FName("15");
	MaleMeshArr[16] = FName("16");

	InitColor();

}

void ACreatorTestCharacter::SelectGirl()
{

	if (bBoy == false)
	{
		BodyDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/GJY/FBodyDataTable.FBodyDataTable'"));
		ChangeAnim();
		CDT = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/GJY/ClothesColorDataTable_F.ClothesColorDataTable_F'"));
	}
	GetMesh()->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("1"), "")->SkeletalBody);
	Part1->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("0"), "")->SkeletalBody);
	Part2->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("2"), "")->SkeletalBody);
	Part3->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("4"), "")->SkeletalBody);
	Part4->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("7"), "")->SkeletalBody);
	Part5->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("8"), "")->SkeletalBody);
	Part6->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("9"), "")->SkeletalBody);
	Part7->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("10"), "")->SkeletalBody);
	Part8->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("11"), "")->SkeletalBody);
	Part9->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("12"), "")->SkeletalBody);
	Part10->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("13"), "")->SkeletalBody);
	Part11->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("14"), "")->SkeletalBody);
	Part12->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("15"), "")->SkeletalBody);
	Part13->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("16"), "")->SkeletalBody);
	Part14->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("17"), "")->SkeletalBody);
	Part15->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("18"), "")->SkeletalBody);
	Part16->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("19"), "")->SkeletalBody);
	Part17->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FName("20"), "")->SkeletalBody);


	FemaleMeshArr[17] = FName("1");
	FemaleMeshArr[0] = FName("0");
	FemaleMeshArr[1] = FName("2");
	FemaleMeshArr[2] = FName("4");
	FemaleMeshArr[3] = FName("7");
	FemaleMeshArr[4] = FName("8");
	FemaleMeshArr[5] = FName("9");
	FemaleMeshArr[6] = FName("10");
	FemaleMeshArr[7] = FName("11");
	FemaleMeshArr[8] = FName("12");
	FemaleMeshArr[9] = FName("13");
	FemaleMeshArr[10] = FName("14");
	FemaleMeshArr[11] = FName("15");
	FemaleMeshArr[12] = FName("16");
	FemaleMeshArr[13] = FName("17");
	FemaleMeshArr[14] = FName("18");
	FemaleMeshArr[15] = FName("19");
	FemaleMeshArr[16] = FName("20");

	InitColor();
}

void ACreatorTestCharacter::ChangeAnim()
{
	if (bBoy == true)
	{
		GetMesh()->SetAnimInstanceClass(ABP_MaleCustom);
		Part1->SetLeaderPoseComponent(GetMesh());
		Part2->SetLeaderPoseComponent(GetMesh());
		Part3->SetLeaderPoseComponent(GetMesh());
		Part4->SetLeaderPoseComponent(GetMesh());
		Part5->SetLeaderPoseComponent(GetMesh());
		Part6->SetLeaderPoseComponent(GetMesh());
		Part7->SetLeaderPoseComponent(GetMesh());
		Part8->SetLeaderPoseComponent(GetMesh());
		Part9->SetLeaderPoseComponent(GetMesh());
		Part10->SetLeaderPoseComponent(GetMesh());
		Part11->SetLeaderPoseComponent(GetMesh());
		Part12->SetLeaderPoseComponent(GetMesh());
		Part13->SetLeaderPoseComponent(GetMesh());
		Part14->SetLeaderPoseComponent(GetMesh());
		Part15->SetLeaderPoseComponent(GetMesh());
		Part16->SetLeaderPoseComponent(GetMesh());
		Part17->SetLeaderPoseComponent(GetMesh());
	}
	else
	{
		GetMesh()->SetAnimInstanceClass(ABP_FemaleCustom);
		Part1->SetLeaderPoseComponent(GetMesh());
		Part2->SetLeaderPoseComponent(GetMesh());
		Part3->SetLeaderPoseComponent(GetMesh());
		Part4->SetLeaderPoseComponent(GetMesh());
		Part5->SetLeaderPoseComponent(GetMesh());
		Part6->SetLeaderPoseComponent(GetMesh());
		Part7->SetLeaderPoseComponent(GetMesh());
		Part8->SetLeaderPoseComponent(GetMesh());
		Part9->SetLeaderPoseComponent(GetMesh());
		Part10->SetLeaderPoseComponent(GetMesh());
		Part11->SetLeaderPoseComponent(GetMesh());
		Part12->SetLeaderPoseComponent(GetMesh());
		Part13->SetLeaderPoseComponent(GetMesh());
		Part14->SetLeaderPoseComponent(GetMesh());
		Part15->SetLeaderPoseComponent(GetMesh());
		Part16->SetLeaderPoseComponent(GetMesh());
		Part17->SetLeaderPoseComponent(GetMesh());
	}
}


void ACreatorTestCharacter::LoadArray()
{
	if (bBoy == true)
	{
		FinalMeshArr[17] = MaleMeshArr[17];
		FinalMeshArr[0] = MaleMeshArr[0];
		FinalMeshArr[1] = MaleMeshArr[1];
		FinalMeshArr[2] = MaleMeshArr[2];
		FinalMeshArr[3] = MaleMeshArr[3];
		FinalMeshArr[4] = MaleMeshArr[4];
		FinalMeshArr[5] = MaleMeshArr[5];
		FinalMeshArr[6] = MaleMeshArr[6];
		FinalMeshArr[7] = MaleMeshArr[7];
		FinalMeshArr[8] = MaleMeshArr[8];
		FinalMeshArr[9] = MaleMeshArr[9];
		FinalMeshArr[10] = MaleMeshArr[10];
		FinalMeshArr[11] = MaleMeshArr[11];
		FinalMeshArr[12] = MaleMeshArr[12];
		FinalMeshArr[13] = MaleMeshArr[13];
		FinalMeshArr[14] = MaleMeshArr[14];
		FinalMeshArr[15] = MaleMeshArr[15];
		FinalMeshArr[16] = MaleMeshArr[16];
	}
	else
	{
		FinalMeshArr[17] = FemaleMeshArr[17];
		FinalMeshArr[0] = FemaleMeshArr[0];
		FinalMeshArr[1] = FemaleMeshArr[1];
		FinalMeshArr[2] = FemaleMeshArr[2];
		FinalMeshArr[3] = FemaleMeshArr[3];
		FinalMeshArr[4] = FemaleMeshArr[4];
		FinalMeshArr[5] = FemaleMeshArr[5];
		FinalMeshArr[6] = FemaleMeshArr[6];
		FinalMeshArr[7] = FemaleMeshArr[7];
		FinalMeshArr[8] = FemaleMeshArr[8];
		FinalMeshArr[9] = FemaleMeshArr[9];
		FinalMeshArr[10] = FemaleMeshArr[10];
		FinalMeshArr[11] = FemaleMeshArr[11];
		FinalMeshArr[12] = FemaleMeshArr[12];
		FinalMeshArr[13] = FemaleMeshArr[13];
		FinalMeshArr[14] = FemaleMeshArr[14];
		FinalMeshArr[15] = FemaleMeshArr[15];
		FinalMeshArr[16] = FemaleMeshArr[16];

	}

	GetMesh()->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[17], "")->SkeletalBody);
	Part1->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[0], "")->SkeletalBody);
	Part2->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[1], "")->SkeletalBody);
	Part3->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[2], "")->SkeletalBody);
	Part4->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[3], "")->SkeletalBody);
	Part5->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[4], "")->SkeletalBody);
	Part6->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[5], "")->SkeletalBody);
	Part7->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[6], "")->SkeletalBody);
	Part8->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[7], "")->SkeletalBody);
	Part9->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[8], "")->SkeletalBody);
	Part10->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[9], "")->SkeletalBody);
	Part11->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[10], "")->SkeletalBody);
	Part12->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[11], "")->SkeletalBody);
	Part13->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[12], "")->SkeletalBody);
	Part14->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[13], "")->SkeletalBody);
	Part15->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[14], "")->SkeletalBody);
	Part16->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[15], "")->SkeletalBody);
	Part17->SetSkeletalMesh(BodyDataTable->FindRow<FSkeletalMeshType>(FinalMeshArr[16], "")->SkeletalBody);
}

void ACreatorTestCharacter::HairColorChange(int _RowNum)
{ 
	HairNum = _RowNum;

	FName RowNum = FName(*FString::FromInt(_RowNum));
	UE_LOG(LogTemp, Warning, TEXT("Color : %d"), _RowNum);
	if(bBoy == false)
	{
		Part2->SetMaterial(0,HDT->FindRow<FMaterialType>(RowNum,"")->MaterialInst);
		Part3->SetMaterial(0, HDT->FindRow<FMaterialType>(RowNum,"")->MaterialInst);
	}
	else
	{
		Part4->SetMaterial(0, HDT->FindRow<FMaterialType>(RowNum,"")->MaterialInst);
		Part5->SetMaterial(0, HDT->FindRow<FMaterialType>(RowNum,"")->MaterialInst);
	}
}

void ACreatorTestCharacter::ClothesColorChange(int _RowNum)
{
	ClothesNum = _RowNum;

	FName RowNum = FName(*FString::FromInt(_RowNum));

	GloveNum = _RowNum;

	if (bBoy == false)
	{
		Part4->SetMaterial(0, CDT->FindRow<FMaterialType>(RowNum, "")->MaterialInst);
		Part5->SetMaterial(0, CDT->FindRow<FMaterialType>(RowNum, "")->MaterialInst);
		Part6->SetMaterial(0, CDT->FindRow<FMaterialType>(RowNum, "")->MaterialInst);
		Part7->SetMaterial(0, CDT->FindRow<FMaterialType>(RowNum, "")->MaterialInst);
		Part8->SetMaterial(0, CDT->FindRow<FMaterialType>(RowNum, "")->MaterialInst);
		Part9->SetMaterial(0, CDT->FindRow<FMaterialType>(RowNum, "")->MaterialInst);
		Part10->SetMaterial(0, CDT->FindRow<FMaterialType>(RowNum, "")->MaterialInst);
		Part11->SetMaterial(0, CDT->FindRow<FMaterialType>(RowNum, "")->MaterialInst);
		Part12->SetMaterial(0, CDT->FindRow<FMaterialType>(RowNum, "")->MaterialInst);
		Part13->SetMaterial(0, CDT->FindRow<FMaterialType>(RowNum, "")->MaterialInst);
		Part14->SetMaterial(0, CDT->FindRow<FMaterialType>(RowNum, "")->MaterialInst);
		Part17->SetMaterial(0, CDT->FindRow<FMaterialType>(RowNum, "")->MaterialInst);


		if (bGlove == true)
		{
			Part9->SetMaterial(0, SDT->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
			Part10->SetMaterial(0, SDT->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
		}

	}
	else
	{
		Part2->SetMaterial(0, CDT->FindRow<FMaterialType>(RowNum, "")->MaterialInst);
		Part3->SetMaterial(0, CDT->FindRow<FMaterialType>(RowNum, "")->MaterialInst);
		Part6->SetMaterial(0, CDT->FindRow<FMaterialType>(RowNum, "")->MaterialInst);
		Part7->SetMaterial(0, CDT->FindRow<FMaterialType>(RowNum, "")->MaterialInst);
		Part8->SetMaterial(0, CDT->FindRow<FMaterialType>(RowNum, "")->MaterialInst);
		Part9->SetMaterial(0, CDT->FindRow<FMaterialType>(RowNum, "")->MaterialInst);
		Part11->SetMaterial(0, CDT->FindRow<FMaterialType>(RowNum, "")->MaterialInst);
		Part12->SetMaterial(0, CDT->FindRow<FMaterialType>(RowNum, "")->MaterialInst);
		Part13->SetMaterial(0, CDT->FindRow<FMaterialType>(RowNum, "")->MaterialInst);
		Part14->SetMaterial(0, CDT->FindRow<FMaterialType>(RowNum, "")->MaterialInst);
		Part15->SetMaterial(0, CDT->FindRow<FMaterialType>(RowNum, "")->MaterialInst);
		Part16->SetMaterial(0, CDT->FindRow<FMaterialType>(RowNum, "")->MaterialInst);
		Part17->SetMaterial(0, CDT->FindRow<FMaterialType>(RowNum, "")->MaterialInst);

		if (bGlove == true)
		{
			Part8->SetMaterial(0, SDT->FindRow<FMaterialType>(FName("1"), "")->MaterialInst);
		}

	}
}

void ACreatorTestCharacter::InitColor()
{	
	bGlove = false;
	HDT = LoadObject<UDataTable>(nullptr, TEXT("/ Script / Engine.DataTable'/Game/GJY/HairColorDataTable.HairColorDataTable'"));
	if (bBoy == false)
	{
		Part2->SetMaterial(0, HDT->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
		Part3->SetMaterial(0, HDT->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
		Part4->SetMaterial(0, CDT->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
		Part5->SetMaterial(0, CDT->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
		Part6->SetMaterial(0, CDT->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
		Part7->SetMaterial(0, CDT->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
		Part8->SetMaterial(0, CDT->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
		Part9->SetMaterial(0, CDT->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
		Part10->SetMaterial(0, CDT->FindRow<FMaterialType>(FName("0"),"")->MaterialInst);
		Part11->SetMaterial(0, CDT->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
		Part12->SetMaterial(0, CDT->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
		Part13->SetMaterial(0, CDT->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
		Part14->SetMaterial(0, CDT->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
		Part15->SetMaterial(0, SDT->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
		Part16->SetMaterial(0, SDT->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
		Part17->SetMaterial(0, CDT->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);

		if (bGlove == true)
		{
			Part9->SetMaterial(0, SDT->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
			Part10->SetMaterial(0, SDT->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
		}
	}
	else
	{	
		Part2->SetMaterial(0, CDT->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
		Part3->SetMaterial(0, CDT->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
		Part4->SetMaterial(0, HDT->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
		Part5->SetMaterial(0, HDT->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
		Part6->SetMaterial(0, CDT->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
		Part7->SetMaterial(0, CDT->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
		Part8->SetMaterial(0, CDT->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
		Part9->SetMaterial(0, CDT->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
		Part10->SetMaterial(0, SDT->FindRow<FMaterialType>(FName("1"), "")->MaterialInst);
		Part11->SetMaterial(0, CDT->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
		Part12->SetMaterial(0, CDT->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
		Part13->SetMaterial(0, CDT->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
		Part14->SetMaterial(0, CDT->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
		Part15->SetMaterial(0, CDT->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
		Part16->SetMaterial(0, CDT->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);
		Part17->SetMaterial(0, CDT->FindRow<FMaterialType>(FName("0"), "")->MaterialInst);

		if (bGlove == true)
		{
			Part8->SetMaterial(0, SDT->FindRow<FMaterialType>(FName("1"), "")->MaterialInst);
		}
	}	
}
