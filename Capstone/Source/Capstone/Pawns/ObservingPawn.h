// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ObservingPawn.generated.h"

UCLASS()
class CAPSTONE_API AObservingPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AObservingPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Toggle the camera lock obvi
	void ToggleCameraLock();

	void CameraZoomOut();
	void CameraZoomIn();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* SceneComponent = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent = nullptr;

	UPROPERTY(EditAnywhere, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	bool CameraLocked = true;

	float CameraMaxHeight = 2000.f;
	float CameraMinHeight = 600.f;
	float CameraSensitivity = 50.f;


	// Setters and Getters. I want them out of my way
public:
	void SetPlayerController(class APlayerController* InController);
	void SetPlayerCharacter(class APlayerCharacter* InCharacter);

	FORCEINLINE APlayerCharacter* GetPlayerCharacter() const { return PlayerCharacter; }
	FORCEINLINE class AObservingPlayerController* GetPlayerController() const { return ObservingPlayerController; }

private:
	AObservingPlayerController* ObservingPlayerController = nullptr;
	APlayerCharacter* PlayerCharacter = nullptr;

};
