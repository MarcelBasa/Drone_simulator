#include "Drone.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

ADrone::ADrone()
{
	PrimaryActorTick.bCanEverTick = true;

	DroneMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Drone mesh"));
	DroneMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = DroneMesh;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
}

void ADrone::BeginPlay()
{
	Super::BeginPlay();

	if (FlySound)
	{
		UGameplayStatics::PlaySound2D(
			GetWorld(),
			FlySound
		);
	}
	// DEBUG
	MovementComponent->Deactivate();
	MoveToTarget(FVector(0, -4000.f, 10000.f));
}

void ADrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsMovingToTarget)
	{
		FVector CurrentLocation = GetActorLocation();

		// SprawdŸ, czy dron jest blisko celu, aby zatrzymaæ ruch
		if (FVector::Dist(CurrentLocation, TargetLocation) <= 10.f)  // Tolerancja 10 jednostek
		{
			bIsMovingToTarget = false;
			UE_LOG(LogTemp, Warning, TEXT("Pass"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Flying"));
			// Interpolacja z równ¹ prêdkoœci¹
			FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, MovementSpeed);
			SetActorLocation(NewLocation);
		}
	}
}

void ADrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ThisClass::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ThisClass::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ThisClass::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ThisClass::LookUp);
}

void ADrone::MoveForward(float Value)
{
	if (Controller != nullptr && Value != 0.f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));
		AddMovementInput(Direction, Value);
	}
}

void ADrone::MoveRight(float Value)
{
	if (Controller != nullptr && Value != 0.f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));
		AddMovementInput(Direction, Value);
	}
}

void ADrone::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ADrone::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void ADrone::MoveToTarget(const FVector& Target)
{
	TargetLocation = Target;
	bIsMovingToTarget = true;
}