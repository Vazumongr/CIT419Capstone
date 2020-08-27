// Troy Records Jr. 2020


#include "BaseWeaponLootActor.h"
#include "BaseWeaponActor.h"

ABaseWeaponLootActor::ABaseWeaponLootActor()
{
    TSubclassOf<UDamageType> DamageType;
    WeaponStats = FWeaponStats(TEXT("NewName"), 50, DamageType);
}

void ABaseWeaponLootActor::Interact(APlayerCharacter* PlayerCharacter)
{
    Destroy();
}
