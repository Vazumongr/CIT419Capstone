// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Capstone/Characters/PlayerCharacter.h"
#include "Capstone/DataStructures/GameStructs.h"


#include "BaseResourceDropActor.generated.h"

UCLASS()
class CAPSTONE_API ABaseResourceDropActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseResourceDropActor();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void LoadGame(FResourceDropSaveData InData);

protected:

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent = nullptr;
	UPROPERTY(EditAnywhere)
	class USphereComponent* TriggerZone = nullptr;

	UPROPERTY()
	float ResourceValue = 10.f;
	UFUNCTION()
	virtual void SaveGame();

	UFUNCTION()
    virtual void Overlapping(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);


};
