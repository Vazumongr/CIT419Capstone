// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "InventoryItemIcon.h"
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

    void CreateInventoryWidget(FWeaponStats* InStats, int32* i);

    void EquipWeapon(UInventoryItemIcon* InIcon);

protected:
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* InventoryTitleText = nullptr;
    UPROPERTY(meta = (BindWidget))
    class UUniformGridPanel* GridPanel = nullptr;
    UPROPERTY(meta = (BindWidget))
    class UInventoryItemIcon* Weapon1 = nullptr;
    UPROPERTY(meta = (BindWidget))
    class UInventoryItemIcon* Weapon2 = nullptr;
    UPROPERTY(meta = (BindWidget))
    class UInventoryItemIcon* Weapon3 = nullptr;
    UPROPERTY(meta = (BindWidget))
    class UInventoryItemIcon* Weapon4 = nullptr;
    UPROPERTY(meta = (BindWidget))
    class UInventoryItemIcon* Weapon5 = nullptr;
    UPROPERTY(EditAnywhere)
    TSubclassOf<class UInventoryItemIcon> InventoryIconClass;

    FString InventoryAsString = "";

private:
    TArray<FString> Out;
    TArray<FWeaponStats> Inventory;
    TArray<UInventoryItemIcon*> InventoryIconArray;

    TMap<UInventoryItemIcon*, FWeaponStats> InventoryWeaponMap;

    class AObservingPlayerController* OwningController;

    void InitializeInventoryArray();
};
