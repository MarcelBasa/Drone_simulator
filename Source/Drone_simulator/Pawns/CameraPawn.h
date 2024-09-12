#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CameraPawn.generated.h"

class UCameraComponent;

UCLASS()
class DRONE_SIMULATOR_API ACameraPawn : public APawn
{
	GENERATED_BODY()
	
public:	
	ACameraPawn();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:	
	UPROPERTY(EditAnywhere)
		UCameraComponent* Camera = nullptr;

};
