// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseEnemyCharacter.generated.h"

UCLASS()
class CAPSTONE_API ABaseEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseEnemyCharacter();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	void DamagePlayer();

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void Die();

	UFUNCTION()
    void GameIsOver();
	
	float Health = 100.0f;
	bool bGameOver = false;

	UPROPERTY(EditAnywhere)
	float dmg = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Type", meta = (AllowPrivateAccess = "true"));
	TSubclassOf<UDamageType> DamageType;

private:
	class APlayerCharacter* PlayerCharacter = nullptr;

	UPROPERTY(EditAnywhere)
	class ULootGenerator* LootGenerator = nullptr;
	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* MuzzleFlashSystem;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> BulletClass;

};
