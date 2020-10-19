// Troy Records Jr. 2020


#include "BaseTurretPawn.h"

#include "Capstone/DataStructures/GameStructs.h"
#include "Capstone/Gamemodes/MainGameMode.h"
#include "Capstone/SaveGames/MySaveGame.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "../../Engine/Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"
#include "../../Engine/Plugins/FX/Niagara/Source/Niagara/Classes/NiagaraSystem.h"
#include "../../Engine/Plugins/FX/Niagara/Source/Niagara/Public/NiagaraComponent.h"

// Sets default values
ABaseTurretPawn::ABaseTurretPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	SetRootComponent(BaseMesh);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

}

// Called when the game starts or when spawned
void ABaseTurretPawn::BeginPlay()
{
	Super::BeginPlay();
	AMainGameMode* GameMode = GetWorld()->GetAuthGameMode<AMainGameMode>();
	if(GameMode != nullptr)
	{
		GameMode->SaveGame.AddUniqueDynamic(this, &ABaseTurretPawn::SaveGame);
	}
	
}

void ABaseTurretPawn::DetectEnemies()
{
	TargetedEnemy = nullptr; 
	const FVector Start = GetActorLocation();
	const FVector End = GetActorLocation();
	// Array of actors to ignore i.e. NOT trace against.
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	ActorsToIgnore.Add(Player);
	TArray<FHitResult> HitArray;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(ObjectTypeQuery3);

	const bool bHit = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), Start, End, TraceRange, ObjectTypes,
		false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitArray, true,
		FLinearColor::Green,FLinearColor::Red, 0);

	if(bHit)
	{
		// Find the closest enemy
		float Distance = TraceRange + 1;
		for(const FHitResult HitResult : HitArray)
		{
			const float ComparedDistance = FVector::Distance(Start, HitResult.ImpactPoint);
			if(ComparedDistance < Distance)
			{
				TargetedEnemy = HitResult.GetActor();
				Distance = ComparedDistance;
			}
		}
		
	}
}

// Called every frame
void ABaseTurretPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DetectEnemies();

	if(TargetedEnemy == nullptr)
	{
		//GEngine->AddOnScreenDebugMessage(2, 0, FColor::Green, TEXT("No one is in range"));
		if(AimingBeam != nullptr)
		{
			AimingBeam->DestroyComponent();
			AimingBeam = nullptr;
		}
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(2, 0, FColor::Green, FString::Printf(TEXT("%s is the closest"), *TargetedEnemy->GetName()));
		const FVector StartLocation = TurretMesh->GetComponentLocation();
		FRotator TurretRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, TargetedEnemy->GetActorLocation());
		TurretRotation.Pitch = 0;
		TurretMesh->SetWorldRotation(TurretRotation);

		if((FPlatformTime::Seconds() - LastFireTime) > ReloadTime)
		{
			const float DamageAmount = 10.0f;
			const TSubclassOf<UDamageType> DamageType;
			FPointDamageEvent PointDamageEvent;
			UGameplayStatics::ApplyDamage(TargetedEnemy, DamageAmount, GetController(), this, DamageType);
			SpawnBeamEffect();
			if(AimingBeam != nullptr)
			{
				AimingBeam->DestroyComponent();
				AimingBeam = nullptr;
			}
			LastFireTime = FPlatformTime::Seconds();
		}
		else
		{
			if(AimingBeam == nullptr)
			{
				SpawnAimingBeam();
			}
			else
			{
				const FVector BeamEnd = GetTransform().InverseTransformPosition(TargetedEnemy->GetActorLocation());
				AimingBeam->SetVectorParameter(FName(TEXT("BeamEnd")),BeamEnd);
				FVector BeamStart = TurretMesh->GetSocketTransform(FName(TEXT("BeamStart"))).GetLocation();
				AimingBeam->SetVectorParameter(FName(TEXT("BeamStart")),BeamStart);
			}
		}
	}
}

// Called to bind functionality to input
void ABaseTurretPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABaseTurretPawn::SetPlayer(AActor* InPlayer)
{
	Player = InPlayer;
}

void ABaseTurretPawn::SaveGame()
{// Load the save if it's there
	UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("MySlot"), 0));
	
	if(SaveGameInstance == nullptr)
	{
		// If there wasn't a save loaded, create one
		SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	}
	
	// Set up the data to be saved
	FTurretSaveData MyData;
	MyData.TurretTransform = GetActorTransform();
	MyData.TurretHealth = 100.f;
	// Save it to the file
	SaveGameInstance->TurretSaveDatas.Add(MyData);
	// Save the savegameinstance
	
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("MySlot"), 0);
	UE_LOG(LogTemp, Warning, TEXT("TurretSaveDatas.Num : %d"), SaveGameInstance->TurretSaveDatas.Num()); // This returns 0 still
}

void ABaseTurretPawn::LoadGame(FTurretSaveData InData)
{
	SetActorTransform(InData.TurretTransform);
	UE_LOG(LogTemp, Warning, TEXT("Loaded a health value of: %f"), InData.TurretHealth);
}

void ABaseTurretPawn::SpawnAimingBeam()
{
	FVector BeamStart = TurretMesh->GetSocketTransform(FName(TEXT("BeamStart"))).GetLocation();
	//StartBeam = GetTransform().InverseTransformPosition(StartBeam);
	const FVector BeamEnd = GetTransform().InverseTransformPosition(TargetedEnemy->GetActorLocation());

	ensure(ShotBeamSystem);
	AimingBeam = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, AimBeamSystem, BeamStart);
	AimingBeam->SetVectorParameter(FName(TEXT("BeamEnd")),BeamEnd);
}

void ABaseTurretPawn::SpawnBeamEffect()
{
	const FVector BeamStart = TurretMesh->GetSocketTransform(FName(TEXT("BeamStart"))).GetLocation();
	const FVector BeamEnd = GetTransform().InverseTransformPosition(TargetedEnemy->GetActorLocation());

	ensure(ShotBeamSystem);
	UNiagaraComponent* Beam = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ShotBeamSystem, BeamStart);
	Beam->SetVectorParameter(FName(TEXT("BeamEnd")),BeamEnd);
	Beam->SetVectorParameter(FName(TEXT("BeamStart")),BeamStart);
}

