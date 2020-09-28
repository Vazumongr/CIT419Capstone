// Troy Records Jr. 2020


#include "HomingProjectile.h"


#include "Capstone/GameModes/MainGameMode.h"
#include "Capstone/Characters/PlayerCharacter.h"
#include "../../Engine/Plugins/FX/Niagara/Source/Niagara/Public/NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AHomingProjectile::AHomingProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	SetRootComponent(StaticMeshComponent);
	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AHomingProjectile::HitEnemy);
	
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara Component"));
	NiagaraComponent->SetupAttachment(StaticMeshComponent);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->bIsHomingProjectile = true;
}

// Called when the game starts or when spawned
void AHomingProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AHomingProjectile::HitEnemy(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor == TargetActor)
	{
		UGameplayStatics::ApplyDamage(TargetActor, DamageEvent.DamageAmount, DamageEvent.PlayerController, DamageEvent.PlayerActor, DamageEvent.DamageType);
		Destroy();
	}
	
}

// Called every frame
void AHomingProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHomingProjectile::SetTarget(AActor* InTargetActor)
{
	ProjectileMovementComponent->HomingTargetComponent = InTargetActor->GetRootComponent();
	TargetActor = InTargetActor;
}

void AHomingProjectile::SetDamageEvent(FMyDamageEvent InDamageEvent)
{
	DamageEvent = InDamageEvent;
}

