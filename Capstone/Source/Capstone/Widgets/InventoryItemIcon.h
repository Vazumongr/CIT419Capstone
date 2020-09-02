// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItemIcon.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_API UInventoryItemIcon : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetStats(FString InName, float InDamage);

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* WeaponNameText;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* WeaponDamageText;

	FString WeaponName;
	FString WeaponDamage;
	
};
