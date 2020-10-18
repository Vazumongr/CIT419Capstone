// Troy Records Jr. 2020


#include "Inventory.h"

// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventory::AddItem(FWeaponStats InObject)
{
	Inventory.Add(InObject);	// Adds the given object to the inventory
}

TArray<FWeaponStats> UInventory::GetInventoryTArray() const
{
	return Inventory;	// Returns the inventory array. Should do as a pointer.
}

void UInventory::SetInventory(TArray<FWeaponStats> InInventory)
{
	Inventory = InInventory;
}

// TODO I don't think I have a use for this anymore
void UInventory::PrintArray()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *ToString());
}

// TODO only used in PrintArray. Not needed.
FString UInventory::ToString()
{
	FString String = TEXT("");
	for ( FWeaponStats Stats : Inventory)
	{
		String = String + Stats.WeaponName + TEXT(", ");
	}
	return String;
}

