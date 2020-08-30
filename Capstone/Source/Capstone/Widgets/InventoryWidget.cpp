// Troy Records Jr. 2020


#include "InventoryWidget.h"

#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"

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
        UUserWidget* NewWidget = CreateWidget<UUserWidget>(this, InventoryIconClass, FName(temp));
        GridPanel->AddChildToUniformGrid(NewWidget,0,i);
    }

    for(UWidget* widget : GridPanel->GetAllChildren())
    {
        UE_LOG(LogTemp, Warning, TEXT("Widget name is %s"), *widget->GetName());
    }
}

void UInventoryWidget::SetInventory(TArray<FWeaponStats> InInventory)
{
    Inventory = InInventory;
    FString DebugMsg = TEXT("Inventory Contains");
    for( FWeaponStats WeaponStats : Inventory)
    {
        DebugMsg = FString::Printf(TEXT("%s, %s"), *DebugMsg, *WeaponStats.WeaponName);
    }
    GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, DebugMsg);
}
