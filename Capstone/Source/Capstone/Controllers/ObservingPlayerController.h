// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ObservingPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_API AObservingPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
    AObservingPlayerController();
    
    virtual void BeginPlay() override;

protected:
    virtual void SetupInputComponent() override;

private:
    UFUNCTION()
    void MoveCommand();
    UFUNCTION()
    void ToggleCameraLock();
    UFUNCTION()
    void CameraZoom(float AxisValue);
    UFUNCTION()
    void PrintInventory();

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

    class UInventoryWidget* InventoryWidget = nullptr;
    
};
