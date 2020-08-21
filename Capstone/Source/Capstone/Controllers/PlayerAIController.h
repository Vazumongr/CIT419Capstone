// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PlayerAIController.generated.h"


UENUM()
enum class FMoveCommandTypes : uint8
{
	None,
	MoveToLocation,
	MoveToInteractable,
	MoveToEnemy
};

/**
 * 
 */
UCLASS()
class CAPSTONE_API APlayerAIController : public AAIController
{
	GENERATED_BODY()

public:
	/** Passed as a value because we don't want the reference to change while processing */
	void ProcessHitResult(FHitResult HitResult);

	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

private:
	void InteractWithItem(FHitResult HitResult, class IInteractableItemInterface* ItemInterface);

	FMoveCommandTypes CurrentCommand;
	IInteractableItemInterface* TargetedItem = nullptr;

public:
	void SetPlayerController( APlayerController* InController);
	void SetPlayerCharacter(class APlayerCharacter* InCharacter);

	FORCEINLINE class AObservingPlayerController* GetPlayerController() const { return PlayerController; }
	FORCEINLINE APlayerCharacter* GetPlayerCharacter() const { return PlayerCharacter; }

private:
	AObservingPlayerController* PlayerController = nullptr;
	APlayerCharacter* PlayerCharacter = nullptr;
};
