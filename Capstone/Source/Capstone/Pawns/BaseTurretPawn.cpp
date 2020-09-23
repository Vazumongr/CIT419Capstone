// Troy Records Jr. 2020


#include "BaseTurretPawn.h"


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
			const float ComparedDistance = FVector::Distance(Start, HitResult.Location);
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
			UE_LOG(LogTemp, Warning, TEXT("I am shooting..."));
			const float DamageAmount = 50.0f;
			const TSubclassOf<UDamageType> DamageType;
			FPointDamageEvent PointDamageEvent;
			UGameplayStatics::ApplyDamage(TargetedEnemy, DamageAmount, GetController(), this, DamageType);
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, BeamSystem, GetActorLocation())->SetVectorParameter(FName(TEXT("BeamEnd")),TargetedEnemy->GetActorLocation());
			LastFireTime = FPlatformTime::Seconds();
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

