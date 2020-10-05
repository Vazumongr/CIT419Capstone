// Troy Records Jr. 2020


#include "LootGenerator.h"

#include "Capstone/DataStructures/GameStructs.h"
#include "Capstone/Actors/BaseWeaponLootActor.h"
#include "Engine/ObjectLibrary.h"

// Sets default values for this component's properties
ULootGenerator::ULootGenerator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void ULootGenerator::BeginPlay()
{
	Super::BeginPlay();

	static TArray<UStaticMesh*> MeshLibrary;	// Static array to hold the data so I don't have a million objects trying to load the assets.

	// TODO probs refactor this into a new method
	if(MeshLibrary.Num() == 0)
	{
		const TSubclassOf<UStaticMesh> BaseClass;	// Get our BaseClass to create the library
        UObjectLibrary* Lib = UObjectLibrary::CreateLibrary(BaseClass, false, false);	// Creates the library to hold the assets
        Lib->AddToRoot();	// Don't allow garbage collection to delete it
        const int32 Loaded = Lib->LoadAssetsFromPath("/Game/Meshes/WeaponMeshes");	// Load the assets from this folder into the library
		
        Lib->GetObjects(MeshLibrary);	// Get a TArray of the assets and import it into our own TArray
        for(UStaticMesh* Mesh : MeshLibrary)
        {
        	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("Loaded %s asset"), *Mesh->GetName()));
        }
	}
	else
	{
		for(UStaticMesh* Mesh : MeshLibrary)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("This asset was already loaded for me: %s"), *Mesh->GetName()));
		}
	}

	MyMeshes = MeshLibrary;	// Copy the mesh library so we have a personal copy for global use.
	
	
	
}

// This handles the weapon spawning
void ULootGenerator::SpawnWeapon()
{
	if(!WeaponClass)
	{
		UE_LOG(LogTemp, Error, TEXT("YOU FORGOT TO ASSING WEAPONCLASS BUD"));
		return;
	}
		
	
	FActorSpawnParameters SpawnParams;
	FVector SpawnLocation = GetOwner()->GetActorLocation();
	ABaseWeaponLootActor* SpawnedWeapon = GetWorld()->SpawnActor<ABaseWeaponLootActor>(WeaponClass, SpawnLocation, FRotator::ZeroRotator);
	
	FWeaponStats WeaponsStats;
	
	WeaponsStats.WeaponDamage = FMath::RandRange(10,100);
	
	WeaponsStats.WeaponName = FString::Printf(TEXT("SpawnedWeapon%s"), *FString::SanitizeFloat(FMath::RandRange(1,99)));	// Creates a random name

	if(MyMeshes.Num() > 0)
	{
		WeaponsStats.StaticMesh = MyMeshes[FMath::RandRange(0,MyMeshes.Num()-1)];	// Grabs a random mesh from MyMeshes
	}
	
	if(SpawnedWeapon != nullptr)
		SpawnedWeapon->SetWeaponStats(WeaponsStats);
	
}

void ULootGenerator::SpawnLoot()
{
	if(FMath::RandRange(1,1) == 1)
	{
		if(HealthOrbClass) SpawnResource(HealthOrbClass);
	}
	if(FMath::RandRange(1,2) == 1)
	{
		SpawnWeapon();
	}
	if(SteelDropClass) SpawnResource(SteelDropClass);
	
}

void ULootGenerator::SpawnResource(TSubclassOf<AActor> ResourceToDrop)
{
	if(!ResourceToDrop)
	{
		UE_LOG(LogTemp, Warning, TEXT("You forgot to assign something"));
		return;
	}
	FActorSpawnParameters SpawnParams;
	FVector SpawnLocation = GetOwner()->GetActorLocation();
	AActor* SpawnedResource = GetWorld()->SpawnActor<AActor>(ResourceToDrop, SpawnLocation, FRotator::ZeroRotator);
}

