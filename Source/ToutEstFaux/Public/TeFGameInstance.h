// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "TeFGameInstance.generated.h"


class AMenuGameMode;

USTRUCT(BlueprintType)
struct  FServerInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString ServerName;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString PlayerCountStr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int32 CurrentPlayers;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int32 MaxPlayers;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int32 ServerArrayIndex;

	void SetPlayerCount()
	{
	PlayerCountStr = FString(FString::FromInt(CurrentPlayers) + "/" + FString::FromInt(MaxPlayers));
	}


};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FServerDel, FServerInfo, ServerListDel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FServerSearchingDel, bool, SearchingForServer);
/**
 *
 */
UCLASS()
class TOUTESTFAUX_API UTeFGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UTeFGameInstance();

	UFUNCTION(BlueprintCallable)
	void CreateServer(FString ServerName, FString HostName);

	UFUNCTION(BlueprintCallable)
	void FindServer();
	UFUNCTION(BlueprintCallable)
	void JoinServer(int32 ArrayIndex);
	UFUNCTION(BlueprintCallable)
	void LeaveSession();

	void SetGameMode(AMenuGameMode* GameMode);


protected:
	
	FName MySessionName;

	UPROPERTY(BlueprintAssignable)
	FServerDel ServerListDel;

	UPROPERTY(BlueprintAssignable)
	FServerSearchingDel SearchingForServer;

	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	virtual void Init() override;
	virtual void OnCreateSessionComplete(FName SessionName, bool Succeeded);
	virtual void OnFindSessionsComplete(bool Succeeded);
	virtual void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	virtual void OnDestroySessionComplete(FName SessionName, bool Succeeded);
	
	
private:
//	FName SessionName = FName("MySessionName");

	UPROPERTY()
	TArray<FServerInfo> AllServers{};

	UPROPERTY()
	AMenuGameMode* _gameMode=nullptr;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess))
	FString _mapName = "L_Game";
};

