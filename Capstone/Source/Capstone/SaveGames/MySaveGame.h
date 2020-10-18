// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"

#include "Capstone/DataStructures/GameStructs.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()

	UMySaveGame();
	
public:
	UPROPERTY()
	FVector PlayerLocation;
	UPROPERTY()
	FPlayerSaveData PlayerSaveData;

	TArray<FTurretSaveData> TurretSaveDatas;
	TArray<FEnemySaveData> EnemySaveDatas;
	TArray<FResourceDropSaveData> ResourceDropSaveDatas;
	TArray<FWeaponDropSaveData> WeaponDropSaveDatas;
	
	
};
