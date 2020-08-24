// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "BaseAboveHeadHealthbar.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_API UBaseAboveHeadHealthbar : public UWidgetComponent
{
	GENERATED_BODY()

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
	virtual void BeginPlay() override;

private:
	virtual void FaceTowardsCamera();

	APlayerCameraManager* PlayerCameraManager = nullptr;
	
};
