// Troy Records Jr. 2020


#include "ObservingPlayerController.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Capstone/Controllers/PlayerAIController.h"
#include "Capstone/Pawns/ObservingPawn.h"

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
    InputComponent->BindAxis("CameraZoom", this, &AObservingPlayerController::CameraZoom);
}

void AObservingPlayerController::MoveCommand()
{
    ensure(PlayerAIController);
    FHitResult HitResult;
    FVector WorldLocation, WorldDirection;
    DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

    FVector StartLocation = PlayerCameraManager->GetCameraLocation();
    FVector EndLocation = (StartLocation + (WorldDirection * 50000));
    
    TArray<AActor*> ActorsToIgnore;

    bool bHit = UKismetSystemLibrary::LineTraceSingle(this, StartLocation, EndLocation, UEngineTypes::ConvertToTraceType(ECC_Camera),
        false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true, FLinearColor::Yellow,
        FLinearColor::White, 5.0f);

    PlayerAIController->MoveToLocation(HitResult.Location);
    UE_LOG(LogTemp, Warning, TEXT("MoveCommand"));
}

void AObservingPlayerController::ToggleCameraLock()
{
    ensure(ObservingPawn);
    ObservingPawn->ToggleCameraLock();
}

void AObservingPlayerController::CameraZoom(float AxisValue)
{
    ensure(ObservingPawn);
    if(AxisValue < 0)
        ObservingPawn->CameraZoomOut();
    else if(AxisValue > 0)
        ObservingPawn->CameraZoomIn();
}

void AObservingPlayerController::SetPlayerAIController(APlayerAIController* InController)
{
    PlayerAIController = InController;
}

void AObservingPlayerController::SetObservingPawn(AObservingPawn* InPawn)
{
    ObservingPawn = InPawn;
}
