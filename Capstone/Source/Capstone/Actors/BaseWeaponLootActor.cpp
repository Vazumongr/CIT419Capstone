// Troy Records Jr. 2020


#include "BaseWeaponLootActor.h"

ABaseWeaponLootActor::ABaseWeaponLootActor()
{
    TSubclassOf<UDamageType> DamageType;
    //WeaponStats = FWeaponStats(TEXT("NewName"), 50, DamageType);
}

void ABaseWeaponLootActor::BeginPlay()
{
    Super::BeginPlay();
    WeaponStats.StaticMesh = StaticMeshComponent->GetStaticMesh();
}

void ABaseWeaponLootActor::Interact(APlayerCharacter* PlayerCharacter)
{
    UE_LOG(LogTemp, Warning, TEXT("Destroying..."));
    //Destroy();
}
