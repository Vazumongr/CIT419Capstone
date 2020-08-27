// Troy Records Jr. 2020


#include "BaseLootActor.h"

// Sets default values
ABaseLootActor::ABaseLootActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMeshComponent->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ABaseLootActor::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseLootActor::Interact(class APlayerCharacter* PlayerCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("%s IS BEING LOOTED"), *GetName());
	Destroy();
}

