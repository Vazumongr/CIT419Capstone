// Troy Records Jr. 2020


#include "BaseLootActor.h"


#include "Niagara/Public/NiagaraComponent.h"

// Sets default values
ABaseLootActor::ABaseLootActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	SetRootComponent(StaticMeshComponent);

	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara Component"));
	NiagaraComponent->SetupAttachment(RootComponent);
	NiagaraComponent->SetUsingAbsoluteRotation(true);
}

// Called when the game starts or when spawned
void ABaseLootActor::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseLootActor::Interact(class APlayerCharacter* PlayerCharacter)
{
	Destroy();
}

