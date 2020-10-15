// Troy Records Jr. 2020


#include "FloatingDamageNumbersComponent.h"

#include "Capstone/Widgets/DamageTextWidget.h"

void UFloatingDamageNumbersComponent::InitWidget()
{
    Super::InitWidget();
    SetWidgetSpace(EWidgetSpace::Screen);
    EndLocation = GetRelativeLocation() + FVector(FMath::RandRange(MinDriftRange, MaxDriftRange),
        FMath::RandRange(MinDriftRange, MaxDriftRange),
        FMath::RandRange(MinDriftRange, MaxDriftRange));
    GetWorld()->GetTimerManager().SetTimer(DeathTimerHandle, this, &UFloatingDamageNumbersComponent::DestroySelf, LifeLength);
    
}

void UFloatingDamageNumbersComponent::SetDamageToDisplay(float DamageToDisplay)
{
    
    if(Widget == nullptr) return;
        
    if(UDamageTextWidget* DamageTextWidget = Cast<UDamageTextWidget>(Widget))
    {
        DamageTextWidget->SetText(DamageToDisplay);
    }
    //DestroyComponent();
}

void UFloatingDamageNumbersComponent::TickComponent(float DeltaTime, ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    SetRelativeLocation(FMath::Lerp(GetRelativeLocation(), EndLocation, LerpAlpha));
    //UE_LOG(LogTemp, Warning, TEXT("I am living!"));
}

void UFloatingDamageNumbersComponent::DestroySelf()
{
    GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
    DestroyComponent();
}
