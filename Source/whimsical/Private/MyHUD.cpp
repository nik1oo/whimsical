#include "MyHUD.h"
#include "Game.h"
#include "Kismet/GameplayStatics.h"


AMyHUD::AMyHUD() {
	Game = Cast<UGame>(UGameplayStatics::GetGameInstance(this)); }

