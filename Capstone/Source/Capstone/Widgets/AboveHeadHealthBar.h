// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AboveHeadHealthBar.generated.h"

/**	TODO CHANGE THE NAMES OF THESE CLASSES BC THEY CONFUSING AS HELL
 * 
 */
UCLASS()
class CAPSTONE_API UAboveHeadHealthBar : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetOwningActor(AActor* NewOwner);

protected:
	UPROPERTY(BlueprintReadOnly);
	AActor* OwningActor;
	
};
