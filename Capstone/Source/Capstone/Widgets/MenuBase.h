// Troy Records Jr. 2020

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuBase.generated.h"

/**
 * 
 */
UCLASS()
class CAPSTONE_API UMenuBase : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void Setup();
	virtual void TearDown();
	
};
