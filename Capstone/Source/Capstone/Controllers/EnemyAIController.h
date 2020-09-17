// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
    virtual void BeginPlay() override;
    
private:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior = nullptr;
	UPROPERTY()
	class UBlackboardComponent* BlackboardComponent = nullptr;
	
};
