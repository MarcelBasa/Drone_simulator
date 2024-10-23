#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuBase.generated.h"

class UCanvasPanel;

UCLASS()
class DRONE_SIMULATOR_API UMenuBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
		UCanvasPanel* Background;
};
