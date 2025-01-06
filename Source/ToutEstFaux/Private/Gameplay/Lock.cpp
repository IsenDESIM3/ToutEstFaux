// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Lock.h"
#include "Global/MainGameState.h"

ALock::ALock()
{
	LockData.Init({ENumbers::E_0,0},10);
	Combination.Init({ENumbers::E_0,0},4);
	LockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LockMesh"));
	LockMesh->SetupAttachment(RootComponent);
	Ring1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ring1"));
	Ring2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ring2"));
	Ring3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ring3"));
	Ring4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ring4"));
	Meshes.Add(Ring1);
	Meshes.Add(Ring2);
	Meshes.Add(Ring3);
	Meshes.Add(Ring4);
	float posX = -36.0f;
	for (int i=0,j=0; i <= 3; i++)
	{
		Meshes[i]->SetupAttachment(LockMesh);
		Meshes[i]->SetRelativeLocation(FVector(posX,0,-30));
		posX += 24.0f;
	}
	
	/*Ring1->OnClicked.AddDynamic(this,&ALock::Click);
	Ring2->OnClicked.AddDynamic(this,&ALock::Click);
	Ring3->OnClicked.AddDynamic(this,&ALock::Click);
	Ring4->OnClicked.AddDynamic(this,&ALock::Click);*/
	
}

void ALock::Click(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	// todo: write here the equivalent of the bp with lines above the function
	
}

void ALock::Release(FVector newpos, FRotator newrot)
{
	!bUnlock ? Super::Release(_initialPos, _initialRot) : Super::Release(newpos, newrot);
}

void ALock::ChangeMat(UMaterialInstance* NewMat)
{
	Ring1->SetMaterial(0,NewMat);
	Ring2->SetMaterial(0,NewMat);
	Ring3->SetMaterial(0,NewMat);
	Ring4->SetMaterial(0,NewMat);
}


void ALock::BeginPlay()
{
	Super::BeginPlay();
	Meshes[0]=(Ring1);
	Meshes[1]=(Ring2);
	Meshes[2]=(Ring3);
	Meshes[3]=(Ring4);
	float vRot = 0.0f;
	for (int i = 0; i <=4;i++)
	{
		LockData[i].rot =vRot;
		vRot+=36.0f;
	}
	vRot = -180.0f;
	for (int i = 5; i <=9;i++)
	{
		LockData[i].rot =vRot;
		vRot+=36.0f;
	}
	GetValueToRotation();
		
	_initialPos = GetActorLocation();
	_initialRot = GetActorRotation();
	
}

void ALock::GetValueToRotation()
{
	for (int i=0; i <= 3; i++)
	{
		for (int j=0; j <= 9; j++)
		{
			if (Combination[i].numbers==LockData[j].numbers)
			{
				Combination[i].rot=LockData[j].rot;
			}
		}
	}
}

void ALock::CheckRotation()
{
	for(int i=0,j=0; i <= 3; i++)
	{
		float rot = Meshes[i]->GetRelativeRotation().Roll;
		if(Combination[i].rot -1 >= rot  || Combination[i].rot +1 <= rot)
		{
			return;
		}
	}
	bUnlock = true;

	if(AMainGameState* GS = Cast<AMainGameState>(GetWorld()->GetGameState()))
	{
		GS->OpenDoor(MyTypeOfLockDoor);
	}
	
		
}

