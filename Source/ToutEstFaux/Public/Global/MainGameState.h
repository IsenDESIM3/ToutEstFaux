// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MainGameMode.h"
#include "Cosplayer/PhotoFrame.h"
#include "MainGameState.generated.h"

/**
 * 
 */
UCLASS()
class TOUTESTFAUX_API AMainGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	AMainGameMode* GetGameMode();
	void SetGameMode(AMainGameMode* GM);

	//Cosplayer Enigma
	void SetPlinths(APlinth* newPlinth);
	void CheckIfCosplayerEnigmaFinish();
	
	void OpenDoor(ETypeOfDoor Type);
	void SetDoor(ADoor* newDoor);

	void SetPhotoFrame(APhotoFrame* NewPhotoFrame);

	void LeaveGame();

	void PlayerFinsih(AMyPlayerController* PlayerController,AActor* NewView);

	void AddWidget(UWidget_Interaction* NewWidget);
	
	
private :
	UPROPERTY()
	AMainGameMode* GameMode;

	//Cosplayer Enigma
	TArray<APlinth*> _listOfAllPlinths{};
	bool bIsCosplayerEnigmaFinish=false;

	UPROPERTY()
	TArray<ADoor*> _Doors{};

	UPROPERTY()
	APhotoFrame* PhotoFrame;

	FTimerHandle ChangePhotoTimerHandle;

	void CheckIfEveryOneFinish();
	void SetupListOfPlayerController();

	TArray<AMyPlayerController*> PCs;

	UPROPERTY(EditDefaultsOnly,meta=(AllowPrivateAccess))
	TSubclassOf<AMyPlayerController>PcClass;

	UPROPERTY()
	TArray<UWidget_Interaction*> Widgets{};

	void End();
	
};
