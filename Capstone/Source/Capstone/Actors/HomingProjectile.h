// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "Capstone/Actors/ProjectileBase.h"
#include "Capstone/DataStructures/GameStructs.h"

#include "HomingProjectile.generated.h"

struct FMyDamageEvent;

UCLASS()
class CAPSTONE_API AHomingProjectile : public AProjectileBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHomingProjectile();


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetTarget(AActor* TargetActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:

	UPROPERTY()
	AActor* TargetActor = nullptr;


};
