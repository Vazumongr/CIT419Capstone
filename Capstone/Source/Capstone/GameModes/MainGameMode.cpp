// Troy Records Jr. 2020


#include "MainGameMode.h"

#include "Capstone/Pawns/ObservingPawn.h"
#include "Capstone/Characters/PlayerCharacter.h"
#include "Capstone/Controllers/PlayerAIController.h"
#include "Capstone/Controllers/ObservingPlayerController.h"

void AMainGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
    AActor* SpawnPoint = ChoosePlayerStart(NewPlayer);
    FVector SpawnLocation = SpawnPoint->GetActorLocation();
    FRotator SpawnRotation = SpawnPoint->GetActorRotation();
    
    FActorSpawnParameters SpawnParameters;    // TODO Set spawn parameters to spawn correctly i.e. rotation
    SpawnParameters.Owner = NewPlayer;

    PlayerCharacter = GetWorld()->SpawnActor<APlayerCharacter>(PlayerCharacterClass, SpawnLocation, SpawnRotation, SpawnParameters);
    
    APlayerAIController* PlayerAIController = GetWorld()->SpawnActor<APlayerAIController>(PlayerAIControllerClass, SpawnParameters);
    PlayerAIController->Possess(PlayerCharacter);
    PlayerAIController->SetPlayerController(NewPlayer);    // TODO this most likely isn't needed. Bad design to have a 2 way street.
    PlayerAIController->SetPlayerCharacter(PlayerCharacter);

    AObservingPawn* ObservingPawn = GetWorld()->SpawnActor<AObservingPawn>(ObservingPawnClass, SpawnParameters);
    NewPlayer->Possess(ObservingPawn);
    ObservingPawn->SetPlayerController(NewPlayer);    // TODO this most likely isn't needed. Bad design to have a 2 way street.
    ObservingPawn->SetPlayerCharacter(PlayerCharacter);

    if(AObservingPlayerController* ObservingPlayerController = Cast<AObservingPlayerController>(NewPlayer))
    {
        ObservingPlayerController->SetObservingPawn(ObservingPawn);
        ObservingPlayerController->SetPlayerAIController(PlayerAIController);
    }
    
}
