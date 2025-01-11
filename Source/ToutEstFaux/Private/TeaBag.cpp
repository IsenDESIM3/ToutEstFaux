// Fill out your copyright notice in the Description page of Project Settings.


#include "TeaBag.h"

	ATeaBag::ATeaBag()
	{
		TeaBagMesh = CreateDefaultSubobject<UStaticMeshComponent>("TeaBagMesh");
		TeaBagMesh->SetupAttachment(GetRootComponent());
		TeaBagMesh->SetRelativeLocation(FVector(0, 0, 0));
		TeaBagMesh->SetRelativeScale3D(FVector(1.5, 1.5, 1.5));

	}

void ATeaBag::BeginPlay()
{
	Super::BeginPlay();
		
		BoxPos = GetActorLocation();
}


void ATeaBag::Release(FVector newpos, FRotator newrot)
{
	Super::Release(newpos, newrot);
}

bool ATeaBag::GetIfINeedToBeDestroy()
{
	return true;
}

AActor* ATeaBag::GetItemTarget()
{
	return TeaCup;
}

FVector ATeaBag::GetReleasePos()
{
	return BoxPos;
}
