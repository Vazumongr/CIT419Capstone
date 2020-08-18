// Troy Records Jr. 2020


#include "PlayerAIController.h"

#include "Capstone/Controllers/ObservingPlayerController.h"

void APlayerAIController::SetPlayerController(APlayerController* InController)
{
    PlayerController = Cast<AObservingPlayerController>(InController);
}

void APlayerAIController::SetPlayerCharacter(APlayerCharacter* InCharacter)
{
    PlayerCharacter = InCharacter;
}
