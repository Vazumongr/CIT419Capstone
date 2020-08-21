// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "Capstone/Interfaces/InteractableItemInterface.h"
#include "GameFramework/Actor.h"
#include "BaseLootActor.generated.h"

UCLASS()
class CAPSTONE_API ABaseLootActor : public AActor, public IInteractableItemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseLootActor();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
