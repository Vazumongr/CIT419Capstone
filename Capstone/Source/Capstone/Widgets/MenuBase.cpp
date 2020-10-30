// Troy Records Jr. 2020


#include "MenuBase.h"

void UMenuBase::Setup()
{
    ensure(this);
    this->AddToViewport();
    this->bIsFocusable = true;

    FInputModeUIOnly InputModeData;
    InputModeData.SetWidgetToFocus(this->TakeWidget());
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

    UWorld* World = GetWorld();
    if(!World) return;

    APlayerController* PlayerController = World->GetFirstPlayerController();
    if(!PlayerController) return;
    
    PlayerController->SetInputMode(InputModeData);
    PlayerController->bShowMouseCursor = true;
}

void UMenuBase::TearDown()
{
    this->RemoveFromViewport();
    this->bIsFocusable = false;

    FInputModeGameOnly InputModeData;
    InputModeData.SetConsumeCaptureMouseDown(false);

    UWorld* World = GetWorld();
    if(!World) return;

    APlayerController* PlayerController = World->GetFirstPlayerController();
    if(!PlayerController) return;
    
    PlayerController->SetInputMode(InputModeData);
    PlayerController->bShowMouseCursor = true;
}
