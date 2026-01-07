#pragma once
#include "CoreMinimal.h"
#include "MyGameMode.h"
#include "MyPlayerController.h"
#include "MyPlayerPawn.h"
#include "MyHUD.h"
#include "Game.generated.h"


UCLASS() class WHIMSICAL_API UGame : public UGameInstance {
	GENERATED_BODY() public:
	FString              PlayerName       = TEXT("DefaultPlayer");
	AMyGameMode*         GameMode         = nullptr;
	AMyPlayerController* PlayerController = nullptr;
	AMyPlayerPawn*       PlayerPawn       = nullptr;
	AMyHUD*              HUD              = nullptr;

	UGame(); };


#define LINK_SINGLETON_WITH_UGAME(FIELD_NAME) \
	Game = Cast<UGame>(UGameplayStatics::GetGameInstance(this));\
	if (Game != nullptr) { Game->FIELD_NAME = this; }


UGame* ActorGetGame(AActor* Actor);

