#include "PlayerPawn.h"
#include "State.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "MyPlayerController.h"


APlayerPawn::APlayerPawn() {
	PrimaryActorTick.bCanEverTick = true;
	UState* State = ActorGetState(this);
	if (State) { UE_LOG(LogTemp, Display, TEXT("Player Name: %s"), *State->PlayerName); }
/*	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootScene;
	StaticCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("StaticCamera"));
	StaticCamera->SetupAttachment(RootScene);*/
	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle")); }


void APlayerPawn::BeginPlay() {
	Super::BeginPlay();
	MainActor = Cast<AMainActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AMainActor::StaticClass()));
/*	PhysicsHandle->GrabStrength = 1000.0;
	if (APlayerController* PC = GetController<APlayerController>()) {
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true; } */}


void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	UE_LOG(LogTemp, Display, TEXT("SETTING UP PLAYER INPUT COMPONENT."));
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Grab", IE_Pressed, this, &APlayerPawn::OnMousePressed);
	PlayerInputComponent->BindAction("Grab", IE_Released, this, &APlayerPawn::OnMouseReleased); }


void APlayerPawn::Tick(float DeltaTime) {
	AMyPlayerController* PlayerController;
	UWorld*              World;

	Super::Tick(DeltaTime);
	World = GetWorld();
	PlayerController = Cast<AMyPlayerController>(GetController());
	if ((World != nullptr) && (PlayerController != nullptr)) {
		DrawDebugPoint(GetWorld(), PlayerController->MouseWorldPos + 1000.0 * PlayerController->MouseWorldDir, 1.0, FColor::Cyan);
		if (GrabbedComponent != nullptr) {
			UE_LOG(LogTemp, Display, TEXT("CARRYING OBJECT"));
	/*		FVector WorldPos, WorldDir;
			if (!GetMouseWorldPosition(DragPlaneDistance, WorldPos, WorldDir)) return;
			FPlane DragPlane(StaticCamera->GetForwardVector(), DragPlaneOrigin);
			FVector TargetPoint = FMath::RayPlaneIntersection(WorldPos, WorldDir, DragPlane);
			PhysicsHandle->SetTargetLocation(TargetPoint);
			DrawDebugLine(GetWorld(), StaticCamera->GetComponentLocation(), TargetPoint, FColor::Cyan, false, -1.0f, 0, 2.0f);*/ } } }


void APlayerPawn::OnMousePressed() {
	FHitResult           HitResult;
	UWorld*              World;
	AMyPlayerController* PlayerController;

	UE_LOG(LogTemp, Display, TEXT("MOUSE PRESSED"));
	PlayerController = Cast<AMyPlayerController>(GetController());
	World = GetWorld();
	bool WasHit = GetWorld()->LineTraceSingleByChannel(HitResult, PlayerController->MouseWorldPos, PlayerController->MouseWorldPos + 5000.0 * PlayerController->MouseWorldDir, ECC_PhysicsBody, FCollisionQueryParams("", false, this));
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
			GrabbedComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore); }
		else { GrabbedComponent = nullptr; } } }


void APlayerPawn::OnMouseReleased() {
	UE_LOG(LogTemp, Display, TEXT("MOUSE RELEASED"));
	if (GrabbedComponent != nullptr) {
		UE_LOG(LogTemp, Display, TEXT("OBJECT RELEASED"));
		GrabbedComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
		GrabbedComponent = nullptr;
		PhysicsHandle->ReleaseComponent(); } }

