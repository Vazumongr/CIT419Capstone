// Troy Records Jr. 2020


#include "BaseAboveHeadHealthbar.h"

#include "Kismet/KismetMathLibrary.h"

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
        UE_LOG(LogTemp, Warning, TEXT("No player controller found..."));
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
    LookAtRotation.Pitch = 0;

    SetWorldRotation(LookAtRotation);
}
