#include "CameraPawn.h"
#include "Camera/CameraComponent.h"

ACameraPawn::ACameraPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	RootComponent = Camera;
}

void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
	SetActorRotation(FRotator(30, 0, 0));
}

void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

