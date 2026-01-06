#include "MyGameMode.h"
#include "MyPlayerController.h"
#include "MouseGrabPawn.h"


AMyGameMode::AMyGameMode() {
	PlayerControllerClass = AMyPlayerController::StaticClass();
	DefaultPawnClass = AMouseGrabPawn::StaticClass();
	UE_LOG(LogTemp, Display, TEXT("Initialized custom game mode.")); }

