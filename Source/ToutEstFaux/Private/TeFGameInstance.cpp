// Fill out your copyright notice in the Description page of Project Settings.


#include "ToutEstFaux/Public/TeFGameInstance.h"
#include "Engine/World.h"
#include "OnlineSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "OnlineSessionSettings.h"
#include "Menu/MenuGameMode.h"
#include "Online/OnlineSessionNames.h"

UTeFGameInstance::UTeFGameInstance()
{
	MySessionName = FName("MySessionName");
}

void UTeFGameInstance::Init()
{
	Super::Init();

	IOnlineSubsystem* SubSystem = IOnlineSubsystem::Get();
	if (SubSystem)
	{
		SessionInterface = SubSystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UTeFGameInstance::OnCreateSessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UTeFGameInstance::OnFindSessionsComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UTeFGameInstance::OnJoinSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UTeFGameInstance::OnDestroySessionComplete);
		}
	}
}

void UTeFGameInstance::OnCreateSessionComplete(FName InSessionName, bool Succeeded)
{
	UE_LOG(LogTemp, Warning, TEXT("OnCreateSessionComplete: %s, Succeeded: %d"), *InSessionName.ToString(), Succeeded);
	if (Succeeded)
	{
		
		GetWorld()->ServerTravel("/Game/Assets/Multijoueur/L_Multi?listen");
	}
}

void UTeFGameInstance::OnFindSessionsComplete(bool Succeeded)
{
	SearchingForServer.Broadcast(false);
	UE_LOG(LogTemp, Warning, TEXT("OnFindSessionsComplete, Succeeded: %d"), Succeeded);
	if (Succeeded && SessionSearch.IsValid())
	{
	
		UE_LOG(LogTemp, Warning, TEXT("SearchResults, Server Count: %d"), SessionSearch->SearchResults.Num());
		int8 ArrayIndex = -1;

		AllServers.Empty();
		
		for (FOnlineSessionSearchResult Result : SessionSearch->SearchResults)
		{
			++ArrayIndex;
			if (!Result.IsValid())
				continue;
			
			FServerInfo Info;
			FString ServerName = "EMPTY SERVER NMAE";
			FString HostName = "EMPTY SERVER NMAE";
			Result.Session.SessionSettings.Get(FName("SERVER_NAME_KEY"), ServerName);
			Result.Session.SessionSettings.Get(FName("SERVER_HOSTNAME_KEY"), HostName);
			Info.ServerName = ServerName;
			Info.MaxPlayers = Result.Session.SessionSettings.NumPublicConnections;
			Info.CurrentPlayers = Info.MaxPlayers - Result.Session.NumOpenPublicConnections;
			Info.ServerArrayIndex = ArrayIndex;
			Info.SetPlayerCount();

			AllServers.Add(Info);
			ServerListDel.Broadcast(Info);
			
	    }

		if(_gameMode)
		{
			_gameMode->ReceiveServers(AllServers);
		}

	}
	
}

void UTeFGameInstance::OnJoinSessionComplete(FName InSessionName, EOnJoinSessionCompleteResult::Type Result)
{
	UE_LOG(LogTemp, Warning, TEXT("OnJoinSessionComplete: %s"), *InSessionName.ToString());

	if (APlayerController* PController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		FString ConnectString = "";
		SessionInterface->GetResolvedConnectString(InSessionName, ConnectString);
		if (ConnectString !="")
			PController->ClientTravel(ConnectString, ETravelType::TRAVEL_Absolute);
		
	}
}

void UTeFGameInstance::CreateServer(FString ServerName, FString HostName)
{
	if (SessionInterface.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Creating Server..."));

		FOnlineSessionSettings SessionSettings;
		SessionSettings.bIsLANMatch = true;  
		SessionSettings.bUsesPresence = true;
		SessionSettings.NumPublicConnections = 5;
		SessionSettings.bShouldAdvertise = true;
		SessionSettings.bAllowJoinInProgress = true;
		SessionSettings.bIsDedicated = false;

		SessionSettings.Set(FName("SERVER_NAME_KEY"), ServerName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
		SessionSettings.Set(FName("SERVER_HOSTNAME_KEY"), HostName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
		SessionInterface->CreateSession(0, MySessionName, SessionSettings);
	}
}

void UTeFGameInstance::FindServer()
{
	SearchingForServer.Broadcast(true);
	if (SessionInterface.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("FindServer"));

		SessionSearch = MakeShareable(new FOnlineSessionSearch());
		SessionSearch->bIsLanQuery = true;
		SessionSearch->MaxSearchResults = 10000;
		SessionSearch->TimeoutInSeconds = 60;
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}

void UTeFGameInstance::JoinServer(int32 ArrayIndex)
{
  FOnlineSessionSearchResult Result = SessionSearch->SearchResults[ArrayIndex];
  if (Result.IsValid())
  {
	  UE_LOG(LogTemp, Warning, TEXT("Joining server at index: %d"), ArrayIndex);
	  SessionInterface->JoinSession(0, MySessionName, Result);
  }
  else
  {
	  UE_LOG(LogTemp, Warning, TEXT("Failed to join server at index: %d"), ArrayIndex);
  }
}
void UTeFGameInstance::LeaveSession()
{
	if (SessionInterface.IsValid())
	{
		
		SessionInterface->DestroySession(MySessionName);
	}

	
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		PlayerController->ClientTravel("Game/Assets/Multijoueur/Menu", ETravelType::TRAVEL_Absolute);
	}

	UE_LOG(LogTemp, Warning, TEXT("Left session and returned to main menu."));
	
}
void UTeFGameInstance::OnDestroySessionComplete(FName SessionName, bool Succeeded)
{
	UE_LOG(LogTemp, Warning, TEXT("OnDestroySessionComplete: %s, Succeeded: %d"), *SessionName.ToString(), Succeeded);
}


void UTeFGameInstance::SetGameMode(AMenuGameMode* GameMode)
{
	_gameMode=GameMode;
}
