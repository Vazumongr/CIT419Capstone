// Troy Records Jr. 2020


#include "PlayerCharacter.h"

#include "Capstone/Interfaces/InteractableItemInterface.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	Health -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Health Remaining: %f"), Health);
	return DamageToApply;
}

void APlayerCharacter::DealDamageToEnemy(AActor* EnemyToDamage)
{
	float DamageAmount = 10;
	FPointDamageEvent PointDamageEvent;
	//EnemyToDamage->TakeDamage(DamageAmount, PointDamageEvent, GetController(), this);
	UGameplayStatics::ApplyDamage(EnemyToDamage, DamageAmount, GetController(), this, DamageType);
}

void APlayerCharacter::InteractWithItem(IInteractableItemInterface* ItemToInteract)
{
	ItemToInteract->Interact();
}

