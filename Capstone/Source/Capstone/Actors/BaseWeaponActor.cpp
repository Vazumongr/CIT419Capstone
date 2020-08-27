// Troy Records Jr. 2020


#include "BaseWeaponActor.h"

#include "Capstone/Characters/PlayerCharacter.h"

// Sets default values
ABaseWeaponActor::ABaseWeaponActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ABaseWeaponActor::Interact(APlayerCharacter* PlayerCharacter)
{
	PlayerCharacter->EquipWeapon(this);
}

// Called when the game starts or when spawned
void ABaseWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

