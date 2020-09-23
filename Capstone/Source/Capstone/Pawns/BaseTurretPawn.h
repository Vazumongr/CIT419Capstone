// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseTurretPawn.generated.h"

UCLASS()
class CAPSTONE_API ABaseTurretPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseTurretPawn();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetPlayer(AActor* InPlayer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	void DetectEnemies();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh = nullptr;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TurretMesh = nullptr;
	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* BeamSystem;

	UPROPERTY(EditAnywhere, Category = "Trace")
	float TraceRange = 500.0f;

	UPROPERTY()
	AActor* TargetedEnemy = nullptr;
	UPROPERTY()
	AActor* Player = nullptr;

	float ReloadTime = 2.f;
	float LastFireTime = 0.f;
	

};
