#include "MyUI.h"
#include "Game.h"
#include "Kismet/GameplayStatics.h"
#include "SMyButtonWidget.h"


void UMyUI::NativeConstruct() {
	UE_LOG(LogTemp, Display, TEXT("UMYUI CONSTRUCTED."));
	LINK_SINGLETON_WITH_UGAME(UI); }


TSharedRef<SWidget> UMyUI::RebuildWidget() {
    return SNew(SMyButtonWidget); }


void UMyUI::ShowUI() {
    if (TSharedPtr<SWidget> Widget = GetCachedWidget()) {
		AddToViewport(99);
		// SetInputMode(FInputModeUIOnly());
		// SetShowMouseCursor(true);
    } }

