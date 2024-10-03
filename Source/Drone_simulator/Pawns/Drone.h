#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Drone.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UCameraComponent;
class UFloatingPawnMovement;
class USoundCue;
class ADroneController;

UCLASS()
class DRONE_SIMULATOR_API ADrone : public APawn
{
	GENERATED_BODY()

public:
	ADrone();

protected:
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere)
		USceneComponent* DefaultRoot = nullptr;
	
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* DroneMesh = nullptr;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Wing1 = nullptr;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Wing2 = nullptr;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Wing3 = nullptr;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Wing4 = nullptr;
	

	UPROPERTY(EditAnywhere)
		UCameraComponent* Camera = nullptr;
	UPROPERTY(EditAnywhere)
		UFloatingPawnMovement* MovementComponent = nullptr;
	UPROPERTY(EditAnywhere)
		USoundCue* FlySound = nullptr;

	FVector TargetLocation;
	bool bIsMovingToTarget;
	float MovementSpeed = 800.f;  // Prêdkoœæ drona

	void MoveToTarget(const FVector& Target);

	ADroneController* DroneContoller = nullptr;
	void PauseButtonClick();
};
