// Fill out your copyright notice in the Description page of Project Settings.


#include "Cosplayer/Figurine.h"

#include "Kismet/GameplayStatics.h"


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
	
	_mainGameMode = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if(_mainGameMode)
	{
		SetUpTeletubbies();
	}
	
}

// Called every frame
void AFigurine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFigurine::SetUpTeletubbies()
{
	FTeletubbiesMatData Data = _mainGameMode->GetTeletubbiesRightData(_myTeletubbies);
	
	mesh->SetMaterial(0,Data.bodyMat);
	mesh->SetMaterial(3,Data.faceMat);
	mesh->SetMaterial(4,Data.earMat);
	antMesh->SetStaticMesh(Data.teletubbiesAntMesh);
	_rightPose=Data.goodPoseNumber;
	antMesh->SetMaterial(0,mesh->GetMaterial(0));
}

void AFigurine::ChangeAnimation()
{
	if(bCanMove)
	{
		_poseIndex++;
		if(_poseIndex>=6)
		{
			_poseIndex=1;
		}
		bCanMove=false;
		GetWorldTimerManager().SetTimer(TimerBeforeNextMove,this,&AFigurine::ChangeCanMove,0.5f);
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

void AFigurine::clicable()
{
	ChangeAnimation();
}

void AFigurine::ChangeCanMove()
{
	bCanMove=true;
}


