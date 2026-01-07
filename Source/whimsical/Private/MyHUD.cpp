#include "MyHUD.h"
#include "Game.h"
#include "Kismet/GameplayStatics.h"


AMyHUD::AMyHUD() {
	UE_LOG(LogTemp, Display, TEXT("AMYHUD CONSTRUCTED."));
	Game = Cast<UGame>(UGameplayStatics::GetGameInstance(this));
	if (Game != nullptr) { Game->HUD = this; } }

