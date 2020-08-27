// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Capstone/Actors/BaseLootActor.h"
#include "BaseWeaponActor.generated.h"

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

	FWeaponStats()
	{
		WeaponName = TEXT("Default Name");
		WeaponDamage = 0.0f;
	}
	
	FWeaponStats(FString InName, float InDamage, TSubclassOf<UDamageType> InDamageType)
	{
		WeaponName = InName;
		WeaponDamage = InDamage;
		DamageType = InDamageType;
	}
};

UCLASS()
class CAPSTONE_API ABaseWeaponActor : public ABaseLootActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeaponActor();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE float GetDamage() const { return WeaponStats.WeaponDamage; }

	FORCEINLINE FWeaponStats GetWeaponStats() const { return WeaponStats; }
	
	virtual void Interact(class APlayerCharacter* PlayerCharacter) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Setup", meta = (AllowPrivateAccess = "true"))
	FWeaponStats WeaponStats;

};
