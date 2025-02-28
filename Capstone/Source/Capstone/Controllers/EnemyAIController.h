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

public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;
	
protected:
    virtual void BeginPlay() override;
    
private:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior = nullptr;
	UPROPERTY()
	class UBlackboardComponent* BlackboardComponent = nullptr;
	UPROPERTY()
	class APlayerCharacter* PlayerCharacter = nullptr;

	UPROPERTY(EditAnywhere)
	float DetectionRange = 1000.0f;
	UPROPERTY(EditAnywhere)
	float TargetRange = 800.0f;
	
};
