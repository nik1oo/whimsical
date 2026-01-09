#include "MyHUD.h"
#include "Game.h"
#include "Kismet/GameplayStatics.h"


AMyHUD::AMyHUD() {
	UE_LOG(LogTemp, Display, TEXT("AMYHUD CONSTRUCTED."));
	LINK_SINGLETON_WITH_UGAME(HUD); }


void AMyHUD::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Display, TEXT("AMYHUD BEGINPLAY.")); }

