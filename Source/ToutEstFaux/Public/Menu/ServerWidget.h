// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TeFGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "ServerWidget.generated.h"

class AMenuGameMode;
/**
 * 
 */
UCLASS()
class TOUTESTFAUX_API UServerWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	UButton* Btn_Join;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Txt_ServerName;

	void SetUpInfo();

	void SetServerInfo(FServerInfo Info);

	void SetGameMode(AMenuGameMode* GameMode);

private:
	FServerInfo _myInfo;
	
	UPROPERTY()
	AMenuGameMode* _gameMode=nullptr;

	UFUNCTION()
	void JoinSession();
};
