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
    void SwitchWeapon();
    UFUNCTION()
    void PrepareTurret();
    UFUNCTION()
    void PlaceTurret();

    // FUNCTIONS
    bool LineTrace(FHitResult& HitResult);

    // VARIABLES
    class ATurretPlacementHighlightActor* TurretPlacement = nullptr;

    float LineTraceRange = 50000.0f;

public:
    void SetPlayerAIController(class APlayerAIController* InController);
    void SetObservingPawn(class AObservingPawn* InPawn);
    FORCEINLINE APlayerAIController* GetPlayerAIController() const { return PlayerAIController; }
    FORCEINLINE AObservingPawn* GetObservingPawn() const { return ObservingPawn; }

private:
    APlayerAIController* PlayerAIController = nullptr;
    AObservingPawn* ObservingPawn = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Interface", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<class UInventoryWidget> InventoryClass;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Interface", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<class UPlayerHUD> HUDClass;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Structures", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<class ABaseTurretPawn> TurretClass;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Structures", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<class ATurretPlacementHighlightActor> TurretPlacementClass;

    UPlayerHUD* HUDWidget = nullptr;
    UInventoryWidget* InventoryWidget = nullptr;
    
};
