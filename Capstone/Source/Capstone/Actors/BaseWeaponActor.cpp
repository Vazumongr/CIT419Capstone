// Troy Records Jr. 2020


#include "BaseWeaponActor.h"

#include "Capstone/Characters/PlayerCharacter.h"

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

