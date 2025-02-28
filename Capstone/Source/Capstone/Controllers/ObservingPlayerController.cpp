// Troy Records Jr. 2020


#include "ObservingPlayerController.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Capstone/Actors/TurretPlacementHighlightActor.h"
#include "Capstone/Controllers/PlayerAIController.h"
#include "Capstone/Gamemodes/MainGameMode.h"
#include "Capstone/Pawns/BaseTurretPawn.h"
#include "Capstone/Pawns/ObservingPawn.h"
#include "Capstone/SaveGames/MySaveGame.h"
#include "Capstone/Widgets/InventoryWidget.h"
#include "Capstone/Widgets/PlayerHUD.h"
#include "Capstone/Widgets/PauseMenu.h"

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
    HUDWidget->LoadGame(LoadedTime);
}

void AObservingPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    // Action Bindings
    InputComponent->BindAction("MoveCommand", IE_Pressed, this, &AObservingPlayerController::MoveCommand);
    InputComponent->BindAction("ToggleCameraLock", IE_Pressed, this, &AObservingPlayerController::ToggleCameraLock);
    InputComponent->BindAction("PrintInventory", IE_Pressed, this, &AObservingPlayerController::OpenInventory);
    InputComponent->BindAction("PauseGame", IE_Pressed, this, &AObservingPlayerController::PauseGame);
    InputComponent->BindAction("PlaceTurret", IE_Pressed, this, &AObservingPlayerController::PrepareTurret);
    InputComponent->BindAction("SaveGame", IE_Pressed, this, &AObservingPlayerController::SaveGame);
    // Axis Bindings
    InputComponent->BindAxis("CameraZoom", this, &AObservingPlayerController::CameraZoom);
}

void AObservingPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);
    if(HUDWidget != nullptr)
        HUDWidget->EndGame();
    //Destroy();
}

void AObservingPlayerController::EquipWeapon(FWeaponStats InStats)
{
    ensure(PlayerAIController);
    PlayerAIController->SwitchWeapon(InStats);
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

void AObservingPlayerController::OpenInventory()
{
    ensure(InventoryClass);    // We assigned it
    if(InventoryWidget == nullptr)    // InventoryWidget doesnt exist yet...
    {
        
        InventoryWidget = Cast<UInventoryWidget>(CreateWidget(this, InventoryClass));    // Create it
        
        if(InventoryWidget != nullptr)    // Makes sure it was created
        {
            InventoryWidget->AddToViewport();    // Add it to our viewport
            InventoryWidget->SetInventory(PlayerAIController->GetInventoryAsArray());    // Set the inventory display
            
            FInputModeGameAndUI InputModeData;    // Set UI only so we can access it easily
            InputModeData.SetWidgetToFocus(InventoryWidget->TakeWidget());
            SetInputMode(InputModeData);
        }
            
    }
    else    // Widget already exists...
    {
        if(InventoryWidget->GetVisibility() == ESlateVisibility::Collapsed)    // If the widget isn't visible...
        {
            InventoryWidget->SetVisibility(ESlateVisibility::Visible);    // Make it visible...
            InventoryWidget->SetInventory(PlayerAIController->GetInventoryAsArray());    // Set its contents
            
            FInputModeGameAndUI InputModeData;
            InputModeData.SetWidgetToFocus(InventoryWidget->TakeWidget());    // Focus the widget
            SetInputMode(InputModeData);
        }
        else    // Else it is visible
        {
            InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);    // Collapse it
            
            FInputModeGameOnly InputModeData;
            InputModeData.SetConsumeCaptureMouseDown(false);
            SetInputMode(InputModeData);
        }
            
    }
}

void AObservingPlayerController::PauseGame()
{
    if(PauseMenu == nullptr)
    {
        PauseMenu = CreateWidget<UPauseMenu>(this, PauseMenuClass);
        UE_LOG(LogTemp, Warning, TEXT("Creating pause menu"));
    }
    
    if(PauseMenu != nullptr)
    {
        PauseMenu->Setup();
        SetPause(true);
        UE_LOG(LogTemp, Warning, TEXT("Pausing"));
    }
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

void AObservingPlayerController::SaveGame()
{
    UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("MySlot"), 0));
	
    if(SaveGameInstance != nullptr)
    {
        SaveGameInstance->PurgeArrays();
    }
    UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("MySlot"), 0);
    
    AMainGameMode* GameMode = GetWorld()->GetAuthGameMode<AMainGameMode>();
    if(GameMode != nullptr)
    {
        GameMode->SaveGame.Broadcast();
    }
    // TODO Purge the previous array
    UE_LOG(LogTemp, Warning, TEXT("Saving..."));
}

void AObservingPlayerController::LoadGame(float InTime)
{
    LoadedTime = InTime;
}

bool AObservingPlayerController::LineTrace(FHitResult& HitResult)
{
    FVector WorldLocation, WorldDirection;
    DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

    FVector StartLocation = PlayerCameraManager->GetCameraLocation();
    FVector EndLocation = (StartLocation + (WorldDirection * LineTraceRange));
    
    TArray<AActor*> ActorsToIgnore;
    if(TurretPlacement != nullptr)
        ActorsToIgnore.Add(TurretPlacement);

    return UKismetSystemLibrary::LineTraceSingle(this, StartLocation, EndLocation, UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel18),
        false, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true, FLinearColor::White,
        FLinearColor::Yellow, 2.0f);
}

void AObservingPlayerController::SetPlayerAIController(APlayerAIController* InController)
{
    PlayerAIController = InController;
}

void AObservingPlayerController::SetObservingPawn(AObservingPawn* InPawn)
{
    ObservingPawn = InPawn;
}
