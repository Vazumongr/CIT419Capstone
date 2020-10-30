// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameOverDelegate);
UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSaveGameDelegate);

/**
 * 
 */
UCLASS()
class CAPSTONE_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()


public:
	void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

	void PlayerDied();

	FORCEINLINE class APlayerCharacter* GetPlayerCharacter() { return PlayerCharacter; }

	FGameOverDelegate GameOver;
	FSaveGameDelegate SaveGame;

	UFUNCTION()
    void LoadEndingScreen();


protected:

	virtual void BeginPlay() override;
	void LoadSave();
	void SpawnEnemy();
	
	UPROPERTY()
	TArray<class AEnemySpawnPoint*> EnemySpawnPoints;

	#pragma region [PlayerSetup]
	UPROPERTY(EditDefaultsOnly, Category = "Character Setup", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<APlayerCharacter> PlayerCharacterClass;
	UPROPERTY(EditDefaultsOnly, Category = "Character Setup", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AObservingPawn> ObservingPawnClass;
	UPROPERTY(EditDefaultsOnly, Category = "Character Setup", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AObservingPlayerController> ObservingPlayerControllerClass;
	UPROPERTY(EditDefaultsOnly, Category = "Character Setup", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class APlayerAIController> PlayerAIControllerClass;
	#pragma endregion
	
	UPROPERTY(EditDefaultsOnly, Category = "Character Setup", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ABaseTurretPawn> TurretClass;
	UPROPERTY(EditDefaultsOnly, Category = "Character Setup", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ABaseEnemyCharacter> EnemyClass;
	UPROPERTY(EditDefaultsOnly, Category = "Character Setup", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ABaseWeaponLootActor> WeaponDropClass;

	FTimerHandle TEnemySpawnHandle;
	float SpawnRateSeconds = 4.0f;
	float MinSpawnRate = .5f;

	UPROPERTY()
	APlayerCharacter* PlayerCharacter;
	UPROPERTY()
	AObservingPlayerController* ObservingPlayerController;
	
	
};
