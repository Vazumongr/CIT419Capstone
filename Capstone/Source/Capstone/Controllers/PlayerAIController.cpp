// Troy Records Jr. 2020


#include "PlayerAIController.h"

#include "Capstone/Controllers/ObservingPlayerController.h"
#include "Capstone/Interfaces/InteractableItemInterface.h"
#include "Capstone/Characters/BaseEnemyCharacter.h"

void APlayerAIController::ProcessHitResult(FHitResult HitResult)
{
    if(IInteractableItemInterface* ItemInterface = Cast<IInteractableItemInterface>(HitResult.GetActor()))
    {
        CurrentCommand = FMoveCommandTypes::MoveToInteractable;
        InteractWithItem(HitResult, ItemInterface);
    }
    else if(ABaseEnemyCharacter* EnemyCharacter = Cast<ABaseEnemyCharacter>(HitResult.GetActor()))
    {
        EnemyCharacter->TestTakeDamage();
    }
    else
    {
        CurrentCommand = FMoveCommandTypes::MoveToLocation;
        MoveToLocation(HitResult.Location);
    }
    // If we clicked on an enemy
        // Attack the enemy
}

void APlayerAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    switch(CurrentCommand)
    {
        case FMoveCommandTypes::MoveToInteractable:
            if(Result.IsSuccess() && TargetedItem != nullptr)
                TargetedItem->Interact();
            break;
        case FMoveCommandTypes::MoveToLocation:
            UE_LOG(LogTemp, Warning, TEXT("Movement completed."));
            break;
        default:
            break;
    }
}

void APlayerAIController::InteractWithItem(FHitResult HitResult, IInteractableItemInterface* ItemInterface)
{
    TargetedItem = ItemInterface;
    MoveToActor(HitResult.GetActor(), 300);
}

void APlayerAIController::SetPlayerController(APlayerController* InController)
{
    PlayerController = Cast<AObservingPlayerController>(InController);
}

void APlayerAIController::SetPlayerCharacter(APlayerCharacter* InCharacter)
{
    PlayerCharacter = InCharacter;
}
