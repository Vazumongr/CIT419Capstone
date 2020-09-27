// Troy Records Jr. 2020


#include "MainMenu.h"

#include "Components/Button.h"

bool UMainMenu::Initialize()
{
    if(!Super::Initialize()) return false;

    if(StartButton != nullptr)
        StartButton->OnClicked.AddDynamic(this, &UMainMenu::StartPressed);
    if(QuitButton != nullptr)
        QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitPressed);

    return true;
}

void UMainMenu::StartPressed()
{
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
