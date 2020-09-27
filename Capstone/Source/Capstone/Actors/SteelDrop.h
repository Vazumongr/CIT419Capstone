// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SteelDrop.generated.h"

UCLASS()
class CAPSTONE_API ASteelDrop : public AActor
{
	GENERATED_BODY()
	public:	
	// Sets default values for this actor's properties
	ASteelDrop();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent = nullptr;
	UPROPERTY(EditAnywhere)
	class USphereComponent* TriggerZone = nullptr;

	UFUNCTION()
    void Overlapping(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);


};