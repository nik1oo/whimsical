#include "SMyFrameWidget.h"
#include "Game.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/SOverlay.h"
#include "Widgets/Layout/SConstraintCanvas.h"
#include "Widgets/Layout/SScaleBox.h"
#include "Widgets/Colors/SColorBlock.h"
#include "Widgets/Layout/SBackgroundBlur.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Brushes/SlateColorBrush.h"
#include "Brushes/SlateRoundedBoxBrush.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Font.h"
#include "SMyButtonWidget.h"


void SMyFrameWidget::Construct(const FArguments& InArgs) {
	static const FSlateBrush FrameBrush = FSlateBrush();
	// LINK_SLATE_WIDGET_WITH_UGAME()
	TWeakObjectPtr<UGame> WeakGame = InArgs._Game;
	if (WeakGame.IsValid()) { Game = WeakGame.Get(); }
	else { Game = nullptr; }
	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);
	const FVector4 CornerRadius = FVector4(32.0, 32.0, 32.0, 32.0);
	FSlateRoundedBoxBrush FillBrush = FSlateRoundedBoxBrush(FLinearColor::Blue, 32.0, FLinearColor::Red, 20.0);
	ChildSlot.HAlign(HAlign_Fill).VAlign(VAlign_Fill) [
		SNew(SBackgroundBlur).BlurStrength(16.0).BlurRadius(8.0).Padding(FMargin(0.0)).HAlign(HAlign_Center).VAlign(VAlign_Center) [
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().AutoWidth() [
				SNew(SColorBlock).Color(FLinearColor(0,0,0,0))
			]
			+ SHorizontalBox::Slot().AutoWidth() [
				SNew(SBox).WidthOverride(0.31 * ViewportSize[0]).HeightOverride(0.9 * ViewportSize[1]).HAlign(HAlign_Fill).VAlign(VAlign_Fill) [
					SNew(SOverlay) +
					SOverlay::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill) [
						SNew(SBackgroundBlur).CornerRadius(CornerRadius).BlurStrength(16.0).BlurRadius(8.0).Padding(FMargin(0.0)) [
							SNew(SColorBlock).Color(FLinearColor(COLOR_DARK_PURPLE_R, COLOR_DARK_PURPLE_G, COLOR_DARK_PURPLE_B, 1.0)).CornerRadius(CornerRadius)
						]
					] +
					SOverlay::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill) [
						// SNew(SColorBlock).Color(FLinearColor::Blue)
						SNew(SBorder).BorderImage(&FillBrush)
					]
				]
			]
			+ SHorizontalBox::Slot().AutoWidth() [
				SNew(SColorBlock).Color(FLinearColor(0,0,0,0))
			]
		]
	];


	// ChildSlot
	// .HAlign(HAlign_Center)
	// .VAlign(VAlign_Center)
	// [
	// 	SNew(SScaleBox)
	// 	.Stretch(EStretch::ScaleToFit)  // Or ScaleToFill
	// 	.StretchDirection(EStretchDirection::Both)
	// 	[
	// 		SNew(SBox)
	// 		.WidthOverride(0.3f * 1920.0f)   // Base on common resolution (hacky)
	// 		.HeightOverride(0.8f * 1080.0f)
	// 		[
	// 			SNew(SMyButtonWidget)
	// 		]
	// 	]
	// ];
 }

