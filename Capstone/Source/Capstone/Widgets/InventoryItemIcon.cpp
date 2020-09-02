// Troy Records Jr. 2020


#include "InventoryItemIcon.h"

#include "Components/TextBlock.h"

void UInventoryItemIcon::SetStats(FString InName, float InDamage)
{
    WeaponName = InName;
    WeaponDamage = FString::SanitizeFloat(InDamage);
    WeaponNameText->SetText(FText::FromString(WeaponName));
    WeaponDamageText->SetText(FText::FromString(WeaponDamage));
}
