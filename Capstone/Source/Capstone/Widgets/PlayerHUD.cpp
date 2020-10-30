// Troy Records Jr. 2020


#include "PlayerHUD.h"

#include "Capstone/GameStates/MainGameState.h"
#include "Capstone/GameInstances/MainGameInstance.h"
#include "Capstone/GameModes/MainGameMode.h"
#include "Capstone/SaveGames/MySaveGame.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

bool UPlayerHUD::Initialize()
{
    if(!Super::Initialize()) return false;
    
    GameState = Cast<AMainGameState>(GetWorld()->GetGameState());
    if(GameState == nullptr) return false;
    AMainGameMode* GameMode = GetWorld()->GetAuthGameMode<AMainGameMode>();
    if(GameMode != nullptr)
    {
        GameMode->SaveGame.AddUniqueDynamic(this, &UPlayerHUD::SaveGame);
    }
    return true;
}

void UPlayerHUD::SetOwningActor(AActor* NewOwner)
{
    OwningActor = NewOwner;
}

void UPlayerHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    if(GameState == nullptr) return;
    const float FTime = InitialTime + GameState->GetServerWorldTimeSeconds();

    const int32 Seconds = FMath::FloorToInt(FMath::Fmod(FTime, 60));

    
    
    const int32 Minutes = FMath::FloorToInt(FTime / 60);
    
    Time = FString::Printf(TEXT("%i:%02d"), Minutes, Seconds);
    
    TimerText->SetText(FText::FromString(Time));
    
    
}

void UPlayerHUD::EndGame()
{
    UMainGameInstance* GameInstance = Cast<UMainGameInstance>(GetGameInstance());
    if(GameInstance != nullptr)
        GameInstance->SetTime(Time);
}

void UPlayerHUD::SaveGame()
{
    UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("MySlot"), 0));
	
    if(SaveGameInstance == nullptr) 
    {
        // If there wasn't a save loaded, create one
        SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
    }
	
    SaveGameInstance->SavedGameTime = InitialTime + GameState->GetServerWorldTimeSeconds();

    // Save the savegameinstance
    UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("MySlot"), 0);
}

void UPlayerHUD::LoadGame(float InTime)
{
    InitialTime = InTime;
}
