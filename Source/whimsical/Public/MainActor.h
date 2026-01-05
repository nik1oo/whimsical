#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainActor.generated.h"


UCLASS() class WHIMSICAL_API AMainActor : public AActor {
	GENERATED_BODY()
public:
	AMainActor();
    UPROPERTY(EditAnywhere, Category = "Camera") AActor* TargetCamera;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override; };

