// Troy Records Jr. 2020


#include "PlayerHUD.h"

#include "Capstone/GameStates/MainGameState.h"
#include "Capstone/GameInstances/MainGameInstance.h"
#include "Components/TextBlock.h"

bool UPlayerHUD::Initialize()
{
    if(!Super::Initialize()) return false;
    
    GameState = Cast<AMainGameState>(GetWorld()->GetGameState());
    if(GameState == nullptr) return false;
    return true;
}

void UPlayerHUD::SetOwningActor(AActor* NewOwner)
{
    OwningActor = NewOwner;
}

void UPlayerHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    if(GameState == nullptr) return;
    const float FTime = GameState->GetServerWorldTimeSeconds();

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
