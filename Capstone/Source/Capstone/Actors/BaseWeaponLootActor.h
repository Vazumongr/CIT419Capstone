// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "Capstone/Actors/BaseLootActor.h"
#include "Capstone/DataStructures/GameStructs.h"
#include "BaseWeaponLootActor.generated.h"


/**
 * 	
 */
UCLASS()
class CAPSTONE_API ABaseWeaponLootActor : public ABaseLootActor
{
	GENERATED_BODY()
	
public:
	ABaseWeaponLootActor();
	
	virtual void BeginPlay() override;
	
	FORCEINLINE FWeaponStats GetWeaponStats() const { return WeaponStats; }
	void SetWeaponStats(FWeaponStats InStats);
	
	virtual void Interact(class APlayerCharacter* PlayerCharacter) override;

	//void LoadGame(FWeaponDropSaveData InData);

private:
	UFUNCTION()
	void SaveGame();
	
	UPROPERTY(EditAnywhere, Category = "Weapon Stats", meta = (AllowPrivateAccess = "true"))
	FWeaponStats WeaponStats;
	UPROPERTY(EditAnywhere, Category = "Setup", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDamageType> DamageType;
	
};
