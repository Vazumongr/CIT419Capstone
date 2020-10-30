// Troy Records Jr. 2020


#include "EnemyAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Capstone/GameModes/MainGameMode.h"
#include "Capstone/Characters/PlayerCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

void AEnemyAIController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);
    UE_LOG(LogTemp, Warning, TEXT("We have killed him!!!!!!!!!!!"));
}

void AEnemyAIController::BeginPlay()
{
    Super::BeginPlay();

    if(AIBehavior)
    {
        RunBehaviorTree(AIBehavior);    // Runs the behavior tree
    }

    BlackboardComponent = GetBlackboardComponent();    // Gets pointer to BBComp

    UWorld* World = GetWorld();
    if(!World) return;

    AMainGameMode* GameMode = Cast<AMainGameMode>(World->GetAuthGameMode());

    PlayerCharacter = GameMode->GetPlayerCharacter();
    
    BlackboardComponent->SetValueAsFloat(TEXT("DetectionRange"),DetectionRange);
    BlackboardComponent->SetValueAsFloat(TEXT("TargetRange"),TargetRange);

    if(GetPawn() == nullptr)
        UE_LOG(LogTemp, Warning, TEXT("The controller is not possessing anything in beginplay"));
    //BlackboardComponent->SetValueAsVector(TEXT("StartLocation"),GetPawn()->GetActorLocation());    // Records start location
}
