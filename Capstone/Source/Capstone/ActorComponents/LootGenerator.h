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

	void SpawnWeapon();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseWeaponLootActor> WeaponClass;

	UPROPERTY()
	UStaticMesh* WeaponMesh = nullptr;

	static TArray<UStaticMesh*> MeshLibrary;

		
};
