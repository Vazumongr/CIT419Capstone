// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ObservingPlayerController.generated.h"

struct FWeaponStats;

/**
 * 
 */
UCLASS()
class CAPSTONE_API AObservingPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
    AObservingPlayerController();
    
    virtual void TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;
    
    virtual void BeginPlay() override;
    
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

    void EquipWeapon(FWeaponStats InStats);
    
    void LoadGame(float InTime);

protected:
    virtual void SetupInputComponent() override;

private:

    // UFUNCTIONS
    UFUNCTION()
    void MoveCommand();
    UFUNCTION()
    void ToggleCameraLock();
    UFUNCTION()
    void CameraZoom(float AxisValue);
    UFUNCTION()
    void OpenInventory();
    UFUNCTION()
    void PauseGame();
    UFUNCTION()
    void PrepareTurret();
    UFUNCTION()
    void PlaceTurret();
    UFUNCTION()
    void SaveGame();

    // FUNCTIONS
    bool LineTrace(FHitResult& HitResult);

    float LoadedTime = 0.f;

    // VARIABLES
    class ATurretPlacementHighlightActor* TurretPlacement = nullptr;

    float LineTraceRange = 50000.0f;

public:
    void SetPlayerAIController(class APlayerAIController* InController);
    void SetObservingPawn(class AObservingPawn* InPawn);
    FORCEINLINE APlayerAIController* GetPlayerAIController() const { return PlayerAIController; }
    FORCEINLINE AObservingPawn* GetObservingPawn() const { return ObservingPawn; }

private:
    UPROPERTY()
    APlayerAIController* PlayerAIController = nullptr;
    UPROPERTY()
    AObservingPawn* ObservingPawn = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Interface", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<class UInventoryWidget> InventoryClass;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Interface", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<class UPauseMenu> PauseMenuClass;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Interface", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<class UPlayerHUD> HUDClass;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Structures", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<class ABaseTurretPawn> TurretClass;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Structures", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<class ATurretPlacementHighlightActor> TurretPlacementClass;

    
    UPROPERTY()
    UPlayerHUD* HUDWidget = nullptr;
    UPROPERTY()
    UInventoryWidget* InventoryWidget = nullptr;
    UPROPERTY()
    UPauseMenu* PauseMenu;
    
};
