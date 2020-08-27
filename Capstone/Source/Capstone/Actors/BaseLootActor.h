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

	virtual void Interact(class APlayerCharacter* PlayerCharacter) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Root;
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* StaticMeshComponent = nullptr;
};
