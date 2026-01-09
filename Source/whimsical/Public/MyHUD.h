#pragma once
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"


class UGame;


UCLASS() class WHIMSICAL_API AMyHUD : public AHUD {
	GENERATED_BODY() public:
	UGame* Game;

	AMyHUD();
	virtual void BeginPlay() override; };

