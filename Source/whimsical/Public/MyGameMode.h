#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameMode.generated.h"


class UGame;


UCLASS() class WHIMSICAL_API AMyGameMode : public AGameModeBase {
	GENERATED_BODY() public:
	UGame* Game;
	// UPROPERTY(EditAnywhere, BlueprintReadOnly) TSubclassOf<APawn> CustomPawnClass;

	AMyGameMode(); };

