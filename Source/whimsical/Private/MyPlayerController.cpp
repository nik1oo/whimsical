#include "MyPlayerController.h"
#include "Game.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"


AMyPlayerController::AMyPlayerController() {
	UE_LOG(LogTemp, Display, TEXT("AMYPLAYERCONTROLLER CONSTRUCTED."));
	LINK_SINGLETON_WITH_UGAME(PlayerController);
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true; }


void AMyPlayerController::BeginPlay() {
	ACameraActor* CameraActor;

	Super::BeginPlay();
	UE_LOG(LogTemp, Display, TEXT("AMYPLAYERCONTROLLER BEGINPLAY."));
	CameraActor = Cast<ACameraActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ACameraActor::StaticClass()));
	if (CameraActor) {
		SetViewTargetWithBlend(CameraActor, 0.0f); }
	else {
		UE_LOG(LogTemp, Display, TEXT("CANT FIND CAMERA.")); } }


void AMyPlayerController::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	GetMousePosition(MousePos[0], MousePos[1]);
	UGameplayStatics::DeprojectScreenToWorld(this, MousePos, MouseWorldPos, MouseWorldDir); }

