// Troy Records Jr. 2020


#include "MainMenu.h"

#include "Components/Button.h"
#include "Capstone/GameInstances/MainGameInstance.h"

bool UMainMenu::Initialize()
{
    if(!Super::Initialize()) return false;

    if(NewGameButton != nullptr)
        NewGameButton->OnClicked.AddDynamic(this, &UMainMenu::StartPressed);
    if(LoadSaveButton != nullptr)
        LoadSaveButton->OnClicked.AddDynamic(this, &UMainMenu::LoadPressed);
    if(QuitButton != nullptr)
        QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitPressed);

    UWorld* World = GetWorld();
    if(!ensure(World)) return false;

    APlayerController* PlayerController = World->GetFirstPlayerController();
    if(!ensure(PlayerController)) return false;

    PlayerController->bShowMouseCursor = true;
    

    return true;
}

void UMainMenu::StartPressed()
{
    GetWorld()->ServerTravel("/Game/Maps/DefaultMap");
}

void UMainMenu::LoadPressed()
{
    UMainGameInstance* GameInstance = Cast<UMainGameInstance>(GetGameInstance());
    GameInstance->bLoadSave = true;
    GetWorld()->ServerTravel("/Game/Maps/DefaultMap");
}

void UMainMenu::QuitPressed()
{
    UWorld* World = GetWorld();
    if(!ensure(World)) return;

    APlayerController* PlayerController = World->GetFirstPlayerController();
    if(!ensure(PlayerController)) return;

    PlayerController->ConsoleCommand(TEXT("quit"));
}
