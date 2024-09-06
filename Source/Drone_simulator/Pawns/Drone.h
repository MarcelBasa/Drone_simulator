#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Drone.generated.h"

class USkeletalMeshComponent;
class UCameraComponent;
class UFloatingPawnMovement;

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
		USkeletalMeshComponent* DroneMesh = nullptr;
	UPROPERTY(EditAnywhere)
		UCameraComponent* Camera = nullptr;
	UPROPERTY(EditAnywhere)
		UFloatingPawnMovement* MovementComponent;

	FVector TargetLocation;
	bool bIsMovingToTarget;
	float MovementSpeed = 800.f;  // Prêdkoœæ drona

	void MoveToTarget(const FVector& Target);
};
