#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FlyHeight.generated.h"

class USpinBox;

UCLASS()
class DRONE_SIMULATOR_API UFlyHeight : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	USpinBox* ChooseFlyHeightSpinBox;
	FVector* FlyPointRef;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnFlyHeightChanged(float NewValue);

public:
	void SetFlyPointRef(FVector& FlyPoint);

};
