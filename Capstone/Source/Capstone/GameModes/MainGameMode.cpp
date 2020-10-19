// Troy Records Jr. 2020


#include "MainGameMode.h"

#include "Capstone/Actors/BaseResourceDropActor.h"
#include "Capstone/Characters/PlayerCharacter.h"
#include "Capstone/Characters/BaseEnemyCharacter.h"
#include "Capstone/Controllers/PlayerAIController.h"
#include "Capstone/Controllers/ObservingPlayerController.h"
#include "Capstone/GameInstances/MainGameInstance.h"
#include "Capstone/Pawns/ObservingPawn.h"
#include "Capstone/Pawns/BaseTurretPawn.h"
#include "Capstone/SaveGames/MySaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

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

    UMainGameInstance* GameInstance = Cast<UMainGameInstance>(GetGameInstance());
    if(GameInstance->bLoadSave) LoadSave();
    
}

void AMainGameMode::PlayerDied()
{
    //GameOver.Broadcast();
    for(AController* Controller : TActorRange<AController>(GetWorld()))
    {
        Controller->GameHasEnded(Controller->GetPawn(), false);
    }
    FTimerHandle RestartTimer;
    GetWorldTimerManager().SetTimer(RestartTimer, this, &AMainGameMode::LoadEndingScreen, 5.f);
}

void AMainGameMode::LoadEndingScreen()
{
    GetWorld()->ServerTravel("/Game/Maps/EndScreenMap");
}

void AMainGameMode::LoadSave()
{
    // Loading stuff from the save
    UE_LOG(LogTemp, Warning, TEXT("I am loading a save! (not really)"));
    UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("MySlot"), 0));
      
    if(SaveGameInstance == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Debug: It's the savegameinstance"));
        return;
    }
    
#pragma region [LoadingPlayerData]
    FPlayerSaveData MyData = SaveGameInstance->PlayerSaveData;
    PlayerCharacter->LoadGame(MyData);
#pragma endregion
    
#pragma region [LoadingTurrets]
    ensure(TurretClass);

    TArray<FTurretSaveData> Turrets = SaveGameInstance->TurretSaveDatas;
    UE_LOG(LogTemp, Warning, TEXT("TurretSaveData.Num : %d"), Turrets.Num());
    for(FTurretSaveData TurretData : Turrets)
    {
        UE_LOG(LogTemp, Warning, TEXT("I should be creating a turret..."));
        ABaseTurretPawn* SpawnedTurret = GetWorld()->SpawnActor<ABaseTurretPawn>(TurretClass, TurretData.TurretTransform);
        SpawnedTurret->LoadGame(TurretData);
    }
#pragma endregion

#pragma region [LoadingEnemies]
    ensure(EnemyClass);

    TArray<FEnemySaveData> Enemies = SaveGameInstance->EnemySaveDatas;
    UE_LOG(LogTemp, Warning, TEXT("EnemySaveDatas.Num : %d"), Enemies.Num());
    for(FEnemySaveData EnemyData : Enemies)
    {
        UE_LOG(LogTemp, Warning, TEXT("I should be creating a turret..."));
        ABaseEnemyCharacter* SpawnedEnemy = GetWorld()->SpawnActor<ABaseEnemyCharacter>(EnemyClass, EnemyData.EnemyTransform);
        SpawnedEnemy->LoadGame(EnemyData);
    }
#pragma endregion

#pragma region [LoadingResourceDrops]
    ensure(EnemyClass);

    TArray<FResourceDropSaveData> ResourceDrops = SaveGameInstance->ResourceDropSaveDatas;
    UE_LOG(LogTemp, Warning, TEXT("ResourceDropSaveDatas.Num : %d"), ResourceDrops.Num());
    for(FResourceDropSaveData ResourceDropData : ResourceDrops)
    {
        UE_LOG(LogTemp, Warning, TEXT("I should be creating a turret..."));
        TSubclassOf<ABaseResourceDropActor> ResourceClass = ResourceDropData.ResourceClass;
        ABaseResourceDropActor* SpawnedResource = GetWorld()->SpawnActor<ABaseResourceDropActor>(ResourceClass, ResourceDropData.ResourceDropTransform);
        SpawnedResource->LoadGame(ResourceDropData);
    }
#pragma endregion
}
