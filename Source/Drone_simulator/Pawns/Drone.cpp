#include "Drone.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Drone_simulator/Controllers/DroneController.h"
#include "Components/TimelineComponent.h"
#include "AutomatedAssetImportData.h"
#include "AssetToolsModule.h"
#include "LiDARPointCloudComponent.h"
#include "LiDARPointCloud.h"  // Zale¿noœci dla LiDAR Point Cloud
//#include "EditorAssetLibrary.h"

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

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
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

	/*TArray<FString> filesToImport;
	FString srcPath = TEXT("C:/Users/Marcelo/Desktop/szczecin.laz");
	srcPath = srcPath.Replace(TEXT("\\"), TEXT("/"));  // Zast¹p backslashe slashem
	filesToImport.Add(srcPath);

	// Utworzenie danych importu
	UAutomatedAssetImportData* importData = NewObject<UAutomatedAssetImportData>();
	importData->bReplaceExisting = true;
	importData->DestinationPath = TEXT("/Game/DynamicImportFiles");  // Œcie¿ka do folderu w projekcie UE
	importData->Filenames = filesToImport;

	// Przeprowadzenie automatycznego importu
	FAssetToolsModule& AssetToolsModule = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools");
	TArray<UObject*> importedAssets = AssetToolsModule.Get().ImportAssetsAutomated(importData);

	// Sprawdzenie, czy import siê uda³ i przetworzenie zaimportowanych zasobów
	if (importedAssets.Num() > 0)
	{
		for (UObject* ImportedAsset : importedAssets)
		{
			if (ImportedAsset)
			{
				// Sprawdzanie, czy zaimportowano LiDAR Point Cloud
				ULidarPointCloud* LidarPointCloud = Cast<ULidarPointCloud>(ImportedAsset);
				if (LidarPointCloud)
				{
					// Pobranie aktualnego œwiata gry
					UWorld* World = GEngine->GetWorldFromContextObject(GetTransientPackage(), EGetWorldErrorMode::LogAndReturnNull);
					if (World)
					{
						// Definicja lokalizacji, rotacji i skali spawnowanego obiektu
						FVector Location = FVector(0.0f, 0.0f, 100.0f);  // Pozycja spawnowanego obiektu
						FRotator Rotation = FRotator::ZeroRotator;  // Bez rotacji
						FActorSpawnParameters SpawnParams;

						// Spawnowanie aktora i dodanie komponentu LiDAR Point Cloud
						AActor* SpawnedActor = World->SpawnActor<AActor>(AActor::StaticClass(), Location, Rotation, SpawnParams);
						if (SpawnedActor)
						{
							// Dodanie komponentu LiDAR Point Cloud do aktora
							ULidarPointCloudComponent* LidarComponent = NewObject<ULidarPointCloudComponent>(SpawnedActor);
							if (LidarComponent)
							{
								LidarComponent->SetPointCloud(LidarPointCloud);
								LidarComponent->RegisterComponent();  // Zarejestrowanie komponentu
								LidarComponent->AttachToComponent(SpawnedActor->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
							}

							// Mo¿liwoœæ ustawienia skali obiektu
							SpawnedActor->SetActorScale3D(FVector(1.0f));
						}
					}
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Import failed or no assets imported."));
	}*/
}