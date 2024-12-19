#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FlyPoint.generated.h"

class UTextBlock;

UCLASS()
class DRONE_SIMULATOR_API UFlyPoint : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextNumber = 0;
	
	void setNumber(int32 count);
};
