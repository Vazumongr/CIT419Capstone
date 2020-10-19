// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "Capstone/DataStructures/GameStructs.h"
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

	UFUNCTION()
	void SaveGame();
	UFUNCTION()
	void LoadGame(FTurretSaveData InData);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	void DetectEnemies();
	void SpawnBeamEffect();
	void SpawnAimingBeam();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh = nullptr;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TurretMesh = nullptr;
	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* AimBeamSystem;
	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* ShotBeamSystem;

	UPROPERTY()
	class UNiagaraComponent* AimingBeam = nullptr;

	UPROPERTY(EditAnywhere, Category = "Trace")
	float TraceRange = 500.0f;

	UPROPERTY()
	AActor* TargetedEnemy = nullptr;
	UPROPERTY()
	AActor* Player = nullptr;

	float ReloadTime = 2.f;
	float LastFireTime = 0.f;
	

};
