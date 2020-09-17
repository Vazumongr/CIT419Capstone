// Troy Records Jr. 2020


#include "EnemyAIController.h"

#include "BehaviorTree/BlackboardComponent.h"

void AEnemyAIController::BeginPlay()
{
    Super::BeginPlay();

    if(AIBehavior)
    {
        RunBehaviorTree(AIBehavior);    // Runs the behavior tree
    }

    BlackboardComponent = GetBlackboardComponent();    // Gets pointer to BBComp
    
    BlackboardComponent->SetValueAsVector(TEXT("StartLocation"),GetPawn()->GetActorLocation());    // Records start location
    BlackboardComponent->SetValueAsVector(TEXT("PlayerLocation"),GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());    // Records start location
}