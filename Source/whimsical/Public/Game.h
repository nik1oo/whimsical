#pragma once
#include "CoreMinimal.h"
#include "MyGameMode.h"
#include "MyPlayerController.h"
#include "MyPlayerPawn.h"
#include "MyHUD.h"
#include "Game.generated.h"


UCLASS() class WHIMSICAL_API UGame : public UGameInstance {
	GENERATED_BODY() public:
	                              FString                  PlayerName        = TEXT("DefaultPlayer");
	                              AMyGameMode*             GameMode          = nullptr;
	                              AMyPlayerController*     PlayerController  = nullptr;
	                              AMyPlayerPawn*           PlayerPawn        = nullptr;
	                              AMyHUD*                  HUD               = nullptr;
	// (TODO): Why are these UProperties? Does this help anyhow? //
	UPROPERTY(VisibleAnywhere)    USceneComponent*         RootScene;
	UPROPERTY(VisibleAnywhere)    USpringArmComponent*     SpringArm;
	UPROPERTY(VisibleAnywhere)    UCameraComponent*        StaticCamera;
	UPROPERTY(VisibleAnywhere)    UPhysicsHandleComponent* PhysicsHandle;
	UPROPERTY(EditAnywhere) float DragPlaneDistance = 500.0;
	UPROPERTY()                   UPrimitiveComponent*     GrabbedComponent  = nullptr;
	                              FVector                  DragPlaneOrigin;
	                              FVector                  GrabPoint;

	UGame();
	void Tick(float DeltaSeconds);
	void OnMousePressed();
	void OnMouseReleased(); };


#define LINK_SINGLETON_WITH_UGAME(FIELD_NAME) \
	Game = Cast<UGame>(UGameplayStatics::GetGameInstance(this));\
	if (Game != nullptr) { Game->FIELD_NAME = this; }


UGame* ActorGetGame(AActor* Actor);

