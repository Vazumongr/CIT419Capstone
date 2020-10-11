// Troy Records Jr. 2020


#include "FloatingDamageNumbersComponent.h"

void UFloatingDamageNumbersComponent::InitWidget()
{
    Super::InitWidget();
    UE_LOG(LogTemp, Warning, TEXT("MyCustomWidgetComponent"));
    SetWidgetSpace(EWidgetSpace::Screen);
}

void UFloatingDamageNumbersComponent::SetDamageToDisplay(float DamageToDisplay)
{
    UE_LOG(LogTemp, Warning, TEXT("%f"), DamageToDisplay);
    //DestroyComponent();
}

void UFloatingDamageNumbersComponent::TickComponent(float DeltaTime, ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    //UE_LOG(LogTemp, Warning, TEXT("I am living!"));
}
