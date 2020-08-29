// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Capstone/DataStructures/GameStructs.h"
#include "Inventory.generated.h"

struct FWeaponStats;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAPSTONE_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventory();
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddItem(FWeaponStats InObject);
	FORCEINLINE FWeaponStats GetItem(int32 Index) const { return Inventory[Index]; }
	FORCEINLINE int32 GetInventorySize() const { return Inventory.Num(); }

	void PrintArray();
	FString ToString();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	TArray<FWeaponStats> Inventory;

		
};
