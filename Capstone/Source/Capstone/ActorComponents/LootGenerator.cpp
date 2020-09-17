// Troy Records Jr. 2020


#include "LootGenerator.h"

#include "Capstone/DataStructures/GameStructs.h"

// Sets default values for this component's properties
ULootGenerator::ULootGenerator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void ULootGenerator::SpawnWeapon()
{
	FActorSpawnParameters SpawnParams;
	FVector SpawnLocation = GetOwner()->GetActorLocation();
	GetWorld()->SpawnActor<ABaseWeaponLootActor>(WeaponClass, SpawnLocation, FRotator::ZeroRotator);
}


// Called when the game starts
void ULootGenerator::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULootGenerator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

