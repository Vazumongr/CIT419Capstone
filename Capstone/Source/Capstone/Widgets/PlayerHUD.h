// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;
	UFUNCTION(BlueprintCallable)
    void SetOwningActor(AActor* NewOwner);
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly);
	AActor* OwningActor;

private:
	UPROPERTY()
	class AMainGameState* GameState = nullptr;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TimerText = nullptr;
};
