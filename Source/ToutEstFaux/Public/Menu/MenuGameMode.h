// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuPlayerController.h"
#include "MenuWidget.h"
#include "ServerWidget.h"
#include "TeFGameInstance.h"
#include "GameFramework/GameModeBase.h"
#include "MenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOUTESTFAUX_API AMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void OnPostLogin(AController* NewPlayer) override;
	
	void CreateServer(FString ServerName, FString HostName);

	void JoinServer(int ServerIndex);

	void FindAllServers();
	void ReceiveServers(TArray<FServerInfo> AllServers);

	void QuitGame();

private:
	UPROPERTY()
	AMenuPlayerController* _playerController=nullptr;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMenuWidget> _menuWidgetClass=nullptr;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UServerWidget> _serverSlotClass=nullptr;

	UPROPERTY()
	UMenuWidget* _menuWidget;

	UPROPERTY()
	UTeFGameInstance* _gameInstance=nullptr;
};
