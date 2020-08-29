// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAPSTONE_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventory();
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddItem(UObject* InObject);
	FORCEINLINE UObject* GetItem(int32 Index) const { return Inventory[Index]; }
	FORCEINLINE int32 GetInventorySize() const { return Inventory.Num(); }

	void PrintArray();
	FString ToString();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	TArray<UObject*> Inventory;

		
};
