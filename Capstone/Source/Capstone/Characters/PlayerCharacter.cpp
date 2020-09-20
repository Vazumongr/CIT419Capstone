// Troy Records Jr. 2020


#include "PlayerCharacter.h"

#include "Capstone/Interfaces/InteractableItemInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Capstone/Actors/BaseWeaponLootActor.h"
#include "Capstone/ActorComponents/Inventory.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InventoryComponent = CreateDefaultSubobject<UInventory>(TEXT("Inventory Component"));
	
	GetMesh()->HideBoneByName(TEXT("pistol"), EPhysBodyOp::PBO_None);	// Hides the gun in the SM
	
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
	return DamageToApply;
}

void APlayerCharacter::DealDamageToEnemy(AActor* EnemyToDamage)
{
	float DamageAmount = EquippedWeaponStats.WeaponDamage;
	TSubclassOf<UDamageType> DamageType = EquippedWeaponStats.DamageType;
	FPointDamageEvent PointDamageEvent;
	UGameplayStatics::ApplyDamage(EnemyToDamage, DamageAmount, GetController(), this, DamageType);
}

void APlayerCharacter::InteractWithItem(IInteractableItemInterface* ItemToInteract)
{
	ItemToInteract->Interact(this);
}

float APlayerCharacter::GetHealthPercent() const
{
	return Health / 100.0f;
}

void APlayerCharacter::PickUpWeapon(ABaseWeaponLootActor* InWeapon)
{
	InventoryComponent->AddItem(InWeapon->GetWeaponStats());
	InWeapon->Interact(this);
	EquipWeapon(InWeapon->GetWeaponStats());
}

void APlayerCharacter::EquipWeapon(FWeaponStats InStats)
{
	if(EquippedWeaponActor != nullptr)
		EquippedWeaponActor->Destroy();
	
	EquippedWeaponActor = GetWorld()->SpawnActor<ABaseWeaponActor>(WeaponActorClass);
	EquippedWeaponActor->InitializeStats(InStats);
	
	EquippedWeaponActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("WeaponSocket"));	// Attaches the gun to the SM bone
	EquippedWeaponActor->SetOwner(this);

	EquippedWeaponStats = InStats;

	FString DebugMsg = FString::Printf(TEXT("Equipped %s, with a damage value of %f"), *EquippedWeaponStats.WeaponName, EquippedWeaponStats.WeaponDamage);

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, DebugMsg);
	UE_LOG(LogTemp, Warning, TEXT("Equipped %s, with a damage value of %f"), *EquippedWeaponStats.WeaponName, EquippedWeaponStats.WeaponDamage);
}

void APlayerCharacter::SwitchWeapon(FWeaponStats InStats)
{
	UE_LOG(LogTemp, Warning, TEXT("I am calling switchweapon..."));
	EquipWeapon(InStats);
	/*
	TArray<FWeaponStats> Inventory = InventoryComponent->GetInventoryTArray();
	for( FWeaponStats Stats : Inventory)
	{
		if(!Stats.WeaponName.Equals(EquippedWeaponStats.WeaponName))
		{
			EquipWeapon(Stats);
			break;
		}
	}
	*/
}

void APlayerCharacter::PrintInventory()
{
	FString DebugMsg = FString::Printf(TEXT("Inventory Contents: %s"), *InventoryComponent->ToString());
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, DebugMsg);
}

FString APlayerCharacter::GetInventoryAsText()
{
	return InventoryComponent->ToString();
}

TArray<FWeaponStats> APlayerCharacter::GetInventoryAsArray()
{
	return InventoryComponent->GetInventoryTArray();
}

