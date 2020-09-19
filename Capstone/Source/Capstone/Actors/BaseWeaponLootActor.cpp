// Troy Records Jr. 2020


#include "BaseWeaponLootActor.h"

ABaseWeaponLootActor::ABaseWeaponLootActor()
{
    TSubclassOf<UDamageType> DamageType;
    //WeaponStats = FWeaponStats(TEXT("NewName"), 50, DamageType);
    UE_LOG(LogTemp, Warning, TEXT("Boring constructor"));
}

void ABaseWeaponLootActor::BeginPlay()
{
    Super::BeginPlay();
    WeaponStats.StaticMesh = StaticMeshComponent->GetStaticMesh();
}

void ABaseWeaponLootActor::SetWeaponStats(FWeaponStats InStats)
{
    WeaponStats = InStats;
    StaticMeshComponent->SetStaticMesh(WeaponStats.StaticMesh);
}

void ABaseWeaponLootActor::Interact(APlayerCharacter* PlayerCharacter)
{
    Destroy();
}
