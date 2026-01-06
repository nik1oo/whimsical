#include "State.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"


UState* ActorGetState(AActor* Actor) {
	UWorld* World;
	if (! Actor) { return nullptr; }
	if (! (World = Actor->GetWorld())) { return nullptr; }
	return Cast<UState>(Actor->GetWorld()->GetGameInstance()); }

