#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StartGameMode.generated.h"

UCLASS()
class DRONE_SIMULATOR_API AStartGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

};
