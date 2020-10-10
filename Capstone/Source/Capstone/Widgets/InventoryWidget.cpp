// Troy Records Jr. 2020


#include "InventoryWidget.h"

#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Capstone/Widgets/InventoryItemIcon.h"
#include "Capstone/Controllers/ObservingPlayerController.h"

bool UInventoryWidget::Initialize()
{
    bool bSuccess = Super::Initialize();
    if(!bSuccess) return false;

    InitializeInventoryArray();

    if(GetOwningPlayer() != nullptr)
        OwningController = Cast<AObservingPlayerController>(GetOwningPlayer());


    return true;;
}

// TODO I think I can remove this
void UInventoryWidget::SetText(FString InText)
{
    InventoryAsString = InText;

    InText.ParseIntoArray(Out,TEXT(", "), true);

    for(int32 i = 0; i < Out.Num(); i++)
    {
        FString temp = Out[i];
        temp = FString::Printf(TEXT("%s %i"), *Out[i], i);
        UInventoryItemIcon* NewWidget = CreateWidget<UInventoryItemIcon>(this, InventoryIconClass, FName(temp));
        GridPanel->AddChildToUniformGrid(NewWidget,0,i);
    }
}

void UInventoryWidget::SetInventory(TArray<FWeaponStats> InInventory)
{
    Inventory = InInventory;
    FString DebugMsg = TEXT("Inventory Contains");
    int32 i = 0;
    for( FWeaponStats WeaponStats : Inventory)
    {
        InventoryIconArray[i]->SetStats(WeaponStats.WeaponName, WeaponStats.WeaponDamage);
        InventoryWeaponMap.Add(InventoryIconArray[i], WeaponStats);
        i++;
    }
}

void UInventoryWidget::CreateInventoryWidget(FWeaponStats* InStats, int32* i)
{
    FString WidgetName(InStats->WeaponName);
    UInventoryItemIcon* NewWidget = CreateWidget<UInventoryItemIcon>(this, InventoryIconClass, FName(WidgetName));
    GridPanel->AddChildToUniformGrid(NewWidget,0,*i);
    NewWidget->SetStats(InStats->WeaponName, InStats->WeaponDamage);
}

void UInventoryWidget::EquipWeapon(UInventoryItemIcon* InIcon)
{
    for(UInventoryItemIcon* Icon : InventoryIconArray)
    {
        if(Icon == InIcon)
        {
            if(InventoryWeaponMap.Find(Icon) == nullptr) return;
            
            FWeaponStats Stats = *InventoryWeaponMap.Find(Icon);
            
            if(OwningController != nullptr)
                OwningController->EquipWeapon(Stats);
        }
    }
    UE_LOG(LogTemp, Warning, TEXT("Tearing"));
    //TearDown();
}

void UInventoryWidget::InitializeInventoryArray()
{
    InventoryIconArray.Add(Weapon1);
    InventoryIconArray.Add(Weapon2);
    InventoryIconArray.Add(Weapon3);
    InventoryIconArray.Add(Weapon4);
    InventoryIconArray.Add(Weapon5);
    for( UInventoryItemIcon* Icon : InventoryIconArray)
    {
        Icon->SetStats(TEXT(" "), -1);
        Icon->SetOwner(this);
    }
}
