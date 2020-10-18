// Troy Records Jr. 2020


#include "PlayerCharacter.h"

#include "Capstone/Interfaces/InteractableItemInterface.h"
#include "Capstone/GameModes/MainGameMode.h"
#include "Capstone/Actors/BaseWeaponLootActor.h"
#include "Capstone/ActorComponents/Inventory.h"
#include "Capstone/SaveGames/MySaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

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
	AMainGameMode* GameMode = GetWorld()->GetAuthGameMode<AMainGameMode>();
	if(GameMode != nullptr)
	{
		GameMode->GameOver.AddUniqueDynamic(this, &APlayerCharacter::GameIsOver);
	}
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FString DebugMsg = FString::Printf(TEXT("Current steel: %f"), Steel);
	//GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Blue, DebugMsg);

}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	Health -= DamageToApply;
	if(Health <= 0)
		Die();
	return DamageToApply;
}

void APlayerCharacter::DealDamageToEnemy(AActor* EnemyToDamage)
{
	FVector StartLocation = GetActorLocation();
	FVector EndLocation = EnemyToDamage->GetActorLocation();
	FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, EndLocation);
	SetActorRotation(Rotation);
	if(EquippedWeaponActor != nullptr)
		EquippedWeaponActor->DealDamageToEnemy(EnemyToDamage, GetController(), this);
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

	// TODO this should be removed
	EquippedWeaponStats = InStats;
	
	UE_LOG(LogTemp, Warning, TEXT("Equipped %s, with a damage value of %f"), *EquippedWeaponStats.WeaponName, EquippedWeaponStats.WeaponDamage);
}

void APlayerCharacter::SwitchWeapon(FWeaponStats InStats)
{
	EquipWeapon(InStats);
}

void APlayerCharacter::PrintInventory()
{
	FString DebugMsg = FString::Printf(TEXT("Inventory Contents: %s"), *InventoryComponent->ToString());
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, DebugMsg);
}

void APlayerCharacter::SaveGame()
{
	UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));

	FPlayerSaveData MyData;
	MyData.Inventory = InventoryComponent->GetInventoryTArray();
	MyData.CurrentHealth = Health;
	MyData.MaxHealth = MaxHealth;
	MyData.PlayerTransform = GetActorTransform();
	MyData.SteelAmount = Steel;

	
	SaveGameInstance->PlayerSaveData = MyData;
	
	
	// Save the savegameinstance
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("MySlot"), 0);
}

void APlayerCharacter::LoadGame(FPlayerSaveData InData)
{
	InventoryComponent->SetInventory(InData.Inventory);
	Health = InData.CurrentHealth;
	MaxHealth = InData.MaxHealth;
	SetActorTransform(InData.PlayerTransform);
	Steel = InData.SteelAmount;
}

FString APlayerCharacter::GetInventoryAsText()
{
	return InventoryComponent->ToString();
}

TArray<FWeaponStats> APlayerCharacter::GetInventoryAsArray()
{
	return InventoryComponent->GetInventoryTArray();
}

void APlayerCharacter::SetInventory(TArray<FWeaponStats> InInventory)
{
	InventoryComponent->Inventory = InInventory;
}

void APlayerCharacter::AddHealth(float InHealth)
{
	Health += InHealth;
}

void APlayerCharacter::AddSteel(float InSteel)
{
	Steel += InSteel;
}

void APlayerCharacter::Die()
{
	AMainGameMode* GameMode = GetWorld()->GetAuthGameMode<AMainGameMode>();
	if(GameMode != nullptr)
	{
		GameMode->PlayerDied();
	}
	
	DetachFromControllerPendingDestroy();
}

void APlayerCharacter::GameIsOver()
{
	
}

