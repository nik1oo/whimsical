#pragma once
#include "CoreMinimal.h"
#include "MainActor.h"
#include "MyGameMode.h"
#include "MyPlayerController.h"
#include "PlayerPawn.h"
#include "Game.generated.h"


UCLASS() class WHIMSICAL_API UGame : public UGameInstance {
	GENERATED_BODY() public:
	FString              PlayerName       = TEXT("DefaultPlayer");
	AMainActor*          Actor            = nullptr;
	AMyGameMode*         GameMode         = nullptr;
	AMyPlayerController* PlayerController = nullptr;
	APlayerPawn*         PlayerPawn       = nullptr;

	UGame(); };


UGame* ActorGetGame(AActor* Actor);

