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
	UFUNCTION(BlueprintCallable)
    void SetOwningActor(AActor* NewOwner);

protected:
	UPROPERTY(BlueprintReadOnly);
	AActor* OwningActor;
};
