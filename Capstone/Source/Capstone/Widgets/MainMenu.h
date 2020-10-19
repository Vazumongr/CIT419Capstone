// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "Capstone/Widgets/MenuBase.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_API UMainMenu : public UMenuBase
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

private:
	UFUNCTION()
	void StartPressed();
	UFUNCTION()
	void LoadPressed();
	UFUNCTION()
	void QuitPressed();

	
	UPROPERTY(meta = (BindWidget))
	class UButton* NewGameButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* LoadSaveButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;
	
};
