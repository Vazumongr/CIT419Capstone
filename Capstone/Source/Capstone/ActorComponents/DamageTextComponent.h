// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "DamageTextComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAPSTONE_API UDamageTextComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamageTextComponent();
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// This is called by the actor it's attached to.
	void SpawnDamageText(float DamageAmount);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Set up", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UDamageTextWidget> DamageTextClass;
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Set up", meta = (AllowPrivateAccess = "true"))
	//TSubclassOf<class UUserWidget> DamageTextClass;


		
};
