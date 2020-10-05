// Troy Records Jr. 2020


#include "BaseWeaponActor.h"

#include "Capstone/Characters/PlayerCharacter.h"
#include "Capstone/Actors/HomingProjectile.h"
#include "../../Engine/Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"
#include "../../Engine/Plugins/FX/Niagara/Source/Niagara/Classes/NiagaraSystem.h"
#include "../../Engine/Plugins/FX/Niagara/Source/Niagara/Public/NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseWeaponActor::ABaseWeaponActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMeshComponent->SetupAttachment(Root);
	
	StaticMeshComponent->SetCollisionProfileName(FName("NoCollision"));
}

void ABaseWeaponActor::InitializeStats(FWeaponStats InStats)
{
	WeaponStats = InStats;
	StaticMeshComponent->SetStaticMesh(WeaponStats.StaticMesh);
}

// Called when the game starts or when spawned
void ABaseWeaponActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseWeaponActor::SpawnMuzzleFlash(FRotator InRotation)
{
	ensure(MuzzleFlashSystem);
	FVector StartLocation = StaticMeshComponent->GetSocketTransform(FName(TEXT("BarrelEnd"))).GetLocation();
	UNiagaraComponent* MuzzleFlash = UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFlashSystem, StaticMeshComponent, TEXT("BarrelEnd"), FVector::ZeroVector,
																			FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset,false);
	//FVector VelocityDirection = GetActorRotation().Vector();
	//MuzzleFlash->SetVectorParameter(FName(TEXT("SpawnDirection")), VelocityDirection);
}

void ABaseWeaponActor::DealDamageToEnemy(AActor* EnemyToDamage, AController* PlayerController, AActor* PlayerActor)
{
	float DamageAmount = WeaponStats.WeaponDamage;
	TSubclassOf<UDamageType> DamageType = WeaponStats.DamageType;
	FPointDamageEvent PointDamageEvent;
	PointDamageEvent.Damage = DamageAmount;
	
	//UGameplayStatics::ApplyDamage(EnemyToDamage, DamageAmount, PlayerController, PlayerActor, DamageType);

	FMyDamageEvent DamageEvent(EnemyToDamage, DamageAmount, PlayerController, PlayerActor, DamageType);

	
	FVector StartLocation = StaticMeshComponent->GetSocketTransform(FName(TEXT("BarrelEnd"))).GetLocation();
	FActorSpawnParameters SpawnParams;
	
	
	AHomingProjectile* Bullet = GetWorld()->SpawnActor<AHomingProjectile>(BulletClass, StartLocation, FRotator::ZeroRotator);
	Bullet->SetTarget(EnemyToDamage);
	Bullet->SetDamageEvent(DamageEvent);

	
	SpawnMuzzleFlash(GetActorRotation());
}

