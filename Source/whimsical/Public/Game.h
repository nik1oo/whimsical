#pragma once
#include "CoreMinimal.h"
#include "MyGameMode.h"
#include "MyPlayerController.h"
#include "MyPlayerPawn.h"
#include "MyHUD.h"
#include "MyUI.h"
#include "Game.generated.h"


#define COLOR_DARK_PURPLE_R 0.11
#define COLOR_DARK_PURPLE_G 0.08
#define COLOR_DARK_PURPLE_B 0.17
#define ColorDarkPurple FVector4d(COLOR_DARK_PURPLE_R, COLOR_DARK_PURPLE_G, COLOR_DARK_PURPLE_B, 1.00)
#define DefaultWidth 1920
#define DefaultHeight 1080


UCLASS() class WHIMSICAL_API UGame : public UGameInstance {
	GENERATED_BODY() public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TSubclassOf<AGameModeBase> AMyGameModeClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TSubclassOf<AHUD> AMyHUDClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TSubclassOf<APlayerController> AMyPlayerControllerClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TSubclassOf<APawn> AMyPlayerPawnClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TSubclassOf<UUserWidget> UMyUIClass;
	// UPROPERTY(EditAnywhere, BlueprintReadWrite) TSubclassOf<AGameModeBase> AMyGameMode;
	                                            FString                  PlayerName        = TEXT("DefaultPlayer");
	                                            AMyGameMode*             GameMode          = nullptr;
	                                            AMyPlayerController*     PlayerController  = nullptr;
	                                            AMyPlayerPawn*           PlayerPawn        = nullptr;
	                                            AMyHUD*                  HUD               = nullptr;
	                                            UMyUI*                   UI                = nullptr;
	// (TODO): Why are these UProperties? Does this help anyhow? //
	UPROPERTY(VisibleAnywhere)                  USceneComponent*         RootScene;
	UPROPERTY(VisibleAnywhere)                  USpringArmComponent*     SpringArm;
	UPROPERTY(VisibleAnywhere)                  UCameraComponent*        StaticCamera;
	UPROPERTY(VisibleAnywhere)                  UPhysicsHandleComponent* PhysicsHandle;
	UPROPERTY()                                 UPrimitiveComponent*     GrabbedComponent  = nullptr;
	                                            FVector                  DragPlaneOrigin;
	                                            FPlane                   DragPlane;
	                                            FVector                  HandVector;
	                                            FVector                  GrabbedObjectVector;

	UGame();
	virtual void Init() override;
	void BeginPlay();
	void Tick(float DeltaSeconds);
	void OnMousePressed();
	void OnMouseReleased();
	void MouseTrace(bool& Hit, FHitResult& HitResult); };


#define LINK_SINGLETON_WITH_UGAME(FIELD_NAME) \
	Game = Cast<UGame>(UGameplayStatics::GetGameInstance(this));\
	if (Game != nullptr) { Game->FIELD_NAME = this; }


#define LINK_SLATE_WIDGET_WITH_UGAME() \
	UGame* WeakGame = InArgs.Game();\
	if (WeakGame.IsValid()) { Game = WeakGame.Get(); }\
	else { Game = nullptr; }


UGame* ActorGetGame(AActor* Actor);

