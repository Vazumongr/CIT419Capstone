// Troy Records Jr. 2020


#include "MainGameMode.h"

#include "Capstone/Actors/BaseResourceDropActor.h"
#include "Capstone/Actors/EnemySpawnPoint.h"
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
#include "TimerManager.h"

AMainGameMode::AMainGameMode()
{
    PrimaryActorTick.bCanEverTick = true;
}

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

    if(AObservingPlayerController* PlayerController = Cast<AObservingPlayerController>(NewPlayer))
    {
        ObservingPlayerController = PlayerController;
        ObservingPlayerController->SetObservingPawn(ObservingPawn);
        ObservingPlayerController->SetPlayerAIController(PlayerAIController);
    }

    UMainGameInstance* GameInstance = Cast<UMainGameInstance>(GetGameInstance());
    if(GameInstance->bLoadSave) LoadSave();
    
}

void AMainGameMode::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    if(GEngine!=nullptr)
    {
        FString DebugMsg = FString::Printf(TEXT("Enemy spawn timer: %f"), SpawnRateSeconds);
        GEngine->AddOnScreenDebugMessage(-1,0,FColor::Cyan,DebugMsg);
        UE_LOG(LogTemp, Warning, TEXT("%s"), *DebugMsg);
    }
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

void AMainGameMode::BeginPlay()
{
    Super::BeginPlay();
    TArray<AActor*> TempActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawnPoint::StaticClass(), TempActors);
    for (AActor* Actor : TempActors)
    {
        if(AEnemySpawnPoint* SpawnPoint = Cast<AEnemySpawnPoint>(Actor))
        {
            EnemySpawnPoints.Add(SpawnPoint);
            UE_LOG(LogTemp, Warning, TEXT("I have found %d spawn points"), EnemySpawnPoints.Num());
        }
    }

    GetWorld()->GetTimerManager().SetTimer(TEnemySpawnHandle, this, &AMainGameMode::SpawnEnemy, SpawnRateSeconds, true);
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

    ObservingPlayerController->LoadGame(SaveGameInstance->SavedGameTime);
    
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
        ABaseEnemyCharacter* SpawnedEnemy = GetWorld()->SpawnActor<ABaseEnemyCharacter>(EnemyClass, EnemyData.EnemyTransform);
        SpawnedEnemy->LoadGame(EnemyData);
    }
#pragma endregion

    #pragma region [LoadingResourceDrops]

    TArray<FResourceDropSaveData> ResourceDrops = SaveGameInstance->ResourceDropSaveDatas;
    UE_LOG(LogTemp, Warning, TEXT("ResourceDropSaveDatas.Num : %d"), ResourceDrops.Num());
    for(FResourceDropSaveData ResourceDropData : ResourceDrops)
    {
        TSubclassOf<ABaseResourceDropActor> ResourceClass = ResourceDropData.ResourceClass;
        ensure(ResourceClass);
        ABaseResourceDropActor* SpawnedResource = GetWorld()->SpawnActor<ABaseResourceDropActor>(ResourceClass, ResourceDropData.ResourceDropTransform);
        SpawnedResource->LoadGame(ResourceDropData);
    }
#pragma endregion
    
    #pragma region [LoadingWeaponDrops]
    ensure(WeaponDropClass);

    TArray<FWeaponDropSaveData> WeaponDrops = SaveGameInstance->WeaponDropSaveDatas;
    UE_LOG(LogTemp, Warning, TEXT("WeaponDropSaveDatas.Num : %d"), WeaponDrops.Num());
    for(FWeaponDropSaveData WeaponDropData : WeaponDrops)
    {
        ABaseWeaponLootActor* SpawnedWeapon = GetWorld()->SpawnActor<ABaseWeaponLootActor>(WeaponDropClass, WeaponDropData.WeaponDropTransform);
        SpawnedWeapon->SetWeaponStats(WeaponDropData.WeaponStats);
    }
#pragma endregion

}

void AMainGameMode::SpawnEnemy()
{
    const int RandomIndex = FMath::RandRange(0,EnemySpawnPoints.Num()-1);
    if(AEnemySpawnPoint* SpawnPoint = EnemySpawnPoints[RandomIndex])
    {
        FActorSpawnParameters SpawnParameters;
        SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

        const FVector SpawnLocationBuffer = FVector((FMath::RandRange(0.f, 80.f), FMath::RandRange(0.f, 80.f), FMath::RandRange(0.f, 80.f)));
        const FVector SpawnLocation = SpawnPoint->GetActorLocation() + SpawnLocationBuffer;
        const FRotator SpawnRotation = SpawnPoint->GetActorRotation();
        
        if(ABaseEnemyCharacter* Enemy = GetWorld()->SpawnActor<ABaseEnemyCharacter>(EnemyClass, SpawnLocation, SpawnRotation, SpawnParameters))
        {
            UE_LOG(LogTemp, Warning, TEXT("SPAWNING ENEMY"));
            if(!(SpawnRateSeconds <= MinSpawnRate))
                SpawnRateSeconds -= .1f;
        }
    }
}
