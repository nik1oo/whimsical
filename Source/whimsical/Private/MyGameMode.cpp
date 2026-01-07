#include "MyGameMode.h"
#include "Game.h"
#include "Kismet/GameplayStatics.h"
#include "MyPlayerController.h"
#include "MyPlayerPawn.h"
#include "MyHUD.h"


AMyGameMode::AMyGameMode() {
	UE_LOG(LogTemp, Display, TEXT("AMYGAMEMODE CONSTRUCTED."));
	Game = Cast<UGame>(UGameplayStatics::GetGameInstance(this));
	if (Game != nullptr) { Game->GameMode = this; }
	PlayerControllerClass = AMyPlayerController::StaticClass();
	DefaultPawnClass = AMyPlayerPawn::StaticClass();
	HUDClass = AMyHUD::StaticClass(); }

