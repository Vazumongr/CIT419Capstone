// Troy Records Jr. 2020


#include "BaseAboveHeadHealthbar.h"

#include "Kismet/KismetMathLibrary.h"
#include "Capstone/Widgets/AboveHeadHealthBar.h"

void UBaseAboveHeadHealthbar::InitWidget()
{
    Super::InitWidget();
    UAboveHeadHealthBar* WidgetInstance = Cast<UAboveHeadHealthBar>(Widget);
    if(WidgetInstance)
    {
        WidgetInstance->SetOwningActor(GetOwner());
    }
}

void UBaseAboveHeadHealthbar::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    FaceTowardsCamera();
}

void UBaseAboveHeadHealthbar::BeginPlay()
{
    Super::BeginPlay();
    
    UWorld* World = GetWorld();
    ensure(World);

    APlayerController* PlayerController = World->GetFirstPlayerController();
    ensure(PlayerController);

    if(PlayerController == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("No player controller found..."));
        return;
    }
    PlayerCameraManager = PlayerController->PlayerCameraManager;

    
}

void UBaseAboveHeadHealthbar::FaceTowardsCamera()
{
    
    if(PlayerCameraManager == nullptr) return;
    
    FVector CameraLocation = PlayerCameraManager->GetCameraLocation();
    
    FVector MyLocation = GetComponentLocation();

    FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(MyLocation, CameraLocation);
    LookAtRotation.Yaw = 180;

    SetWorldRotation(LookAtRotation);
}
