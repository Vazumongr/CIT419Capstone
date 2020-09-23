// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Capstone/Actors/BaseWeaponLootActor.h"

#include "LootGenerator.generated.h"

class ABaseWeaponLootActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAPSTONE_API ULootGenerator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULootGenerator();
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Starts the lot spawn sequence
	void SpawnLoot();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	// Base class for my weapons
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseWeaponLootActor> WeaponClass;
	// Class for health orb
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> HealthOrbClass;

	// Mesh for the weapon. TODO Might not be needed anymore
	UPROPERTY()
	UStaticMesh* WeaponMesh = nullptr;

	// Array to hold meshes retrieved during asset loading.
	UPROPERTY()
	TArray<UStaticMesh*> MyMeshes;
	
	// Spawns the weapon
	void SpawnWeapon();
	
	// Spawns the weapon
	void SpawnHealthOrb();

		
};
