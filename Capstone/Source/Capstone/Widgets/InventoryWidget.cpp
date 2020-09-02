// Troy Records Jr. 2020


#include "InventoryWidget.h"

#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Capstone/Widgets/InventoryItemIcon.h"

bool UInventoryWidget::Initialize()
{
    bool bSuccess = Super::Initialize();
    if(!bSuccess) return false;


    return true;;
}

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
        i++;
        CreateInventoryWidget(&WeaponStats, &i);
    }
    //GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, DebugMsg);
}

void UInventoryWidget::CreateInventoryWidget(FWeaponStats* InStats, int32* i)
{
    FString WidgetName(InStats->WeaponName);
    UInventoryItemIcon* NewWidget = CreateWidget<UInventoryItemIcon>(this, InventoryIconClass, FName(WidgetName));
    GridPanel->AddChildToUniformGrid(NewWidget,0,*i);
    NewWidget->SetStats(InStats->WeaponName, InStats->WeaponDamage);
}
