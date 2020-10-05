// Fill out your copyright notice in the Description page of Project Settings.


#include "ObservingPawn.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SceneComponent.h"
#include "Capstone/Controllers/ObservingPlayerController.h"
#include "Capstone/Characters/PlayerCharacter.h"

// Sets default values
AObservingPawn::AObservingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(SceneComponent);
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(FName(TEXT("Spring Arm")));
	SpringArmComponent->SetupAttachment(RootComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(FName(TEXT("Camera")));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

}

// Called when the game starts or when spawned
void AObservingPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObservingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(CameraLocked)
	{
		ensure(PlayerCharacter);
		SetActorLocation(PlayerCharacter->GetActorLocation());
	}

}

// Called to bind functionality to input
void AObservingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AObservingPawn::ToggleCameraLock()
{
	CameraLocked = !CameraLocked;
}

void AObservingPawn::CameraZoomOut()
{
	SpringArmComponent->TargetArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength += CameraSensitivity, CameraMinHeight, CameraMaxHeight);
}

void AObservingPawn::CameraZoomIn()
{
	SpringArmComponent->TargetArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength -= CameraSensitivity, CameraMinHeight, CameraMaxHeight);
}

void AObservingPawn::SetPlayerController(APlayerController* InController)
{
	ObservingPlayerController = Cast<AObservingPlayerController>(InController);
}

void AObservingPawn::SetPlayerCharacter(APlayerCharacter* InCharacter)
{
	PlayerCharacter = InCharacter;
}

