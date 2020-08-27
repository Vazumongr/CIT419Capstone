// Troy Records Jr. 2020


#include "PlayerCharacter.h"

#include "Capstone/Interfaces/InteractableItemInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Capstone/Actors/BaseWeaponActor.h"

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

	WeaponActor = GetWorld()->SpawnActor<ABaseWeaponActor>(WeaponActorClass);
	GetMesh()->HideBoneByName(TEXT("pistol"), EPhysBodyOp::PBO_None);
	EquipWeapon(WeaponActor);
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
	return DamageToApply;
}

void APlayerCharacter::DealDamageToEnemy(AActor* EnemyToDamage)
{
	float DamageAmount = EquippedWeaponStats.WeaponDamage;
	FPointDamageEvent PointDamageEvent;
	UGameplayStatics::ApplyDamage(EnemyToDamage, DamageAmount, GetController(), this, DamageType);
}

void APlayerCharacter::InteractWithItem(IInteractableItemInterface* ItemToInteract)
{
	ItemToInteract->Interact(this);
}

void APlayerCharacter::EquipWeapon(ABaseWeaponLootActor* InWeapon)
{
	if(EquippedWeapon != nullptr)	// If we have a weapon equipped already, get rid of it.
		EquippedWeapon->Destroy();

	// Create a weapon actor from the loot actor

	/*
	WeaponActor = InWeapon;
	WeaponActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	WeaponActor->SetOwner(this);
	EquippedWeaponStats = InWeapon->GetWeaponStats();
	*/
	UE_LOG(LogTemp, Warning, TEXT("Equipped %s, with a damage value of %f"), *EquippedWeaponStats.WeaponName, EquippedWeaponStats.WeaponDamage);
}

