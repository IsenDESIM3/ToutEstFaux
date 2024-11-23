// Fill out your copyright notice in the Description page of Project Settings.


#include "Cosplayer/Figurine.h"

#include "IndexTypes.h"

// Sets default values
AFigurine::AFigurine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh Component"));
	Mesh->SetupAttachment(RootComponent);

	Ant_Mesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ant Mesh"));
	Ant_Mesh->SetupAttachment(Mesh,FName("Ant_Socket"));
	
	

}

// Called when the game starts or when spawned
void AFigurine::BeginPlay()
{
	Super::BeginPlay();
	SetUpTeletubbies();
	
}

// Called every frame
void AFigurine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFigurine::SetUpTeletubbies()
{
	if(!ListOfTeletubbiesMatData.IsEmpty())
	{
		for(int i=0;i<ListOfTeletubbiesMatData.Num();i++)
		{
			if(ListOfTeletubbiesMatData[i].Teletubbies==MyTeletubbies)
			{
				Mesh->SetMaterial(0,ListOfTeletubbiesMatData[i].BodyMat);
				Mesh->SetMaterial(3,ListOfTeletubbiesMatData[i].FaceMat);
				Mesh->SetMaterial(4,ListOfTeletubbiesMatData[i].EarMat);
				Ant_Mesh->SetStaticMesh(ListOfTeletubbiesMatData[i].Teletubbies_Ant_Mesh);
				RightPose=ListOfTeletubbiesMatData[i].GoodPoseNumber;
				break;
			}
		}
	}
	Ant_Mesh->SetMaterial(0,Mesh->GetMaterial(0));
}

void AFigurine::ChangeAnimation()
{
	if(ActualAnimationNumber!=RightPose)
	{
		if(ActualAnimationNumber>0)
		{
			ActualAnimationNumber=0;
			return;
		}
	
		index++;
		if(index>=AllAnimationsPosible.Num())
		{
			index=0;
		}

		ActualAnimationNumber=AllAnimationsPosible[index];
	}
}



int AFigurine::GetAnimationNumberToPlay()
{
	return ActualAnimationNumber!=-1?ActualAnimationNumber:0;
}


