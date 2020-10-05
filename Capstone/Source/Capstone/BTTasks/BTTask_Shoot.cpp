// Troy Records Jr. 2020


#include "BTTask_Shoot.h"

#include "AIController.h"
#include "Capstone/Characters/BaseEnemyCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
    NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if(ABaseEnemyCharacter* Pawn = Cast<ABaseEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn()))
        Pawn->DamagePlayer();

    return EBTNodeResult::Succeeded;
}
