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

private:
	UPROPERTY(EditAnywhere)
	float MinDriftRange = 5.f;
	UPROPERTY(EditAnywhere)
	float MaxDriftRange = 50.f;
	UPROPERTY(EditAnywhere)
	float LerpAlpha = .5f;
	UFUNCTION()
	void DestroySelf();
	
	FVector EndLocation;
	FTimerHandle DeathTimerHandle;
	float LifeLength = 2.f;
	
};
