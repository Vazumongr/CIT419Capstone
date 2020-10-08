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
    UE_LOG(LogTemp, Warning, TEXT("Resume"));
    this->RemoveFromViewport();
    this->bIsFocusable = false;
}

void UPauseMenu::QuitGame()
{
    UE_LOG(LogTemp, Warning, TEXT("Quit"));
    UWorld* World = GetWorld();
    if(!ensure(World)) return;

    APlayerController* PlayerController = World->GetFirstPlayerController();
    if(!ensure(PlayerController)) return;

    PlayerController->ConsoleCommand(TEXT("quit"));
}
