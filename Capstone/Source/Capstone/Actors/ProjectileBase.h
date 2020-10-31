// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Capstone/DataStructures/GameStructs.h"

#include "ProjectileBase.generated.h"

UCLASS()
class CAPSTONE_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetDamageEvent(FMyDamageEvent InDamageEvent);
	void SetOwningActor(AActor* InOwner);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly)
	class UProjectileMovementComponent* ProjectileMovementComponent = nullptr;
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* StaticMeshComponent = nullptr;
	UPROPERTY(EditDefaultsOnly)
	class UNiagaraComponent* NiagaraComponent = nullptr;

	FMyDamageEvent DamageEvent;

	float MovementSpeed = 1300.f;
	
	UFUNCTION()
    void HitEnemy(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

private:
	UPROPERTY()
	AActor* OwningActor;
	
	


};
