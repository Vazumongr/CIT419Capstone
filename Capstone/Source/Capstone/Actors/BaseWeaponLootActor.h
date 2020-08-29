// Troy Records Jr. 2020

#pragma once

#include "BaseWeaponActor.h"
#include "CoreMinimal.h"
#include "Capstone/Actors/BaseLootActor.h"
#include "BaseWeaponLootActor.generated.h"

USTRUCT()
struct FWeaponStats
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FString WeaponName;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float WeaponDamage;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDamageType> DamageType;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMesh* StaticMesh;

	FWeaponStats()
	{
		WeaponName = TEXT("Default Name");
		WeaponDamage = 10.0f;
		StaticMesh = nullptr;
	}
	
	FWeaponStats(FString InName, float InDamage, TSubclassOf<UDamageType> InDamageType, UStaticMesh* InMesh)
	{
		WeaponName = InName;
		WeaponDamage = InDamage;
		DamageType = InDamageType;
		StaticMesh = InMesh;
	}
};
/**
 * 	TODO Gonna refactor all this weapon stuff again later.
 */
UCLASS()
class CAPSTONE_API ABaseWeaponLootActor : public ABaseLootActor
{
	GENERATED_BODY()

	ABaseWeaponLootActor();
	
public:
	virtual void BeginPlay() override;
	
	FORCEINLINE FWeaponStats GetWeaponStats() const { return WeaponStats; }
	
	virtual void Interact(class APlayerCharacter* PlayerCharacter) override;

private:
	UPROPERTY(EditAnywhere, Category = "Weapon Stats", meta = (AllowPrivateAccess = "true"))
	FWeaponStats WeaponStats;
	
};
