// Troy Records Jr. 2020


#include "DamageTextComponent.h"

#include "Blueprint/UserWidget.h"
#include "Capstone/Widgets/DamageTextWidget.h"

// Sets default values for this component's properties
UDamageTextComponent::UDamageTextComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDamageTextComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDamageTextComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDamageTextComponent::SpawnDamageText(float DamageAmount)
{
	UDamageTextWidget* DamageText = CreateWidget<UDamageTextWidget>(GetWorld(), DamageTextClass);
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if(PlayerController == nullptr) return;
	
	DamageText->SetOwner(this, PlayerController);
	DamageText->SetText(DamageAmount);
	DamageText->AddToViewport();
	
	const FVector Location = GetComponentLocation();
	FVector2D ScreenLocation;
	PlayerController->ProjectWorldLocationToScreen(Location, ScreenLocation);

	DamageText->SetPositionInViewport(ScreenLocation);
	DamageText->Destruct();
}

