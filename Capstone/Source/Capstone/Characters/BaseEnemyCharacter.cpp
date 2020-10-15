// Troy Records Jr. 2020


#include "BaseEnemyCharacter.h"

#include "Capstone/Characters/PlayerCharacter.h"
#include "Capstone/GameModes/MainGameMode.h"
#include "Capstone/ActorComponents/LootGenerator.h"
#include "Capstone/ActorComponents/DamageTextComponent.h"
#include "Capstone/ActorComponents/FloatingDamageNumbersComponent.h"
#include "Capstone/Actors/HomingProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "../../Engine/Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"
#include "../../Engine/Plugins/FX/Niagara/Source/Niagara/Classes/NiagaraSystem.h"
#include "../../Engine/Plugins/FX/Niagara/Source/Niagara/Public/NiagaraComponent.h"
#include "Blueprint/UserWidget.h"

// Sets default values
ABaseEnemyCharacter::ABaseEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LootGenerator = CreateDefaultSubobject<ULootGenerator>(FName(TEXT("Loot Generator")));

	DamageNumberLocation = CreateDefaultSubobject<USceneComponent>(FName(TEXT("Damage Number Location")));
	DamageNumberLocation->SetupAttachment(RootComponent);
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

	FVector StartLocation = GetMesh()->GetBoneLocation("gun_pin");
	FActorSpawnParameters SpawnParams;

	FMyDamageEvent DamageEvent(PlayerCharacter, DamageAmount, GetController(), this, DamageType);

	if(!BulletClass) return;

	FVector SpawnLocation = GetMesh()->GetBoneLocation("gun_pin");
	
	FRotator SpawnRotation(0,GetActorRotation().Yaw,0);

	FTransform SpawnTransform(SpawnRotation, SpawnLocation, FVector::OneVector);
	
	AHomingProjectile* Bullet = Cast<AHomingProjectile>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this,BulletClass,SpawnTransform,ESpawnActorCollisionHandlingMethod::AlwaysSpawn,this));
	if(Bullet == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("The Bullet is null"));
		return;
	}
	Bullet->SetTarget(PlayerCharacter);
	Bullet->SetDamageEvent(DamageEvent);
	UGameplayStatics::FinishSpawningActor(Bullet, SpawnTransform);
	UE_LOG(LogTemp, Warning, TEXT("Spawned Rotation of: %s"), *Bullet->GetActorRotation().ToString());

	ensure(MuzzleFlashSystem);
	UNiagaraComponent* MuzzleFlash = UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFlashSystem, GetMesh(), TEXT("gun_pin"), FVector::ZeroVector,
                                                                            FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset,false);
}

void ABaseEnemyCharacter::SpawnDamageNumbers(float DamageToDisplay)
{
	ensure(FloatingDamageNumbersClass);
	UFloatingDamageNumbersComponent* FloatingDamageNumbers = NewObject<UFloatingDamageNumbersComponent>(this, FloatingDamageNumbersClass);
	if(FloatingDamageNumbers)
	{
		FloatingDamageNumbers->RegisterComponent();
		FloatingDamageNumbers->AttachToComponent(DamageNumberLocation, FAttachmentTransformRules::KeepRelativeTransform);
		FloatingDamageNumbers->SetDamageToDisplay(DamageToDisplay);
	}
}

void ABaseEnemyCharacter::Die()
{
	ensure(LootGenerator);
	LootGenerator->SpawnLoot();
	DetachFromControllerPendingDestroy();
	DetachAllSceneComponents(DamageNumberLocation, FDetachmentTransformRules::KeepRelativeTransform);
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

	//DamageTextComponent->SpawnDamageText(DamageAmount);

	SpawnDamageNumbers(DamageAmount);
		
	return DamageApplied;
}

float ABaseEnemyCharacter::GetHealthPercent() const
{
	return Health / 100.0f;
}

