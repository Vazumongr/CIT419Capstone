// Troy Records Jr. 2020


#include "BaseWeaponLootActor.h"

ABaseWeaponLootActor::ABaseWeaponLootActor()
{
    
}

void ABaseWeaponLootActor::BeginPlay()
{
    Super::BeginPlay();
    WeaponStats.StaticMesh = StaticMeshComponent->GetStaticMesh();
    TArray<UMaterialInterface*> Materials;
    StaticMeshComponent->GetUsedMaterials(Materials);
    UMaterialInterface* NewMat = nullptr;
    for(UMaterialInterface* Material : Materials)
    {
        //UE_LOG(LogTemp, Warning, TEXT("%s"), *Material->GetName());
    }
}

void ABaseWeaponLootActor::SetWeaponStats(FWeaponStats InStats)
{
    WeaponStats = InStats;
    ensure(StaticMeshComponent);
    StaticMeshComponent->SetStaticMesh(WeaponStats.StaticMesh);
}

void ABaseWeaponLootActor::Interact(APlayerCharacter* PlayerCharacter)
{
    Destroy();
}
