#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Pawn.h"
#include "Drone.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UCameraComponent;
class UFloatingPawnMovement;
class USoundCue;
class ADroneController;
class UCurveFloat;

UCLASS()
class DRONE_SIMULATOR_API ADrone : public APawn
{
	GENERATED_BODY()

public:
	ADrone();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* DroneMesh = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* Wing1 = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* Wing2 = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* Wing3 = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* Wing4 = nullptr;

	UFUNCTION()
		void TimelineProgress(float Value);

protected:
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void Zoom(float Value);

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere)
		USceneComponent* DefaultRoot = nullptr;
	UPROPERTY(EditAnywhere)
		UCameraComponent* Camera = nullptr;
	UPROPERTY(EditAnywhere)
		UFloatingPawnMovement* MovementComponent = nullptr;
	UPROPERTY(EditAnywhere)
		USoundCue* FlySound = nullptr;

	FTimeline CurveTimeline;
	UPROPERTY(EditAnywhere)
		UCurveFloat* CurveFloat;

	ADroneController* DroneContoller = nullptr;
	void PauseButtonClick();
};
