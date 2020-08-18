// Troy Records Jr. 2020


#include "MainGameMode.h"

void AMainGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{

    FActorSpawnParameters SpawnParameters;
    SpawnParameters.Owner = NewPlayer;

    APlayerCharacter* PlayerCharacter = GetWorld()->SpawnActor<APlayerCharacter>(PlayerCharacterClass, SpawnParameters);
    
    APlayerAIController* PlayerAIController = GetWorld()->SpawnActor<APlayerAIController>(PlayerAIControllerClass, SpawnParameters);
    PlayerAIController->Possess(PlayerCharacter);

    AObservingPawn* ObservingPawn = GetWorld()->SpawnActor<AObservingPawn>(ObservingPawnClass, SpawnParameters);
    NewPlayer->Possess(ObservingPawn);
    
}
