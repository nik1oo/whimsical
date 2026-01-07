#include "MyPlayerController.h"
#include "Game.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"


AMyPlayerController::AMyPlayerController() {
	Game = Cast<UGame>(UGameplayStatics::GetGameInstance(this));
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true; }


void AMyPlayerController::BeginPlay() {
	ACameraActor* CameraActor;

	CameraActor = Cast<ACameraActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ACameraActor::StaticClass()));
	if (CameraActor) { SetViewTargetWithBlend(CameraActor, 0.0f); } }


void AMyPlayerController::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	GetMousePosition(MousePos[0], MousePos[1]);
	UGameplayStatics::DeprojectScreenToWorld(this, MousePos, MouseWorldPos, MouseWorldDir); }

