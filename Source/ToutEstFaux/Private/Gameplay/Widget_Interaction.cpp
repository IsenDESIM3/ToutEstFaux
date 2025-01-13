// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Widget_Interaction.h"

#include "TeFGameInstance.h"
#include "Global/MainGameMode.h"
#include "Global/MyPlayerController.h"
#include "Kismet/GameplayStatics.h"

void UWidget_Interaction::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_Play->OnClicked.AddDynamic(this,&UWidget_Interaction::Play);
	Btn_Options->OnClicked.AddDynamic(this,&UWidget_Interaction::Option);
	Btn_Leave->OnClicked.AddDynamic(this,&UWidget_Interaction::Leave);
	Btn_Quit->OnClicked.AddDynamic(this,&UWidget_Interaction::Leave);
	
}

void UWidget_Interaction::ChangeView(bool bGameView)
{
	if(bGameView)
	{
		HB_Game->SetVisibility(ESlateVisibility::Visible);
		HB_Menu->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		HB_Menu->SetVisibility(ESlateVisibility::Visible);
		HB_Game->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UWidget_Interaction::SetPlayerController(AMyPlayerController* NewController)
{
	_MyController=NewController;
}

void UWidget_Interaction::ChargementScreen_Implementation()
{
}


void UWidget_Interaction::Play()
{
	ChangeView(true);
	if(_MyController)
	{
		_MyController->ChangeMenuMode(false);
	}
}

void UWidget_Interaction::Option()
{
	if(GrubSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(),GrubSound,3);
	}
}

void UWidget_Interaction::Leave()
{
	ChargementScreen();
	
	//GetWorld()->ServerTravel("/Game/GameMaps/L_Menu?listen");
	
	UTeFGameInstance* _gameInstance= Cast<UTeFGameInstance>(GetGameInstance());
	if(_gameInstance)
	{
		_gameInstance->LeaveSession(true);
	}
	
}

void UWidget_Interaction::Credit_Implementation()
{
}

void UWidget_Interaction::ShowWaitUi()
{
	HB_End->SetVisibility(ESlateVisibility::Visible);
	HB_Game->SetVisibility(ESlateVisibility::Collapsed);
	HB_Menu->SetVisibility(ESlateVisibility::Collapsed);
}
