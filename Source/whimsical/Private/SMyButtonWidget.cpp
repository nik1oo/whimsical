#include "SMyButtonWidget.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"


void SMyButtonWidget::Construct(const FArguments& InArgs) {
	ButtonText = SNew(STextBlock)
		.Text(FText::FromString(TEXT("Click Me! (0)")));
	static const FButtonStyle MyButtonStyle = FButtonStyle()
		.SetNormal(FSlateRoundedBoxBrush(FLinearColor(0.2f, 0.2f, 0.8f, 1.0f), 12.0f))
		.SetHovered(FSlateRoundedBoxBrush(FLinearColor(0.3f, 0.3f, 1.0f, 1.0f), 12.0f))
		.SetPressed(FSlateRoundedBoxBrush(FLinearColor(0.1f, 0.1f, 0.6f, 1.0f), 12.0f))
		.SetNormalPadding(FMargin(20.0f, 10.0f))
		.SetPressedPadding(FMargin(22.0f, 12.0f));
	ChildSlot [
		SNew(SBox)
		.Padding(20.0f)
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center) [
			SNew(SButton)
			.ButtonStyle(&MyButtonStyle)
			.Text_Lambda([this]() { return ButtonText->GetText(); })
			.OnClicked(FOnClicked::CreateSP(this, &SMyButtonWidget::OnButtonClicked)) ] ]; }


FReply SMyButtonWidget::OnButtonClicked() {
	ClickCount++;
	ButtonText->SetText(FText::FromString(FString::Printf(TEXT("Clicked %d times!"), ClickCount)));
	UE_LOG(LogTemp, Log, TEXT("Button clicked %d times!"), ClickCount);
	return FReply::Handled(); }

