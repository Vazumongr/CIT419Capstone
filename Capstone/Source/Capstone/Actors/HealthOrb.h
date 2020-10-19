// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "Capstone/Actors/BaseResourceDropActor.h"
#include "HealthOrb.generated.h"

UCLASS()
class CAPSTONE_API AHealthOrb : public ABaseResourceDropActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthOrb();

protected:
	
	virtual void Overlapping(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;


};
