// Troy Records Jr. 2020


#include "BaseWeaponLootActor.h"

#include "Capstone/SaveGames/MySaveGame.h"
#include "Capstone/GameModes/MainGameMode.h"
#include "Kismet/GameplayStatics.h"

ABaseWeaponLootActor::ABaseWeaponLootActor()
{
    
}

void ABaseWeaponLootActor::BeginPlay()
{
    Super::BeginPlay();
    WeaponStats.StaticMesh = StaticMeshComponent->GetStaticMesh();
    WeaponStats.DamageType = DamageType;
    TArray<UMaterialInterface*> Materials;
    StaticMeshComponent->GetUsedMaterials(Materials);
    UMaterialInterface* NewMat = nullptr;
    for(UMaterialInterface* Material : Materials)
    {
        //UE_LOG(LogTemp, Warning, TEXT("%s"), *Material->GetName());
    }
    AMainGameMode* GameMode = GetWorld()->GetAuthGameMode<AMainGameMode>();
    if(GameMode != nullptr)
    {
        GameMode->SaveGame.AddUniqueDynamic(this, &ABaseWeaponLootActor::SaveGame);
    }
}

void ABaseWeaponLootActor::SetWeaponStats(FWeaponStats InStats)
{
    WeaponStats = InStats;
    ensure(StaticMeshComponent);
    StaticMeshComponent->SetStaticMesh(WeaponStats.StaticMesh);
}

void ABaseWeaponLootActor::Interact(APlayerCharacter* PlayerCharacter)
{
    Destroy();
}

void ABaseWeaponLootActor::SaveGame()
{
    // Load the save if it's there
    UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("MySlot"), 0));
	
    if(SaveGameInstance == nullptr) 
    {
        // If there wasn't a save loaded, create one
        SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
    }

    FWeaponDropSaveData MyData;
    MyData.WeaponStats = WeaponStats;
    MyData.WeaponDropTransform = GetActorTransform();
	
    SaveGameInstance->WeaponDropSaveDatas.Add(MyData);
	
	
    // Save the savegameinstance
    UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("MySlot"), 0);
    
    UE_LOG(LogTemp, Warning, TEXT("WeaponDropSaveDatas.Num : %d"), SaveGameInstance->WeaponDropSaveDatas.Num());
}
