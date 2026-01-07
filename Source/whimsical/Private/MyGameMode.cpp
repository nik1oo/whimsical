#include "MyGameMode.h"
#include "MyPlayerController.h"
#include "PlayerPawn.h"


AMyGameMode::AMyGameMode() {
	PlayerControllerClass = AMyPlayerController::StaticClass();
	DefaultPawnClass = APlayerPawn::StaticClass();
	UE_LOG(LogTemp, Display, TEXT("Initialized custom game mode.")); }

