// Troy Records Jr. 2020


#include "BaseEnemyCharacter.h"

#include "Capstone/Characters/PlayerCharacter.h"
#include "Capstone/GameModes/MainGameMode.h"
#include "Capstone/ActorComponents/LootGenerator.h"
#include "Capstone/Actors/HomingProjectile.h"
#include "../../Engine/Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"
#include "../../Engine/Plugins/FX/Niagara/Source/Niagara/Classes/NiagaraSystem.h"
#include "../../Engine/Plugins/FX/Niagara/Source/Niagara/Public/NiagaraComponent.h"

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
	{
		PlayerCharacter = MainGameMode->GetPlayerCharacter();
		MainGameMode->GameOver.AddUniqueDynamic(this, &ABaseEnemyCharacter::GameIsOver);
	}
		

	if(PlayerCharacter == nullptr)
		UE_LOG(LogTemp, Error, TEXT("Not finding player character..."));
}

// Called every frame
void ABaseEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(bGameOver) return;

}

void ABaseEnemyCharacter::DamagePlayer()
{
	ensure(PlayerCharacter);
	float DamageAmount = dmg;
	FPointDamageEvent PointDamageEvent;
	//FDamageEvent DamageEvent;
	//PlayerCharacter->TakeDamage(DamageAmount, DamageEvent, GetController(), this);

	FVector StartLocation = GetMesh()->GetBoneLocation("gun_pin");
	FActorSpawnParameters SpawnParams;

	FMyDamageEvent DamageEvent(PlayerCharacter, DamageAmount, GetController(), this, DamageType);

	if(!BulletClass) return;
	
	AHomingProjectile* Bullet = GetWorld()->SpawnActor<AHomingProjectile>(BulletClass, StartLocation, FRotator::ZeroRotator);
	if(Bullet == nullptr) return;
	Bullet->SetTarget(PlayerCharacter);
	Bullet->SetDamageEvent(DamageEvent);

	ensure(MuzzleFlashSystem);
	UNiagaraComponent* MuzzleFlash = UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFlashSystem, GetMesh(), TEXT("gun_pin"), FVector::ZeroVector,
                                                                            FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset,false);
}

void ABaseEnemyCharacter::Die()
{
	ensure(LootGenerator);
	LootGenerator->SpawnLoot();
	DetachFromControllerPendingDestroy();
	Destroy();
}

void ABaseEnemyCharacter::GameIsOver()
{
	bGameOver = true;
	DetachFromControllerPendingDestroy();
}

float ABaseEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const TSubclassOf<UDamageType> InDamageType = DamageEvent.DamageTypeClass;
	if(DamageType == InDamageType)
	{
		DamageAmount = 100.0f;
	}
		
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	Health -= DamageApplied;
	if(Health <= 0)
	{
		Die();
	}
		
	return DamageApplied;
}

float ABaseEnemyCharacter::GetHealthPercent() const
{
	return Health / 100.0f;
}

