// Troy Records Jr. 2020


#include "EndMenu.h"

#include "Capstone/GameInstances/MainGameInstance.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

bool UEndMenu::Initialize()
{
    if(!Super::Initialize()) return false;

    if(StartButton != nullptr)
        StartButton->OnClicked.AddDynamic(this, &UEndMenu::StartPressed);
    if(QuitButton != nullptr)
        QuitButton->OnClicked.AddDynamic(this, &UEndMenu::QuitPressed);

    UWorld* World = GetWorld();
    if(!ensure(World)) return false;

    APlayerController* PlayerController = World->GetFirstPlayerController();
    if(!ensure(PlayerController)) return false;

    PlayerController->bShowMouseCursor = true;

    if(EndMessage == nullptr) return false;
    UMainGameInstance* GameInstance = Cast<UMainGameInstance>(GetGameInstance());
    EndMessage->SetText(FText::FromString(GameInstance->GetTime()));

    return true;
}

void UEndMenu::StartPressed()
{
    GetWorld()->ServerTravel("/Game/Maps/DefaultMap");
}

void UEndMenu::QuitPressed()
{
    UWorld* World = GetWorld();
    if(!ensure(World)) return;

    APlayerController* PlayerController = World->GetFirstPlayerController();
    if(!ensure(PlayerController)) return;

    PlayerController->ConsoleCommand(TEXT("quit"));
}