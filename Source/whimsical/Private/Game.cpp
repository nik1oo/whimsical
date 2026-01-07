#include "Game.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "MyPlayerController.h"


UGame* Game = nullptr;


// Order of creation:
//  * AMyGameMode
//  * AMyPlayerController
//  * AMyPlayerPawn


UGame::UGame() {
	UE_LOG(LogTemp, Display, TEXT("UGAME CONSTRUCTED."));
	Game = this;
	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle")); }


void UGame::OnMousePressed() {
	FHitResult           HitResult;
	UWorld*              World;

	UE_LOG(LogTemp, Display, TEXT("MOUSE PRESSED"));
	World = GetWorld();
	if (World == nullptr) { return; }
	bool WasHit = World->LineTraceSingleByChannel(HitResult, PlayerController->MouseWorldPos, PlayerController->MouseWorldPos + 5000.0 * PlayerController->MouseWorldDir, ECC_PhysicsBody, FCollisionQueryParams("", false, PlayerPawn));
	if (WasHit) {
		UE_LOG(LogTemp, Display, TEXT("OBJECT HIT"));
		GrabPoint = HitResult.ImpactPoint;
		DrawDebugSphere(GetWorld(), GrabPoint, 2.0, 12, FColor::Red, false, 1.0f);
		GrabbedComponent = Cast<UPrimitiveComponent>(HitResult.GetComponent());
		if (GrabbedComponent->IsSimulatingPhysics()) {
			UE_LOG(LogTemp, Display, TEXT("OBJECT GRABBED"));
			DragPlaneOrigin = GrabPoint;
			PhysicsHandle->GrabComponentAtLocationWithRotation(
				GrabbedComponent,
				NAME_None,
				HitResult.ImpactPoint,
				GrabbedComponent->GetComponentRotation());
			GrabbedComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
			GrabbedComponent->SetEnableGravity(false); }
		else { GrabbedComponent = nullptr; } } }


void UGame::OnMouseReleased() {
	UE_LOG(LogTemp, Display, TEXT("MOUSE RELEASED"));
	if (GrabbedComponent != nullptr) {
		UE_LOG(LogTemp, Display, TEXT("OBJECT RELEASED"));
		GrabbedComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
		GrabbedComponent = nullptr;
		PhysicsHandle->ReleaseComponent(); } }


void UGame::Tick(float DeltaTime) {
	UWorld*              World;

	World = GetWorld();
	if ((World == nullptr) || (PlayerController == nullptr)) { return; }
	DrawDebugPoint(GetWorld(), PlayerController->MouseWorldPos + 1000.0 * PlayerController->MouseWorldDir, 1.0, FColor::Cyan);
	if (GrabbedComponent != nullptr) {
		UE_LOG(LogTemp, Display, TEXT("CARRYING OBJECT"));
/*		FVector WorldPos, WorldDir;
		if (!GetMouseWorldPosition(DragPlaneDistance, WorldPos, WorldDir)) return;
		FPlane DragPlane(StaticCamera->GetForwardVector(), DragPlaneOrigin);
		FVector TargetPoint = FMath::RayPlaneIntersection(WorldPos, WorldDir, DragPlane);
		PhysicsHandle->SetTargetLocation(TargetPoint);
		DrawDebugLine(GetWorld(), StaticCamera->GetComponentLocation(), TargetPoint, FColor::Cyan, false, -1.0f, 0, 2.0f);*/
	} }


// (TODO): Remove this. //
UGame* ActorGetGame(AActor* Actor) {
	UWorld* World;
	if (! Actor) { return nullptr; }
	if (! (World = Actor->GetWorld())) { return nullptr; }
	return Cast<UGame>(Actor->GetWorld()->GetGameInstance()); }


