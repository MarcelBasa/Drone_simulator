#include "Drone.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Drone_simulator/Controllers/DroneController.h"
#include "Components/TimelineComponent.h"
#include "LidarPointCloudComponent.h"
#include "LidarPointCloud.h"

ADrone::ADrone()
{
	PrimaryActorTick.bCanEverTick = true;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	SetRootComponent(DefaultRoot);

	DroneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Drone mesh"));
	DroneMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DroneMesh->SetupAttachment(RootComponent);

	Wing1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wing 1 mesh"));
	Wing1->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Wing1->SetupAttachment(DroneMesh);

	Wing2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wing 2 mesh"));
	Wing2->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Wing2->SetupAttachment(DroneMesh);
	
	Wing3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wing 3 mesh"));
	Wing3->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Wing3->SetupAttachment(DroneMesh);

	Wing4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wing 4 mesh"));
	Wing4->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Wing4->SetupAttachment(DroneMesh);
	

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;

	LidarPointCloudComponent = CreateDefaultSubobject<ULidarPointCloudComponent>(TEXT("LidarPointCloudComponent"));
	LidarPointCloudComponent->SetupAttachment(RootComponent);

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
}

void ADrone::LoadLidarPointCloud(const FString& FilePath)
{
	if (!FPaths::FileExists(FilePath))
	{
		UE_LOG(LogTemp, Warning, TEXT("Lidar file not found: %s"), *FilePath);
		return;
	}

	// Create a Lidar Point Cloud object from the file
	ULidarPointCloud* LoadedPointCloud = ULidarPointCloud::CreateFromFile(FilePath); // The second parameter determines if loading is asynchronous

	if (LoadedPointCloud)
	{
		// Set the Lidar Point Cloud to the LidarPointCloudComponent
		LidarPointCloudComponent->SetPointCloud(LoadedPointCloud);
		UE_LOG(LogTemp, Log, TEXT("Lidar Point Cloud successfully loaded and set."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load Lidar Point Cloud from file: %s"), *FilePath);
	}
}

void ADrone::TimelineProgress(float Value)
{
	if (Camera)
	{
		float newFieldOfView = FMath::Lerp(30, 90, Value);
		Camera->SetFieldOfView(newFieldOfView);
	}
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
	if (CurveFloat)
	{
		FOnTimelineFloat TimeLineProgress;
		TimeLineProgress.BindUFunction(this, FName("TimelineProgress"));
		CurveTimeline.AddInterpFloat(CurveFloat, TimeLineProgress);
	}

	FString LidarFilePath = TEXT("C:/Users/Marcelo/Desktop/szczecin.laz");
	LoadLidarPointCloud(LidarFilePath);
}

void ADrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurveTimeline.TickTimeline(DeltaTime);
}

void ADrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ThisClass::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ThisClass::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ThisClass::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ThisClass::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Zoom"), this, &ThisClass::Zoom);
	PlayerInputComponent->BindAction(TEXT("Pause"), IE_Pressed, this, &ThisClass::PauseButtonClick);
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

void ADrone::Zoom(float Value)
{
	if (Value > 0)
	{
		if (CurveTimeline.IsPlaying() == false || CurveTimeline.IsReversing())
		{
			CurveTimeline.Play();
		}
	}
	else if (Value < 0)
	{
		if (CurveTimeline.IsPlaying() == false || !CurveTimeline.IsReversing())
		{
			CurveTimeline.Reverse();
		}
	}
}

void ADrone::PauseButtonClick()
{
	DroneContoller = DroneContoller == nullptr ? Cast<ADroneController>(Controller) : DroneContoller;
	if(DroneContoller)
		DroneContoller->HandleSetPauseMenu();
}