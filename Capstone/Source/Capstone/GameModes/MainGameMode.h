// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameOverDelegate);

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

	UFUNCTION()
    void LoadEndingScreen();

private:
	
	UPROPERTY(EditDefaultsOnly, Category = "Character Setup", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<APlayerCharacter> PlayerCharacterClass;
	UPROPERTY(EditDefaultsOnly, Category = "Character Setup", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AObservingPawn> ObservingPawnClass;
	UPROPERTY(EditDefaultsOnly, Category = "Character Setup", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AObservingPlayerController> ObservingPlayerControllerClass;
	UPROPERTY(EditDefaultsOnly, Category = "Character Setup", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class APlayerAIController> PlayerAIControllerClass;

	APlayerCharacter* PlayerCharacter = nullptr;
	
	
};
