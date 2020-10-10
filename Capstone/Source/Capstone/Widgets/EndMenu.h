// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "MenuBase.h"
#include "Capstone/Widgets/MenuBase.h"
#include "EndMenu.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_API UEndMenu : public UMenuBase
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

private:
	UFUNCTION()
    void StartPressed();
	UFUNCTION()
    void QuitPressed();

	
	UPROPERTY(meta = (BindWidget))
	class UButton* StartButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* EndMessage;
	
};
