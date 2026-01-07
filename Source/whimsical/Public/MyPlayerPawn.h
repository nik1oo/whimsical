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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)     USceneComponent*         RootScene;
	UPROPERTY(VisibleAnywhere)                        USpringArmComponent*     SpringArm;
	UPROPERTY(VisibleAnywhere)                        UCameraComponent*        StaticCamera;
	UPROPERTY(VisibleAnywhere)                        UPhysicsHandleComponent* PhysicsHandle;
	UPROPERTY(EditAnywhere, Category="Drag Settings") float                    DragPlaneDistance = 500.0;
	UPROPERTY()                                       UPrimitiveComponent*     GrabbedComponent = nullptr;
	                                                  FVector                  DragPlaneOrigin;
	                                                  FVector                  GrabPoint;

	AMyPlayerPawn();
	void OnMousePressed();
	void OnMouseReleased();
	bool GetMouseWorldPosition(float Distance, FVector& OutWorldPos, FVector& OutWorldDir);
	void UpdateDragTarget();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; };

