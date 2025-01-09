// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "TeFGameInstance.generated.h"


class IOnlineSubsystem;
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

};

/**
 *
 */
UCLASS()
class TOUTESTFAUX_API UTeFGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UTeFGameInstance();
	
UFUNCTION(Blueprintable)
	void CreateServer(FString ServerName, FString HostName);

	UFUNCTION(Blueprintable,BlueprintCallable,Category="Session")
	void FindServer();
	
	//UFUNCTION(Blueprintable)
	void JoinServer(int32 ArrayIndex);

	UFUNCTION(Blueprintable,BlueprintCallable,Category="Session")
	void LeaveSession();

	void SetGameMode(AMenuGameMode* GameMode);

protected:
	IOnlineSubsystem* SubSystem;
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	
	//Delegates
	virtual void Init() override;
	virtual void OnCreateSessionComplete(FName ServerName, bool bWasSuccess);
	virtual void OnFindSessionsComplete(bool bWasSuccess);
	virtual void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	virtual void OnDestroySessionComplete(FName NameSession, bool bWasSuccessful);

private:
	FName MySessionName;
	
	FName SessionName = FName("MySessionName");

	UPROPERTY()
	TArray<FServerInfo> AllServers{};

	UPROPERTY()
	AMenuGameMode* _gameMode=nullptr;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess))
	FString _mapName = "L_Level1";
};

