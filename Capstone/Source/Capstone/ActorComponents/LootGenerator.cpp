// Troy Records Jr. 2020


#include "LootGenerator.h"

#include "Capstone/DataStructures/GameStructs.h"
#include "Capstone/Actors/BaseWeaponLootActor.h"

// Sets default values for this component's properties
ULootGenerator::ULootGenerator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshObject(TEXT("/Game/Meshes/SM_Rifle"));
	if(!ensure(StaticMeshObject.Object))
	{
		UE_LOG(LogTemp, Warning, TEXT("Weapon mesh not found..."));
		return;
	}
	WeaponMesh = StaticMeshObject.Object;

	// ...
}

void ULootGenerator::SpawnWeapon()
{
	if(!WeaponClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("YOU FORGOT TO ASSING WEAPONCLASS BUD"));
		return;
	}
		
	
	FActorSpawnParameters SpawnParams;
	FVector SpawnLocation = GetOwner()->GetActorLocation();
	ABaseWeaponLootActor* SpawnedWeapon = GetWorld()->SpawnActor<ABaseWeaponLootActor>(WeaponClass, SpawnLocation, FRotator::ZeroRotator);
	
	FWeaponStats WeaponsStats;
	WeaponsStats.WeaponDamage = 30.0f;
	WeaponsStats.WeaponName = FString(TEXT("SpawnedWeapon"));
	ensure(WeaponMesh);
	if(WeaponMesh != nullptr)
		WeaponsStats.StaticMesh = WeaponMesh;
	if(SpawnedWeapon != nullptr)
		SpawnedWeapon->SetWeaponStats(WeaponsStats);
	
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

