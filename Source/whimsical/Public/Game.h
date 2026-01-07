#pragma once
#include "CoreMinimal.h"
#include "MyGameMode.h"
#include "MyPlayerController.h"
#include "MyPlayerPawn.h"
#include "Game.generated.h"


UCLASS() class WHIMSICAL_API UGame : public UGameInstance {
	GENERATED_BODY() public:
	FString              PlayerName       = TEXT("DefaultPlayer");
	AMyGameMode*         GameMode         = nullptr;
	AMyPlayerController* PlayerController = nullptr;
	AMyPlayerPawn*       PlayerPawn       = nullptr;

	UGame(); };


UGame* ActorGetGame(AActor* Actor);

