// Troy Records Jr. 2020


#include "ObservingPlayerController.h"

void AObservingPlayerController::BeginPlay()
{
    Super::BeginPlay();

    bShowMouseCursor = true;
}

void AObservingPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    InputComponent->BindAction("MoveCommand", IE_Pressed, this, &AObservingPlayerController::MoveCommand);
    InputComponent->BindAction("ToggleCameraLock", IE_Pressed, this, &AObservingPlayerController::ToggleCameraLock);
}

void AObservingPlayerController::MoveCommand()
{
    UE_LOG(LogTemp, Warning, TEXT("MoveCommand"));
}

void AObservingPlayerController::ToggleCameraLock()
{
    UE_LOG(LogTemp, Warning, TEXT("ToggleCameraLock"));
}
