#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"


UCLASS() class WHIMSICAL_API AMyPlayerController : public APlayerController {
	GENERATED_BODY() public:
	UPROPERTY(VisibleAnywhere) FVector2D MousePos;
	UPROPERTY(VisibleAnywhere) FVector   MouseWorldPos;
	UPROPERTY(VisibleAnywhere) FVector   MouseWorldDir;

	AMyPlayerController();
	virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override; };

