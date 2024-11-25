// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/MenuGameMode.h"

#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void AMenuGameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	_playerController=Cast<AMenuPlayerController>(NewPlayer);
	if(_playerController && _menuWidgetClass)
	{
		_menuWidget=CreateWidget<UMenuWidget>(_playerController,_menuWidgetClass);
		if(_menuWidget)
		{
			_menuWidget->AddToViewport(0);
			_menuWidget->SetMenuGameMode(this);
		}
	}

	_gameInstance= Cast<UTeFGameInstance>(GetGameInstance());
	if(_gameInstance)
	{
		_gameInstance->SetGameMode(this);
	}
}

void AMenuGameMode::CreateServer(FString ServerName, FString HostName)
{
	if(_gameInstance)
	{
		if(ServerName == "")
		{
			ServerName = "Pas de Nom";
		}
		_gameInstance->CreateServer(ServerName,HostName);
	}
}

void AMenuGameMode::JoinServer(int ServerIndex)
{
	if(_gameInstance)
	{
		_menuWidget->ChargementScreen();
		_gameInstance->JoinServer(ServerIndex);
	}
}

void AMenuGameMode::FindAllServers()
{
	if(_gameInstance && _playerController)
	{
		_gameInstance->FindServer();
	}
}

void AMenuGameMode::ReceiveServers(TArray<FServerInfo> AllServers)
{
	for(FServerInfo InfoFind : AllServers)
	{
		UServerWidget* ServerSlot = CreateWidget<UServerWidget>(_playerController,_serverSlotClass);

		if(ServerSlot)
		{
			ServerSlot->SetServerInfo(InfoFind);
			
			ServerSlot->SetGameMode(this);
			_menuWidget->AddServerSlot(ServerSlot);
		}
	}

	_menuWidget->ShowUnshowRefreshButton(true);
}

void AMenuGameMode::QuitGame()
{
	if(_playerController)
	{
		UKismetSystemLibrary::QuitGame(GetWorld(),_playerController,EQuitPreference::Quit,false);
	}
	else
	{
		UKismetSystemLibrary::QuitGame(GetWorld(),
		UGameplayStatics::GetPlayerController(GetWorld(),0),EQuitPreference::Quit,false);
	}
	
}
