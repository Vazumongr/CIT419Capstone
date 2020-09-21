// Troy Records Jr. 2020


#include "TurretPlacementHighlightActor.h"

// Sets default values
ATurretPlacementHighlightActor::ATurretPlacementHighlightActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	SetRootComponent(BaseMesh);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

}

// Called when the game starts or when spawned
void ATurretPlacementHighlightActor::BeginPlay()
{
	Super::BeginPlay();

	if(BadMaterial == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("You did not assign the bad material."));
		return;
	}
	if(GoodMaterial == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("You did not assign the good material."));
		return;
	}
	SetBadMaterial();
	
}

// Called every frame
void ATurretPlacementHighlightActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATurretPlacementHighlightActor::SetGoodMaterial()
{
	BaseMesh->SetMaterial(0, GoodMaterial);
	TurretMesh->SetMaterial(0, GoodMaterial);
}

void ATurretPlacementHighlightActor::SetBadMaterial()
{
	BaseMesh->SetMaterial(0, BadMaterial);
	TurretMesh->SetMaterial(0, BadMaterial);
}

