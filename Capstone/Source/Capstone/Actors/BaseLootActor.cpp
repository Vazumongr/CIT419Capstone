// Troy Records Jr. 2020


#include "BaseLootActor.h"

// Sets default values
ABaseLootActor::ABaseLootActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseLootActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseLootActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseLootActor::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("%s IS BEING LOOTED"), *GetName());
	Destroy();
}

