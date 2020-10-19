// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "Capstone/Actors/BaseResourceDropActor.h"
#include "SteelDrop.generated.h"

UCLASS()
class CAPSTONE_API ASteelDrop : public ABaseResourceDropActor
{
	GENERATED_BODY()
	public:	
	// Sets default values for this actor's properties
	ASteelDrop();

	
    virtual void Overlapping(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;


};