#include "MyGameMode.h"
#include "Game.h"
#include "Kismet/GameplayStatics.h"
#include "MyPlayerController.h"
#include "MyPlayerPawn.h"
#include "MyHUD.h"


AMyGameMode::AMyGameMode() {
	UE_LOG(LogTemp, Display, TEXT("AMYGAMEMODE CONSTRUCTED."));
	LINK_SINGLETON_WITH_UGAME(GameMode);
	PlayerControllerClass = AMyPlayerController::StaticClass();
	DefaultPawnClass = AMyPlayerPawn::StaticClass();
	HUDClass = AMyHUD::StaticClass(); }

