// Troy Records Jr. 2020


#include "BaseResourceDropActor.h"

#include "Capstone/SaveGames/MySaveGame.h"
#include "Capstone/GameModes/MainGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseResourceDropActor::ABaseResourceDropActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ABaseResourceDropActor::BeginPlay()
{
	Super::BeginPlay();
	AMainGameMode* GameMode = GetWorld()->GetAuthGameMode<AMainGameMode>();
	if(GameMode != nullptr)
	{
		GameMode->SaveGame.AddUniqueDynamic(this, &ABaseResourceDropActor::SaveGame);
	}
}

void ABaseResourceDropActor::LoadGame(FResourceDropSaveData InData)
{
	ResourceValue = InData.ResourceValue;
	SetActorTransform(InData.ResourceDropTransform);
}

void ABaseResourceDropActor::SaveGame()
{
	// Load the save if it's there
	UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("MySlot"), 0));
	
	if(SaveGameInstance == nullptr) 
	{
		// If there wasn't a save loaded, create one
		SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	}

	FResourceDropSaveData MyData;
	MyData.ResourceValue = ResourceValue;
	MyData.ResourceDropTransform = GetActorTransform();
	MyData.ResourceClass = GetClass();

	
	SaveGameInstance->ResourceDropSaveDatas.Add(MyData);
	
	
	// Save the savegameinstance
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("MySlot"), 0);
}

void ABaseResourceDropActor::Overlapping(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		Destroy();
	}
}

