#include "MyPlayerPawn.h"
#include "Game.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "MyPlayerController.h"


AMyPlayerPawn::AMyPlayerPawn() {
	UE_LOG(LogTemp, Display, TEXT("AMYPLAYERPAWN CONSTRUCTED."));
	LINK_SINGLETON_WITH_UGAME(PlayerPawn);
	PrimaryActorTick.bCanEverTick = true;
/*	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootScene;
	StaticCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("StaticCamera"));
	StaticCamera->SetupAttachment(RootScene);*/ }


void AMyPlayerPawn::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Display, TEXT("AMYPLAYERPAWN BEGINPLAY."));
	Game->BeginPlay(); }


void AMyPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	UE_LOG(LogTemp, Display, TEXT("AMYPLAYERPAWN SETUPPLAYERINPUTCOMPONENT."));
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Grab", IE_Pressed, Game, &UGame::OnMousePressed);
	PlayerInputComponent->BindAction("Grab", IE_Released, Game, &UGame::OnMouseReleased); }


void AMyPlayerPawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	Game->Tick(DeltaTime); }

