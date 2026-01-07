#include "MyGameMode.h"
#include "Game.h"
#include "Kismet/GameplayStatics.h"
#include "MyPlayerController.h"
#include "MyPlayerPawn.h"
#include "MyHUD.h"


AMyGameMode::AMyGameMode() {
	Game = Cast<UGame>(UGameplayStatics::GetGameInstance(this));
	PlayerControllerClass = AMyPlayerController::StaticClass();
	DefaultPawnClass = AMyPlayerPawn::StaticClass();
	HUDClass = AMyHUD::StaticClass();
	UE_LOG(LogTemp, Display, TEXT("Initialized custom game mode.")); }

