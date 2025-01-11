// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Widget_Interaction.generated.h"

class AMyPlayerController;
/**
 * 
 */
UCLASS()
class TOUTESTFAUX_API UWidget_Interaction : public UUserWidget
{
	GENERATED_BODY()

public:

	void ChangeView(bool bGameView);

	void SetPlayerController(AMyPlayerController* NewController);

	UFUNCTION(BlueprintNativeEvent)
	void ChargementScreen();

	UFUNCTION(BlueprintNativeEvent)
	void Credit();

	void ShowWaitUi();
	
protected:
	UPROPERTY(meta=(BindWidget))
	UHorizontalBox* HB_Game;

	UPROPERTY(meta=(BindWidget))
	UHorizontalBox* HB_Menu;

	UPROPERTY(meta=(BindWidget))
	UHorizontalBox* HB_End;

	UPROPERTY(meta=(BindWidget))
	UButton* Btn_Play;

	UPROPERTY(meta=(BindWidget))
	UButton* Btn_Options;

	UPROPERTY(meta=(BindWidget))
	UButton* Btn_Leave;

	UPROPERTY(meta=(BindWidget))
	UButton* Btn_Quit;

private:

	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void Play();

	UFUNCTION()
	void Option();

	UFUNCTION()
	void Leave();

	UPROPERTY()
	AMyPlayerController* _MyController=nullptr;
	
	
};
