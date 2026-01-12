#pragma once
#include "CoreMinimal.h"
#include "Widgets/SWidget.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"
#include "Engine/Font.h"
#include "Input/Reply.h"


class SMyButtonWidget : public SCompoundWidget {
	SLATE_BEGIN_ARGS(SMyButtonWidget) {}
	SLATE_END_ARGS()
	public:
	TSharedPtr<STextBlock> ButtonText;
	int32 ClickCount = 0;
	UFont* Font;

	void Construct(const FArguments& InArgs);
	FReply OnButtonClicked(); };

