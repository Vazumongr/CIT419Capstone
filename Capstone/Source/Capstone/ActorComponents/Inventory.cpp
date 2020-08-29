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
	Inventory.Add(InObject);
}

void UInventory::PrintArray()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *ToString());
}

FString UInventory::ToString()
{
	FString String = TEXT("");
	for ( FWeaponStats Stats : Inventory)
	{
		String = String + Stats.WeaponName + TEXT(", ");
	}
	return String;
}

