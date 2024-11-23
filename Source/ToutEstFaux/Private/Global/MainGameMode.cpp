// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/MainGameMode.h"

#include "Cosplayer/Plinth.h"
#include "Global/MyPlayerController.h"

void AMainGameMode::SetPlinths(APlinth* newPlinth)
{
	_listOfAllPlinths.AddUnique(newPlinth);
}

void AMainGameMode::CheckIfCosplayerEnigmaFinish()
{
	if(!bIsCosplayerEnigmaFinish)
	{
		if(_listOfAllPlinths.Num()>=4)
		{
			for(int i=0; i<_listOfAllPlinths.Num();i++)
			{
				if(!_listOfAllPlinths[i]->GetIsComplete())
				{
					return;
				}
			}
			bIsCosplayerEnigmaFinish=true;
			GEngine->AddOnScreenDebugMessage(-1,10,FColor::Green, "Cosplayer Enigma Finish");
		}
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
	
	AMyPlayerController* newController = Cast<AMyPlayerController>(NewPlayer);
	if(newController)
	{
		_listOfPlayerController.AddUnique(newController);
	}
}

void AMainGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	AMyPlayerController* outController = Cast<AMyPlayerController>(Exiting);
	if(outController)
	{
		_listOfPlayerController.Remove(outController);
	}
}
