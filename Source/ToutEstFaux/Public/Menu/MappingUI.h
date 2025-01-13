// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/InputKeySelector.h"
#include "Components/TextBlock.h"
#include "MappingUI.generated.h"

struct FInputActionKeyMapping;
class AMenuGameMode;
/**
 * 
 */
UCLASS()
class TOUTESTFAUX_API UMappingUI : public UUserWidget
{
	GENERATED_BODY()
	virtual void NativeConstruct() override;
	
protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_Commande;

	UPROPERTY(meta=(BindWidget))
	UInputKeySelector* Iks_Input;

public:
	void SetWidget(FText Text, FKey NewKey,AMenuGameMode* GameMode);

private:

	UFUNCTION(BlueprintCallable,Category="Input")
	void InputChange(FKey NewInput);
	
	UPROPERTY()
	AMenuGameMode* _menuGameMode=nullptr;
};
