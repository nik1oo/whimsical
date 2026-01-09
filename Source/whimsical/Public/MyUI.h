#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUI.generated.h"


class UGame;


UCLASS() class WHIMSICAL_API UMyUI : public UUserWidget {
	GENERATED_BODY() public:
	UGame* Game;

	virtual TSharedRef<SWidget> RebuildWidget() override;
	UFUNCTION(BlueprintCallable)
	void ShowUI();
	virtual void NativeConstruct() override; };

