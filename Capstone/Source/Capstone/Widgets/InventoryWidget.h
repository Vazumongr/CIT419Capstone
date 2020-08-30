// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Capstone/DataStructures/GameStructs.h"


#include "InventoryWidget.generated.h"
struct FWeaponStats;

/**
 * 
 */
UCLASS()
class CAPSTONE_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual bool Initialize() override;

    void SetText(FString InText);

    void SetInventory(TArray<FWeaponStats> InInventory);

protected:
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* InventoryTitleText = nullptr;
    UPROPERTY(meta = (BindWidget))
    class UUniformGridPanel* GridPanel = nullptr;
    UPROPERTY(EditAnywhere)
    TSubclassOf<UUserWidget> InventoryIconClass;

    FString InventoryAsString = "";

private:
    TArray<FString> Out;
    TArray<FWeaponStats> Inventory;
};
