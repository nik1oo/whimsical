#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameMode.generated.h"


UCLASS() class WHIMSICAL_API AMyGameMode : public AGameModeBase {
	GENERATED_BODY() public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TSubclassOf<APawn> CustomPawnClass;

	AMyGameMode(); };

