// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "Capstone/Actors/BaseLootActor.h"
#include "Capstone/DataStructures/GameStructs.h"
#include "BaseWeaponLootActor.generated.h"


/**
 * 	TODO Gonna refactor all this weapon stuff again later.
 */
UCLASS()
class CAPSTONE_API ABaseWeaponLootActor : public ABaseLootActor
{
	GENERATED_BODY()
	
public:
	ABaseWeaponLootActor();
	
	virtual void BeginPlay() override;
	
	FORCEINLINE FWeaponStats GetWeaponStats() const { return WeaponStats; }
	
	virtual void Interact(class APlayerCharacter* PlayerCharacter) override;

private:
	UPROPERTY(EditAnywhere, Category = "Weapon Stats", meta = (AllowPrivateAccess = "true"))
	FWeaponStats WeaponStats;
	
};
