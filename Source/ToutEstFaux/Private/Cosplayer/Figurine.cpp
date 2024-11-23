// Fill out your copyright notice in the Description page of Project Settings.


#include "Cosplayer/Figurine.h"


// Sets default values
AFigurine::AFigurine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	myPhysicCollider=CreateDefaultSubobject<UBoxComponent>(TEXT("my Physic Colliders"));
	myPhysicCollider->SetupAttachment(RootComponent);
	
	mesh=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh Component"));
	mesh->SetupAttachment(myPhysicCollider);

	antMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ant Mesh"));
	antMesh->SetupAttachment(mesh,FName("Ant_Socket"));
	
	

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
	if(!_listOfTeletubbiesMatData.IsEmpty())
	{
		for(int i=0;i<_listOfTeletubbiesMatData.Num();i++)
		{
			if(_listOfTeletubbiesMatData[i].teletubbies==_myTeletubbies)
			{
				mesh->SetMaterial(0,_listOfTeletubbiesMatData[i].bodyMat);
				mesh->SetMaterial(3,_listOfTeletubbiesMatData[i].faceMat);
				mesh->SetMaterial(4,_listOfTeletubbiesMatData[i].earMat);
				antMesh->SetStaticMesh(_listOfTeletubbiesMatData[i].teletubbiesAntMesh);
				_rightPose=_listOfTeletubbiesMatData[i].goodPoseNumber;
				break;
			}
		}
	}
	antMesh->SetMaterial(0,mesh->GetMaterial(0));
}

void AFigurine::ChangeAnimation()
{
	_poseIndex++;
	if(_poseIndex>=6)
	{
		_poseIndex=1;
	}

}



int AFigurine::GetAnimationNumberToPlay()
{
	return _poseIndex;
}

ETeletubbies AFigurine::GetMyTeletubbiesType()
{
	return _myTeletubbies;
}


ETeletubbies AFigurine::GetTeletubbiesType()
{
	return _myTeletubbies;
}

bool AFigurine::GetIfFigurineIsInRightPose()
{
	return _rightPose==_poseIndex;
}


