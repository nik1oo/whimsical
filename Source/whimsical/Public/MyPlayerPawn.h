#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "MyPlayerPawn.generated.h"


class UGame;


UCLASS() class WHIMSICAL_API AMyPlayerPawn : public APawn {
	GENERATED_BODY() public:
	UGame* Game;

	AMyPlayerPawn();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; };

