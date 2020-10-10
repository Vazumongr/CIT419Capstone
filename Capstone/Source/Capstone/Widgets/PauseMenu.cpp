// Troy Records Jr. 2020


#include "PauseMenu.h"

#include "Components/Button.h"

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
    UE_LOG(LogTemp, Warning, TEXT("Quit"));
    UWorld* World = GetWorld();
    if(!ensure(World)) return;

    World->ServerTravel("/Game/Maps/MainMenuMap");
}
