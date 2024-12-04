// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Lock.h"

#include <ThirdParty/ShaderConductor/ShaderConductor/External/DirectXShaderCompiler/include/dxc/DXIL/DxilConstants.h>

ALock::ALock()
{
	Combination.Init(0,4);
	goodRot.Init(0,4);
	rot.Init(0,4);
	locked.Init(false,4);
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
	
}

void ALock::BeginPlay()
{
	Super::BeginPlay();
	GetValueToRotation();
	Meshes[0]=(Ring1);
	Meshes[1]=(Ring2);
	Meshes[2]=(Ring3);
	Meshes[3]=(Ring4);
	CheckRotation(0);
	CheckRotation(1);
	CheckRotation(2);
	CheckRotation(3);
}

void ALock::GetValueToRotation()
{
	for(int i=0,j=0; i <= 3; i++)
	{
		switch (Combination[i])
		{
			case 69:
				goodRot[i]= 0;
				break;
			case 89:
				goodRot[i]=36.0f;
				break;
			case 84:
				goodRot[i]=72.0f;
				break;
			case 87:
				goodRot[i]=108.0f;
				break;
			case 75:
				goodRot[i]=144.0f;
				break;
			case 90:
				goodRot[i]=-180.0f;
				break;
			case 74:
				goodRot[i]=-144.0f;
				break;
			case 72:
				goodRot[i]=-108.0f;
				break;
			case 77:
				goodRot[i]=-72.0f;
				break;
			case 78:
				goodRot[i]=-36.0f;
				break;
		}
	}
}

void ALock::CheckRotation(int index)
{
	for(int i=0,j=0; i <= 3; i++)
	{
		rot[i] = Meshes[i]->GetRelativeRotation().Roll;
	}
		switch(index)	
		{
		case 0:
			if(rot[0]==goodRot[0] || goodRot[0]==0){ locked[0]=true;}
			else locked[0]=false;
		case 1:
			if(rot[1]==goodRot[1] || goodRot[1]==0){ locked[1]=true;}
			else locked[1]=false;
		case 2:
			if(rot[2]==goodRot[2] || goodRot[2]==0){ locked[2]=true;}
			else{ locked[2]=false;}
		case 3:
			if(rot[3]==goodRot[3] || goodRot[3]==0){ locked[3]=true;}
			else locked[3]=false;
		}
	
	if(locked[0] == true && locked[1] == true && locked[2] == true && locked[3] == true)
	{
		bUnlock = true;
		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Green,"Unlocked");
	}
	else GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,"Locked");
}

