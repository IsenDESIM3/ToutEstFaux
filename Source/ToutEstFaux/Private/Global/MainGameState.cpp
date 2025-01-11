// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/MainGameState.h"
#include "Cosplayer/Plinth.h"
#include "Global/Door.h"

AMainGameMode* AMainGameState::GetGameMode()
{
	return  GameMode;
}

void AMainGameState::SetGameMode(AMainGameMode* GM)
{
	GameMode = GM;
}

void AMainGameState::SetPlinths(APlinth* newPlinth)
{
	_listOfAllPlinths.Add(newPlinth);
}

void AMainGameState::CheckIfCosplayerEnigmaFinish()
{
	if(!bIsCosplayerEnigmaFinish)
	{
		if(_listOfAllPlinths.Num()>=4)
		{
			for(APlinth* Collider : _listOfAllPlinths)
			{
				if(!Collider->GetIsComplete())
				{
					return;
				}
			}
			bIsCosplayerEnigmaFinish=true;
			OpenDoor(ETypeOfDoor::E_NormalDoor);
		}
	}
}

void AMainGameState::OpenDoor(ETypeOfDoor Type)
{
	for (ADoor* Door : _Doors)
	{
		if(Door->GetTypeOfDoor()==Type)
		{
			//GEngine->AddOnScreenDebugMessage(-1,2,FColor::Green,"OPEN THE DOOR");
			Door->SetOpenDoor();
		}
	}
}

void AMainGameState::SetDoor(ADoor* newDoor)
{
	_Doors.AddUnique(newDoor);
}

void AMainGameState::LeaveGame()
{
	if(GameMode)
	{
		GetWorld()->ServerTravel("/Game/GameMaps/Menu?listen");
	}
}

