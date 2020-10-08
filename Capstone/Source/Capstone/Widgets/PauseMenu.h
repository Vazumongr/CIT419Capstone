// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

private:
	UFUNCTION()
	void ResumeGame();
	UFUNCTION()
	void QuitGame();


	
	UPROPERTY(meta = (BindWidget))
	class UButton* ResumeButton = nullptr;
	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton = nullptr;
	
};
