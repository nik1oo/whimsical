#pragma once
#include "CoreMinimal.h"
#include "State.generated.h"


class AActor;
class UActorComponent;
class AController;
class APlayerController;
class UGameInstance;


UCLASS() class WHIMSICAL_API UState : public UGameInstance {
	GENERATED_BODY() public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="State") FString PlayerName = TEXT("DefaultPlayer"); };


UState* ActorGetState(AActor* Actor);


// template <typename T> UWorld* GetWorld(T* Obj) {
// 	if (Obj == nullptr) { return nullptr; }
// 	if (auto* Actor = Cast<AActor>(Obj)) { return Actor->GetWorld(); }
// 	if (auto* Component = Cast<UActorComponent>(Obj)) { return Component->GetWorld(); }
// 	if (auto* Controller = Cast<AController>(Obj)) { return Controller->GetWorld(); }
// 	if (auto* PlayerController = Cast<APlayerController>(Obj)) { return PlayerController->GetWorld(); }
// 	if (auto* GameInstance = Cast<UGameInstance>(Obj)) { return GameInstance->GetWorld(); }
// 	if (UObject* Outer = Obj->GetOuter()) { return Outer->GetWorld(); }
// 	return nullptr; }

