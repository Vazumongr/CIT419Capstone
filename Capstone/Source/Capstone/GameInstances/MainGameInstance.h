// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
    void StartGame();
    void QuitGame();
    void SetTime(FString& TimeSeconds);
    FString& GetTime();

    UFUNCTION(BlueprintCallable)
    void LogTime();

    bool bLoadSave;

private:
    FString TimeSeconds;
};
