// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/MainGameState.h"
#include "Cosplayer/Plinth.h"
#include "Global/Door.h"
#include "Global/MyPlayerController.h"
#include "Kismet/GameplayStatics.h"

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

			if(PhotoFrame)
			{
				GetWorldTimerManager().SetTimer(ChangePhotoTimerHandle,PhotoFrame,&APhotoFrame::ChangeMat,2.f);
			}
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

void AMainGameState::SetPhotoFrame(APhotoFrame* NewPhotoFrame)
{
	PhotoFrame=NewPhotoFrame;
}

void AMainGameState::LeaveGame()
{
	if(GameMode)
	{
		GetWorld()->ServerTravel("/Game/GameMaps/Menu?listen");
	}
}

void AMainGameState::PlayerFinsih(AMyPlayerController* PlayerController,AActor* NewView)
{
	PlayerController->ClearInput();
	if(NewView)
	{
		PlayerController->SetViewTargetWithBlend(NewView,0,VTBlend_Linear);
	}
	PlayerController->bShowMouseCursor=true;
	PlayerController->SetFinish(true);

	PlayerController->End();
	//CheckIfEveryOneFinish();
	
}

void AMainGameState::AddWidget(UWidget_Interaction* NewWidget)
{
	Widgets.AddUnique(NewWidget);
}

void AMainGameState::AddKlaket(AKlakette* NewKlaket)
{
	Klaket=NewKlaket;
}

void AMainGameState::ShowKlakets()
{
	if(Klaket)
	{
		Klaket->Spawn();
	}
	
}


void AMainGameState::CheckIfEveryOneFinish()
{
	if(PCs.IsEmpty())
	{
		SetupListOfPlayerController();
	}

	for (AMyPlayerController* Pc : PCs)
	{
		if(!Pc->GetFinish())
		{
			return;
		}
	}

	End();
	
}

void AMainGameState::SetupListOfPlayerController()
{
	TArray<AActor*>TempList;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(),PcClass,TempList);

	PCs.Empty();
	for (AActor* Actor : TempList)
	{
		if(AMyPlayerController* Pc = Cast<AMyPlayerController>(Actor))
		{
			PCs.AddUnique(Pc);
		}
	}
}

void AMainGameState::End()
{
	for (AMyPlayerController* Pc : PCs)
	{
		Pc->End();
	}
	
	
}

