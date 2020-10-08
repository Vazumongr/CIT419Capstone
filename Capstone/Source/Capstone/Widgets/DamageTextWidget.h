// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

#include "DamageTextWidget.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_API UDamageTextWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetOwner(USceneComponent* InOwner, APlayerController* InPlayerController);
	void SetText(float InDamage);

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY()
	USceneComponent* Owner = nullptr;
	UPROPERTY()
	APlayerController* PlayerController = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DamageText = nullptr;
};
