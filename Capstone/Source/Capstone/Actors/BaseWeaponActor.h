// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Capstone/Actors/BaseLootActor.h"
//#include "Capstone/Actors/BaseWeaponLootActor.h"
#include "BaseWeaponActor.generated.h"

UCLASS()
class CAPSTONE_API ABaseWeaponActor : public ABaseLootActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeaponActor();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*FORCEINLINE float GetDamage() const { return WeaponStats.WeaponDamage; }

	FORCEINLINE FWeaponStats GetWeaponStats() const { return WeaponStats; }*/
	
	virtual void Interact(class APlayerCharacter* PlayerCharacter) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:/*
	UPROPERTY(EditAnywhere, Category = "Setup", meta = (AllowPrivateAccess = "true"))
	FWeaponStats WeaponStats;*/

};
