// Troy Records Jr. 2020


#include "MySaveGame.h"

void UMySaveGame::PurgeArrays()
{
    UE_LOG(LogTemp, Warning, TEXT("Purging arrays..."));
    TurretSaveDatas.Empty();
    UE_LOG(LogTemp, Warning, TEXT("TurretSavesDatas: %d"), TurretSaveDatas.Num());
    EnemySaveDatas.Empty();
    UE_LOG(LogTemp, Warning, TEXT("EnemySaveDatas: %d"), EnemySaveDatas.Num());
    ResourceDropSaveDatas.Empty();
    UE_LOG(LogTemp, Warning, TEXT("ResourceDropSaveDatas: %d"), ResourceDropSaveDatas.Num());
    WeaponDropSaveDatas.Empty();
    UE_LOG(LogTemp, Warning, TEXT("WeaponDropSaveDatas: %d"), WeaponDropSaveDatas.Num());
}
