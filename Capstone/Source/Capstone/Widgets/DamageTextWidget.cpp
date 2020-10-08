// Troy Records Jr. 2020


#include "DamageTextWidget.h"

#include "Components/TextBlock.h"



void UDamageTextWidget::SetOwner(USceneComponent* InOwner, APlayerController* InPlayerController)
{
    Owner = InOwner;
    PlayerController = InPlayerController;
}

void UDamageTextWidget::SetText(float InDamage)
{
    DamageText->SetText(FText::FromString(FString::SanitizeFloat(InDamage)));
}

void UDamageTextWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    
    const FVector WorldLocation = Owner->GetComponentLocation();
    FVector2D ScreenLocation;
    
    if(PlayerController == nullptr) return;
    PlayerController->ProjectWorldLocationToScreen(WorldLocation, ScreenLocation);
    SetPositionInViewport(ScreenLocation);
}
