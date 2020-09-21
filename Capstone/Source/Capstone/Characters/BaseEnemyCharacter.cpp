// Troy Records Jr. 2020


#include "BaseEnemyCharacter.h"

#include "Capstone/Characters/PlayerCharacter.h"
#include "Capstone/GameModes/MainGameMode.h"
#include "Capstone/ActorComponents/LootGenerator.h"

// Sets default values
ABaseEnemyCharacter::ABaseEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LootGenerator = CreateDefaultSubobject<ULootGenerator>(FName(TEXT("Loot Generator")));

}

// Called when the game starts or when spawned
void ABaseEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	AMainGameMode* MainGameMode = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode());
	if(MainGameMode != nullptr)
		PlayerCharacter = MainGameMode->GetPlayerCharacter();

	if(PlayerCharacter == nullptr)
		UE_LOG(LogTemp, Warning, TEXT("Not finding player character..."));
}

void ABaseEnemyCharacter::DamagePlayer()
{
	ensure(PlayerCharacter);
	float DamageAmount = 0;
	FPointDamageEvent PointDamageEvent;
	FDamageEvent DamageEvent;
	PlayerCharacter->TakeDamage(DamageAmount, DamageEvent, GetController(), this);
}

void ABaseEnemyCharacter::Die()
{
	ensure(LootGenerator);
	LootGenerator->SpawnWeapon();
	DetachFromControllerPendingDestroy();
	Destroy();
}

// Called every frame
void ABaseEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DamagePlayer();

}

float ABaseEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	TSubclassOf<UDamageType> InDamageType = DamageEvent.DamageTypeClass;
	if(DamageType == InDamageType)
	{
		DamageAmount = 100.0f;
	}
		
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	Health -= DamageApplied;
	if(Health <= 0)
	{
		if(PlayerCharacter)
			PlayerCharacter->AddSteel(10);
		Die();
	}
		
	return DamageApplied;
}

float ABaseEnemyCharacter::GetHealthPercent() const
{
	return Health / 100.0f;
}

