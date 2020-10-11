// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "FloatingDamageNumbersComponent.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_API UFloatingDamageNumbersComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	virtual void InitWidget() override;
	void SetDamageToDisplay(float DamageToDisplay);

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
};
