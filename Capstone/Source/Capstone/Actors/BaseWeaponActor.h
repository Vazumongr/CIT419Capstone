// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Capstone/DataStructures/GameStructs.h"
#include "BaseWeaponActor.generated.h"

struct FWeaponStats;

UCLASS()
class CAPSTONE_API ABaseWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeaponActor();

	void InitializeStats(FWeaponStats InStats);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SpawnMuzzleFlash(FRotator InRotation);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Root;
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* StaticMeshComponent = nullptr;

private:
	FWeaponStats WeaponStats;
	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* MuzzleFlashSystem;

};
