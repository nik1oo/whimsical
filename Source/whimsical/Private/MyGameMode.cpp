#include "MyGameMode.h"


AMyGameMode::AMyGameMode() {
	//CustomPawnClass = AMouseDragPawn::StaticClass();
	UE_LOG(LogTemp, Display, TEXT("Initialized custom game mode.")); }


APawn* AMyGameMode::SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot) {
	// if (!CustomPawnClass)
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("CustomPawnClass is not set in GameMode! Falling back to Super."));
	// 	return Super::SpawnDefaultPawnFor_Implementation(NewPlayer, StartSpot);
	// }

	// if (!NewPlayer)
	// {
	// 	return nullptr;
	// }

	// FActorSpawnParameters SpawnInfo;
	// SpawnInfo.Instigator = NewPlayer->GetPawn();
	// SpawnInfo.Owner = NewPlayer;
	// SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// // Use PlayerStart if available, otherwise spawn at origin or controller location
	// AActor* ChosenStart = StartSpot ? StartSpot : GetWorld()->GetFirstPlayerController()->GetPawn();

	// APawn* SpawnedPawn = GetWorld()->SpawnActor<APawn>(
	// 	CustomPawnClass,
	// 	ChosenStart ? ChosenStart->GetActorLocation() : FVector::ZeroVector,
	// 	ChosenStart ? ChosenStart->GetActorRotation() : FRotator::ZeroRotator,
	// 	SpawnInfo
	// );

	// return SpawnedPawn;
	return nullptr; }

