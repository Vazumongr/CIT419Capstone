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
    virtual void BeginPlay() override;

protected:
    virtual void SetupInputComponent() override;

private:
    UFUNCTION()
    void MoveCommand();
    UFUNCTION()
    void ToggleCameraLock();
    
};
