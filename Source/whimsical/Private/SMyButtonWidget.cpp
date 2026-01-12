#include "SMyButtonWidget.h"
#include "Game.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Brushes/SlateColorBrush.h"
#include "Engine/Font.h"


void SMyButtonWidget::Construct(const FArguments& InArgs) {
	Font = Cast<UFont>(FindObject<UObject>(nullptr, TEXT("/Game/Fonts/FSEX302.FSEX302")));
	ButtonText = SNew(STextBlock)
		.Text(FText::FromString(TEXT("Click Me! (0)")))
		.Font(FSlateFontInfo(Font, 15))
	    .ColorAndOpacity(FLinearColor::White);;
	static const FButtonStyle MyButtonStyle = FButtonStyle()
		.SetNormal(FSlateRoundedBoxBrush(FLinearColor(ColorDarkPurple), FLinearColor::Black, 2.0))
		.SetHovered(FSlateRoundedBoxBrush(FLinearColor(0.3, 0.3, 1.0, 1.0), 24.0))
		.SetPressed(FSlateRoundedBoxBrush(FLinearColor(0.1, 0.1, 0.6, 1.0), 24.0))
		.SetNormalPadding(FMargin(20.0, 10.0))
		.SetPressedPadding(FMargin(22.0, 12.0));
	ChildSlot [
		SNew(SBox)
		.Padding(20.0)
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center) [
			SNew(SButton)
			.ButtonStyle(&MyButtonStyle)
			.Text_Lambda([this]() { return ButtonText->GetText(); })
			.OnClicked(FOnClicked::CreateSP(this, &SMyButtonWidget::OnButtonClicked))
			.Content() [
		        ButtonText.ToSharedRef() ] ] ]; }


FReply SMyButtonWidget::OnButtonClicked() {
	ClickCount++;
	ButtonText->SetText(FText::FromString(FString::Printf(TEXT("Clicked %d times!"), ClickCount)));
	UE_LOG(LogTemp, Log, TEXT("Button clicked %d times!"), ClickCount);
	return FReply::Handled(); }

