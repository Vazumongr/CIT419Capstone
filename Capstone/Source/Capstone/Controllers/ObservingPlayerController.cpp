// Troy Records Jr. 2020


#include "ObservingPlayerController.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Capstone/Actors/TurretPlacementHighlightActor.h"
#include "Capstone/Controllers/PlayerAIController.h"
#include "Capstone/Pawns/BaseTurretPawn.h"
#include "Capstone/Pawns/ObservingPawn.h"
#include "Capstone/Widgets/InventoryWidget.h"
#include "Capstone/Widgets/PlayerHUD.h"

AObservingPlayerController::AObservingPlayerController()
{
    
}

void AObservingPlayerController::TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
    Super::TickActor(DeltaTime, TickType, ThisTickFunction);
    if(TurretPlacement != nullptr)
    {
        ensure(PlayerAIController);
        FHitResult HitResult;
        bool bHit = LineTrace(HitResult);
        if(bHit)
        {
            if(Cast<APawn>(HitResult.Actor) || PlayerAIController->GetSteel() < 10)
            {
                TurretPlacement->SetBadMaterial();
            }
            else
            {
                TurretPlacement->SetGoodMaterial();
            }
            TurretPlacement->SetActorLocation(HitResult.Location);
        }
    }
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

void AObservingPlayerController::EquipWeapon(FWeaponStats InStats)
{
    ensure(PlayerAIController);
    PlayerAIController->SwitchWeapon(InStats);
}

void AObservingPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    // Action Bindings
    InputComponent->BindAction("MoveCommand", IE_Pressed, this, &AObservingPlayerController::MoveCommand);
    InputComponent->BindAction("ToggleCameraLock", IE_Pressed, this, &AObservingPlayerController::ToggleCameraLock);
    InputComponent->BindAction("PrintInventory", IE_Pressed, this, &AObservingPlayerController::PrintInventory);
    InputComponent->BindAction("SwitchWeapon", IE_Pressed, this, &AObservingPlayerController::SwitchWeapon);
    InputComponent->BindAction("PlaceTurret", IE_Pressed, this, &AObservingPlayerController::PrepareTurret);
    // Axis Bindings
    InputComponent->BindAxis("CameraZoom", this, &AObservingPlayerController::CameraZoom);
}

/** Handle the move command and send the HitResult to the PlayerAIController if we have it */
void AObservingPlayerController::MoveCommand()
{
    if(TurretPlacement != nullptr)
    {
        PlaceTurret();
        TurretPlacement->Destroy();
        TurretPlacement = nullptr;
        return;
    }
    
    ensure(PlayerAIController);
    FHitResult HitResult;

    bool bHit = LineTrace(HitResult);
    
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
    //PlayerAIController->SwitchWeapon();
}

void AObservingPlayerController::PrepareTurret()
{
    if(TurretPlacement != nullptr)
    {
        TurretPlacement->Destroy();
        TurretPlacement = nullptr;
        return;
    }
    FHitResult HitResult;
    bool bHit = LineTrace(HitResult);

    if(bHit)
    {
        ensure(TurretClass);
        FActorSpawnParameters Params;
        FRotator Rotation;
        TurretPlacement = GetWorld()->SpawnActor<ATurretPlacementHighlightActor>(TurretPlacementClass, HitResult.Location, Rotation, Params);
    }
}

void AObservingPlayerController::PlaceTurret()
{
    FHitResult HitResult;

    // TODO if we ain't clicking on the ground, no placement.
    const bool bHit = LineTrace(HitResult);


    if(bHit)
    {
        // IF we have enough steel
        if(Cast<APawn>(HitResult.Actor) || PlayerAIController->GetSteel() < 10)
        {
            return;
        }
        ensure(TurretClass);
        FActorSpawnParameters Params;
        FRotator Rotation = FRotator::ZeroRotator;
        ABaseTurretPawn* SpawnedTurret = GetWorld()->SpawnActor<ABaseTurretPawn>(TurretClass, HitResult.Location, Rotation, Params);
        PlayerAIController->AddSteel(-10);
        SpawnedTurret->SetPlayer(PlayerAIController->GetPawn());
    }
}


bool AObservingPlayerController::LineTrace(FHitResult& HitResult)
{
    FVector WorldLocation, WorldDirection;
    DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

    FVector StartLocation = PlayerCameraManager->GetCameraLocation();
    FVector EndLocation = (StartLocation + (WorldDirection * LineTraceRange));    // TODO no magic numbers
    
    TArray<AActor*> ActorsToIgnore;
    if(TurretPlacement != nullptr)
        ActorsToIgnore.Add(TurretPlacement);

    return UKismetSystemLibrary::LineTraceSingle(this, StartLocation, EndLocation, UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel18),
        false, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true, FLinearColor::Yellow,
        FLinearColor::White, 5.0f);
}

void AObservingPlayerController::SetPlayerAIController(APlayerAIController* InController)
{
    PlayerAIController = InController;
}

void AObservingPlayerController::SetObservingPawn(AObservingPawn* InPawn)
{
    ObservingPawn = InPawn;
}
