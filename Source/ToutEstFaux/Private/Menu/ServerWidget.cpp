// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/ServerWidget.h"

#include "Menu/MenuGameMode.h"

void UServerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Btn_Join->OnClicked.AddDynamic(this,&UServerWidget::JoinSession);
}

void UServerWidget::SetUpInfo()
{
	Txt_ServerName->SetText(FText::FromString(_myInfo.ServerName));
}

void UServerWidget::SetServerInfo(FServerInfo Info)
{
	_myInfo = Info;
	SetUpInfo();
}

void UServerWidget::SetGameMode(AMenuGameMode* GameMode)
{
	_gameMode= GameMode;
}

void UServerWidget::JoinSession()
{
	if(_gameMode)
	{
		_gameMode->JoinServer(_myInfo.ServerArrayIndex);
	}
}
