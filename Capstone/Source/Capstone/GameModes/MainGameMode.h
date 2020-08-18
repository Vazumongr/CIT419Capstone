// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "Capstone/Characters/PlayerCharacter.h"
#include "Capstone/Controllers/ObservingPlayerController.h"
#include "Capstone/Controllers/PlayerAIController.h"
#include "Capstone/Pawns/ObservingPawn.h"
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
	TSubclassOf<APlayerCharacter> PlayerCharacterClass;
	UPROPERTY(EditDefaultsOnly, Category = "Character Setup", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AObservingPawn> ObservingPawnClass;
	UPROPERTY(EditDefaultsOnly, Category = "Character Setup", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AObservingPlayerController> ObservingPlayerControllerClass;
	UPROPERTY(EditDefaultsOnly, Category = "Character Setup", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<APlayerAIController> PlayerAIControllerClass;
	
	
};
