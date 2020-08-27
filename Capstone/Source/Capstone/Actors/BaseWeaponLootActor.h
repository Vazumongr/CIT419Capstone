// Troy Records Jr. 2020

#pragma once

#include "BaseWeaponActor.h"
#include "CoreMinimal.h"
#include "Capstone/Actors/BaseWeaponActor.h"
#include "Capstone/Actors/BaseLootActor.h"
#include "BaseWeaponLootActor.generated.h"

struct FWeaponStats;

/**
 * 
 */
UCLASS()
class CAPSTONE_API ABaseWeaponLootActor : public ABaseLootActor
{
	GENERATED_BODY()

	ABaseWeaponLootActor();
	
public:
	FORCEINLINE FWeaponStats GetWeaponStats() const { return WeaponStats; }
	
	virtual void Interact(class APlayerCharacter* PlayerCharacter) override;

private:
	FWeaponStats WeaponStats;
	
};
