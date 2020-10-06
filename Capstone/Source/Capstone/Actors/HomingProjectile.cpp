// Troy Records Jr. 2020


#include "HomingProjectile.h"


#include "Capstone/GameModes/MainGameMode.h"
#include "Capstone/Characters/PlayerCharacter.h"
#include "../../Engine/Plugins/FX/Niagara/Source/Niagara/Public/NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default valuesPre
AHomingProjectile::AHomingProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	ProjectileMovementComponent->bIsHomingProjectile = true;
}

// Called when the game starts or when spawned
void AHomingProjectile::BeginPlay()
{
	Super::BeginPlay();
	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AHomingProjectile::HitEnemy);
}

// Called every frame
void AHomingProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHomingProjectile::SetTarget(AActor* InTargetActor)
{
	if(ProjectileMovementComponent == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("The PMC is null"));
		return;
	}
	if(InTargetActor == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("The ITA is null"));
		return;
	}
	ProjectileMovementComponent->HomingTargetComponent = InTargetActor->GetRootComponent();
	TargetActor = InTargetActor;
}

