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
	InventoryComponent->PrintArray();
	InventoryComponent->AddItem(this);
	InventoryComponent->PrintArray();
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
	
	//EquippedWeaponStats = InWeapon->GetWeaponStats();	// Original
 
	InventoryComponent->AddItem(InWeapon);	// Adds the weapon to our inventory
	
	InWeapon->Interact(this);	// Interacts with it so it does what it needs to do

	int32 WeaponIndex = InventoryComponent->GetInventorySize() - 1;	// Get the index of it in the inventory
	
	ABaseWeaponLootActor* EquippedWeapon = Cast<ABaseWeaponLootActor>(InventoryComponent->GetItem(WeaponIndex));	// Get the weapon from the inventory
	
	EquippedWeaponStats = EquippedWeapon->GetWeaponStats();	// Get the stats

	// Pointer to our gun actor class
	//EquippedWeaponActor = InWeapon;
	InWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("WeaponSocket"));	// Attaches the gun to the SM bone
	InWeapon->SetOwner(this);	
	
	UE_LOG(LogTemp, Warning, TEXT("Equipped %s, with a damage value of %f"), *EquippedWeaponStats.WeaponName, EquippedWeaponStats.WeaponDamage);
}

void APlayerCharacter::PrintInventory()
{
	InventoryComponent->PrintArray();
}

