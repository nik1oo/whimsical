#include "Game.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"


UGame* Game = nullptr;


// Order of creation:
//  * AMyGameMode
//  * AMyPlayerController
//  * APlayerPawn


UGame::UGame() {
	Game = this; }


UGame* ActorGetGame(AActor* Actor) {
	UWorld* World;
	if (! Actor) { return nullptr; }
	if (! (World = Actor->GetWorld())) { return nullptr; }
	return Cast<UGame>(Actor->GetWorld()->GetGameInstance()); }

