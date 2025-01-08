// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/MainGameMode.h"

#include "TeFGameInstance.h"
#include "Global/MainGameState.h"
#include "Global/MyPlayerController.h"
#include "Kismet/GameplayStatics.h"

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	if(AMainGameState* GS = Cast<AMainGameState>(UGameplayStatics::GetGameState(GetWorld())))
	{
		GS->SetGameMode(this);
	}
}



FTeletubbiesMatData AMainGameMode::GetTeletubbiesRightData(ETeletubbies TeletubbiesType)
{
	if(!_listOfTeletubbiesMatData.IsEmpty())
	{
		for(int i=0;i<_listOfTeletubbiesMatData.Num();i++)
		{
			if(_listOfTeletubbiesMatData[i].teletubbies==TeletubbiesType)
			{
				return _listOfTeletubbiesMatData[i];
			}
		}
		return _listOfTeletubbiesMatData[0];
	}

	FTeletubbiesMatData Empthy;
	Empthy.teletubbies= ETeletubbies::E_Po;
	Empthy.bodyMat=nullptr;
	Empthy.earMat=nullptr;
	Empthy.faceMat=nullptr;
	Empthy.goodPoseNumber=0;
	Empthy.teletubbiesAntMesh=nullptr;
	
	return Empthy;
}

void AMainGameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
	
	NewPlayer->UnPossess();
	
	AMyPlayerController* newController = Cast<AMyPlayerController>(NewPlayer);
	if(newController)
	{
		_listOfPlayerController.AddUnique(newController);
		GEngine->AddOnScreenDebugMessage(-1,2,FColor::Yellow,"Nouveau Controller");
	}

	AActor* PlayerStart = FindPlayerStart(NewPlayer,FString::FromInt(_listOfPlayerController.Num()-1));

	if(_characterClass)
	{
		AMyCharacters* NewCharacter = GetWorld()->SpawnActor<AMyCharacters>(_characterClass,PlayerStart->GetTransform());
		_listOfCharacter.AddUnique(NewCharacter);

		NewPlayer->Possess(NewCharacter);
	}
	
}

void AMainGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	AMyPlayerController* outController = Cast<AMyPlayerController>(Exiting);
	if(outController)
	{
		if(outController == _listOfPlayerController[0])
		{
			_listOfPlayerController.Remove(outController);
			if(UTeFGameInstance* GI = Cast<UTeFGameInstance>(GetGameInstance()))
			{
				GI->LeaveSession();
			}
		}
		_listOfPlayerController.Remove(outController);
	}
}







