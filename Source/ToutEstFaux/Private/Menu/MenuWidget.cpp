// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/MenuWidget.h"
#include "Menu/MenuGameMode.h"


void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	VB_Server->SetVisibility(ESlateVisibility::Collapsed);
	VB_Main->SetVisibility(ESlateVisibility::Visible);
	VB_CreateMenu->SetVisibility(ESlateVisibility::Collapsed);
	VB_ServerMenu->SetVisibility(ESlateVisibility::Visible);
	VB_ListOfServer->SetVisibility(ESlateVisibility::Collapsed);
	
	Btn_Quit->OnClicked.AddDynamic(this,&UMenuWidget::QuitTheGame);
	Btn_Play->OnClicked.AddDynamic(this,&UMenuWidget::Play);
	Btn_Back->OnClicked.AddDynamic(this,&UMenuWidget::Back);

	Btn_CreateServer->OnClicked.AddDynamic(this,&UMenuWidget::OpenCreateMenu);
	Btn_Refresh->OnClicked.AddDynamic(this,&UMenuWidget::RefreshServer);
	Btn_Create->OnClicked.AddDynamic(this,&UMenuWidget::CreateSession);
	
}

void UMenuWidget::SetMenuGameMode(AMenuGameMode* GameMode)
{
	_menuGameMode=GameMode;
}

void UMenuWidget::AddServerSlot(UWidget* NewWidget)
{
	if(VB_ListOfServer->GetVisibility() == ESlateVisibility::Collapsed)
	{
		VB_ListOfServer->SetVisibility(ESlateVisibility::Visible);
	}
	
	VB_ListOfServer->AddChild(NewWidget);
}

void UMenuWidget::ShowUnshowRefreshButton(bool bShow)
{
	if(bShow)
	{
		CT_Chargement->SetVisibility(ESlateVisibility::Collapsed);
		Btn_Refresh->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Btn_Refresh->SetVisibility(ESlateVisibility::Collapsed);
		CT_Chargement->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMenuWidget::ChargementScreen_Implementation()
{
}

void UMenuWidget::QuitTheGame()
{
	if(_menuGameMode)
	{
		_menuGameMode->QuitGame();
	}
}

void UMenuWidget::Play()
{
	ChangeMenu();
}

void UMenuWidget::Back()
{
	ChangeMenu();
}

void UMenuWidget::ChangeMenu()
{
	if(VB_Main->GetVisibility()==ESlateVisibility::Visible)
	{
		VB_Main->SetVisibility(ESlateVisibility::Collapsed);
		VB_Server->SetVisibility(ESlateVisibility::Visible);
		RefreshServer();
	}
	else
	{
		
		if(VB_ServerMenu->GetVisibility()==ESlateVisibility::Visible)
		{
			VB_Server->SetVisibility(ESlateVisibility::Collapsed);
			VB_Main->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			VB_CreateMenu->SetVisibility(ESlateVisibility::Collapsed);
			VB_ServerMenu->SetVisibility(ESlateVisibility::Visible);
		}
		
	}
}

void UMenuWidget::OpenCreateMenu()
{
	VB_ServerMenu->SetVisibility(ESlateVisibility::Collapsed);
	VB_CreateMenu->SetVisibility(ESlateVisibility::Visible);
}

void UMenuWidget::RefreshServer()
{
	CleanListOfServers();
	
	ShowUnshowRefreshButton(false);
	if(_menuGameMode)
	{
		_menuGameMode->FindAllServers();
	}
}

void UMenuWidget::CreateSession()
{
	if(_menuGameMode)
	{
		_menuGameMode->CreateServer(ETB_ServerName->GetText().ToString(),ETB_HostName->GetText().ToString());
	}
}

void UMenuWidget::CleanListOfServers()
{
	VB_ListOfServer->ClearChildren();
	VB_ListOfServer->SetVisibility(ESlateVisibility::Collapsed);
}


