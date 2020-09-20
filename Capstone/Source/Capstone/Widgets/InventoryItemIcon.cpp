// Troy Records Jr. 2020


#include "InventoryItemIcon.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Capstone/Widgets/InventoryWidget.h"

bool UInventoryItemIcon::Initialize()
{
    bool Success = Super::Initialize();
    if(!Success) return false;

    if(!ensure(ButtonIcon)) return false;
    ButtonIcon->OnClicked.AddDynamic(this, &UInventoryItemIcon::Pressed);

    return true;
}

// TODO refactor this to accept FWeaponStats
void UInventoryItemIcon::SetStats(FString InName, float InDamage)
{
    WeaponName = InName;
    WeaponDamage = FString::SanitizeFloat(InDamage);
    if(InDamage < 0)
        WeaponDamage = TEXT(" ");
    
    WeaponNameText->SetText(FText::FromString(WeaponName));
    WeaponDamageText->SetText(FText::FromString(WeaponDamage));
}

void UInventoryItemIcon::SetOwner(UInventoryWidget* InOwner)
{
    Owner = InOwner;
}

void UInventoryItemIcon::Pressed()
{
	Owner->EquipWeapon(this);
}
