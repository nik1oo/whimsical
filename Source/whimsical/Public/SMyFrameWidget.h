#pragma once
#include "CoreMinimal.h"
#include "Widgets/SWidget.h"
#include "Widgets/SCompoundWidget.h"
#include "Engine/Font.h"
#include "Input/Reply.h"


class UGame;


class SMyFrameWidget : public SCompoundWidget {
	SLATE_BEGIN_ARGS(SMyFrameWidget) {}
	SLATE_ARGUMENT(TWeakObjectPtr<UGame>, Game)
	SLATE_END_ARGS()
	public:
	UGame* Game;

	void Construct(const FArguments& InArgs); };

