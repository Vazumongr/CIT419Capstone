// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Capstone/DataStructures/GameStructs.h"

#include "HomingProjectile.generated.h"

struct FMyDamageEvent;

UCLASS()
class CAPSTONE_API AHomingProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHomingProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetTarget(AActor* TargetActor);
	void SetDamageEvent(FMyDamageEvent InDamageEvent);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:

	UFUNCTION()
	void HitEnemy(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UPROPERTY(EditDefaultsOnly)
	class UProjectileMovementComponent* ProjectileMovementComponent = nullptr;
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* StaticMeshComponent = nullptr;
	UPROPERTY(EditDefaultsOnly)
	class UNiagaraComponent* NiagaraComponent = nullptr;

	FMyDamageEvent DamageEvent;

	AActor* TargetActor = nullptr;


};
