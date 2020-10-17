// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"

#include "Capstone/DataStructures/GameStructs.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

enum GameStructs;

/**
 * 
 */
UCLASS()
class CAPSTONE_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()

	UMySaveGame();
	
public:
	UPROPERTY(EditAnywhere)
	FVector PlayerLocation;

	UPROPERTY(EditAnywhere)
	TArray<FWeaponStats> Inventory;
	
};
