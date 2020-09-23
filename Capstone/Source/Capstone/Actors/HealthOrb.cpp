// Troy Records Jr. 2020


#include "HealthOrb.h"

#include "Capstone/Characters/PlayerCharacter.h"
#include "Components/SphereComponent.h"

// Sets default values
AHealthOrb::AHealthOrb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Static Mesh Component")));
	SetRootComponent(StaticMeshComponent);
	StaticMeshComponent->SetSimulatePhysics(true);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshObject(TEXT("/Engine/BasicShapes/Sphere"));
	if(StaticMeshObject.Object != nullptr)
	{
		StaticMeshComponent->SetStaticMesh(StaticMeshObject.Object);
	}

	TriggerZone = CreateDefaultSubobject<USphereComponent>(FName(TEXT("Trigger Zone")));
	TriggerZone->SetupAttachment(StaticMeshComponent);
	TriggerZone->SetGenerateOverlapEvents(true);
	TriggerZone->SetSphereRadius(250.0f);
	//TriggerZone->SetRelativeLocation(FVector(0,0,50.0f));

	TriggerZone->OnComponentBeginOverlap.AddDynamic(this, &AHealthOrb::Overlapping);
}

// Called when the game starts or when spawned
void AHealthOrb::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHealthOrb::Overlapping(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		Player->AddHealth(10);
		Destroy();
	}
	
}

// Called every frame
void AHealthOrb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

