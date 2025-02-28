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
	
public:

	void PurgeArrays();
	
	UPROPERTY()
	float SavedGameTime;
	
	UPROPERTY()
	FPlayerSaveData PlayerSaveData;
	// TODO ALL THESE NEED PURGED WHEN SAVING
	UPROPERTY()
	TArray<FTurretSaveData> TurretSaveDatas;
	UPROPERTY()
	TArray<FEnemySaveData> EnemySaveDatas;
	UPROPERTY()
	TArray<FResourceDropSaveData> ResourceDropSaveDatas;
	UPROPERTY()
	TArray<FWeaponDropSaveData> WeaponDropSaveDatas;
	
	
};
