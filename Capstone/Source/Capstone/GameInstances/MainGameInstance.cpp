// Troy Records Jr. 2020


#include "MainGameInstance.h"

void UMainGameInstance::StartGame()
{
    UE_LOG(LogTemp, Warning, TEXT("StartGame called"));
}

void UMainGameInstance::QuitGame()
{
    UE_LOG(LogTemp, Warning, TEXT("QuitGame called"));
}

void UMainGameInstance::SetTime(FString& InTimeSeconds)
{
    TimeSeconds = InTimeSeconds;
}

FString& UMainGameInstance::GetTime()
{
    return TimeSeconds;
}

void UMainGameInstance::LogTime()
{
    UE_LOG(LogTemp, Warning, TEXT("%s"), *TimeSeconds);
}
