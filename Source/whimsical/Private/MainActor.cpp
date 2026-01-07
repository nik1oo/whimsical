#include "MainActor.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"


AMainActor::AMainActor() {
	PrimaryActorTick.bCanEverTick = true; }


void AMainActor::BeginPlay() {
	Super::BeginPlay(); }


void AMainActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime); }

