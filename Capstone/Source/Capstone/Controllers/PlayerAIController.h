// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PlayerAIController.generated.h"


struct FWeaponStats;

UENUM()
enum class FMoveCommandTypes : uint8
{
	None,
	MoveToLocation,
	MoveToInteractable,
	MoveToAttack,
	MoveToWeapon
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

	void SwitchWeapon(FWeaponStats InStats);
	
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

	void PrintInventory();
	FString GetInventoryAsText();
	TArray<FWeaponStats> GetInventoryAsArray();

private:
	void InteractWithItem(FHitResult HitResult, class IInteractableItemInterface* ItemInterface);
	void DealDamageToEnemy(class ABaseEnemyCharacter* EnemyCharacter);
	void EquipWeapon(class ABaseWeaponLootActor* WeaponActor);

	FMoveCommandTypes CurrentCommand;
	IInteractableItemInterface* TargetedItem = nullptr;
	ABaseEnemyCharacter* TargetedEnemy = nullptr;
	ABaseWeaponLootActor* TargetedWeapon = nullptr;

public:
	void SetPlayerController( APlayerController* InController);
	void SetPlayerCharacter(class APlayerCharacter* InCharacter);
	void AddSteel(float InSteel);

	FORCEINLINE class AObservingPlayerController* GetPlayerController() const { return PlayerController; }
	FORCEINLINE APlayerCharacter* GetPlayerCharacter() const { return PlayerCharacter; }
	float GetSteel() const;

private:
	AObservingPlayerController* PlayerController = nullptr;	// TODO I don't think I should be having a ptr to that.
	APlayerCharacter* PlayerCharacter = nullptr;
};
