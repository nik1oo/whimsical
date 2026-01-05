#include "MainActor.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"


AMainActor::AMainActor() {
	PrimaryActorTick.bCanEverTick = true; }


void AMainActor::BeginPlay() {
	Super::BeginPlay();
	if (TargetCamera) {
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PC) {
			PC->SetViewTargetWithBlend(TargetCamera, 0.0f); } } }


void AMainActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime); }

