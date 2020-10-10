// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "Capstone/Widgets/MenuBase.h"
#include "PauseMenu.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_API UPauseMenu : public UMenuBase
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
