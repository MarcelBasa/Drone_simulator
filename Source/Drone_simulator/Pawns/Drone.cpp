#include "Drone.h"

ADrone::ADrone()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ADrone::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

