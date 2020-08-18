// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PlayerAIController.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_API APlayerAIController : public AAIController
{
	GENERATED_BODY()

public:
	void SetPlayerController( APlayerController* InController);
	void SetPlayerCharacter(class APlayerCharacter* InCharacter);

	FORCEINLINE class AObservingPlayerController* GetPlayerController() const { return PlayerController; }
	FORCEINLINE APlayerCharacter* GetPlayerCharacter() const { return PlayerCharacter; }

private:
	AObservingPlayerController* PlayerController = nullptr;
	APlayerCharacter* PlayerCharacter = nullptr;
};
