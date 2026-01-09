#include "Game.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "MyPlayerController.h"


UGame* Game = nullptr;


/*
// In MyPlayerController.h
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
TSubclassOf<UUserWidget> ButtonUIClass;

// In MyPlayerController.cpp constructor
AMyPlayerController::AMyPlayerController()
{
	ButtonUIClass = UWMyButtonUI::StaticClass();
}

// In BeginPlay() or input binding
void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ButtonUIClass)
	{
		UUserWidget* Widget = CreateWidget<UUserWidget>(this, ButtonUIClass);
		if (Widget)
		{
			Widget->AddToViewport();
		}
	}
}
*/


UGame::UGame() {
	UE_LOG(LogTemp, Display, TEXT("UGAME CONSTRUCTED."));
	Game = this;
	AMyGameModeClass = AMyGameMode::StaticClass();
	AMyHUDClass = AMyHUD::StaticClass();
	AMyPlayerControllerClass = AMyPlayerController::StaticClass();
	AMyPlayerPawnClass = AMyPlayerPawn::StaticClass();
	UMyUIClass = UMyUI::StaticClass();
	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
	// FVector TargetPoint = FMath::RayPlaneIntersection(WorldPos, WorldDir, DragPlane);
	DragPlaneOrigin = FVector{ 50.0, 0.0, 180.0 };
	DragPlane = FPlane(DragPlaneOrigin, FVector{ 1.0, 0.0, 0.0 }); }


// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
// TSubclassOf<UUserWidget> ButtonUIClass;


void UGame::Init() {
	Super::Init();
	UE_LOG(LogTemp, Display, TEXT("UGAME INITIALIZED.")); }


void UGame::BeginPlay() {
	UE_LOG(LogTemp, Display, TEXT("UGAME BEGINPLAY."));
	UUserWidget* Widget = CreateWidget<UUserWidget>(this, UMyUIClass);
	if (Widget) {
		Widget->AddToViewport(); } }


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
		// DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 2.0, 12, FColor::Red, false, 1.0f);
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
			GrabbedComponent->SetEnableGravity(false);
			GrabbedComponent->SetLinearDamping(16.0);
			GrabbedComponent->SetAngularDamping(10.0); }
		else { GrabbedComponent = nullptr; } } }


void UGame::OnMouseReleased() {
	UE_LOG(LogTemp, Display, TEXT("MOUSE RELEASED"));
	if (GrabbedComponent != nullptr) {
		UE_LOG(LogTemp, Display, TEXT("OBJECT RELEASED"));
		GrabbedComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
		GrabbedComponent->SetEnableGravity(true);
		GrabbedComponent->SetLinearDamping(0.0);
		GrabbedComponent->SetAngularDamping(0.0);
		GrabbedComponent = nullptr;
		PhysicsHandle->ReleaseComponent(); } }


float GrabForceCurve(float Distance) {
	const float Radius = 30;
	if (Distance < Radius) {
		return (1.0 - FMath::Cos(Distance * 3.14159265 / Radius)) / 2.0; }
	else {
		return 1.0; } }


float AlignmentForceCurve(float AlignmentError) {
	return (4.0 / 3.14159265) * FMath::Atan(FMath::Pow(AlignmentError + 1.0, 32)) - 1.0; }


void UGame::Tick(float DeltaTime) {
	UWorld*              World;

	World = GetWorld();
	if ((World == nullptr) || (PlayerController == nullptr)) { return; }
	HandVector = FMath::RayPlaneIntersection(PlayerController->MouseWorldPos, PlayerController->MouseWorldDir, DragPlane);
	// DrawDebugPoint(GetWorld(), HandVector, 4.0, FColor::Green);
	if (GrabbedComponent != nullptr) {
		UE_LOG(LogTemp, Display, TEXT("DELTA TIME %f."), DeltaTime);
		GrabbedObjectVector = GrabbedComponent->GetComponentLocation();
		// Carry Force //
		FVector ForceVector = (HandVector - GrabbedObjectVector);
		float Distance = ForceVector.Size();
		ForceVector.Normalize();
		FVector Impulse = GrabForceCurve(Distance) * 20000.0 * DeltaTime * ForceVector;
		GrabbedComponent->AddImpulse(Impulse, NAME_None, true);
		// Rotation Force //
		FVector ComponentUpVector = GrabbedComponent->GetUpVector();
		FVector WorldUpVector = FVector::UpVector;
		FVector TorqueAxis = FVector::CrossProduct(ComponentUpVector, WorldUpVector);
		float AlignmentError = 1.0 - (FVector::DotProduct(ComponentUpVector, WorldUpVector) + 1.0) / 2.0;
		if (AlignmentError > 0.001) {
			GrabbedComponent->AddTorqueInRadians(TorqueAxis.GetSafeNormal() * 100000.0 * AlignmentForceCurve(AlignmentError)); } } }


// (TODO): Remove this. //
UGame* ActorGetGame(AActor* Actor) {
	UWorld* World;
	if (! Actor) { return nullptr; }
	if (! (World = Actor->GetWorld())) { return nullptr; }
	return Cast<UGame>(Actor->GetWorld()->GetGameInstance()); }


