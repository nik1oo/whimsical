#include "Game.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
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
	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
	// FVector TargetPoint = FMath::RayPlaneIntersection(WorldPos, WorldDir, DragPlane);
	DragPlaneOrigin = FVector{ 620.0, 0.0, 180.0 };
	DragPlane = FPlane(DragPlaneOrigin, FVector{ 1.0, 0.0, 0.0 }); }


void UGame::MouseTrace(bool& Hit, FHitResult& HitResult) {
	UWorld* World = GetWorld();
	Hit = World->LineTraceSingleByChannel(HitResult, PlayerController->MouseWorldPos, PlayerController->MouseWorldPos + 5000.0 * PlayerController->MouseWorldDir, ECC_PhysicsBody, FCollisionQueryParams("", false, PlayerPawn)); }


void UGame::OnMousePressed() {
	FHitResult HitResult;
	UWorld*    World;
	bool       Hit;

	UE_LOG(LogTemp, Display, TEXT("MOUSE PRESSED"));
	World = GetWorld();
	if (World == nullptr) { return; }
	MouseTrace(Hit, HitResult);
	if (Hit) {
	// if (World->LineTraceSingleByChannel(HitResult, PlayerController->MouseWorldPos, PlayerController->MouseWorldPos + 5000.0 * PlayerController->MouseWorldDir, ECC_PhysicsBody, FCollisionQueryParams("", false, PlayerPawn))) {
		UE_LOG(LogTemp, Display, TEXT("OBJECT HIT"));
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 2.0, 12, FColor::Red, false, 1.0f);
		GrabbedComponent = Cast<UPrimitiveComponent>(HitResult.GetComponent());
		// UKismetSystemLibrary::DrawDebugPlane(World, DragPlane, DragPlaneOrigin, 1000.0, FColor::Cyan, 1.0, EDrawDebugSceneDepthPriorityGroup::World);
		if (GrabbedComponent->IsSimulatingPhysics()) {
			UE_LOG(LogTemp, Display, TEXT("OBJECT GRABBED"));
			PhysicsHandle->GrabComponentAtLocationWithRotation(
				GrabbedComponent,
				NAME_None,
				HitResult.ImpactPoint,
				GrabbedComponent->GetComponentRotation());
			GrabbedComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
			// GrabbedComponent->SetEnableGravity(false);
			}
		else { GrabbedComponent = nullptr; } } }


void UGame::OnMouseReleased() {
	UE_LOG(LogTemp, Display, TEXT("MOUSE RELEASED"));
	if (GrabbedComponent != nullptr) {
		UE_LOG(LogTemp, Display, TEXT("OBJECT RELEASED"));
		GrabbedComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
		GrabbedComponent = nullptr;
		PhysicsHandle->ReleaseComponent(); } }


void PrimitiveComponentApplyDrag(UPrimitiveComponent* PrimitiveComponent, float DragCoefficient) {
	FVector Velocity = PrimitiveComponent->GetPhysicsLinearVelocity();
	FVector DragForce = -Velocity.GetSafeNormal();
	if (DragForce.Size() == 0.0) { return; }
	DragForce *= DragCoefficient * FMath::Pow(Velocity.Size(), 2.0);
	UE_LOG(LogTemp, Display, TEXT("VELOCITY %f %f %f DRAG %f %f %f."), Velocity[0], Velocity[1], Velocity[2], DragForce[0], DragForce[1], DragForce[2]);
	PrimitiveComponent->AddForce(DragForce, NAME_None, true); }


void UGame::Tick(float DeltaTime) {
	UWorld*              World;

	World = GetWorld();
	if ((World == nullptr) || (PlayerController == nullptr)) { return; }
	HandVector = FMath::RayPlaneIntersection(PlayerController->MouseWorldPos, PlayerController->MouseWorldDir, DragPlane);
	DrawDebugPoint(GetWorld(), HandVector, 4.0, FColor::Red);
	// DrawDebugPoint(GetWorld(), PlayerController->MouseWorldPos + 1000.0 * PlayerController->MouseWorldDir, 1.0, FColor::Cyan);
	if (GrabbedComponent != nullptr) {
		UE_LOG(LogTemp, Display, TEXT("DELTA TIME %f."), DeltaTime);
		GrabbedObjectVector = GrabbedComponent->GetComponentLocation();
/*		FVector WorldPos, WorldDir;
		if (!GetMouseWorldPosition(DragPlaneDistance, WorldPos, WorldDir)) return;
		FPlane DragPlane(StaticCamera->GetForwardVector(), DragPlaneOrigin);
		FVector TargetPoint = FMath::RayPlaneIntersection(WorldPos, WorldDir, DragPlane);
		PhysicsHandle->SetTargetLocation(TargetPoint);
		DrawDebugLine(GetWorld(), StaticCamera->GetComponentLocation(), TargetPoint, FColor::Cyan, false, -1.0f, 0, 2.0f);*/
		FVector ForceVector = (HandVector - GrabbedObjectVector);
		float Distance = ForceVector.Size();
		ForceVector.Normalize();
		FVector Impulse = 10000.0 * DeltaTime * ForceVector/* / FMath::Pow(Distance, 2.0)*/;
		GrabbedComponent->AddImpulse(Impulse, NAME_None, true);
		FVector Velocity = GrabbedComponent->GetPhysicsLinearVelocity();
		// UE_LOG(LogTemp, Display, TEXT("DISTANCE %f."), Distance);
		// DICK
		// if (Distance <= 40.0) {
			// GrabbedComponent->SetPhysicsLinearVelocity(FVector{ 0.0, 0.0, 0.0 }, false, NAME_None);
			PrimitiveComponentApplyDrag(GrabbedComponent, 0.2); // (TODO): Tweak DragCoefficient and carry force and set accurate mass to the objects. //
		// }
		// GrabbedComponent->AddImpulse();
	} }


// (TODO): Remove this. //
UGame* ActorGetGame(AActor* Actor) {
	UWorld* World;
	if (! Actor) { return nullptr; }
	if (! (World = Actor->GetWorld())) { return nullptr; }
	return Cast<UGame>(Actor->GetWorld()->GetGameInstance()); }


