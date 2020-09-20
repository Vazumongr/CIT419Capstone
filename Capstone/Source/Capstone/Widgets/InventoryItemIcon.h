// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItemIcon.generated.h"

class UInventoryWidget;

/**
 * 
 */
UCLASS()
class CAPSTONE_API UInventoryItemIcon : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;
	void SetStats(FString InName, float InDamage);
	void SetOwner(UInventoryWidget* InOwner);

private:

	UFUNCTION()
	void Pressed();
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* WeaponNameText;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* WeaponDamageText;
	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonIcon;

	FString WeaponName;
	FString WeaponDamage;

	UPROPERTY()
	UInventoryWidget* Owner = nullptr;
	
};
