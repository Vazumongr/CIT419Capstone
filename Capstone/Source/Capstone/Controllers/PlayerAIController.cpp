// Troy Records Jr. 2020


#include "PlayerAIController.h"

#include "Capstone/Controllers/ObservingPlayerController.h"
#include "Capstone/Interfaces/InteractableItemInterface.h"
#include "Capstone/Characters/BaseEnemyCharacter.h"
#include "Capstone/Characters/PlayerCharacter.h"
#include "Capstone/Actors/BaseWeaponActor.h"
#include "Capstone/Actors/BaseWeaponLootActor.h"

void APlayerAIController::ProcessHitResult(FHitResult HitResult)
{
    if(ABaseWeaponLootActor* WeaponActor = Cast<ABaseWeaponLootActor>(HitResult.GetActor()))
    {
        CurrentCommand = FMoveCommandTypes::MoveToWeapon;
        EquipWeapon(WeaponActor);
    }
    else if(IInteractableItemInterface* ItemInterface = Cast<IInteractableItemInterface>(HitResult.GetActor()))
    {
        CurrentCommand = FMoveCommandTypes::MoveToInteractable;
        InteractWithItem(HitResult, ItemInterface);
    }
    else if(ABaseEnemyCharacter* EnemyCharacter = Cast<ABaseEnemyCharacter>(HitResult.GetActor()))
    {
        CurrentCommand = FMoveCommandTypes::MoveToAttack;
        DealDamageToEnemy(EnemyCharacter);
    }
    else
    {
        CurrentCommand = FMoveCommandTypes::MoveToLocation;
        MoveToLocation(HitResult.Location);
    }
}

void APlayerAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    switch(CurrentCommand)
    {
        case FMoveCommandTypes::MoveToInteractable:
            if(Result.IsSuccess() && TargetedItem != nullptr && PlayerCharacter != nullptr)
                PlayerCharacter->InteractWithItem(TargetedItem);
            break;
        case FMoveCommandTypes::MoveToWeapon:
            if(Result.IsSuccess() && TargetedWeapon != nullptr && PlayerCharacter != nullptr)
                PlayerCharacter->PickUpWeapon(TargetedWeapon);
            break;
        case FMoveCommandTypes::MoveToLocation:
            break;
        case FMoveCommandTypes::MoveToAttack:
            if(Result.IsSuccess() && TargetedEnemy != nullptr && PlayerCharacter != nullptr)
            {
                PlayerCharacter->DealDamageToEnemy(TargetedEnemy);
            }
                
        default:
            break;
    }
}
// TODO this ain't being used??
void APlayerAIController::SwitchWeapon(FWeaponStats InStats)
{
    ensure(PlayerCharacter);
    PlayerCharacter->SwitchWeapon(InStats);
}

void APlayerAIController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);
    //Destroy();
}

void APlayerAIController::PrintInventory()
{
    ensure(PlayerCharacter);
    PlayerCharacter->PrintInventory();
}

FString APlayerAIController::GetInventoryAsText()
{
    ensure(PlayerCharacter);
    return PlayerCharacter->GetInventoryAsText();
}

TArray<FWeaponStats> APlayerAIController::GetInventoryAsArray()
{
    ensure(PlayerCharacter);
    return PlayerCharacter->GetInventoryAsArray();
}

void APlayerAIController::SetInventory(TArray<FWeaponStats> InInventory)
{
    ensure(PlayerCharacter);
    PlayerCharacter->SetInventory(InInventory);
}

void APlayerAIController::SaveGame()
{
    ensure(PlayerCharacter);
    PlayerCharacter->SaveGame();
}

void APlayerAIController::LoadGame(FPlayerSaveData InData)
{
    PlayerCharacter->LoadGame(InData);
}

void APlayerAIController::InteractWithItem(FHitResult HitResult, IInteractableItemInterface* ItemInterface)
{
    TargetedItem = ItemInterface;
    MoveToActor(HitResult.GetActor(), 300);
}

void APlayerAIController::DealDamageToEnemy(ABaseEnemyCharacter* EnemyCharacter)
{
    TargetedEnemy = EnemyCharacter;
    MoveToActor(EnemyCharacter, 1000);
    
}

void APlayerAIController::EquipWeapon(ABaseWeaponLootActor* WeaponActor)
{
    TargetedWeapon = WeaponActor;
    MoveToActor(WeaponActor, 100);
}

void APlayerAIController::SetPlayerController(APlayerController* InController)
{
    PlayerController = Cast<AObservingPlayerController>(InController);
}

void APlayerAIController::SetPlayerCharacter(APlayerCharacter* InCharacter)
{
    PlayerCharacter = InCharacter;
}

void APlayerAIController::AddSteel(float InSteel)
{
    PlayerCharacter->AddSteel(InSteel);
}

float APlayerAIController::GetSteel() const
{
    return PlayerCharacter->GetSteel();
}
