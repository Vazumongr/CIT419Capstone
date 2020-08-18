// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

private:
	
	UPROPERTY(EditDefaultsOnly, Category = "Character Setup", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class APlayerCharacter> PlayerCharacterClass;
	UPROPERTY(EditDefaultsOnly, Category = "Character Setup", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AObservingPawn> ObservingPawnClass;
	UPROPERTY(EditDefaultsOnly, Category = "Character Setup", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AObservingPlayerController> ObservingPlayerControllerClass;
	UPROPERTY(EditDefaultsOnly, Category = "Character Setup", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class APlayerAIController> PlayerAIControllerClass;
	
	
};
