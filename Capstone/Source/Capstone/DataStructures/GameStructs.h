// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameStructs.generated.h"


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
 * 
 */
UCLASS()
class CAPSTONE_API UGameStructs : public UObject
{
	GENERATED_BODY()
	
};
