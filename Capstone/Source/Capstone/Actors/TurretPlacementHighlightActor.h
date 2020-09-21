// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurretPlacementHighlightActor.generated.h"

UCLASS()
class CAPSTONE_API ATurretPlacementHighlightActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurretPlacementHighlightActor();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetGoodMaterial();
	void SetBadMaterial();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh = nullptr;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TurretMesh = nullptr;
	UPROPERTY(EditAnywhere)
	UMaterialInstance* BadMaterial = nullptr;
	UPROPERTY(EditAnywhere)
	UMaterialInstance* GoodMaterial = nullptr;
	UPROPERTY(EditAnywhere)
	UMaterialInterface* InterMaterial = nullptr;

};
