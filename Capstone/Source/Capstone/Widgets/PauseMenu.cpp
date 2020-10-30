// Troy Records Jr. 2020


#include "PauseMenu.h"

#include "Components/Button.h"
#include "Capstone/SaveGames/MySaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Capstone/GameModes/MainGameMode.h"

bool UPauseMenu::Initialize()
{
    if(!Super::Initialize()) return false;

    
    if(ResumeButton != nullptr)
        ResumeButton->OnClicked.AddDynamic(this, &UPauseMenu::ResumeGame);
    if(QuitButton != nullptr)
        QuitButton->OnClicked.AddDynamic(this, &UPauseMenu::QuitGame);

    return true;
}

void UPauseMenu::ResumeGame()
{
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if(!PlayerController) Initialize();
    PlayerController->SetPause(false);
    TearDown();
}

void UPauseMenu::QuitGame()
{
    TearDown();
    // TODO THIS WILL BE HANDLED ELSEWHERE
    UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("MySlot"), 0));
	
    if(SaveGameInstance != nullptr)
    {
        SaveGameInstance->PurgeArrays();
    }
    UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("MySlot"), 0);
    
    AMainGameMode* GameMode = GetWorld()->GetAuthGameMode<AMainGameMode>();
    if(GameMode != nullptr)
    {
        GameMode->SaveGame.Broadcast();
    }
    // TODO Purge the previous array
    UE_LOG(LogTemp, Warning, TEXT("Saving..."));
    UE_LOG(LogTemp, Warning, TEXT("Quit"));
    UWorld* World = GetWorld();
    if(!ensure(World)) return;

    World->ServerTravel("/Game/Maps/MainMenuMap");
}
