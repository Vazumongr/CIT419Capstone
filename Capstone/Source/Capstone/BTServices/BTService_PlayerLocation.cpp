// Troy Records Jr. 2020


#include "BTService_PlayerLocation.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"

UBTService_PlayerLocation::UBTService_PlayerLocation()
{
    NodeName = TEXT("Update Player Location");
}

void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
    if(PlayerPawn == nullptr) return;

    AAIController* Controller = OwnerComp.GetAIOwner();
    if(Controller == nullptr) return;

    APawn* EnemyPawn = Controller->GetPawn();
    if(EnemyPawn == nullptr) return;

    UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();

    float TargetRange = MyBlackboard->GetValueAsFloat(TEXT("TargetRange"));
    float DetectionRange = MyBlackboard->GetValueAsFloat(TEXT("DetectionRange"));
    float Dist = FVector::Dist(EnemyPawn->GetActorLocation(), PlayerPawn->GetActorLocation());


    if(Dist <= TargetRange)
    {
        MyBlackboard->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
        MyBlackboard->SetValueAsBool(TEXT("bCanTarget"), true);
    }
    else if(Dist <= DetectionRange)
    {
        MyBlackboard->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
        MyBlackboard->ClearValue(TEXT("bCanTarget"));
    }
    else
    {
        MyBlackboard->ClearValue(GetSelectedBlackboardKey());
        MyBlackboard->ClearValue(TEXT("bCanTarget"));
    }

    
    
}
