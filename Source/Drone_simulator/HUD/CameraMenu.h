#pragma once

#include "CoreMinimal.h"
#include "MenuBase.h"
#include "CameraMenu.generated.h"

class UButton;

UCLASS()
class DRONE_SIMULATOR_API UCameraMenu : public UMenuBase
{
	GENERATED_BODY()

public:

protected:
	virtual void NativeConstruct() override;

private:
	
};
