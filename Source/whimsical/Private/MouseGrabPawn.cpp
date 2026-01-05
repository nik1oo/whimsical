#include "MouseGrabPawn.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"


AMouseGrabPawn::AMouseGrabPawn() {
	PrimaryActorTick.bCanEverTick = true;
/*	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootScene;
	StaticCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("StaticCamera"));
	StaticCamera->SetupAttachment(RootScene);
	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true; */}


void AMouseGrabPawn::BeginPlay() {
	Super::BeginPlay();
/*	PhysicsHandle->GrabStrength = GrabStrength;
	if (APlayerController* PC = GetController<APlayerController>()) {
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true; } */}


void AMouseGrabPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
/*	PlayerInputComponent->BindAction("Grab", IE_Pressed, this, &AMouseGrabPawn::OnMousePressed);
	PlayerInputComponent->BindAction("Grab", IE_Released, this, &AMouseGrabPawn::OnMouseReleased); */}


void AMouseGrabPawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
/*	if (PhysicsHandle->GetGrabbedComponent()) {
		UpdateDragTarget(); } */}


bool AMouseGrabPawn::GetMouseWorldPosition(float Distance, FVector& OutWorldPos, FVector& OutWorldDir) {
/*	if (!StaticCamera || !GetController()) return false;
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC) return false;
	float MouseX, MouseY;
	if (!PC->GetMousePosition(MouseX, MouseY)) return false;
	return UGameplayStatics::DeprojectScreenToWorld(PC, FVector2D(MouseX, MouseY), OutWorldPos, OutWorldDir); */
	return true; }


void AMouseGrabPawn::OnMousePressed() {
/*	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC || !StaticCamera) return;
	FVector WorldPos, WorldDir;
	if (!GetMouseWorldPosition(DragPlaneDistance, WorldPos, WorldDir)) return;
	FVector TraceEnd = WorldPos + WorldDir * 2000.0f;
	FHitResult Hit;
	bool bHit = GetWorld()->LineTraceSingleByChannel(
		Hit,
		WorldPos,
		TraceEnd,
		ECC_PhysicsBody,
		FCollisionQueryParams("", false, this));
	if (bHit && Hit.GetComponent() && Hit.GetComponent()->IsSimulatingPhysics()) {
		GrabbedComponent = Cast<UPrimitiveComponent>(Hit.GetComponent());
		DragPlaneOrigin = Hit.ImpactPoint;
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			GrabbedComponent,
			NAME_None,
			Hit.ImpactPoint,
			GrabbedComponent->GetComponentRotation());
		GrabbedComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 16.0f, 12, FColor::Green, false, 5.0f); } */}


void AMouseGrabPawn::UpdateDragTarget() {
/*	FVector WorldPos, WorldDir;
	if (!GetMouseWorldPosition(DragPlaneDistance, WorldPos, WorldDir)) return;
	FPlane DragPlane(StaticCamera->GetForwardVector(), DragPlaneOrigin);
	FVector TargetPoint = FMath::RayPlaneIntersection(WorldPos, WorldDir, DragPlane);
	PhysicsHandle->SetTargetLocation(TargetPoint);
	DrawDebugLine(GetWorld(), StaticCamera->GetComponentLocation(), TargetPoint, FColor::Cyan, false, -1.0f, 0, 2.0f); */}


void AMouseGrabPawn::OnMouseReleased() {
/*	if (PhysicsHandle->GetGrabbedComponent()) {
		if (GrabbedComponent) {
			GrabbedComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
			GrabbedComponent = nullptr; }
		PhysicsHandle->ReleaseComponent(); } */}

