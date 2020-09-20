// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Capstone/Actors/BaseWeaponLootActor.h"
#include "Capstone/Actors/BaseWeaponActor.h"


#include "PlayerCharacter.generated.h"

UCLASS()
class CAPSTONE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Combat related
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	void DealDamageToEnemy(AActor* EnemyToDamage);
	
	void InteractWithItem(class IInteractableItemInterface* ItemToInteract);

	UFUNCTION(BlueprintCallable)
	float GetHealthPercent() const;

	// Loot related
	void PickUpWeapon(class ABaseWeaponLootActor* InWeapon);
	
	void EquipWeapon(struct FWeaponStats InWeapon);
	
	void SwitchWeapon(FWeaponStats InStats);
	
	void PrintInventory();
	
	FString GetInventoryAsText();
	
	TArray<FWeaponStats> GetInventoryAsArray();

	

private:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage Type", meta = (AllowPrivateAccess = "true"));
	TSubclassOf<ABaseWeaponActor> WeaponActorClass;
	
	UPROPERTY()
	class ABaseWeaponActor* EquippedWeaponActor = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UInventory* InventoryComponent;

	FWeaponStats EquippedWeaponStats;

	float Health = 100.0f;



};
