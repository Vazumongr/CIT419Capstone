// Troy Records Jr. 2020


#include "ObservingPlayerController.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Capstone/Controllers/PlayerAIController.h"
#include "Capstone/Pawns/ObservingPawn.h"
#include "Capstone/Widgets/InventoryWidget.h"
#include "Capstone/Widgets/PlayerHUD.h"

AObservingPlayerController::AObservingPlayerController()
{
    
}

void AObservingPlayerController::BeginPlay()
{
    Super::BeginPlay();

    bShowMouseCursor = true;

    // TODO refactor into own method
    ensure(HUDClass);
    HUDWidget = CreateWidget<UPlayerHUD>(this, HUDClass, FName(TEXT("HUD")));
    HUDWidget->AddToViewport();
    ensure(PlayerAIController);
    HUDWidget->SetOwningActor(PlayerAIController->GetPawn());
}

void AObservingPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    // Action Bindings
    InputComponent->BindAction("MoveCommand", IE_Pressed, this, &AObservingPlayerController::MoveCommand);
    InputComponent->BindAction("ToggleCameraLock", IE_Pressed, this, &AObservingPlayerController::ToggleCameraLock);
    InputComponent->BindAction("PrintInventory", IE_Pressed, this, &AObservingPlayerController::PrintInventory);
    InputComponent->BindAction("SwitchWeapon", IE_Pressed, this, &AObservingPlayerController::SwitchWeapon);
    InputComponent->BindAction("PlaceTurret", IE_Pressed, this, &AObservingPlayerController::PlaceTurret);
    // Axis Bindings
    InputComponent->BindAxis("CameraZoom", this, &AObservingPlayerController::CameraZoom);
}

/** Handle the move command and send the HitResult to the PlayerAIController if we have it */
void AObservingPlayerController::MoveCommand()
{
    // TODO Refactor LineTrace into another method
    ensure(PlayerAIController);
    FHitResult HitResult;
    FVector WorldLocation, WorldDirection;
    DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

    FVector StartLocation = PlayerCameraManager->GetCameraLocation();
    FVector EndLocation = (StartLocation + (WorldDirection * 50000));    // TODO no magic numbers
    
    TArray<AActor*> ActorsToIgnore;

    bool bHit = UKismetSystemLibrary::LineTraceSingle(this, StartLocation, EndLocation, UEngineTypes::ConvertToTraceType(ECC_Camera),
        false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true, FLinearColor::Yellow,
        FLinearColor::White, 5.0f);
    
    if(bHit) PlayerAIController->ProcessHitResult(HitResult);
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

void AObservingPlayerController::PrintInventory()
{
    ensure(PlayerAIController);
    PlayerAIController->PrintInventory();

    ensure(InventoryClass);
    if(InventoryWidget == nullptr)
    {
        InventoryWidget = Cast<UInventoryWidget>(CreateWidget(this, InventoryClass));
        
        if(InventoryWidget != nullptr)
        {
            InventoryWidget->AddToViewport();
            InventoryWidget->SetInventory(PlayerAIController->GetInventoryAsArray());
        }
            
    }
    else
    {
        if(InventoryWidget->GetVisibility() == ESlateVisibility::Collapsed)
        {
            InventoryWidget->SetVisibility(ESlateVisibility::Visible);
            InventoryWidget->SetInventory(PlayerAIController->GetInventoryAsArray());
        }
        else
            InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
    }
    
        
   
}

void AObservingPlayerController::SwitchWeapon()
{
    ensure(PlayerAIController);
    PlayerAIController->SwitchWeapon();
}

void AObservingPlayerController::PlaceTurret()
{
    FHitResult HitResult;
    FVector WorldLocation, WorldDirection;
    DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

    FVector StartLocation = PlayerCameraManager->GetCameraLocation();
    FVector EndLocation = (StartLocation + (WorldDirection * 50000));    // TODO no magic numbers
    
    TArray<AActor*> ActorsToIgnore;

    bool bHit = UKismetSystemLibrary::LineTraceSingle(this, StartLocation, EndLocation, UEngineTypes::ConvertToTraceType(ECC_Camera),
        false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true, FLinearColor::Yellow,
        FLinearColor::White, 5.0f);

    if(bHit)
    {
        ensure(TurretClass);
        FActorSpawnParameters Params;
        FRotator Rotation;
        GetWorld()->SpawnActor<AActor>(TurretClass, HitResult.Location, Rotation, Params);
    }
}

void AObservingPlayerController::SetPlayerAIController(APlayerAIController* InController)
{
    PlayerAIController = InController;
}

void AObservingPlayerController::SetObservingPawn(AObservingPawn* InPawn)
{
    ObservingPawn = InPawn;
}
