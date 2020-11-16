// Troy Records Jr. 2020


#include "ProjectileBase.h"

#include "Capstone/Characters/PlayerCharacter.h"
#include "../../Engine/Plugins/FX/Niagara/Source/Niagara/Public/NiagaraComponent.h"
#include "Capstone/Characters/BaseEnemyCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	SetRootComponent(StaticMeshComponent);
	//StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBase::HitEnemy);
	
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara Component"));
	NiagaraComponent->SetupAttachment(StaticMeshComponent);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->InitialSpeed = MovementSpeed;
	ProjectileMovementComponent->MaxSpeed = MovementSpeed;
	ProjectileMovementComponent->ProjectileGravityScale = 0;

	InitialLifeSpan = 10.f;

}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectileBase::HitEnemy(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*
	if(ABaseEnemyCharacter* EnemyHit = Cast<ABaseEnemyCharacter>(OtherActor))
	{
		UGameplayStatics::ApplyDamage(EnemyHit, DamageEvent.DamageAmount, DamageEvent.PlayerController, DamageEvent.PlayerActor, DamageEvent.DamageType);
		Destroy();
	}
	*/
	if(OtherActor == OwningActor) return;
	ensure(OwningActor);
	TSubclassOf<AActor> OwnerClass = OwningActor->GetClass();
	TSubclassOf<AActor> OtherClass = OtherActor->GetClass();
	
	if(OwnerClass == OtherClass) return;
	
	UGameplayStatics::ApplyDamage(OtherActor, DamageEvent.DamageAmount, DamageEvent.PlayerController, DamageEvent.PlayerActor, DamageEvent.DamageType);
	UE_LOG(LogTemp, Warning, TEXT("I am destroying..."));
	Destroy();
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectileBase::SetDamageEvent(FMyDamageEvent InDamageEvent)
{
	DamageEvent = InDamageEvent;
}

void AProjectileBase::SetOwningActor(AActor* InOwner)
{
	OwningActor = InOwner;
}

