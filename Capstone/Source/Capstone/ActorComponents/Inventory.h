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

	// Adds a weapon to the inventory, storing it as a struct, essentially it's metadata
	void AddItem(FWeaponStats InObject);
	// Returns the weapon struct at a given index
	FORCEINLINE FWeaponStats GetItem(int32 Index) const { return Inventory[Index]; }
	// Returns the size of the iventory
	FORCEINLINE int32 GetInventorySize() const { return Inventory.Num(); }
	// Returns a copy of the inventory. TODO should probably return a pointer to this so there aren't copies floating around.
	FORCEINLINE TArray<FWeaponStats> GetInventoryTArray() const;

	void SetInventory(TArray<FWeaponStats> InInventory);

	// Prints the inventory
	void PrintArray();
	// Converts inventory contents to a string
	FString ToString();
	
	// This is the inventory array that holds all the data
	TArray<FWeaponStats> Inventory;		// TODO MOVE BACK TO PRIVATE EVENTUALLY

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

		
};
