#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "MouseGrabPawn.generated.h"


UCLASS() class WHIMSICAL_API AMouseGrabPawn : public APawn {
	GENERATED_BODY() public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)     USceneComponent*         RootScene;
	UPROPERTY(VisibleAnywhere)                        USpringArmComponent*     SpringArm;
	UPROPERTY(VisibleAnywhere)                        UCameraComponent*        StaticCamera;
	UPROPERTY(VisibleAnywhere)                        UPhysicsHandleComponent* PhysicsHandle;
	UPROPERTY(EditAnywhere, Category="Drag Settings") float                    DragPlaneDistance = 500.0;
	UPROPERTY()                                       UPrimitiveComponent*     GrabbedComponent = nullptr;
	                                                  FVector                  DragPlaneOrigin;
	AMouseGrabPawn();
	void OnMousePressed();
	void OnMouseReleased();
	bool GetMouseWorldPosition(float Distance, FVector& OutWorldPos, FVector& OutWorldDir);
	void UpdateDragTarget();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; };

